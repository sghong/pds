/* drivers/input/misc/tap_sensor/kx022-spi.c - Kionix accelerometer driver
 *
 * Copyright (C) 2014 Qeexo, Co.
 * Written by Robert Xiao <robert@qeexo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//#define DO_POWERON_TEST
/* Enable the use of the Qualcomm-specific BAM DMA driver
   to read the data at very high speed. */
#define ENABLE_BAM_DMA

#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>

#ifdef ENABLE_BAM_DMA
#include <mach/msm_spi.h>
#include <linux/dma-mapping.h>
#endif

#ifdef CONFIG_OF
#include <linux/of.h>
#endif

#include "kx022.h"

#define DEVNAME "kx022"

MODULE_LICENSE("Dual BSD/GPL");

#define Q_ERROR(fmt, ...) printk(KERN_ALERT DEVNAME ": " fmt "\n", ##__VA_ARGS__)
#define Q_DEBUG(fmt, ...) printk(KERN_DEBUG DEVNAME ": " fmt "\n", ##__VA_ARGS__)

/* Configuration */
/* Fixed precision 24.8 numbers */
#define FIXED_DIVIDE(a,b) (((a) << 8) / (b))

static const struct {
	u32 freq;		/* 24.8 fixed point */
	int osa;
} kx022_freq_table[] = {
	[0] = {FIXED_DIVIDE(50, 64), KX022_ODCNTL_OSA_0_781HZ},
	[1] = {FIXED_DIVIDE(50, 32), KX022_ODCNTL_OSA_1_563HZ},
	[2] = {FIXED_DIVIDE(50, 16), KX022_ODCNTL_OSA_3_125HZ},
	[3] = {FIXED_DIVIDE(50, 8), KX022_ODCNTL_OSA_6_25HZ},
	[4] = {FIXED_DIVIDE(50, 4), KX022_ODCNTL_OSA_12_5HZ},
	[5] = {FIXED_DIVIDE(50, 2), KX022_ODCNTL_OSA_25HZ},
	[6] = {FIXED_DIVIDE(50, 1), KX022_ODCNTL_OSA_50HZ},
	[7] = {FIXED_DIVIDE(100, 1), KX022_ODCNTL_OSA_100HZ},
	[8] = {FIXED_DIVIDE(200, 1), KX022_ODCNTL_OSA_200HZ},
	[9] = {FIXED_DIVIDE(400, 1), KX022_ODCNTL_OSA_400HZ},
	[10] = {FIXED_DIVIDE(800, 1), KX022_ODCNTL_OSA_800HZ},
	[11] = {FIXED_DIVIDE(1600, 1), KX022_ODCNTL_OSA_1600HZ},
	[12] = {FIXED_DIVIDE(25600, 1), KX022_ODCNTL_OSA_25600HZ_0ST},
};
static int kx022_cur_freq = 12;	/* index into freq_table */

static const struct {
	u32 range;
	int gsel;
} kx022_grange_table[] = {
	[0] = {2, KX022_CNTL1_GSEL_2G},
	[1] = {4, KX022_CNTL1_GSEL_4G},
	[2] = {8, KX022_CNTL1_GSEL_8G},
};
static int kx022_cur_grange = 0;	/* index into grange_table */

static bool kx022_powered = false;
static bool kx022_suspended = false;

static int kx022_poweron(void);
static int kx022_poweroff(void);

/* SPI */
static struct spi_device *kx022_spi;

static int kx022_read_byte(u8 reg) {
	if (!kx022_powered) {
		Q_ERROR("power is off: refusing to perform SPI transaction");
		return -ESHUTDOWN;
	}

	return spi_w8r8(kx022_spi, reg | 0x80);
}

/* Read a continuous block of registers starting at startreg. */
static int kx022_read(u8 startreg, void *data, int len) {
	u8 cmd = startreg | 0x80;

	if (!kx022_powered) {
		Q_ERROR("power is off: refusing to perform SPI transaction");
		return -ESHUTDOWN;
	}

	return spi_write_then_read(kx022_spi, &cmd, 1, data, len);
}

static int kx022_write_byte(u8 reg, u8 val) {
	u8 buf[] = { reg, val };

	if (!kx022_powered) {
		Q_ERROR("power is off: refusing to perform SPI transaction");
		return -ESHUTDOWN;
	}

	return spi_write(kx022_spi, buf, 2);
}

