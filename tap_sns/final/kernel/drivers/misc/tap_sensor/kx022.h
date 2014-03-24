#ifndef _KX022_H
#define _KX022_H

/* Registers */
enum kx022_reg {
	KX022_XHPL = 0x00,	/* R */
	KX022_XHPH = 0x01,	/* R */
	KX022_YHPL = 0x02,	/* R */
	KX022_YHPH = 0x03,	/* R */
	KX022_ZHPL = 0x04,	/* R */
	KX022_ZHPH = 0x05,	/* R */
	KX022_XOUTL = 0x06,	/* R */
	KX022_XOUTH = 0x07,	/* R */
	KX022_YOUTL = 0x08,	/* R */
	KX022_YOUTH = 0x09,	/* R */
	KX022_ZOUTL = 0x0A,	/* R */
	KX022_ZOUTH = 0x0B,	/* R */
	KX022_COTR = 0x0C,	/* R */
	KX022_WHO_AM_I = 0x0F,	/* R/W */
	KX022_TSCP = 0x10,	/* R: Current Tilt Position Register */
	KX022_TSPP = 0x11,	/* R: Previous Tilt Position Register */
	KX022_INS1 = 0x12,	/* R: Triggering Axis for tap/double tap int */
	KX022_INS2 = 0x13,	/* R: Which function caused an int */
	KX022_INS3 = 0x14,	/* R: Which axis and direction of detected motion */
	KX022_STAT = 0x15,	/* R: Status of interrupt */
	KX022_INL = 0x17,	/* R: interrupt release */
	KX022_CNTL1 = 0x18,	/* R/W: Control Reg 1 */
	KX022_CNTL2 = 0x19,	/* R/W: Control Reg 2 */
	KX022_CNTL3 = 0x1A,	/* R/W: Control Reg 3 */
	KX022_ODCNTL = 0x1B,	/* R/W: ODR + Filter Settings */
	KX022_INC1 = 0x1C,	/* R/W: Int Pin 1 */
	KX022_INC2 = 0x1D,	/* R/W: Axis and Direction of Detected Motion */
	KX022_INC3 = 0x1E,	/* R/W: Axis and Direction of tap/double tap */
	KX022_INC4 = 0x1F,	/* R/W ?: Routing functions to Int Pin 1 */
	KX022_INC5 = 0x20,	/* R/W: More Int Pin 1 Settings */
	KX022_INC6 = 0x21,	/* R/W: Routing functions to Int Pin 2 */
	KX022_TILT_TIMER = 0x22,	/* R/W: Count Reg for Tilt Position State Timer (1/ODR delay period) */
	KX022_WUFC = 0x23,	/* R/W: Count Reg for Motion Detection Timer (1/ODR delay period) */
	KX022_TDTRC = 0x24,	/* R/W: Enable/Disable reporting Tap/Double Tap */
	KX022_TDTC = 0x25,	/* R/W: Counter Info for Double Tap Events */
	KX022_TTH = 0x26,	/* R/W: 9-bit Jerk High Threshold for Tap Event */
	KX022_TTL = 0x27,	/* R/W: 7-bit Jerk Low Threshold for Tap Event */
	KX022_FTD = 0x28,	/* R/W: Counter Info for any Tap Event */
	KX022_STD = 0x29,	/* R/W: Counter Info for Double Tap Events */
	KX022_TLT = 0x2A,	/* R/W: Counter Info for Tap Events */
	KX022_TWS = 0x2B,	/* R/W: Counter Info for any Tap Event */
	KX022_ATH = 0x30,	/* R/W: Threshold for Wake-up interrupt */
	KX022_TILT_ANGLE_LL = 0x32,	/* R/W: Low Level Threshold for Tilt Angle Detection */
	KX022_TILT_ANGLE_HL = 0x33,	/* R/W: High Level Threshold for Tilt Angle Detection */
	KX022_HYST_SET = 0x34,	/* R/W: Hysteresis placed between the Screen Rotation States */
	KX022_BUF_CNTL1 = 0x3A,	/* R/W: R/W Control Reg */
	KX022_BUF_CNTL2 = 0x3B,	/* R/W: R/W Control Reg, Sample Buffer Operation */
	KX022_BUF_STATUS_1 = 0x3C,	/* R: Buffer Status */
	KX022_BUF_STATUS_2 = 0x3D,	/* R: Buffer Trigger Function */
	KX022_BUF_CLEAR = 0x3E,	/* W: Clear Buffer Status and Info */
	KX022_BUF_READ = 0x3F,	/* R: Buffer Output */
};

