


/* -------------------------------------------------------------------- */
/* GPIO, VREG & resolution */
/* -------------------------------------------------------------------- */
#define MAX_NUM_FINGER				10

// Screen resolution
#define SCREEN_RESOLUTION_X					    1080
#define SCREEN_RESOLUTION_SCREEN_Y			1920
#define SCREEN_RESOLUTION_TOUCHKEY_Y		185
#define SCREEN_RESOLUTION_WHOLE_Y			  (SCREEN_RESOLUTION_SCREEN_Y + SCREEN_RESOLUTION_TOUCHKEY_Y)

#define PAN_HAVE_TOUCH_KEY
#ifdef PAN_HAVE_TOUCH_KEY
#define PAN_TOUCH_KEY_COUNT		3

struct pan_touch_key_config {
	struct {
		int center;
		int margin;
		int key;
	}x[PAN_TOUCH_KEY_COUNT];

	struct {
		int center;
		int margin;		
	}y;	
};
#define PAN_1ST_TOUCH_KEY_X				    215
#define PAN_2ND_TOUCH_KEY_X				    540
#define PAN_3RD_TOUCH_KEY_X				    865
#define PAN_TOUCH_KEY_Y					      2050

#define PAN_1ST_TOUCH_KEY_MARGIN_X		50
#define PAN_2ND_TOUCH_KEY_MARGIN_X		125
#define PAN_3RD_TOUCH_KEY_MARGIN_X		50

#define PAN_1ST_TOUCH_KEY_TYPE			  KEY_MENU
#define PAN_2ND_TOUCH_KEY_TYPE			  KEY_HOMEPAGE
#define PAN_3RD_TOUCH_KEY_TYPE			  KEY_BACK

#define PAN_TOUCH_KEY_MARGIN_Y			  50	
#endif

#define MXT_FW21_REFERENCE_MIN		    4160
#define MXT_FW21_REFERENCE_MAX		    10400

// define ITO_TYPE_CHECK

/* -------------------------------------------------------------------- */
/* DEVICE   : mxT768E CONFIGURATION */
/* -------------------------------------------------------------------- */

/* SPT_USERDATA_T38 INSTANCE 0 */
#define T7_IDLEACQINT						        255
#define T7_ACTVACQINT						        255	// free-run
#define T7_ACTV2IDLETO					        50 
#define T7_CFG								          67

/* GEN_ACQUISITIONCONFIG_T8 INSTANCE 0  */
#define T8_CHRGTIME							        66
#define T8_RESERVED_0                   0
#define T8_TCHDRIFT						 	        10
#define T8_DRIFTST						 	        10
#define T8_TCHAUTOCAL						        0
#define T8_SYNC								          0
#define T8_ATCHCALST						        255
#define T8_ATCHCALSTHR                  1
#define T8_ATCHFRCCALTHR         			  0
#define T8_ATCHFRCCALRATIO       			  0
#define T8_RESERVED_1       				    0
#define T8_RESERVED_2      					    0
#define T8_RESERVED_3       				    0


/* [TOUCH_KEYARRAY_T15 INSTANCE 0]    */
#define T15_CTRL							          0
#define T15_XORIGIN							        0
#define T15_YORIGIN							        0
#define T15_XSIZE							          0
#define T15_YSIZE							          0
#define T15_AKSCFG							        0
#define T15_BLEN							          0
#define T15_TCHTHR							        0
#define T15_TCHDI							          0
#define T15_RESERVED_0						      0
#define T15_RESERVED_1						      0 

/*  [SPT_COMMSCONFIG_T18 INSTANCE 0]        */
#define T18_CTRL							          0
#define T18_COMMAND							        0

/* T19*/
#define T19_CTRL							          0
#define T19_REPORTMASK						      0
#define T19_DIR								          0
#define T19_INTPULLUP						        0
#define T19_OUT								          0
#define T19_WAKE							          0