static int __devinit kx022_spi_probe(struct spi_device *spi) {
	Q_DEBUG("probe enter");

	kx022_spi = spi;

	return 0;
}

static int __devexit kx022_spi_remove(struct spi_device *spi) {
	return kx022_poweroff();
}

#ifdef CONFIG_PM_SLEEP
static int kx022_spi_suspend(struct device *dev) {
    int ret = 0;
    if(kx022_powered) {
        kx022_suspended = true;
        ret = kx022_poweroff();
    }
    return ret;
}

static int kx022_spi_resume(struct device *dev) {
    int ret = 0;
    if(kx022_suspended) {
        ret = kx022_poweron();
    }
    return ret;
}

static SIMPLE_DEV_PM_OPS(kx022_pm_ops, kx022_spi_suspend, kx022_spi_resume);
#endif

#ifdef CONFIG_OF
static struct of_device_id kx022_table[] = {
    {.compatible = "tap_sensor,knxdev_spi"},
    {},
};
#endif

static struct spi_driver kx022_spi_driver = {
	.driver = {
		.name = "kx022_spi",
		.bus = &spi_bus_type,
#ifdef CONFIG_OF
        .of_match_table = kx022_table,
#endif
		.owner = THIS_MODULE,
#ifdef CONFIG_PM_SLEEP
		.pm	= &kx022_pm_ops,
#endif
	},
	.probe = kx022_spi_probe,
	.remove = __devexit_p(kx022_spi_remove),
};


/* Buffering */
#define READ_BUF_COUNT 8192 /* number of samples */
#define READ_BUF_SIZE (READ_BUF_COUNT*sizeof(s16))
#define LATCH_DATA_COUNT 2048	/* number of samples */
#define LATCH_DATA_SIZE (sizeof(kx022_latch_data))

enum kx022_readmode {
	READMODE_NONE = 0,	/* No buffering: only the userspace /xyz and /raw_xyz are available */
	READMODE_DMA,		/* Fast buffering using DMA to the SPI controller */
};

static enum kx022_readmode kx022_cur_readmode = READMODE_NONE;
static s16 kx022_latch_data[LATCH_DATA_COUNT];
static u32 kx022_read_samplecnt = 0;

#ifdef ENABLE_BAM_DMA
static struct task_struct *kx022_read_thread = NULL;
static s16 *kx022_read_circbuf = NULL;
static int kx022_read_circbuf_idx = 0;

static DEFINE_MUTEX(kx022_read_lock);

static char *kx022_dma_txbuf = NULL;
static char *kx022_dma_rxbuf = NULL;
static int kx022_dma_len = 0;
static dma_addr_t kx022_dma_txdma = DMA_ERROR_CODE;
static dma_addr_t kx022_dma_rxdma = DMA_ERROR_CODE;

static void kx022_read_free_dma(void);

static int kx022_read_alloc_dma(int len) {
    kx022_dma_len = len;

    kx022_dma_txbuf = dma_alloc_coherent(kx022_spi->master->dev.parent, len, &kx022_dma_txdma, GFP_KERNEL);
    if(!kx022_dma_txbuf)
        goto fail;
    kx022_dma_rxbuf = dma_alloc_coherent(kx022_spi->master->dev.parent, len, &kx022_dma_rxdma, GFP_KERNEL);
    if(!kx022_dma_rxbuf)
        goto fail;

    memset(kx022_dma_txbuf, 0x80 | KX022_ZOUTL, len);
    memset(kx022_dma_rxbuf, 0xdd, len);

    return 0;

fail:
    kx022_read_free_dma();
    return -ENOMEM;
}

static void kx022_read_free_dma(void) {
    dma_free_coherent(kx022_spi->master->dev.parent, kx022_dma_len, kx022_dma_txbuf, kx022_dma_txdma);
    dma_free_coherent(kx022_spi->master->dev.parent, kx022_dma_len, kx022_dma_rxbuf, kx022_dma_rxdma);

    kx022_dma_txbuf = NULL;
    kx022_dma_rxbuf = NULL;
    kx022_dma_len = 0;
}