enum kx022_int {
	KX022_INS1_TLE = 0x20,	/* X Negative (X-) Reported */
	KX022_INS1_TRI = 0x10,	/* X Positive (X+) Reported */
	KX022_INS1_TDO = 0x08,	/* Y Negative (Y-) Reported */
	KX022_INS1_TUP = 0x04,	/* Y Positive (Y+) Reported */
	KX022_INS1_TFD = 0x02,	/* Z Negative (Z-) Reported */
	KX022_INS1_TFU = 0x01,	/* Z Positive (Z+) Reported */

	KX022_INS2_BFI = 0x40,	/* Buffer Full Interrupt */
	KX022_INS2_WMI = 0x20,	/* Watermark Interrupt */
	KX022_INS2_DRDY = 0x10,	/* Data Ready */
	KX022_INS2_TDTS_NOTAP = 0x0,	/* No Tap */
	KX022_INS2_TDTS_SNGTAP = 0x04,	/* Single Tap */
	KX022_INS2_TDTS_DBLTAP = 0x08,	/* Double Tap */
	KX022_INS2_TDTS_DNE = 0x0C,	/* Does Not Exist */
	KX022_INS2_WUFS = 0x02,	/* Wake Up */
	KX022_INS2_TPS = 0x01,	/* Tilt Position Status (0=State Not Changed, 1=State Changed) */

	KX022_INS3_XNWU = 0x20,	/* X Negative (X-) Reported */
	KX022_INS3_XPWU = 0x10,	/* X Positive (X+) Reported */
	KX022_INS3_YNWU = 0x08,	/* Y Negative (Y-) Reported */
	KX022_INS3_YPWU = 0x04,	/* Y Positive (Y+) Reported */
	KX022_INS3_ZNWU = 0x02,	/* Z Negative (Z-) Reported */
	KX022_INS3_ZPWU = 0x01,	/* Z Positive (Z+) Reported */

	KX022_STATUS_REG_INT = 0x10,	/* OR'ed interrupt info of all functions */

	KX022_INC1_IEN = 0x20,	/* Interrupt Enable */
	KX022_INC1_IEA = 0x10,	/* Polarity of Interrupt */
	KX022_INC1_IEL = 0x08,	/* Response of Int Pin */
	KX022_INC1_STNULL = 0x04,	/* ST on both carriers for MEMS Characterization (NO IDEA WHAT'S GOING ON HERE) */
	KX022_INC1_STPOL = 0x02,	/* Polarity of ST */
	KX022_INC1_SPI3E = 0x01,	/* 3-Wire SPI interface */

	KX022_INC2_XNWU = 0x20,	/* Wake Up Enable, X Negative (X-) */
	KX022_INC2_XPWU = 0x10,	/* Wake Up Enable, X Positive (X+) */
	KX022_INC2_YNWU = 0x08,	/* Wake Up Enable, Y Negative (Y-) */
	KX022_INC2_YPWU = 0x04,	/* Wake Up Enable, Y Positive (Y+) */
	KX022_INC2_ZNWU = 0x02,	/* Wake Up Enable, Z Negative (Z-) */
	KX022_INC2_ZPWU = 0x01,	/* Wake Up Enable, Z Positive (Z+) */

	KX022_INC3_TLEM = 0x20,	/* Tap/Double Tap Enable, X Negative (X-) */
	KX022_INC3_TRIM = 0x10,	/* Tap/Double Tap Enable, X Positive (X+) */
	KX022_INC3_TDOM = 0x08,	/* Tap/Double Tap Enable, Y Negative (Y-) */
	KX022_INC3_TUPM = 0x04,	/* Tap/Double Tap Enable, Y Positive (Y+) */
	KX022_INC3_TFDM = 0x02,	/* Tap/Double Tap Enable, Z Negative (Z-) */
	KX022_INC3_TFUM = 0x01,	/* Tap/Double Tap Enable, Z Positive (Z+) */