/* [TOUCH_PROXIMITY_T23 INSTANCE 0] */
#define T23_CTRL							          0
#define T23_XORIGIN               		  0
#define T23_YORIGIN               			0
#define T23_XSIZE                 			0
#define T23_YSIZE                 			0
#define T23_RESERVED              			0
#define T23_BLEN                  			0
#define T23_FXDDTHR               			0
#define T23_FXDDI                 			0
#define T23_AVERAGE               			0
#define T23_MVNULLRATE            			0
#define T23_MVDTHR                			0

/* [SPT_SELFTEST_T25 INSTANCE 0] */
#define T25_CTRL							          3
#define T25_CMD								          0
#define T25_SIGLIM_0_UPSIGLIM        		0
#define T25_SIGLIM_0_LOSIGLIM        		0
#define T25_SIGLIM_1_UPSIGLIM        		0
#define T25_SIGLIM_1_LOSIGLIM        		0
#define T25_SIGLIM_2_UPSIGLIM        		30000
#define T25_SIGLIM_2_LOSIGLIM        		0
#define T25_PINDWELLUS						      0
#define T25_SIGRANGELIM_0					      0
#define T25_SIGRANGELIM_1					      0
#define T25_SIGRANGELIM_2					      10000

// GRIPSUPPRESSION_T40
#define T40_CTRL                			  0
#define T40_XLOGRIP             			  0
#define T40_XHIGRIP             			  0
#define T40_YLOGRIP             			  0
#define T40_YHIGRIP							        0

/* PROCI_TOUCHSUPPRESSION_T42 */
#define T42_CTRL							          0	// palm suppression OFF : protect mode //51
#define T42_RESERVED					          0	/* 0 (TCHTHR/4), 1 to 255 */
#define T42_MAXAPPRAREA						      0   /* 0 (40ch), 1 to 255 */
#define T42_MAXTCHAREA						      0   /* 0 (35ch), 1 to 255 */
#define T42_SUPSTRENGTH						      0   /* 0 (128), 1 to 255 */
#define T42_SUPEXTTO						        0	/* 0 (never expires), 1 to 255 (timeout in cycles) */
#define T42_MAXNUMTCHS          			  0	/* 0 to 9 (maximum number of touches minus 1) */
#define T42_SHAPESTRENGTH					      0	/* 0 (10), 1 to 31 */
#define T42_SUPDIST							        0	// 7
#define T42_DISTHYST						        0

/* SPT_CTECONFIG_T46  */
// TODO:ADDED
#define T46_CTRL							          4	/*Reserved */
#define T46_RESERVED					          0	/*0: 16X14Y, 1: 17X13Y, 2: 18X12Y, 3: 19X11Y, 4: 20X10Y, 5: 21X15Y, 6: 22X8Y, */
#define T46_IDLESYNCSPERX				      	8
#define T46_ACTVSYNCSPERX					      16
#define T46_ADCSPERSYNC						      0 
#define T46_PULSESPERADC					      0   /*0:1  1:2   2:3   3:4 pulses */
#define T46_XSLEW							          4   // 1   *0:500nsec,  1:350nsec */
#define T46_SYNCDELAY						        0		
#define T46_XVOLTAGE						        1	//TODO: not exists in doc.	

/* PROCI_STYLUS_T47 */              
//TODO: added
#define T47_CTRL							          9
#define T47_CONTMIN							        25
#define T47_CONTMAX							        40
#define T47_STABILITY						        255
#define T47_MAXTCHAREA          			  2
#define T47_AMPLTHR							        25
#define T47_STYSHAPE						        10
#define T47_HOVERSUP						        140
#define T47_CONFTHR							        0
#define T47_SYNCSPERX						        24
#define T47_XPOSADJ							        32
#define T47_YPOSADJ							        32
#define T47_CFG								          0 //15
#define T47_RESERVED0                   0
#define T47_RESERVED1						        0
#define T47_RESERVED2 						      0
#define T47_RESERVED3						        0
#define T47_RESERVED4						        0
#define T47_RESERVED5 					        0
#define T47_RESERVED6                   0
#define T47_SUPSTYTO                    1
#define T47_MAXNUMSTY                   1
#define T47_XEDGECTRL						        174
#define T47_XEDGEDIST						        23
#define T47_YEDGECTRL						        191
#define T47_YEDGEDIST						        34