static int kx022_read_thread_dma(void *unused)
{
    int ret;

    /* Deassertion time = 1+SPI_DEASSERT clocks.
    37 clock periods per read ~= 25600Hz sampling rate. */
    spi_qsd_set_deassert_clocks(kx022_spi, 4);

    /* Available clock speeds: 960KHz, 4.8MHz, 9.6MHz, 12MHz, 15MHz, 19.2MHz, 25MHz, 50MHz */
    ret = spi_qsd_run_cyclic_dma(kx022_spi, 32, 960000, 1,
        kx022_dma_txdma, kx022_dma_rxdma, kx022_dma_len);

    /* Wait until we're signalled to exit */
    set_current_state(TASK_INTERRUPTIBLE);
    while (!kthread_should_stop()) {
        schedule();
        set_current_state(TASK_INTERRUPTIBLE);
    }

    return ret;
}

static int kx022_read_start(void)
{
    int ret = 0;

	BUG_ON(kx022_read_thread != NULL);
	BUG_ON(kx022_read_circbuf != NULL);

    mutex_lock(&kx022_read_lock);

	switch (kx022_cur_readmode) {
	case READMODE_NONE:
		break;
	case READMODE_DMA: {
        ret = kx022_read_alloc_dma(READ_BUF_COUNT * 4);
        if (ret < 0)
            break;

		kx022_read_circbuf = kzalloc(READ_BUF_SIZE, GFP_KERNEL);
		if (kx022_read_circbuf == NULL) {
		    ret = -ENOMEM;
		    break;
		}

		kx022_read_thread = kthread_create(kx022_read_thread_dma, NULL, "kx022_read");
		if (IS_ERR(kx022_read_thread)) {
			ret = PTR_ERR(kx022_read_thread);
			kx022_read_thread = NULL;
			break;
		}
		wake_up_process(kx022_read_thread);
		ret = 0;
		break;
	}
	default:
	    ret = -EINVAL;
	    break;
	}

    mutex_unlock(&kx022_read_lock);
	return ret;
}

static void kx022_read_stop(void)
{
    mutex_lock(&kx022_read_lock);

	if (kx022_dma_txbuf)
		spi_qsd_stop_cyclic_dma(kx022_spi);

	if (kx022_read_thread)
		kthread_stop(kx022_read_thread);
	kx022_read_thread = NULL;

	kfree(kx022_read_circbuf);
	kx022_read_circbuf = NULL;

    if (kx022_dma_txbuf)
        kx022_read_free_dma();

    mutex_unlock(&kx022_read_lock);
}

static int kx022_set_readmode(enum kx022_readmode mode)
{
	/* Check mode now so we don't unnecessarily stop the thread. */
	switch (mode) {
	case READMODE_NONE:
	case READMODE_DMA:
		break;
	default:
		return -EINVAL;
	}

	kx022_read_stop();
	kx022_cur_readmode = mode;
	return kx022_read_start();
}

static int kx022_read_latch(void)
{
	int start, end;

    mutex_lock(&kx022_read_lock);

	if (kx022_read_circbuf == NULL) {
        mutex_unlock(&kx022_read_lock);
		return -EHOSTDOWN;
	}

    if (kx022_cur_readmode == READMODE_DMA) {
        int i;
        bool changed;

        /* QUP SPI core endian-reverses blocks of 4 bytes */
        for(i=0; i<READ_BUF_COUNT; i++) {
            if(kx022_dma_rxbuf[i*4 + 1] != 0xbb)
                kx022_read_circbuf[i] = kx022_dma_rxbuf[i*4 + 2] | (kx022_dma_rxbuf[i*4 + 1] << 8);
        }
        memset(kx022_dma_rxbuf, 0xbb, READ_BUF_COUNT * 4);

        changed = false;
        Q_DEBUG("before wait");
        do {
            mutex_unlock(&kx022_read_lock);
            usleep_range(200, 300);
            mutex_lock(&kx022_read_lock);

            if(kx022_read_circbuf == NULL) {
                mutex_unlock(&kx022_read_lock);
                return -EHOSTDOWN;
            }

            for(i=0; i<READ_BUF_COUNT; i++) {
                if(kx022_dma_rxbuf[i*4 + 1] != 0xbb) {
                    kx022_read_circbuf_idx = i;
                    changed = true;
                    break;
                }
            }
        } while(!changed);
        Q_DEBUG("after wait");

        Q_DEBUG("circbuf idx=%d", kx022_read_circbuf_idx);
    }

    end = kx022_read_circbuf_idx;
    start = end - LATCH_DATA_COUNT;
    if (start < 0) {
        memcpy(kx022_latch_data,
               kx022_read_circbuf + READ_BUF_COUNT + start,
               -start * sizeof(s16));
        memcpy(kx022_latch_data - start, kx022_read_circbuf, end * sizeof(s16));
    } else {
        memcpy(kx022_latch_data, kx022_read_circbuf + start,
               LATCH_DATA_COUNT * sizeof(s16));
    }

    mutex_unlock(&kx022_read_lock);

	return 0;
}
#else /* !ENABLE_BAM_DMA */
static int kx022_read_start(void) {return 0;}
static void kx022_read_stop(void) {}
static int kx022_set_readmode(enum kx022_readmode mode) {return 0;}
static int kx022_read_latch(void) {return 0;}
#endif /* ENABLE_BAM_DMA */