	KX022_INC4_BFI = 0x40,	/* Buffer Full Interrupt */
	KX022_INC4_WMI = 0x20,	/* Watermark Interrupt */
	KX022_INC4_DRDYI = 0x10,	/* Data Ready Interrupt */
	KX022_INC4_TDTI = 0x04,	/* Tap/Double Tap Interrupt */
	KX022_INC4_WUFI = 0x02,	/* Wake Up Interrupt */
	KX022_INC4_TPI = 0x01,	/* Tilt Position Interrupt */

	KX022_INC5_IEN = 0x20,	/* Enable Int Pin 2? */
	KX022_INC5_IEA = 0x10,	/* Polarity of Int Pin 2? */
	KX022_INC5_IEL = 0x08,	/* Response of Int Pin 2? */

	KX022_INC6_BFI = 0x40,	/* Buffer Full Interrupt */
	KX022_INC6_WMI = 0x20,	/* Watermark Interrupt */
	KX022_INC6_DRDYI = 0x10,	/* Data Ready Interrupt */
	KX022_INC6_TDTI = 0x04,	/* Tap/Double Tap Interrupt */
	KX022_INC6_WUFI = 0x02,	/* Wake Up Interrupt */
	KX022_INC6_TPI = 0x01,	/* Tilt Position Interrupt */

	KX022_TDTRC_DTRE = 0x02,	/* 0 = Disable Double Tap Interrupt, 1 = Enable Double Tap Interrupt */
	KX022_TDTRC_STRE = 0x01,	/* 0 = Disable Single Tap Interrupt, 1 = Enable Single Tap Interrupt */
};

enum kx022_cntl {
	KX022_CNTL1_PC1 = 1 << 7,	/* Operating Mode (0 = Stand-By Mode, 1 = Operating Mode) */
	KX022_CNTL1_RES = 1 << 6,	/* Resolution (0 = 8-bit, 1 = 16-bit w/ Bandwidth(Hz) = ODR/2) */
	KX022_CNTL1_DRDYE = 1 << 5,	/* Enables the reporting of Data Ready Interrupt */
	KX022_CNTL1_GSEL_MASK = 3 << 3,	/* sensitivity (°æXg) */
	KX022_CNTL1_GSEL_2G = 0 << 3,
	KX022_CNTL1_GSEL_4G = 1 << 3,
	KX022_CNTL1_GSEL_8G = 2 << 3,
	KX022_CNTL1_TDTE = 1 << 2,	/* Enable Tap Direction Interrupt */
	KX022_CNTL1_WUFE = 1 << 1,	/* Enable Wake Up (Motion Detection) */
	KX022_CNTL1_TPE = 1 << 0,	/* Enable Tap Position Interrupt */

	KX022_CNTL2_SRST = 1 << 7,	/* Initiates Software Reset (RAM reboot routine) */
	KX022_CNTL2_COTC = 1 << 6,	/* Command Test Control */
	KX022_CNTL2_TLEM = 1 << 5,	/* Enable Tilt Axis Int, X Negative (X-) */
	KX022_CNTL2_TRIM = 1 << 4,	/* Enable Tilt Axis Int, X Positive (X+) */
	KX022_CNTL2_TDOM = 1 << 3,	/* Enable Tilt Axis Int, Y Negative (Y-) */
	KX022_CNTL2_TUPM = 1 << 2,	/* Enable Tilt Axis Int, Y Positive (Y+) */
	KX022_CNTL2_TFDM = 1 << 1,	/* Enable Tilt Axis Int, Z Negative (Z-) */
	KX022_CNTL2_TFUM = 1 << 0,	/* Enable Tilt Axis Int, Z Positive (Z+) */