//PROCI_ADDAPTIVETHRESHOLD_T55
#define T55_CTRL							          1
#define T55_TARGETTHR						        0
#define T55_THRADJLIM						        0
#define T55_RESETSTEPTIME					      0
#define T55_FORCECHGDIST					      0
#define T55_FORCECHGTIME					      0
#define T55_LOWESTTHR						        0

// PROCI_SHIELDLESS_T56 
// TODO: added 24 25~ 31
#define T56_CTRL							          3 //0
#define T56_RESERVED							      0
#define T56_OPTINT						          1 //ymlee
#define T56_INTTIME							        61
#define T56_INTDELAY0						        5
#define T56_INTDELAY1						        5
#define T56_INTDELAY2						        5
#define T56_INTDELAY3						        5
#define T56_INTDELAY4						        5
#define T56_INTDELAY5						        5
#define T56_INTDELAY6						        5
#define T56_INTDELAY7						        5
#define T56_INTDELAY8						        5
#define T56_INTDELAY9						        5
#define T56_INTDELAY10						      5
#define T56_INTDELAY11						      5
#define T56_INTDELAY12						      5
#define T56_INTDELAY13						      5
#define T56_INTDELAY14						      5
#define T56_INTDELAY15						      5
#define T56_INTDELAY16						      5
#define T56_INTDELAY17						      5
#define T56_INTDELAY18						      5
#define T56_INTDELAY19						      5
#define T56_INTDELAY20						      5
#define T56_INTDELAY21						      5	  	
#define T56_INTDELAY22						      5
#define T56_INTDELAY23						      5
#define T56_INTDELAY24						      5
#define T56_INTDELAY25						      5
#define T56_INTDELAY26						      5
#define T56_INTDELAY27						      5
#define T56_INTDELAY28						      5
#define T56_INTDELAY29						      5
#define T56_MULTICUTGC						      0
#define T56_GCLIMIT							        0

// SPT_TIMER_T61 
#define T61_CTRL							          0
#define T61_CMD								          0
#define T61_MODE							          0
#define T61_PERIOD							        0

//PROCI_LENSBENDING_T65
#define T65_CTRL							          3
#define T65_GRADTHR							        6
#define T65_YLONOISEMUL						      0
#define T65_YLONOISEDIV						      0
#define T65_YHINOISEMUL						      0
#define T65_YHINOISEDIV						      0
#define T65_LPFILTCOEF						      0
#define T65_FORCESCALE						      0
#define T65_FCALFAILTHR						      0
#define T65_FORCETHR						        0
#define T65_FORCETHRHYST					      0
#define T65_FORCEDI							        0
#define T65_FORCEHYST						        0

/* SPT_GOLDENREFERENCES_T66 */
#define T66_CTRL							          0
#define T66_FCALFAILTHR						      20
#define T66_FCALDRIFTCNT					      255
#define T66_FCALDRIFTCOEF					      0
#define T66_FCALDRIFTLIM					      0

/*  PROCI_PALMGESTUREPROCESSOR_T69  */
#define T69_CTRL							          0
#define T69_LONGDIMTHR						      0
#define T69_SHORTDIMTHR						      0
#define T69_LONGDIMHYST						      0
#define T69_SHORTDIMHYST					      0
#define T69_MOVTHR							        0
#define T69_MOVTHRTO						        0
#define T69_AREATHR							        0
#define T69_AREATHRTO						        0

/* SPT_DYNAMICCONFIGURATIONCONTROLLER_T70 */
#define T70_CTRL							          0
#define T70_EVENT							          0
#define T70_OBJTYPE							        0
#define T70_RESERVED						        0
#define T70_OBJINST							        0
#define T70_DSTOFFSET						        0
#define T70_SRCOFFSET						        0
#define T70_LENGTH							        0