/* Test */
#ifdef DO_POWERON_TEST
static void kx022_test(void) {
	const static int TEST_SIZE = 131072;
    char *test_inbuf = kzalloc(TEST_SIZE, GFP_KERNEL);
    char *test_outbuf = kzalloc(TEST_SIZE, GFP_KERNEL);
	int ret;
	int i;

	struct spi_transfer tx = {
			.tx_buf = test_inbuf,
			.rx_buf = test_outbuf,
			.len = TEST_SIZE,
			.bits_per_word = 16,
			.speed_hz = 960000,
			.cs_change = 1,
	};

	struct spi_message m;

	memset(test_inbuf, 0x8F, TEST_SIZE);
	memset(test_outbuf, 0xdd, TEST_SIZE);

    Q_DEBUG("test_inbuf=%p, test_outbuf=%p", test_inbuf, test_outbuf);

	spi_message_init(&m);
	spi_message_add_tail(&tx, &m);

	ret = spi_sync(kx022_spi, &m);
	if(ret < 0) {
		Q_ERROR("%s spi_sync failed: %d", __func__, ret);
		goto done;
	}

	for(i=0; i<64; i++) {
		Q_DEBUG("outbuf[%d] = %02x", i, test_outbuf[i]);
	}
	for(i=64; i>0; i--) {
		int k = TEST_SIZE - i;
		Q_DEBUG("outbuf[%d] = %02x", k, test_outbuf[k]);
	}

done:
    kfree(test_inbuf);
    kfree(test_outbuf);
}

#ifdef ENABLE_BAM_DMA
static void kx022_test_dma(void) {
    const int TEST_SIZE = 8192;

    int ret;
	int i;

    ret = kx022_read_alloc_dma(TEST_SIZE);
    if(ret < 0) {
        Q_ERROR("kx022_read_alloc_dma failed");
        return;
    }

    kx022_read_thread = kthread_create(kx022_read_thread_dma, NULL, "kx022_read");
    if (IS_ERR(kx022_read_thread)) {
        Q_ERROR("kthread_create failed: %ld", PTR_ERR(kx022_read_thread));
        return;
    }
    wake_up_process(kx022_read_thread);

	msleep(1000);

	for(i=0; i<64; i++) {
		Q_DEBUG("outbuf[%d] = %02x", i, kx022_dma_rxbuf[i]);
	}
	for(i=64; i>0; i--) {
		int k = TEST_SIZE - i;
		Q_DEBUG("outbuf[%d] = %02x", k, kx022_dma_rxbuf[k]);
	}

	memset(kx022_dma_rxbuf, 0xbb, TEST_SIZE);

    usleep_range(100, 200);

	for(i=0; i<TEST_SIZE; i++) {
		if(kx022_dma_rxbuf[i] != 0xbb) {
			Q_DEBUG("rxbuf nonzero found at %d", i);
			break;
		}
	}

	spi_qsd_stop_cyclic_dma(kx022_spi);
    kthread_stop(kx022_read_thread);
    kx022_read_thread = NULL;

	kx022_read_free_dma();
}
#endif /* ENABLE_BAM_DMA */
#endif /* DO_POWERON_TEST */