	KX022_CNTL3_OTP_MASK = 3 << 6,	/* Tilt Position ODR (Hz) */
	KX022_CNTL3_OTP_1_6HZ = 0 << 6,
	KX022_CNTL3_OTP_6_3HZ = 1 << 6,
	KX022_CNTL3_OTP_12_5HZ = 2 << 6,
	KX022_CNTL3_OTP_50HZ = 3 << 6,
	KX022_CNTL3_OTDT_MASK = 7 << 3,	/* Directional Tap ODR (Hz) */
	KX022_CNTL3_OTDT_50HZ = 0 << 3,
	KX022_CNTL3_OTDT_100HZ = 1 << 3,
	KX022_CNTL3_OTDT_200HZ = 2 << 3,
	KX022_CNTL3_OTDT_400HZ = 3 << 3,
	KX022_CNTL3_OTDT_12_5HZ = 4 << 3,
	KX022_CNTL3_OTDT_25HZ = 5 << 3,
	KX022_CNTL3_OTDT_800HZ = 6 << 3,
	KX022_CNTL3_OTDT_1600HZ = 7 << 3,
	KX022_CNTL3_OWUF_MASK = 7 << 0,	/* Wake Up ODR (Hz) */
	KX022_CNTL3_OWUF_0_781HZ = 0 << 0,
	KX022_CNTL3_OWUF_1_563HZ = 1 << 0,
	KX022_CNTL3_OWUF_3_125HZ = 2 << 0,
	KX022_CNTL3_OWUF_6_25HZ = 3 << 0,
	KX022_CNTL3_OWUF_12_5HZ = 4 << 0,
	KX022_CNTL3_OWUF_25HZ = 5 << 0,
	KX022_CNTL3_OWUF_50HZ = 6 << 0,
	KX022_CNTL3_OWUF_100HZ = 7 << 0,

	KX022_ODCNTL_IIR_BYPASS = 1 << 7,	/* 0 = Filter Applied, 1 = Filter Bypassed */
	KX022_ODCNTL_LPRO = 1 << 6,	/* 0 = Filter Corner Roll Off Frequency to ODR/9, 1 = Filter Corner Roll Off Frequency to ODR/2 */
	KX022_ODCNTL_OSA_MASK = 0x0F,	/* Accelerometer ODR (Hz) */
	KX022_ODCNTL_OSA_12_5HZ = 0x00,
	KX022_ODCNTL_OSA_25HZ = 0x01,
	KX022_ODCNTL_OSA_50HZ = 0x02,
	KX022_ODCNTL_OSA_100HZ = 0x03,
	KX022_ODCNTL_OSA_200HZ = 0x04,
	KX022_ODCNTL_OSA_400HZ = 0x05,
	KX022_ODCNTL_OSA_800HZ = 0x06,
	KX022_ODCNTL_OSA_1600HZ = 0x07,
	KX022_ODCNTL_OSA_0_781HZ = 0x08,
	KX022_ODCNTL_OSA_1_563HZ = 0x09,
	KX022_ODCNTL_OSA_3_125HZ = 0x0A,
	KX022_ODCNTL_OSA_6_25HZ = 0x0B,
	KX022_ODCNTL_OSA_25600HZ_800ST = 0x0C,	/* Accelerometer ODR, 25,600 Hz, ST = 800 Hz */
	KX022_ODCNTL_OSA_25600HZ_1600ST = 0x0D,	/* Accelerometer ODR, 25,600 Hz, ST = 1600 Hz */
	KX022_ODCNTL_OSA_25600HZ_3200ST = 0x0E,	/* Accelerometer ODR, 25,600 Hz, ST = 3200 Hz */
	KX022_ODCNTL_OSA_25600HZ_0ST = 0x0F,	/* Accelerometer ODR, 25,600 Hz, ST = None */
	KX022_ODCNTL_OSA_25600HZ = 0x0F,	/* Alias for previous value */

	KX022_BUF_CNTL2_BUFE = 1 << 7,	/* Buffer Enable */
	KX022_BUF_CNTL2_BRES = 1 << 6,	/* Buffer Resolution (0 = 8bit, 1 = 16bit) */
	KX022_BUF_CNTL2_BFIE = 1 << 5,	/* Buffer Full Interrupt Enable */
	KX022_BUF_CNTL2_BUFM_MASK = 3 << 0,	/* Buffer mode */
	KX022_BUF_CNTL2_BUFM_FIFO = 0 << 0,	/* FIFO MODE, Only new data when not full */
	KX022_BUF_CNTL2_BUFM_STREAM = 1 << 0,	/* STREAM MODE, Oldest Data discarded */
	KX022_BUF_CNTL2_BUFM_TRIGGER = 2 << 0,	/* TRIGGER MODE, When trigger event collect SMP[6:0] samples */
	KX022_BUF_CNTL2_BUFM_FILO = 3 << 0,	/* FILO MODE, oldest data is discarded, newest sample resturned first */
};

#endif /* _KX022_H */