/* SPT_DYNAMICCONFIGURATIONCONTAINER_T71 */
#define T71_DATA0							          0

/* PROCG_NOISESUPPRESSION_T72  */
#define T72_CTRL							          255 
#define T72_CALCFG1							        0
#define T72_CFG1							          0
#define T72_CFG2							          17
#define T72_DEBUGCFG 						        0
#define T72_HOPCNT 							        20
#define T72_HOPCNTPER           			  10 
#define T72_HOPEVALTO           			  5   
#define T72_HOPST							          2
#define T72_NLGAINDUALX						      48 
#define T72_MINNLTHR						        7
#define T72_INCNLTHR						        8  
#define T72_FALLNLTHR						        4
#define T72_NLTHRMARGIN						      3
#define T72_MINTHRADJ						        48
#define T72_NLTHRLIMIT						      40
#define T72_BGSCAN           				    13  
#define T72_NLGAINSINGX           			80  
#define T72_BLKNLTHR						        0
#define T72_RESERVED						        0
#define T72_STABCTRL						        0	 
#define T72_STABFREQ_0						      82
#define T72_STABFREQ_1						      48
#define T72_STABFREQ_2						      116
#define T72_STABFREQ_3						      13
#define T72_STABFREQ_4						      152
#define T72_STABTCHAPX_0					      23
#define T72_STABTCHAPX_1					      32
#define T72_STABTCHAPX_2					      17
#define T72_STABTCHAPX_3					      54
#define T72_STABTCHAPX_4					      14
#define T72_STABNOTCHAPX_0					    15
#define T72_STABNOTCHAPX_1					    21
#define T72_STABNOTCHAPX_2					    11
#define T72_STABNOTCHAPX_3					    36
#define T72_STABNOTCHAPX_4					    9
#define T72_STABPC							        0
#define T72_STABLOWNLTHR					      0 	
#define T72_STABHIGHNLTHR					      6
#define T72_STABCNT							        85
#define T72_NOISCTRL						        15
#define T72_NOISFREQ_0						      82
#define T72_NOISFREQ_1						      48
#define T72_NOISFREQ_2						      116
#define T72_NOISFREQ_3						      13
#define T72_NOISFREQ_4						      152
#define T72_NOISTCHAPX_0					      23
#define T72_NOISTCHAPX_1					      32
#define T72_NOISTCHAPX_2					      17
#define T72_NOISTCHAPX_3					      54
#define T72_NOISTCHAPX_4					      14
#define T72_NOISNOTCHAPX_0					    15
#define T72_NOISNOTCHAPX_1					    21
#define T72_NOISNOTCHAPX_2					    11
#define T72_NOISNOTCHAPX_3					    36
#define T72_NOISNOTCHAPX_4					    9
#define T72_NOISPC							        0
#define T72_NOISLOWNLTHR					      3
#define T72_NOISHIGHNLTHR					      14
#define T72_NOISCNT							        6
#define T72_VNOICTRL						        15
#define T72_VNOIFREQ_0						      82
#define T72_VNOIFREQ_1						      48
#define T72_VNOIFREQ_2						      116
#define T72_VNOIFREQ_3						      13
#define T72_VNOIFREQ_4						      152
#define T72_VNOITCHAPX_0					      37
#define T72_VNOITCHAPX_1					      52
#define T72_VNOITCHAPX_2					      28
#define T72_VNOITCHAPX_3					      62
#define T72_VNOITCHAPX_4					      21
#define T72_VNOINOTCHAPX_0					    37
#define T72_VNOINOTCHAPX_1					    52
#define T72_VNOINOTCHAPX_2					    28
#define T72_VNOINOTCHAPX_3					    63
#define T72_VNOINOTCHAPX_4					    21
#define T72_VNOIPC							        0
#define T72_VNOILOWNLTHR					      18
#define T72_VNOIHIGHNLTHR					      0 	
#define T72_VNOICNT							        52