/* Power */
static int kx022_poweron(void) {
	int whoami;
	int ret;

    /* Note: kx022 on vega is permanently powered via VREG_S3A_1P8 */

	/* Wait for poweron */
	usleep_range(10000, 15000);

    kx022_spi->max_speed_hz = 9600000;

	ret = spi_setup(kx022_spi);
	if(ret) {
		Q_ERROR("failed to setup KX022 SPI: ret=%d", ret);
		goto fail;
	}

	/* Wait for SPI controller to settle */
	usleep_range(10000, 15000);

	kx022_powered = true;

    kx022_write_byte(KX022_CNTL2, KX022_CNTL2_SRST);
    while(kx022_read_byte(KX022_CNTL2) & KX022_CNTL2_SRST)
        usleep_range(1000, 1500);

	whoami = kx022_read_byte(KX022_WHO_AM_I);
	if (whoami < 0) {
		Q_ERROR("WHO_AM_I read failed");
		ret = whoami;
		goto fail;
	}

	Q_DEBUG("chip WHO_AM_I: %d", whoami);
	/* put chip in standby mode before writing control regs */
	kx022_write_byte(KX022_CNTL1, 0);
	/* enable interrupt pin */
	kx022_write_byte(KX022_INC1, KX022_INC1_IEN | KX022_INC1_IEA | KX022_INC1_IEL);
	/* enable data ready interrupt on pin 1 */
	kx022_write_byte(KX022_INC4, KX022_INC4_DRDYI);	/* Data Ready Interrupt Enable on Pin 1 */
	/* configure filter & ODR settings */
	kx022_write_byte(KX022_ODCNTL,
			 KX022_ODCNTL_IIR_BYPASS | KX022_ODCNTL_LPRO |
			 kx022_freq_table[kx022_cur_freq].osa);
	/* set data format, sensitivity, and enable data ready interrupt; also enable chip */
	kx022_write_byte(KX022_CNTL1,
			 KX022_CNTL1_PC1 | KX022_CNTL1_RES | KX022_CNTL1_DRDYE |
			 kx022_grange_table[kx022_cur_grange].gsel);

	ret = kx022_read_start();
	if (ret < 0) {
		Q_ERROR("Failed to start read thread");
		goto fail;
	}

#ifdef DO_POWERON_TEST
	/* XXX DEBUG */
	kx022_test();
#ifdef ENABLE_BAM_DMA
    kx022_test_dma();
#endif
#endif

	return 0;
fail:
	kx022_poweroff();
	return ret;
}

static int kx022_poweroff(void) {
	kx022_powered = false;

	kx022_read_stop();

	return 0;
}

/* Userspace interface */
static ssize_t kx022_freq_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	u32 freq = kx022_freq_table[kx022_cur_freq].freq;
	u32 int_part = freq >> 8;
	u32 frac_part = freq & 0xff;

	if (frac_part)
		return sprintf(buf, "%d.%04d\n", int_part,
			       frac_part * 10000 / 256);
	else
		return sprintf(buf, "%d\n", int_part);
}

static int kx022_write_freq(int osa)
{
	int cntl1, pc1;

	Q_DEBUG("Setting OSA to %d", osa);

	if (!kx022_powered) {
		Q_DEBUG
		    ("device offline: will write frequency when chip is started");
		return 0;
	}

	if (kx022_cur_readmode != READMODE_NONE) {
		Q_DEBUG("read thread active; can't set frequency");
		return -EBUSY;
	}

	cntl1 = kx022_read_byte(KX022_CNTL1);
	if (cntl1 < 0)
		return cntl1;	/* error */

	pc1 = cntl1 & KX022_CNTL1_PC1;
	if (pc1)
		kx022_write_byte(KX022_CNTL1, cntl1 & ~pc1);
	kx022_write_byte(KX022_ODCNTL,
			 (kx022_read_byte(KX022_ODCNTL) & ~KX022_ODCNTL_OSA_MASK) | osa);
	if (pc1)
		kx022_write_byte(KX022_CNTL1, cntl1);

	return 0;
}

static ssize_t kx022_freq_store(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t size)
{
	unsigned long newval;
	int res;
	int i;

	res = kstrtoul(buf, 0, &newval);
	if (res < 0)
		return res;

	/* convert to fixed point */
	newval = FIXED_DIVIDE(newval, 1);

	for (i = 0; i < ARRAY_SIZE(kx022_freq_table); i++) {
		if (kx022_freq_table[i].freq + FIXED_DIVIDE(1, 2) >= newval) {
			res = kx022_write_freq(kx022_freq_table[i].osa);
			if (res < 0)
				return res;
			kx022_cur_freq = i;
			return size;
		}
	}
	return -EINVAL;
}

