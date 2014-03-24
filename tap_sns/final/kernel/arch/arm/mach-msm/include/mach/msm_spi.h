/* Copyright (c) 2008-2009, 2012-2013 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/*
 * SPI driver for Qualcomm MSM platforms.
 */

/**
 * msm_spi_platform_data: msm spi-controller's configuration data
 *
 * @active_only when set, votes when system active and removes the vote when
 *       system goes idle (optimises for performance). When unset, voting using
 *       runtime pm (optimizes for power).
 * @master_id master id number of the controller's wrapper (BLSP or GSBI).
 *       When zero, clock path voting is disabled.
 */
struct msm_spi_platform_data {
	u32 max_clock_speed;
	bool active_only;
	u32  master_id;
	int (*gpio_config)(void);
	void (*gpio_release)(void);
	int (*dma_config)(void);
	const char *rsl_id;
	u32  pm_lat;
	u32  infinite_mode;
	bool ver_reg_exists;
	bool use_bam;
	u32  bam_consumer_pipe_index;
	u32  bam_producer_pipe_index;
};

/* <<< QEEXO: Deassert wait time control */
extern int spi_qsd_set_deassert_clocks(struct spi_device *spi, int clocks);
/* >>> QEEXO: Deassert wait time control */

/* <<< QEEXO: Cyclic SPI DMA transfers */
/* Start running a cyclic DMA transfer.
txbuf and rxbuf may be NULL, though they should not both be NULL.
This function won't return until stop_cyclic_dma is called.
@bpw Number of bits per word (8, 16 or 32).
@speed_hz Transmission speed, in Hz (approximate)
@auto_cs Automatic CS change between transfers?
@tx_dma Transmission buffer.
@rx_dma Receive buffer.
@len Length of both buffers.
*/
extern int spi_qsd_run_cyclic_dma(struct spi_device *spi, int bpw, int speed_hz, int auto_cs, dma_addr_t tx_dma, dma_addr_t rx_dma, int len);
/* Stop cyclic DMA transfer in progress and deactivate the SPI controller. */
extern int spi_qsd_stop_cyclic_dma(struct spi_device *spi);
/* >>> QEEXO: Cyclic SPI DMA transfers */