/* PROCI_GLOVEDETECTION_T78  */
#define T78_CTRL							          13 
#define T78_MINAREA							        4 
#define T78_CONFTHR							        10
#define T78_MINDIST							        15	 
#define T78_GLOVEMODETO						      0
#define T78_SUPTO							          2
#define T78_SYNCSPERX						        16 

/* _TOUCH_MULTITOUCHSCREEN_T100 INSTANCE 0 */
#define T100_CTRL							          131
#define T100_CFG1							          48
#define T100_SCRAUX							        0
#define T100_TCHAUX							        0
#define T100_TCHEVENTCFG					      0
#define T100_AKSCFG							        0
#define T100_NUMTCH							        5
#define T100_XYCFG							        136
#define T100_XORIGIN						        0
#define T100_XSIZE							        30
#define T100_XPITCH							        0
#define T100_XLOCLIP						        1
#define T100_XHICLIP						        1   
#define T100_XRANGE							        4095
#define T100_XEDGECFG						        20
#define T100_XEDGEDIST						      30
#define T100_DXXEDGECFG						      0
#define T100_DXXEDGEDIST					      0 
#define T100_YORIGIN						        0
#define T100_YSIZE							        16
#define T100_YPITCH							        0
#define T100_YLOCLIP						        2
#define T100_YHICLIP						        2
#define T100_YRANGE							        4095
#define T100_YEDGECFG						        30
#define T100_YEDGEDIST						      50
#define T100_GAIN							          8
#define T100_DXGAIN							        3
#define T100_TCHTHR							        48  
#define T100_TCHHYST						        3
#define T100_INTTHR							        12 
#define T100_NOISESF						        0
#define T100_CUTOFFTHR						      0
#define T100_MRGTHR							        15
#define T100_MRGTHRADJSTR					      0
#define T100_MRGHYST						        15
#define T100_DXTHRSF						        0
#define T100_TCHDIDOWN						      2
#define T100_TCHDIUP						        2
#define T100_NEXTTCHDI						      1
#define T100_RESERVED							      0
#define T100_JUMPLIMIT						      35
#define T100_MOVFILTER						      2
#define T100_MOVSMOOTH						      190
#define T100_MOVPRED						        48
#define T100_MOVHYSTI						        5
#define T100_MOVHYSTN						        2
#define T100_AMPLHYST						        0
#define T100_SCRAREAHYST					      0
#define T100_INTTHRHYST						      255

/* SPT_TOUCHSCREENHOVER_T101 INSTANCE 0 */
#define T101_CTRL							1
#define T101_XLOCLIP						0
#define T101_XHICLIP						0		 
#define T101_XRANGE							0
#define T101_XEDGECFG						0
#define T101_XEDGEDIST						0 
#define T101_XGAIN							10
#define T101_XHVRTHR						40 
#define T101_XHVRHYST						10
#define T101_YLOCLIP						3
#define T101_YHICLIP						3
#define T101_YEDGECFG						40
#define T101_YEDGEDIST						50
#define T101_YGAIN							12
#define T101_YHVRTHR						40 
#define T101_YHVRHYST						10
#define T101_HVRDI							16
#define T101_CONFTHR						0
#define T101_MOVFILTER						4
#define T101_MOVSMOOTH						240
#define T101_MOVPRED						48
#define T101_MOVHYSTI						50 
#define T101_MOVHYSTN						30
#define T101_HVRAUX							0 

/* SPT_SELFCAPHOVERCTECONFIG_T102  */
#define T102_CTRL							3
#define T102_CMD							0
#define T102_TUNTHR							1200 
#define T102_TUNAVGCYCLES					0
#define T102_TUNCFG							0
#define T102_MODE							6 
#define T102_PRECHRGTIME					120
#define T102_CHRGTIME						160 
#define T102_INTTIME						80
#define T102_RESERVED_0						0
#define T102_RESERVED_1						0
#define T102_RESERVED_2						0
#define T102_IDLESYNCSPERL					32
#define T102_ACTVSYNCSPERL					32
#define T102_DRIFTINT						254 
#define T102_DRIFTST						1
#define T102_DRIFTSTHRSF					255
#define T102_FILTER							9
#define T102_FILTCFG						3 
#define T102_RESERVED_3						0
#define T102_RESERVED_4						0