static ssize_t kx022_grange_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", kx022_grange_table[kx022_cur_grange].range);
}

static int kx022_write_grange(int gsel)
{
	int cntl1, pc1;

	Q_DEBUG("Setting GSEL to %d", gsel);

	if (!kx022_powered) {
		Q_DEBUG
		    ("device offline: will write grange when chip is started");
		return 0;
	}

	if (kx022_cur_readmode != READMODE_NONE) {
		Q_DEBUG("read thread active; can't set g range");
		return -EBUSY;
	}

	cntl1 = kx022_read_byte(KX022_CNTL1);
	if (cntl1 < 0)
		return cntl1;	/* error */

	pc1 = cntl1 & KX022_CNTL1_PC1;
	if (pc1)
		kx022_write_byte(KX022_CNTL1, cntl1 & ~pc1);
	kx022_write_byte(KX022_CNTL1, (cntl1 & ~KX022_CNTL1_GSEL_MASK) | gsel);

	return 0;
}

static ssize_t kx022_grange_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t size)
{
	unsigned long newval;
	int res;
	int i;

	res = kstrtoul(buf, 0, &newval);
	if (res < 0)
		return res;

	for (i = 0; i < ARRAY_SIZE(kx022_grange_table); i++) {
		if (kx022_grange_table[i].range >= newval) {
			res = kx022_write_grange(kx022_grange_table[i].gsel);
			if (res < 0)
				return res;
			kx022_cur_grange = i;
			return size;
		}
	}
	return -EINVAL;
}

static ssize_t kx022_pwr_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	return sprintf(buf, "%d\n", kx022_powered);
}

static ssize_t kx022_pwr_store(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t size)
{
	bool newval;
	int res;

	res = strtobool(buf, &newval);
	if (res < 0)
		return res;

	if (newval == kx022_powered)
		return size;

	if (newval) {
		res = kx022_poweron();
		if (res < 0)
			return res;
	} else {
		kx022_poweroff();
	}
	/* poweron/poweroff set kx022_powered */

	return size;
}

static ssize_t kx022_readmode_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", kx022_cur_readmode);
}

static ssize_t kx022_readmode_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t size)
{
	unsigned long newval;
	int res;

	res = kstrtoul(buf, 0, &newval);
	if (res < 0)
		return res;

	res = kx022_set_readmode(newval);
	if (res < 0)
		return res;

	return size;
}

static ssize_t kx022_readsamples_show(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", kx022_read_samplecnt);
}

static ssize_t kx022_latch_store(struct device *dev,
				 struct device_attribute *attr, const char *buf,
				 size_t size)
{
	/* Ignore written value. */
	int ret;

	ret = kx022_read_latch();
	if (ret < 0)
		return ret;

	return size;
}

static ssize_t kx022_xyz_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	s16 data[3];
	ssize_t outlen;
	int i;
	int ret;

	if (kx022_cur_readmode != READMODE_NONE) {
		Q_ERROR("read thread active; can't perform single XYZ read");
		return -EBUSY;
	}

	ret = kx022_read(KX022_XOUTL, data, 6);
	if (ret < 0)
		return ret;

	outlen = 0;
	for (i = 0; i < 3; i++) {
		int val = (s16)le16_to_cpu(data[i]);
		bool sign = val < 0;
		int intpart, fracpart;

		/* Convert value into 17.15 fixed-point float */
		if (sign)
			val = -val;
		val *= kx022_grange_table[kx022_cur_grange].range;
		intpart = val >> 15;
		fracpart = val & 0x7fff;
		ret = sprintf(buf + outlen, "%s%d.%06d%c", sign ? "-" : "",
			      intpart,
			      fracpart * 15625 / 512 /* 1000000 / 32768 */ ,
			      (i == 2) ? '\n' : ' ');
		if (ret < 0)
			return ret;
		outlen += ret;
	}
	return outlen;
}

static ssize_t kx022_raw_xyz_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	s16 data[3];
	s16 x, y, z;
	int ret;

	if (kx022_cur_readmode != READMODE_NONE) {
		Q_ERROR("read thread active; can't perform single XYZ read");
		return -EBUSY;
	}

	ret = kx022_read(KX022_XOUTL, data, 6);
	if (ret < 0)
		return ret;

	x = le16_to_cpu(data[0]);
	y = le16_to_cpu(data[1]);
	z = le16_to_cpu(data[2]);

	return sprintf(buf, "%d %d %d\n", x, y, z);
}