#ifdef ITO_TYPE_CHECK
typedef struct {
	int min;
	int max;
} ito_table_element;

static ito_table_element ito_table[] = {
	{      0,	 400000},	// 0V
	{ 500000,	 700000},	// 0.6V
	{ 800000,	1000000},	// 0.9V
	{1100000,	1300000},	// 1.2V
	{1700000,	1900000},	// 1.8V
};

#define number_of_elements(ito_table) sizeof(ito_table)/sizeof(ito_table_element)
#define TOUCH_ID_MPP PM8XXX_AMUX_MPP_6
#endif

enum tsp_power_pin_type {
	POWER_NOT_USED=0,
	POWER_GPIO_SETUP,	// gpio setup
	POWER_PM_REGULATOR,	// PMIC regulator setup
};

enum gpio_direction {	
	GPIO_OUTPUT_LOW=0,	// out port, default low
	GPIO_OUTPUT_HIGH,	// out port, default high
	GPIO_INPUT,			// in port
};

enum power_up_down {	
	POWER_DOWN=0,
	POWER_UP,
};

#define GPIO_TOUCH_RST			60
#define GPIO_TOUCH_CHG			61
#define GPIO_TOUCH_DVDD 		94

struct tsp_power_pin_ctrl {
	int	type;
	const char *name;

	struct {
		int	num;		
		int	direction;
	} gpio;

	struct {		
		int	volt;
	} regulator;
};
static int tsp_power_pin_setuped = 0;

static struct tsp_power_pin_ctrl atmel_mxt_avdd;
static struct tsp_power_pin_ctrl atmel_mxt_dvdd;
static struct tsp_power_pin_ctrl atmel_mxt_vddio;
static struct tsp_power_pin_ctrl atmel_mxt_int;
static struct tsp_power_pin_ctrl atmel_mxt_rst;

void TSP_Power_Pin_Init(void) {
	if ( tsp_power_pin_setuped == 1 ) return;

	atmel_mxt_avdd.type = POWER_PM_REGULATOR;
	atmel_mxt_avdd.name = "8941_l10";
	atmel_mxt_avdd.regulator.volt = 2800000;

	atmel_mxt_dvdd.type = POWER_GPIO_SETUP;
	atmel_mxt_dvdd.name = "touch_power_dvdd";
	atmel_mxt_dvdd.gpio.num = GPIO_TOUCH_DVDD;	
	atmel_mxt_dvdd.gpio.direction = GPIO_OUTPUT_HIGH;

	atmel_mxt_vddio.type = POWER_NOT_USED;

	atmel_mxt_int.type = POWER_GPIO_SETUP;	
	atmel_mxt_int.name = "touch_int_n";
	atmel_mxt_int.gpio.num = GPIO_TOUCH_CHG;
	atmel_mxt_int.gpio.direction = GPIO_INPUT;	

	atmel_mxt_rst.type = POWER_GPIO_SETUP;
	atmel_mxt_rst.name = "touch_rst_n";
	atmel_mxt_rst.gpio.num = GPIO_TOUCH_RST;	
	atmel_mxt_rst.gpio.direction = GPIO_OUTPUT_LOW; 

	tsp_power_pin_setuped = 1;
}