static ssize_t kx022_latchdata_read(struct file *filp, struct kobject *kobj,
				    struct bin_attribute *attr, char *buffer,
				    loff_t pos, size_t size)
{
	if (pos >= LATCH_DATA_SIZE)
		return 0;

	if (pos + size > LATCH_DATA_SIZE)
		size = LATCH_DATA_SIZE - pos;

	memcpy(buffer, ((char *)kx022_latch_data) + pos, size);

	return size;
}

static struct class *qeexo_class;
static struct device *kx022_device;
static DEVICE_ATTR(freq, 0644, kx022_freq_show, kx022_freq_store);
static DEVICE_ATTR(grange, 0644, kx022_grange_show, kx022_grange_store);
static DEVICE_ATTR(pwr, 0644, kx022_pwr_show, kx022_pwr_store);
static DEVICE_ATTR(readmode, 0644, kx022_readmode_show, kx022_readmode_store);
static DEVICE_ATTR(readsamples, 0444, kx022_readsamples_show, NULL);
static DEVICE_ATTR(latch, 0200, NULL, kx022_latch_store);
static DEVICE_ATTR(xyz, 0444, kx022_xyz_show, NULL);
static DEVICE_ATTR(raw_xyz, 0444, kx022_raw_xyz_show, NULL);
static struct device_attribute *dev_attrs[] = {
	&dev_attr_freq,
	&dev_attr_grange,
	&dev_attr_pwr,
	&dev_attr_readmode,
	&dev_attr_readsamples,
	&dev_attr_latch,
	&dev_attr_xyz,
	&dev_attr_raw_xyz,
};

static struct bin_attribute dev_attr_latchdata = {
	.attr = {
		 .name = "latchdata",
		 .mode = 0400,
		 },
	.size = LATCH_DATA_COUNT * sizeof(s16),
	.read = kx022_latchdata_read,
	.write = NULL,
};

static int kx022_create_device_files(struct device *dev)
{
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(dev_attrs); i++) {
		ret = device_create_file(dev, dev_attrs[i]);
		if (ret < 0) {
			Q_ERROR("Failed to create device file %s",
				dev_attrs[i]->attr.name);
			return ret;
		}
	}

	return device_create_bin_file(dev, &dev_attr_latchdata);
}

static void kx022_remove_device_files(struct device *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dev_attrs); i++) {
		device_remove_file(dev, dev_attrs[i]);
	}

	device_remove_bin_file(dev, &dev_attr_latchdata);
}

/* Setup/teardown */
static void kx022_cleanup(int v)
{
	switch (v) {
	case 0:
	case 10:
		spi_unregister_driver(&kx022_spi_driver);
	case 20:
		kx022_poweroff();
	case 25:
		kx022_remove_device_files(kx022_device);
	case 30:
		device_destroy(qeexo_class, 0);
	case 40:
		class_destroy(qeexo_class);
	default:
		break;
	}
	kx022_powered = false;
}

static int __init kx022_init(void)
{
	int ret;

	qeexo_class = class_create(THIS_MODULE, "qeexo");
	if (IS_ERR(qeexo_class)) {
		Q_ERROR("failed to register class");
		kx022_cleanup(50);
		return PTR_ERR(qeexo_class);
	}

	kx022_device = device_create(qeexo_class,
				     /*parent */ NULL, /*devt */ 0, /*drvdata */
				     NULL, DEVNAME);
	if (IS_ERR(kx022_device)) {
		Q_ERROR("failed to register device");
		kx022_cleanup(40);
		return PTR_ERR(qeexo_class);
	}

	ret = kx022_create_device_files(kx022_device);
	if (ret < 0) {
		Q_ERROR("failed to create device files");
		kx022_cleanup(25);
		return ret;
	}

	ret = spi_register_driver(&kx022_spi_driver);
	if (ret < 0) {
		Q_ERROR("spi_register_driver failed");
		kx022_cleanup(20);
		return ret;
	}

	return 0;
}

static void __exit kx022_exit(void)
{
	kx022_cleanup(0);
}

module_init(kx022_init);
module_exit(kx022_exit);