int TSP_PowerSetup(struct tsp_power_pin_ctrl pp_ctrl, int up_down) 
{
	int rc;
	struct regulator *regulator;

	switch ( pp_ctrl.type ) {
	case POWER_NOT_USED:
		break;
	case POWER_GPIO_SETUP:			
		if ( up_down == POWER_UP ) {
			rc = gpio_request(pp_ctrl.gpio.num, pp_ctrl.name);
			if (rc) {
				gpio_free(pp_ctrl.gpio.num);				
				if (rc) {
					printk("[+++ Atmel Max Touch] %s: %d failed, rc=%d\n",pp_ctrl.name, pp_ctrl.gpio.num, rc);
				}
			}

			if ( pp_ctrl.gpio.direction == GPIO_INPUT ) 
				rc = gpio_direction_input(pp_ctrl.gpio.num);				
			else 
				rc = gpio_direction_output(pp_ctrl.gpio.num, pp_ctrl.gpio.direction);

			if (rc) {
				printk("[+++ Atmel Max Touch] %s: %d failed, rc=%d\n",pp_ctrl.name, pp_ctrl.gpio.num, rc);
			}
		}
		else {
			if ( pp_ctrl.gpio.direction == GPIO_OUTPUT_HIGH || pp_ctrl.gpio.direction == GPIO_OUTPUT_LOW) {
				gpio_set_value(pp_ctrl.gpio.num, 0);
				msleep(10);
			}

			gpio_free(pp_ctrl.gpio.num);
		}		

		break;
	case POWER_PM_REGULATOR:

		if ( up_down == POWER_UP ) {
			regulator = regulator_get(NULL, pp_ctrl.name);
			if(regulator == NULL) {
				printk("[+++ Atmel Max Touch] %s: regulator_get failed \n", pp_ctrl.name);
				return -EINVAL;
			}

			rc = regulator_set_voltage(regulator, pp_ctrl.regulator.volt, pp_ctrl.regulator.volt);
			if (rc) { 
				printk("[+++ Atmel Max Touch] %s: set_voltage %duV failed, rc=%d\n", pp_ctrl.name, pp_ctrl.regulator.volt, rc);
				return rc;
			}
			rc = regulator_enable(regulator);
			if (rc) {
				printk("[+++ Atmel Max Touch] %s: regulator enable failed (%d)\n", pp_ctrl.name, rc);
				return rc;
			}
			regulator_put(regulator);
		}
		else {
			regulator = regulator_get(NULL, pp_ctrl.name);
			if (regulator == NULL ) {
				printk("[+++ Atmel Max Touch] %s: regulator_get failed \n", pp_ctrl.name);
				return -EINVAL;
			}
			rc = regulator_disable(regulator);
			if (rc) {
				printk("%s: regulator disable failed (%d)\n", pp_ctrl.name, rc);
				return rc;
			}
			regulator_put(regulator);
		}
		break;
	}
	return 0;
}

void TSP_reset_pin_shake(void)
{
	TSP_Power_Pin_Init();

	msleep(10);
	gpio_set_value(atmel_mxt_rst.gpio.num, 0);	
	msleep(100);

	gpio_set_value(atmel_mxt_rst.gpio.num, 1);	

	msleep(10);
}

int TSP_PowerOn(void)
{
	TSP_Power_Pin_Init();

	TSP_PowerSetup(atmel_mxt_avdd, POWER_UP);
	TSP_PowerSetup(atmel_mxt_dvdd, POWER_UP);
	TSP_PowerSetup(atmel_mxt_vddio, POWER_UP);
	TSP_PowerSetup(atmel_mxt_int, POWER_UP);
	TSP_PowerSetup(atmel_mxt_rst, POWER_UP);

	TSP_reset_pin_shake();
	msleep(100);

	return 0;
}

void TSP_PowerOff(void)
{
	TSP_Power_Pin_Init();

	TSP_PowerSetup(atmel_mxt_avdd, POWER_DOWN);
	TSP_PowerSetup(atmel_mxt_dvdd, POWER_DOWN);
	TSP_PowerSetup(atmel_mxt_vddio, POWER_DOWN);
	TSP_PowerSetup(atmel_mxt_int, POWER_DOWN);
	TSP_PowerSetup(atmel_mxt_rst, POWER_DOWN);

	msleep(100);
}
