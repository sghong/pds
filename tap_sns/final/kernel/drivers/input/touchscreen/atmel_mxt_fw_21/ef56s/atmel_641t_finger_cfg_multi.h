
#include "atmel_mxt_fw21.h"

/* -------------------------------------------------------------------- */
/* GPIO, VREG & resolution */
/* -------------------------------------------------------------------- */
#define MAX_NUM_FINGER					10

// Screen resolution
#define SCREEN_RESOLUTION_X				1079
#define SCREEN_RESOLUTION_SCREEN_Y		1919
#define SCREEN_RESOLUTION_TOUCHKEY_Y	185
#define SCREEN_RESOLUTION_WHOLE_Y		(SCREEN_RESOLUTION_SCREEN_Y + SCREEN_RESOLUTION_TOUCHKEY_Y)

#ifdef PAN_HAVE_TOUCH_KEY
#define PAN_TOUCH_KEY_COUNT				3

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

//++p11309 - 2013.07.01 for TP10
#if (BOARD_VER < TP10 ) 

	#define PAN_1ST_TOUCH_KEY_X				215
	#define PAN_2ND_TOUCH_KEY_X				540
	#define PAN_3RD_TOUCH_KEY_X				865

	#define PAN_TOUCH_KEY_Y					2050
	#define PAN_TOUCH_KEY_MARGIN_Y			65	

	#define PAN_1ST_TOUCH_KEY_MARGIN_X		65
	#define PAN_2ND_TOUCH_KEY_MARGIN_X		125
	#define PAN_3RD_TOUCH_KEY_MARGIN_X		65

#else

	#define PAN_1ST_TOUCH_KEY_X				215
	#define PAN_2ND_TOUCH_KEY_X				540
	#define PAN_3RD_TOUCH_KEY_X				875

	#define PAN_TOUCH_KEY_Y					2040 // 2050 - 2013.08.01
	#define PAN_TOUCH_KEY_MARGIN_Y			50	 // 55 - 2013.08.01

	#define PAN_1ST_TOUCH_KEY_MARGIN_X		90
	#define PAN_2ND_TOUCH_KEY_MARGIN_X		140
	#define PAN_3RD_TOUCH_KEY_MARGIN_X		95

#endif
//--p11309

#define PAN_1ST_TOUCH_KEY_TYPE			KEY_MENU
#define PAN_2ND_TOUCH_KEY_TYPE			KEY_HOMEPAGE
#define PAN_3RD_TOUCH_KEY_TYPE			KEY_BACK

#endif

#define MXT_FW21_REFERENCE_MIN		    22000
#define MXT_FW21_REFERENCE_MAX		    28000

// define ITO_TYPE_CHECK

/* -------------------------------------------------------------------- */
/* DEVICE   : mxT768E CONFIGURATION */
/* -------------------------------------------------------------------- */

/*--------------- DEFINITION TOUCH MODE --------------------------------*/ 

#define TOUCH_MODE_NORMAL         0
#define TOUCH_MODE_HIGH_SENSITIVE 1
#define TOUCH_MODE_PEN            2
#define TOUCH_MODE_MAX_NUM	      3 

static int mTouch_mode=TOUCH_MODE_NORMAL;
//++ p11309 - 2014.01.02 for Preventing from wakeup of touch IC On Sleep.
static int mTouch_mode_on_sleep=TOUCH_MODE_NORMAL;
//-- p11309

//++ p11309 - 2013.07.10 for Smart Cover Status
#ifdef PAN_SUPPORT_SMART_COVER	
	#define SMART_COVER_AREA_TOP		0
	#define SMART_COVER_AREA_BOTTOM		780		// 620
	#define SMART_COVER_AREA_LEFT		185		// 0
	#define SMART_COVER_AREA_RIGHT		895		// 1080 
#endif
//++ p11309 - 2013.07.19 Support Soft Dead zone
#ifdef PAN_SUPPORT_SOFT_DEAD_ZONE
	#define PAN_SOFT_DEAD_ZONE_SIZE		20
	#define PAN_SOFT_DZ_X_R_LO			(SCREEN_RESOLUTION_X - PAN_SOFT_DEAD_ZONE_SIZE)
	#define PAN_SOFT_DZ_X_R_HI			SCREEN_RESOLUTION_X
	#define PAN_SOFT_DZ_Y_BTM_LO		SCREEN_RESOLUTION_SCREEN_Y - PAN_SOFT_DEAD_ZONE_SIZE
	#define PAN_SOFT_DZ_Y_BTM_HI		SCREEN_RESOLUTION_SCREEN_Y + PAN_SOFT_DEAD_ZONE_SIZE
#endif
//-- p11309

/* SPT_USERDATA_T38 INSTANCE 0 */
static gen_powerconfig_t7_config_t obj_power_config_t7[TOUCH_MODE_MAX_NUM] = {
	{
		.idleacqint  = 255,	/* T7_IDLEACQINT */	
		.actvacqint  = 255,	/* T7_ACTVACQINT */		// free-run
		.actv2idleto = 50,	/* T7_ACTV2IDLETO */
		.cfg         = 3,	/* T7_CFG */ 		
	},
	{
		.idleacqint  = 255,	/* T7_IDLEACQINT */	
		.actvacqint  = 255,	/* T7_ACTVACQINT */		// free-run
		.actv2idleto = 50,	/* T7_ACTV2IDLETO */
		.cfg         = 3,	/* T7_CFG */ 		
	},
	{
		.idleacqint  = 255,	/* T7_IDLEACQINT */	
		.actvacqint  = 255,	/* T7_ACTVACQINT */		// free-run
		.actv2idleto = 50,	/* T7_ACTV2IDLETO */
		.cfg         = 3,	/* T7_CFG */ 		
	},
};


/* GEN_ACQUISITIONCONFIG_T8 INSTANCE 0  */
static gen_acquisitionconfig_t8_config_t obj_acquisition_config_t8[TOUCH_MODE_MAX_NUM] = {
//++ p11309 - 2013.08.04 for Slim Sensor Config for Board version.
	{
		.chrgtime        = 80,  /* T8_CHRGTIME */
		.reserved0       = 0,   /* T8_RESERVED_0 */             
		.tchdrift        = 5,   /* T8_TCHDRIFT */			
		.driftst         = 1,   /* T8_DRIFTST */				
		.tchautocal      = 0,   /* T8_TCHAUTOCAL */				
		.sync            = 0,   /* T8_SYNC */					
		.atchcalst       = 255, /* T8_ATCHCALST */			
		.atchcalsthr     = 1,   /* T8_ATCHCALSTHR */            
		.atchfrccalthr   = 255, /* T8_ATCHFRCCALTHR */        	
		.atchfrccalratio = 127, /*T8_ATCHFRCCALRATIO */      	
		.reserved[0]     = 0,   /* T8_RESERVED_1 */      		
		.reserved[1]     = 0,   /* T8_RESERVED_2 */      		
		.reserved[2]     = 0,   /* T8_RESERVED_3 */      		
	},
	{
		.chrgtime        = 80,  /* T8_CHRGTIME */
		.reserved0       = 0,   /* T8_RESERVED_0 */             
		.tchdrift        = 5,   /* T8_TCHDRIFT */			
		.driftst         = 1,   /* T8_DRIFTST */				
		.tchautocal      = 0,   /* T8_TCHAUTOCAL */				
		.sync            = 0,   /* T8_SYNC */					
		.atchcalst       = 255, /* T8_ATCHCALST */			
		.atchcalsthr     = 1,   /* T8_ATCHCALSTHR */            
		.atchfrccalthr   = 255, /* T8_ATCHFRCCALTHR */        	
		.atchfrccalratio = 127, /*T8_ATCHFRCCALRATIO */      	
		.reserved[0]     = 0,   /* T8_RESERVED_1 */      		
		.reserved[1]     = 0,   /* T8_RESERVED_2 */      		
		.reserved[2]     = 0,   /* T8_RESERVED_3 */      		
	},
	{
		.chrgtime        = 80,  /* T8_CHRGTIME */
		.reserved0       = 0,   /* T8_RESERVED_0 */             
		.tchdrift        = 5,   /* T8_TCHDRIFT */			
		.driftst         = 1,   /* T8_DRIFTST */				
		.tchautocal      = 0,   /* T8_TCHAUTOCAL */				
		.sync            = 0,   /* T8_SYNC */					
		.atchcalst       = 255, /* T8_ATCHCALST */			
		.atchcalsthr     = 1,   /* T8_ATCHCALSTHR */            
		.atchfrccalthr   = 255, /* T8_ATCHFRCCALTHR */        	
		.atchfrccalratio = 127, /*T8_ATCHFRCCALRATIO */      	
		.reserved[0]     = 0,   /* T8_RESERVED_1 */      		
		.reserved[1]     = 0,   /* T8_RESERVED_2 */      		
		.reserved[2]     = 0,   /* T8_RESERVED_3 */      		
	},
};

/* [TOUCH_KEYARRAY_T15 INSTANCE 0]    */
static touch_keyarray_t15_config_t obj_key_array_t15[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl        = 0, /* T15_CTRL */				
		.xorigin     = 0, /* T15_XORIGIN */			
		.yorigin     = 0, /* T15_YORIGIN */			
		.xsize       = 0, /* T15_XSIZE */				
		.ysize       = 0, /* T15_YSIZE */				
		.akscfg      = 0, /* T15_AKSCFG */			
		.blen        = 0, /* T15_BLEN	*/				
		.tchthr      = 0, /* T15_TCHTHR */			
		.tchdi       = 0, /* T15_TCHDI */				
		.reserved[0] = 0, /* T15_RESERVED_0 */		
		.reserved[1] = 0, /* T15_RESERVED_1 */		
	},
	{
		.ctrl        = 0, /* T15_CTRL */				
		.xorigin     = 0, /* T15_XORIGIN */			
		.yorigin     = 0, /* T15_YORIGIN */			
		.xsize       = 0, /* T15_XSIZE */				
		.ysize       = 0, /* T15_YSIZE */				
		.akscfg      = 0, /* T15_AKSCFG */			
		.blen        = 0, /* T15_BLEN	*/				
		.tchthr      = 0, /* T15_TCHTHR */			
		.tchdi       = 0, /* T15_TCHDI */				
		.reserved[0] = 0, /* T15_RESERVED_0 */		
		.reserved[1] = 0, /* T15_RESERVED_1 */		
	},
	{
		.ctrl        = 0, /* T15_CTRL */				
		.xorigin     = 0, /* T15_XORIGIN */			
		.yorigin     = 0, /* T15_YORIGIN */			
		.xsize       = 0, /* T15_XSIZE */				
		.ysize       = 0, /* T15_YSIZE */				
		.akscfg      = 0, /* T15_AKSCFG */			
		.blen        = 0, /* T15_BLEN	*/				
		.tchthr      = 0, /* T15_TCHTHR */			
		.tchdi       = 0, /* T15_TCHDI */				
		.reserved[0] = 0, /* T15_RESERVED_0 */		
		.reserved[1] = 0, /* T15_RESERVED_1 */		
	},
};

/*  [SPT_COMMSCONFIG_T18 INSTANCE 0]        */
static spt_commsconfig_t18_config_t obj_comm_config_t18[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl = 0,/* T18_CTRL */
		.cmd  = 0, /* T18_COMMAND */
	},
	{
		.ctrl = 0,/* T18_CTRL */
		.cmd  = 0, /* T18_COMMAND */
	},
	{
		.ctrl = 0,/* T18_CTRL */
		.cmd  = 0, /* T18_COMMAND */
	},
};

/* T19*/
static spt_gpiopwm_t19_config_t obj_gpiopwm_config_t19[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl       = 0, /* T19_CTRL */
		.reportmask = 0, /* T19_REPORTMASK */
		.dir        = 0, /* T19_DIR */
		.intpullup  = 0, /* T19_INTPULLUP */
		.out        = 0, /* T19_OUT */
		.wake       = 0, /* T19_WAKE */
	},
	{
		.ctrl       = 0, /* T19_CTRL */
		.reportmask = 0, /* T19_REPORTMASK */
		.dir        = 0, /* T19_DIR */
		.intpullup  = 0, /* T19_INTPULLUP */
		.out        = 0, /* T19_OUT */
		.wake       = 0, /* T19_WAKE */
	},
	{
		.ctrl       = 0, /* T19_CTRL */
		.reportmask = 0, /* T19_REPORTMASK */
		.dir        = 0, /* T19_DIR */
		.intpullup  = 0, /* T19_INTPULLUP */
		.out        = 0, /* T19_OUT */
		.wake       = 0, /* T19_WAKE */
	},
};

/* [TOUCH_PROXIMITY_T23 INSTANCE 0] */
static touch_proximity_t23_config_t obj_proximity_sensor_t23[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl       = 0, /* T23_CTRL	*/					
		.xorigin    = 0, /* T23_XORIGIN */				
		.yorigin    = 0, /* T23_YORIGIN */               
		.xsize      = 0, /* T23_XSIZE */                 
		.ysize      = 0, /* T23_YSIZE */                 
		.reserved   = 0, /* T23_RESERVED */              
		.blen       = 0, /* T23_BLEN */                  
		.fxddthr    = 0, /* T23_FXDDTHR */               
		.fxddi      = 0, /* T23_FXDDI */                 
		.average    = 0, /* T23_AVERAGE */               
		.mvnullrate = 0, /* T23_MVNULLRATE */            
		.mvdthr     = 0, /* T23_MVDTHR*/                 
	},
	{
		.ctrl       = 0, /* T23_CTRL	*/					
		.xorigin    = 0, /* T23_XORIGIN */				
		.yorigin    = 0, /* T23_YORIGIN */               
		.xsize      = 0, /* T23_XSIZE */                 
		.ysize      = 0, /* T23_YSIZE */                 
		.reserved   = 0, /* T23_RESERVED */              
		.blen       = 0, /* T23_BLEN */                  
		.fxddthr    = 0, /* T23_FXDDTHR */               
		.fxddi      = 0, /* T23_FXDDI */                 
		.average    = 0, /* T23_AVERAGE */               
		.mvnullrate = 0, /* T23_MVNULLRATE */            
		.mvdthr     = 0, /* T23_MVDTHR*/                 
	},
	{
		.ctrl       = 0, /* T23_CTRL	*/					
		.xorigin    = 0, /* T23_XORIGIN */				
		.yorigin    = 0, /* T23_YORIGIN */               
		.xsize      = 0, /* T23_XSIZE */                 
		.ysize      = 0, /* T23_YSIZE */                 
		.reserved   = 0, /* T23_RESERVED */              
		.blen       = 0, /* T23_BLEN */                  
		.fxddthr    = 0, /* T23_FXDDTHR */               
		.fxddi      = 0, /* T23_FXDDI */                 
		.average    = 0, /* T23_AVERAGE */               
		.mvnullrate = 0, /* T23_MVNULLRATE */            
		.mvdthr     = 0, /* T23_MVDTHR*/                 
	},
};

/* [SPT_SELFTEST_T25 INSTANCE 0] */
static spt_selftest_t25_config_t obj_self_test_t25[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl               = 3,     /* T25_CTRL */							
		.cmd                = 0,     /* T25_CMD */				
#if(NUM_OF_TOUCH_OBJECTS)
		.siglim[0].upsiglim = 0,     /* T25_SIGLIM_0_UPSIGLIM */        		
		.siglim[0].losiglim = 0,     /* T25_SIGLIM_0_LOSIGLIM */       		
		.siglim[1].upsiglim = 0,     /* T25_SIGLIM_1_UPSIGLIM */       		
		.siglim[1].losiglim = 0,     /* T25_SIGLIM_1_LOSIGLIM */       		
		.siglim[2].upsiglim = 30000, /* T25_SIGLIM_2_UPSIGLIM */       		
		.siglim[2].losiglim = 0,     /* T25_SIGLIM_2_LOSIGLIM */       		
#endif
		.pindwellus         = 0,     /* T25_PINDWELLUS */					
#if(NUM_OF_TOUCH_OBJECTS)
		.sigrangelim[0]     = 0,     /* T25_SIGRANGELIM_0 */					
		.sigrangelim[1]     = 0,     /* T25_SIGRANGELIM_1 */					
		.sigrangelim[2]     = 10000, /* T25_SIGRANGELIM_2 */					
#endif
	},
	{
		.ctrl               = 3,     /* T25_CTRL */							
		.cmd                = 0,     /* T25_CMD */				
#if(NUM_OF_TOUCH_OBJECTS)
		.siglim[0].upsiglim = 0,     /* T25_SIGLIM_0_UPSIGLIM */        		
		.siglim[0].losiglim = 0,     /* T25_SIGLIM_0_LOSIGLIM */       		
		.siglim[1].upsiglim = 0,     /* T25_SIGLIM_1_UPSIGLIM */       		
		.siglim[1].losiglim = 0,     /* T25_SIGLIM_1_LOSIGLIM */       		
		.siglim[2].upsiglim = 30000, /* T25_SIGLIM_2_UPSIGLIM */       		
		.siglim[2].losiglim = 0,     /* T25_SIGLIM_2_LOSIGLIM */       		
#endif
		.pindwellus         = 0,     /* T25_PINDWELLUS */					
#if(NUM_OF_TOUCH_OBJECTS)
		.sigrangelim[0]     = 0,     /* T25_SIGRANGELIM_0 */					
		.sigrangelim[1]     = 0,     /* T25_SIGRANGELIM_1 */					
		.sigrangelim[2]     = 10000, /* T25_SIGRANGELIM_2 */					
#endif
	},
	{
		.ctrl               = 3,     /* T25_CTRL */							
		.cmd                = 0,     /* T25_CMD */				
#if(NUM_OF_TOUCH_OBJECTS)
		.siglim[0].upsiglim = 0,     /* T25_SIGLIM_0_UPSIGLIM */        		
		.siglim[0].losiglim = 0,     /* T25_SIGLIM_0_LOSIGLIM */       		
		.siglim[1].upsiglim = 0,     /* T25_SIGLIM_1_UPSIGLIM */       		
		.siglim[1].losiglim = 0,     /* T25_SIGLIM_1_LOSIGLIM */       		
		.siglim[2].upsiglim = 30000, /* T25_SIGLIM_2_UPSIGLIM */       		
		.siglim[2].losiglim = 0,     /* T25_SIGLIM_2_LOSIGLIM */       		
#endif
		.pindwellus         = 0,     /* T25_PINDWELLUS */					
#if(NUM_OF_TOUCH_OBJECTS)
		.sigrangelim[0]     = 0,     /* T25_SIGRANGELIM_0 */					
		.sigrangelim[1]     = 0,     /* T25_SIGRANGELIM_1 */					
		.sigrangelim[2]     = 10000, /* T25_SIGRANGELIM_2 */					
#endif
	},
};

// GRIPSUPPRESSION_T40
static proci_gripsuppression_t40_config_t obj_grip_suppression_t40[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl    = 17, /* T40_CTRL */					
		.xlogrip = 0, /* T40_XLOGRIP */             	
		.xhigrip = 0, /* T40_XHIGRIP */            	
		.ylogrip = 20, /* T40_YLOGRIP */            	
		.yhigrip = 15, /* T40_YHIGRIP */				
	},
	{
		.ctrl    = 17, /* T40_CTRL */					
		.xlogrip = 0, /* T40_XLOGRIP */             	
		.xhigrip = 0, /* T40_XHIGRIP */            	
		.ylogrip = 20, /* T40_YLOGRIP */            	
		.yhigrip = 15, /* T40_YHIGRIP */				
	},
	{
		.ctrl    = 17, /* T40_CTRL */					
		.xlogrip = 0, /* T40_XLOGRIP */             	
		.xhigrip = 0, /* T40_XHIGRIP */            	
		.ylogrip = 20, /* T40_YLOGRIP */            	
		.yhigrip = 15, /* T40_YHIGRIP */				
	},
};

/* PROCI_TOUCHSUPPRESSION_T42 */
static proci_touchsuppression_t42_config_t obj_touch_suppression_t42[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl          = 11,  /* T42_CTRL */					// palm suppression OFF : protect mode //51
		.reserved      = 150, /* T42_RESERVED */				/* 0 (TCHTHR/4), 1 to 255 */
		.maxapprarea   = 80,  /* T42_MAXAPPRAREA */			    /* 0 (40ch), 1 to 255 */
		.maxtcharea    = 120, /* T42_MAXTCHAREA */			    /* 0 (35ch), 1 to 255 */
		.supstrength   = 255, /* T42_SUPSTRENGTH */			    /* 0 (128), 1 to 255 */
		.supextto      = 200, /* T42_SUPEXTTO */				/* 0 (never expires), 1 to 255 (timeout in cycles) */
		.maxnumtchs    = 9,   /* T42_MAXNUMTCHS */          	/* 0 to 9 (maximum number of touches minus 1) */
		.shapestrength = 31,   /* T42_SHAPESTRENGTH */			/* 0 (10), 1 to 31 */
		.supdist       = 1,   /* T42_SUPDIST */					// 7
		.disthyst      = 1,   /* T42_DISTHYST */	
		.maxscrnarea   = 0,
		.cfg           = 0,
		.reserved_1	   = 0,
	},
	{
		.ctrl          = 11,  /* T42_CTRL */					// palm suppression OFF : protect mode //51
		.reserved      = 150, /* T42_RESERVED */				/* 0 (TCHTHR/4), 1 to 255 */
		.maxapprarea   = 80,  /* T42_MAXAPPRAREA */			    /* 0 (40ch), 1 to 255 */
		.maxtcharea    = 120, /* T42_MAXTCHAREA */			    /* 0 (35ch), 1 to 255 */
		.supstrength   = 255, /* T42_SUPSTRENGTH */			    /* 0 (128), 1 to 255 */
		.supextto      = 200, /* T42_SUPEXTTO */				/* 0 (never expires), 1 to 255 (timeout in cycles) */
		.maxnumtchs    = 9,   /* T42_MAXNUMTCHS */          	/* 0 to 9 (maximum number of touches minus 1) */
		.shapestrength = 31,   /* T42_SHAPESTRENGTH */			/* 0 (10), 1 to 31 */
		.supdist       = 1,   /* T42_SUPDIST */					// 7
		.disthyst      = 1,   /* T42_DISTHYST */	
		.maxscrnarea   = 0,
		.cfg           = 0,
		.reserved_1	   = 0,
	},
	{
		.ctrl          = 11,  /* T42_CTRL */					// palm suppression OFF : protect mode //51
		.reserved      = 150, /* T42_RESERVED */				/* 0 (TCHTHR/4), 1 to 255 */
		.maxapprarea   = 80,  /* T42_MAXAPPRAREA */			    /* 0 (40ch), 1 to 255 */
		.maxtcharea    = 120, /* T42_MAXTCHAREA */			    /* 0 (35ch), 1 to 255 */
		.supstrength   = 255, /* T42_SUPSTRENGTH */			    /* 0 (128), 1 to 255 */
		.supextto      = 200, /* T42_SUPEXTTO */				/* 0 (never expires), 1 to 255 (timeout in cycles) */
		.maxnumtchs    = 9,   /* T42_MAXNUMTCHS */          	/* 0 to 9 (maximum number of touches minus 1) */
		.shapestrength = 31,   /* T42_SHAPESTRENGTH */			/* 0 (10), 1 to 31 */
		.supdist       = 1,   /* T42_SUPDIST */					// 7
		.disthyst      = 1,   /* T42_DISTHYST */	
		.maxscrnarea   = 0,
		.cfg           = 0,
		.reserved_1	   = 0,
	},
};

/* SPT_CTECONFIG_T46  */
static spt_cteconfig_t46_config_t obj_cte_config_t46[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl          = 4,	 /* T46_CTRL */						/*Reserved */
		.reserved      = 0,	 /* T46_RESERVED	*/				/*0: 16X14Y, 1: 17X13Y, 2: 18X12Y, 3: 19X11Y, 4: 20X10Y, 5: 21X15Y, 6: 22X8Y, */
		.idlesyncsperx = 32, /* T46_IDLESYNCSPERX */				
		.actvsyncsperx = 40, /* T46_ACTVSYNCSPERX */				
		.adcspersync   = 0,  /* T46_ADCSPERSYNC */				
		.pulsesperadc  = 0,  /* T46_PULSESPERADC */				/*0:1  1:2   2:3   3:4 pulses */
		.xslew         = 4,  /* T46_XSLEW */					// 1   *0:500nsec,  1:350nsec */
		.syncdelay     = 0,	 /* T46_SYNCDELAY */						
		.xvoltage      = 1,	 /* T46_XVOLTAGE */					//TODO: not exists in doc.	
	},
	{
		.ctrl          = 4,	 /* T46_CTRL */						/*Reserved */
		.reserved      = 0,	 /* T46_RESERVED	*/				/*0: 16X14Y, 1: 17X13Y, 2: 18X12Y, 3: 19X11Y, 4: 20X10Y, 5: 21X15Y, 6: 22X8Y, */
		.idlesyncsperx = 32, /* T46_IDLESYNCSPERX */				
		.actvsyncsperx = 40, /* T46_ACTVSYNCSPERX */				
		.adcspersync   = 0,  /* T46_ADCSPERSYNC */				
		.pulsesperadc  = 0,  /* T46_PULSESPERADC */				/*0:1  1:2   2:3   3:4 pulses */
		.xslew         = 4,  /* T46_XSLEW */					// 1   *0:500nsec,  1:350nsec */
		.syncdelay     = 0,	 /* T46_SYNCDELAY */						
		.xvoltage      = 1,	 /* T46_XVOLTAGE */					//TODO: not exists in doc.	
	},
	{
		.ctrl          = 4,	 /* T46_CTRL */						/*Reserved */
		.reserved      = 0,	 /* T46_RESERVED	*/				/*0: 16X14Y, 1: 17X13Y, 2: 18X12Y, 3: 19X11Y, 4: 20X10Y, 5: 21X15Y, 6: 22X8Y, */
		.idlesyncsperx = 32, /* T46_IDLESYNCSPERX */				
		.actvsyncsperx = 40, /* T46_ACTVSYNCSPERX */				
		.adcspersync   = 0,  /* T46_ADCSPERSYNC */				
		.pulsesperadc  = 0,  /* T46_PULSESPERADC */				/*0:1  1:2   2:3   3:4 pulses */
		.xslew         = 4,  /* T46_XSLEW */					// 1   *0:500nsec,  1:350nsec */
		.syncdelay     = 0,	 /* T46_SYNCDELAY */						
		.xvoltage      = 1,	 /* T46_XVOLTAGE */					//TODO: not exists in doc.	
	},
};

/* PROCI_STYLUS_T47 */              
static proci_stylus_t47_config_t obj_stylus_t47[TOUCH_MODE_MAX_NUM] = {
	{	// Mode 0
		.ctrl       = 0,   /* T47_CTRL */						
		.contmin    = 25,  /* T47_CONTMIN */					
		.contmax    = 40,  /* T47_CONTMAX */					
		.stability  = 255, /* T47_STABILITY */					
		.maxtcharea = 2,   /* T47_MAXTCHAREA */          		
		.amplthr    = 25,  /* T47_AMPLTHR */					
		.styshape   = 10,  /* T47_STYSHAPE */					
		.hoversup   = 140, /* T47_HOVERSUP */					
		.confthr    = 1,   /* T47_CONFTHR */					
		.syncsperx  = 24,  /* T47_SYNCSPERX */					
		.xposadj    = 32,  /* T47_XPOSADJ */					
		.yposadj    = 32,  /* T47_YPOSADJ */					
		.cfg        = 0,   /* T47_CFG */						   //15
		.reserved0  = 0,   /* T47_RESERVED0 */                 
		.reserved1  = 0,   /* T47_RESERVED1 */					
		.reserved2  = 0,   /* T47_RESERVED2 */ 				
		.reserved3  = 0,   /* T47_RESERVED3 */					
		.reserved4  = 0,   /* T47_RESERVED4 */					
		.reserved5  = 0,   /* T47_RESERVED5 */ 				
		.reserved6  = 0,   /* T47_RESERVED6 */                 
		.supstyto   = 1,   /* T47_SUPSTYTO */                  
		.maxnumsty  = 0,   /* T47_MAXNUMSTY */                 
		.xedgectrl  = 0, /* T47_XEDGECTRL */					
		.xedgedist  = 0,  /* T47_XEDGEDIST */					
		.yedgectrl  = 0, /* T47_YEDGECTRL */					
		.yedgedist  = 0,  /* T47_YEDGEDIST */					
	},
	{	// Mode 0
		.ctrl       = 0,   /* T47_CTRL */						
		.contmin    = 25,  /* T47_CONTMIN */					
		.contmax    = 40,  /* T47_CONTMAX */					
		.stability  = 255, /* T47_STABILITY */					
		.maxtcharea = 2,   /* T47_MAXTCHAREA */          		
		.amplthr    = 25,  /* T47_AMPLTHR */					
		.styshape   = 10,  /* T47_STYSHAPE */					
		.hoversup   = 140, /* T47_HOVERSUP */					
		.confthr    = 1,   /* T47_CONFTHR */					
		.syncsperx  = 24,  /* T47_SYNCSPERX */					
		.xposadj    = 32,  /* T47_XPOSADJ */					
		.yposadj    = 32,  /* T47_YPOSADJ */					
		.cfg        = 0,   /* T47_CFG */						   //15
		.reserved0  = 0,   /* T47_RESERVED0 */                 
		.reserved1  = 0,   /* T47_RESERVED1 */					
		.reserved2  = 0,   /* T47_RESERVED2 */ 				
		.reserved3  = 0,   /* T47_RESERVED3 */					
		.reserved4  = 0,   /* T47_RESERVED4 */					
		.reserved5  = 0,   /* T47_RESERVED5 */ 				
		.reserved6  = 0,   /* T47_RESERVED6 */                 
		.supstyto   = 1,   /* T47_SUPSTYTO */                  
		.maxnumsty  = 0,   /* T47_MAXNUMSTY */                 
		.xedgectrl  = 0, /* T47_XEDGECTRL */					
		.xedgedist  = 0,  /* T47_XEDGEDIST */					
		.yedgectrl  = 0, /* T47_YEDGECTRL */					
		.yedgedist  = 0,  /* T47_YEDGEDIST */					
	},
	{	// Mode 0
		.ctrl       = 0,   /* T47_CTRL */						
		.contmin    = 25,  /* T47_CONTMIN */					
		.contmax    = 40,  /* T47_CONTMAX */					
		.stability  = 255, /* T47_STABILITY */					
		.maxtcharea = 2,   /* T47_MAXTCHAREA */          		
		.amplthr    = 25,  /* T47_AMPLTHR */					
		.styshape   = 10,  /* T47_STYSHAPE */					
		.hoversup   = 140, /* T47_HOVERSUP */					
		.confthr    = 1,   /* T47_CONFTHR */					
		.syncsperx  = 24,  /* T47_SYNCSPERX */					
		.xposadj    = 32,  /* T47_XPOSADJ */					
		.yposadj    = 32,  /* T47_YPOSADJ */					
		.cfg        = 0,   /* T47_CFG */						   //15
		.reserved0  = 0,   /* T47_RESERVED0 */                 
		.reserved1  = 0,   /* T47_RESERVED1 */					
		.reserved2  = 0,   /* T47_RESERVED2 */ 				
		.reserved3  = 0,   /* T47_RESERVED3 */					
		.reserved4  = 0,   /* T47_RESERVED4 */					
		.reserved5  = 0,   /* T47_RESERVED5 */ 				
		.reserved6  = 0,   /* T47_RESERVED6 */                 
		.supstyto   = 1,   /* T47_SUPSTYTO */                  
		.maxnumsty  = 0,   /* T47_MAXNUMSTY */                 
		.xedgectrl  = 0, /* T47_XEDGECTRL */					
		.xedgedist  = 0,  /* T47_XEDGEDIST */					
		.yedgectrl  = 0, /* T47_YEDGECTRL */					
		.yedgedist  = 0,  /* T47_YEDGEDIST */					
	},
};

//PROCI_ADDAPTIVETHRESHOLD_T55
static proci_adaptivethreshold_t55_config_t obj_adaptive_threshold_t55[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl  		   = 0, /* T55_CTRL */						
		.targetthr	   = 45, /* T55_TARGETTHR */					
		.thradjlim	   = 0, /* T55_THRADJLIM */					
		.resetsteptime = 0, /* T55_RESETSTEPTIME */				
		.forcechgdist  = 0, /* T55_FORCECHGDIST */				
		.forcechgtime  = 0, /* T55_FORCECHGTIME */				
		.lowestthr     = -100, /* T55_LOWESTTHR */					
	},
	{
		.ctrl  		   = 1, /* T55_CTRL */						
		.targetthr	   = 45, /* T55_TARGETTHR */					
		.thradjlim	   = 0, /* T55_THRADJLIM */					
		.resetsteptime = 0, /* T55_RESETSTEPTIME */				
		.forcechgdist  = 0, /* T55_FORCECHGDIST */				
		.forcechgtime  = 0, /* T55_FORCECHGTIME */				
		.lowestthr     = -128, /* T55_LOWESTTHR */					
	},
	{
		.ctrl  		   = 1, /* T55_CTRL */						
		.targetthr	   = 35, /* T55_TARGETTHR */					
		.thradjlim	   = 0, /* T55_THRADJLIM */					
		.resetsteptime = 0, /* T55_RESETSTEPTIME */				
		.forcechgdist  = 0, /* T55_FORCECHGDIST */				
		.forcechgtime  = 0, /* T55_FORCECHGTIME */				
		.lowestthr     = -128, /* T55_LOWESTTHR */					
	},
};

// PROCI_SHIELDLESS_T56 
static proci_shieldless_t56_config_t obj_slim_sensor_t56[TOUCH_MODE_MAX_NUM] = {
//++ p11309 - 2013.08.04 for Slim Sensor Config for Board version.
	{
		.ctrl  		 = 3,  /* T56_CTRL */									//0
		.reserved    = 0,  /* T56_RESERVED */							    
		.optint		 = 1,  /* T56_OPTINT */						        //ymlee
		.inttime     = 60, /* T56_INTTIME */							    
		.intdelay0	 = 6,  /* T56_INTDELAY0 */						        
		.intdelay1	 = 6,  /* T56_INTDELAY1 */						        
		.intdelay2	 = 6,  /* T56_INTDELAY2 */						        
		.intdelay3	 = 6,  /* T56_INTDELAY3 */						        
		.intdelay4	 = 6,  /* T56_INTDELAY4 */						        
		.intdelay5	 = 6,  /* T56_INTDELAY5 */						        
		.intdelay6	 = 6,  /* T56_INTDELAY6 */						        
		.intdelay7	 = 6,  /* T56_INTDELAY7 */						        
		.intdelay8	 = 6,  /* T56_INTDELAY8 */						        
		.intdelay9	 = 6,  /* T56_INTDELAY9 */						        
		.intdelay10	 = 6,  /* T56_INTDELAY10 */						    
		.intdelay11	 = 6,  /* T56_INTDELAY11 */							
		.intdelay12	 = 8,  /* T56_INTDELAY12 */						    
		.intdelay13	 = 8,  /* T56_INTDELAY13 */							
		.intdelay14	 = 8,  /* T56_INTDELAY14 */						    
		.intdelay15	 = 8,  /* T56_INTDELAY15 */						    
		.intdelay16	 = 8,  /* T56_INTDELAY16 */						    
		.intdelay17	 = 8,  /* T56_INTDELAY17 */						    
		.intdelay18	 = 8,  /* T56_INTDELAY18 */						    
		.intdelay19	 = 8,  /* T56_INTDELAY19 */						    
		.intdelay20	 = 8,  /* T56_INTDELAY20 */						    
		.intdelay21	 = 8,  /* T56_INTDELAY21 */						      	
		.intdelay22	 = 8,  /* T56_INTDELAY22 */						    
		.intdelay23	 = 8,  /* T56_INTDELAY23 */						    
		.intdelay24	 = 8,  /* T56_INTDELAY24 */						    
		.intdelay25	 = 8,  /* T56_INTDELAY25 */						    
		.intdelay26	 = 8,  /* T56_INTDELAY26 */						    
		.intdelay27	 = 8,  /* T56_INTDELAY27 */						    
		.intdelay28	 = 8,  /* T56_INTDELAY28 */						    
		.intdelay29  = 8,  /* T56_INTDELAY29 */						    
		.intdelay30  = 8,  /* T56_INTDELAY29 */						    
		.intdelay31  = 8,  /* T56_INTDELAY29 */						    
		.multicutgc	 = 0,  /* T56_MULTICUTGC */						    
		.gclimit     = 0,  /* T56_GCLIMIT */
	},
	{
		.ctrl  		 = 3,  /* T56_CTRL */									//0
		.reserved    = 0,  /* T56_RESERVED */							    
		.optint		 = 1,  /* T56_OPTINT */						        //ymlee
		.inttime     = 60, /* T56_INTTIME */							    
		.intdelay0	 = 6,  /* T56_INTDELAY0 */						        
		.intdelay1	 = 6,  /* T56_INTDELAY1 */						        
		.intdelay2	 = 6,  /* T56_INTDELAY2 */						        
		.intdelay3	 = 6,  /* T56_INTDELAY3 */						        
		.intdelay4	 = 6,  /* T56_INTDELAY4 */						        
		.intdelay5	 = 6,  /* T56_INTDELAY5 */						        
		.intdelay6	 = 6,  /* T56_INTDELAY6 */						        
		.intdelay7	 = 6,  /* T56_INTDELAY7 */						        
		.intdelay8	 = 6,  /* T56_INTDELAY8 */						        
		.intdelay9	 = 6,  /* T56_INTDELAY9 */						        
		.intdelay10	 = 6,  /* T56_INTDELAY10 */						    
		.intdelay11	 = 6,  /* T56_INTDELAY11 */							
		.intdelay12	 = 8,  /* T56_INTDELAY12 */						    
		.intdelay13	 = 8,  /* T56_INTDELAY13 */							
		.intdelay14	 = 8,  /* T56_INTDELAY14 */						    
		.intdelay15	 = 8,  /* T56_INTDELAY15 */						    
		.intdelay16	 = 8,  /* T56_INTDELAY16 */						    
		.intdelay17	 = 8,  /* T56_INTDELAY17 */						    
		.intdelay18	 = 8,  /* T56_INTDELAY18 */						    
		.intdelay19	 = 8,  /* T56_INTDELAY19 */						    
		.intdelay20	 = 8,  /* T56_INTDELAY20 */						    
		.intdelay21	 = 8,  /* T56_INTDELAY21 */						      	
		.intdelay22	 = 8,  /* T56_INTDELAY22 */						    
		.intdelay23	 = 8,  /* T56_INTDELAY23 */						    
		.intdelay24	 = 8,  /* T56_INTDELAY24 */						    
		.intdelay25	 = 8,  /* T56_INTDELAY25 */						    
		.intdelay26	 = 8,  /* T56_INTDELAY26 */						    
		.intdelay27	 = 8,  /* T56_INTDELAY27 */						    
		.intdelay28	 = 8,  /* T56_INTDELAY28 */						    
		.intdelay29  = 8,  /* T56_INTDELAY29 */						    
		.intdelay30  = 8,  /* T56_INTDELAY29 */						    
		.intdelay31  = 8,  /* T56_INTDELAY29 */						    
		.multicutgc	 = 0,  /* T56_MULTICUTGC */						    
		.gclimit     = 0,  /* T56_GCLIMIT */
	},
	{
		.ctrl  		 = 3,  /* T56_CTRL */									//0
		.reserved    = 0,  /* T56_RESERVED */							    
		.optint		 = 1,  /* T56_OPTINT */						        //ymlee
		.inttime     = 60, /* T56_INTTIME */							    
		.intdelay0	 = 6,  /* T56_INTDELAY0 */						        
		.intdelay1	 = 6,  /* T56_INTDELAY1 */						        
		.intdelay2	 = 6,  /* T56_INTDELAY2 */						        
		.intdelay3	 = 6,  /* T56_INTDELAY3 */						        
		.intdelay4	 = 6,  /* T56_INTDELAY4 */						        
		.intdelay5	 = 6,  /* T56_INTDELAY5 */						        
		.intdelay6	 = 6,  /* T56_INTDELAY6 */						        
		.intdelay7	 = 6,  /* T56_INTDELAY7 */						        
		.intdelay8	 = 6,  /* T56_INTDELAY8 */						        
		.intdelay9	 = 6,  /* T56_INTDELAY9 */						        
		.intdelay10	 = 6,  /* T56_INTDELAY10 */						    
		.intdelay11	 = 6,  /* T56_INTDELAY11 */							
		.intdelay12	 = 8,  /* T56_INTDELAY12 */						    
		.intdelay13	 = 8,  /* T56_INTDELAY13 */							
		.intdelay14	 = 8,  /* T56_INTDELAY14 */						    
		.intdelay15	 = 8,  /* T56_INTDELAY15 */						    
		.intdelay16	 = 8,  /* T56_INTDELAY16 */						    
		.intdelay17	 = 8,  /* T56_INTDELAY17 */						    
		.intdelay18	 = 8,  /* T56_INTDELAY18 */						    
		.intdelay19	 = 8,  /* T56_INTDELAY19 */						    
		.intdelay20	 = 8,  /* T56_INTDELAY20 */						    
		.intdelay21	 = 8,  /* T56_INTDELAY21 */						      	
		.intdelay22	 = 8,  /* T56_INTDELAY22 */						    
		.intdelay23	 = 8,  /* T56_INTDELAY23 */						    
		.intdelay24	 = 8,  /* T56_INTDELAY24 */						    
		.intdelay25	 = 8,  /* T56_INTDELAY25 */						    
		.intdelay26	 = 8,  /* T56_INTDELAY26 */						    
		.intdelay27	 = 8,  /* T56_INTDELAY27 */						    
		.intdelay28	 = 8,  /* T56_INTDELAY28 */						    
		.intdelay29  = 8,  /* T56_INTDELAY29 */						    
		.intdelay30  = 8,  /* T56_INTDELAY29 */						    
		.intdelay31  = 8,  /* T56_INTDELAY29 */						    
		.multicutgc	 = 0,  /* T56_MULTICUTGC */						    
		.gclimit     = 0,  /* T56_GCLIMIT */
	},
};

// SPT_TIMER_T61 
static spt_timer_t61_config_t obj_timer_t61[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl   = 0, /* T61_CTRL */					
		.cmd    = 0, /* T61_CMD */					
		.mode   = 0, /* T61_MODE */					
		.period = 0, /* T61_PERIOD */				
	},
	{
		.ctrl   = 0, /* T61_CTRL */					
		.cmd    = 0, /* T61_CMD */					
		.mode   = 0, /* T61_MODE */					
		.period = 0, /* T61_PERIOD */				
	},
	{
		.ctrl   = 0, /* T61_CTRL */					
		.cmd    = 0, /* T61_CMD */					
		.mode   = 0, /* T61_MODE */					
		.period = 0, /* T61_PERIOD */				
	},
};

//PROCI_LENSBENDING_T65
static proci_lensbending_t65_config_t obj_lens_bending_t65[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl         = 1, /* T65_CTRL */						
		.gradthr      = 6, /* T65_GRADTHR */					
		.ylonoisemul  = 0, /* T65_YLONOISEMUL */				
		.ylonoisediv  = 0, /* T65_YLONOISEDIV */				
		.yhinoisemul  = 0, /* T65_YHINOISEMUL */				
		.yhinoisediv  = 0, /* T65_YHINOISEDIV */				
		.lpfiltcoef   = 5, /* T65_LPFILTCOEF */				
		.forcescale   = 0, /* T65_FORCESCALE */										
		.forcethr     = 0, /* T65_FORCETHR */					
		.forcethrhyst = 0, /* T65_FORCETHRHYST */				
		.forcedi      = 0, /* T65_FORCEDI */					
		.forcehyst    = 0, /* T65_FORCEHYST */	
		.atchratio	  = 1,
		.totvarlim    = 0,
	},
	{
		.ctrl         = 1, /* T65_CTRL */						
		.gradthr      = 6, /* T65_GRADTHR */					
		.ylonoisemul  = 0, /* T65_YLONOISEMUL */				
		.ylonoisediv  = 0, /* T65_YLONOISEDIV */				
		.yhinoisemul  = 0, /* T65_YHINOISEMUL */				
		.yhinoisediv  = 0, /* T65_YHINOISEDIV */				
		.lpfiltcoef   = 5, /* T65_LPFILTCOEF */				
		.forcescale   = 0, /* T65_FORCESCALE */										
		.forcethr     = 0, /* T65_FORCETHR */					
		.forcethrhyst = 0, /* T65_FORCETHRHYST */				
		.forcedi      = 0, /* T65_FORCEDI */					
		.forcehyst    = 0, /* T65_FORCEHYST */	
		.atchratio	  = 1,
		.totvarlim    = 0,
	},
	{
		.ctrl         = 1, /* T65_CTRL */						
		.gradthr      = 6, /* T65_GRADTHR */					
		.ylonoisemul  = 0, /* T65_YLONOISEMUL */				
		.ylonoisediv  = 0, /* T65_YLONOISEDIV */				
		.yhinoisemul  = 0, /* T65_YHINOISEMUL */				
		.yhinoisediv  = 0, /* T65_YHINOISEDIV */				
		.lpfiltcoef   = 5, /* T65_LPFILTCOEF */				
		.forcescale   = 0, /* T65_FORCESCALE */										
		.forcethr     = 0, /* T65_FORCETHR */					
		.forcethrhyst = 0, /* T65_FORCETHRHYST */				
		.forcedi      = 0, /* T65_FORCEDI */					
		.forcehyst    = 0, /* T65_FORCEHYST */	
		.atchratio	  = 1,
		.totvarlim    = 0,
	},
};

/* SPT_GOLDENREFERENCES_T66 */
static spt_goldenreferences_t66_config_t obj_mxt_startup_t66[TOUCH_MODE_MAX_NUM] = {
	{
#ifdef PAN_TOUCH_CAL_COMMON
		.ctrl          = 0,   /* T66_CTRL	*/			
#else
		.ctrl          = 0,   /* T66_CTRL	*/			
#endif
		.fcalfailthr   = 0,  /* T66_FCALFAILTHR */	
		.fcaldriftcnt  = 0, /* T66_FCALDRIFTCNT */	
	},
	{
#ifdef PAN_TOUCH_CAL_COMMON
		.ctrl          = 0,   /* T66_CTRL	*/			
#else
		.ctrl          = 0,   /* T66_CTRL	*/			
#endif
		.fcalfailthr   = 0,  /* T66_FCALFAILTHR */	
		.fcaldriftcnt  = 0, /* T66_FCALDRIFTCNT */	
	},
	{
#ifdef PAN_TOUCH_CAL_COMMON
		.ctrl          = 0,   /* T66_CTRL	*/			
#else
		.ctrl          = 0,   /* T66_CTRL	*/			
#endif
		.fcalfailthr   = 0,  /* T66_FCALFAILTHR */	
		.fcaldriftcnt  = 0, /* T66_FCALDRIFTCNT */	
	},
};

/*  PROCI_PALMGESTUREPROCESSOR_T69  */
static proci_palmgestureprocessor_t69_config_t obj_palm_gesture_processor_t69[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl          = 0, /* T69_CTRL */			 
		.longdimthr    = 0,	/* T69_LONGDIMTHR */	
		.shortdimthr   = 0, /* T69_SHORTDIMTHR */	
		.longdimhyst   = 0,	/* T69_LONGDIMHYST */	
		.shortdimhyst  = 0,	/* T69_SHORTDIMHYST */	
		.movthr        = 0,	/* T69_MOVTHR */		
		.movthrto      = 0,	/* T69_MOVTHRTO */		
		.areathr       = 0,	/* T69_AREATHR */		
		.areathrto     = 0,	/* T69_AREATHRTO */		
	},
	{
		.ctrl          = 0, /* T69_CTRL */			 
		.longdimthr    = 0,	/* T69_LONGDIMTHR */	
		.shortdimthr   = 0, /* T69_SHORTDIMTHR */	
		.longdimhyst   = 0,	/* T69_LONGDIMHYST */	
		.shortdimhyst  = 0,	/* T69_SHORTDIMHYST */	
		.movthr        = 0,	/* T69_MOVTHR */		
		.movthrto      = 0,	/* T69_MOVTHRTO */		
		.areathr       = 0,	/* T69_AREATHR */		
		.areathrto     = 0,	/* T69_AREATHRTO */		
	},
	{
		.ctrl          = 0, /* T69_CTRL */			 
		.longdimthr    = 0,	/* T69_LONGDIMTHR */	
		.shortdimthr   = 0, /* T69_SHORTDIMTHR */	
		.longdimhyst   = 0,	/* T69_LONGDIMHYST */	
		.shortdimhyst  = 0,	/* T69_SHORTDIMHYST */	
		.movthr        = 0,	/* T69_MOVTHR */		
		.movthrto      = 0,	/* T69_MOVTHRTO */		
		.areathr       = 0,	/* T69_AREATHR */		
		.areathrto     = 0,	/* T69_AREATHRTO */		
	},
};

/* SPT_DYNAMICCONFIGURATIONCONTROLLER_T70 */
//++ p11309 - 2013.07.19 for T70 dynamic config
#define T70_MAX_INSTANCE_SIZE		8
static spt_dynamicconfigurationcontroller_t70_config_t obj_dynamic_config_controller_t70[TOUCH_MODE_MAX_NUM][T70_MAX_INSTANCE_SIZE] = {
	// mode - 0
	{
		{
			.ctrl      = 3,		/* T70-0_CTRL */		
			.event     = 24,	/* T70-0_EVENT */		
			.objtype   = 100,	/* T70-0_OBJTYPE */	
			.reserved  = 0,		/* T70-0_RESERVED */	
			.objinst   = 0,		/* T70-0_OBJINST */	
			.dstoffset = 7,		/* T70-0_DSTOFFSET */	
			.srcoffset = 0,		/* T70-0_SRCOFFSET */	
			.length    = 5,		/* T70-0_LENGTH */			    
		},
		{
			.ctrl      = 3,		/* T70-1_CTRL */		
			.event     = 26,	/* T70-1_EVENT */		
			.objtype   = 100,	/* T70-1_OBJTYPE */	
			.reserved  = 0,		/* T70-1_RESERVED */	
			.objinst   = 0,		/* T70-1_OBJINST */	
			.dstoffset = 7,		/* T70-1_DSTOFFSET */	
			.srcoffset = 0,		/* T70-1_SRCOFFSET */	
			.length    = 5,		/* T70-1_LENGTH */			    
		},
		{
			.ctrl      = 3,		/* T70-2_CTRL */		
			.event     = 21,	/* T70-2_EVENT */		
			.objtype   = 100,	/* T70-2_OBJTYPE */	
			.reserved  = 0,		/* T70-2_RESERVED */	
			.objinst   = 0,		/* T70-2_OBJINST */	
			.dstoffset = 7,		/* T70-2_DSTOFFSET */	
			.srcoffset = 6,		/* T70-2_SRCOFFSET */	
			.length    = 5,		/* T70-2_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-3_CTRL */		
			.event     = 0,		/* T70-3_EVENT */		
			.objtype   = 0,		/* T70-3_OBJTYPE */	
			.reserved  = 0,		/* T70-3_RESERVED */	
			.objinst   = 0,		/* T70-3_OBJINST */	
			.dstoffset = 0,		/* T70-3_DSTOFFSET */	
			.srcoffset = 0,		/* T70-3_SRCOFFSET */	
			.length    = 0,		/* T70-3_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-4_CTRL */		
			.event     = 0,		/* T70-4_EVENT */		
			.objtype   = 0,		/* T70-4_OBJTYPE */	
			.reserved  = 0,		/* T70-4_RESERVED */	
			.objinst   = 0,		/* T70-4_OBJINST */	
			.dstoffset = 0,		/* T70-4_DSTOFFSET */	
			.srcoffset = 0,		/* T70-4_SRCOFFSET */	
			.length    = 0,		/* T70-4_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-5_CTRL */		
			.event     = 0,		/* T70-5_EVENT */		
			.objtype   = 0,		/* T70-5_OBJTYPE */	
			.reserved  = 0,		/* T70-5_RESERVED */	
			.objinst   = 0,		/* T70-5_OBJINST */	
			.dstoffset = 0,		/* T70-5_DSTOFFSET */	
			.srcoffset = 0,		/* T70-5_SRCOFFSET */	
			.length    = 0,		/* T70-5_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-6_CTRL */		
			.event     = 0,		/* T70-6_EVENT */		
			.objtype   = 0,		/* T70-6_OBJTYPE */	
			.reserved  = 0,		/* T70-6_RESERVED */	
			.objinst   = 0,		/* T70-6_OBJINST */	
			.dstoffset = 0,		/* T70-6_DSTOFFSET */	
			.srcoffset = 0,		/* T70-6_SRCOFFSET */	
			.length    = 0,		/* T70-6_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-7_CTRL */		
			.event     = 0,		/* T70-7_EVENT */		
			.objtype   = 0,		/* T70-7_OBJTYPE */	
			.reserved  = 0,		/* T70-7_RESERVED */	
			.objinst   = 0,		/* T70-7_OBJINST */	
			.dstoffset = 0,		/* T70-7_DSTOFFSET */	
			.srcoffset = 0,		/* T70-7_SRCOFFSET */	
			.length    = 0,		/* T70-7_LENGTH */			    
		},	
	},
	// mode - 1
	{
		{
			.ctrl      = 3,				/* T70-0_CTRL */		
			.event     = 24,		/* T70-0_EVENT */		
			.objtype   = 100,		/* T70-0_OBJTYPE */	
			.reserved  = 0,				/* T70-0_RESERVED */	
			.objinst   = 0,				/* T70-0_OBJINST */	
			.dstoffset = 7,				/* T70-0_DSTOFFSET */	
			.srcoffset = 0,				/* T70-0_SRCOFFSET */	
			.length    = 5,				/* T70-0_LENGTH */			    
		},				 
		{				 
			.ctrl      = 3,				/* T70-1_CTRL */		
			.event     = 26,		/* T70-1_EVENT */		
			.objtype   = 100,		/* T70-1_OBJTYPE */	
			.reserved  = 0,				/* T70-1_RESERVED */	
			.objinst   = 0,				/* T70-1_OBJINST */	
			.dstoffset = 7,				/* T70-1_DSTOFFSET */	
			.srcoffset = 0,				/* T70-1_SRCOFFSET */	
			.length    = 5,				/* T70-1_LENGTH */			    
		},				 
		{				 
			.ctrl      = 3,				/* T70-2_CTRL */		
			.event     = 21,		/* T70-2_EVENT */		
			.objtype   = 100,		/* T70-2_OBJTYPE */	
			.reserved  = 0,				/* T70-2_RESERVED */	
			.objinst   = 0,				/* T70-2_OBJINST */	
			.dstoffset = 7,				/* T70-2_DSTOFFSET */	
			.srcoffset = 6,				/* T70-2_SRCOFFSET */	
			.length    = 5,				/* T70-2_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-3_CTRL */		
			.event     = 0,		/* T70-3_EVENT */		
			.objtype   = 0,		/* T70-3_OBJTYPE */	
			.reserved  = 0,		/* T70-3_RESERVED */	
			.objinst   = 0,		/* T70-3_OBJINST */	
			.dstoffset = 0,		/* T70-3_DSTOFFSET */	
			.srcoffset = 0,		/* T70-3_SRCOFFSET */	
			.length    = 0,		/* T70-3_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-4_CTRL */		
			.event     = 0,		/* T70-4_EVENT */		
			.objtype   = 0,		/* T70-4_OBJTYPE */	
			.reserved  = 0,		/* T70-4_RESERVED */	
			.objinst   = 0,		/* T70-4_OBJINST */	
			.dstoffset = 0,		/* T70-4_DSTOFFSET */	
			.srcoffset = 0,		/* T70-4_SRCOFFSET */	
			.length    = 0,		/* T70-4_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-5_CTRL */		
			.event     = 0,		/* T70-5_EVENT */		
			.objtype   = 0,		/* T70-5_OBJTYPE */	
			.reserved  = 0,		/* T70-5_RESERVED */	
			.objinst   = 0,		/* T70-5_OBJINST */	
			.dstoffset = 0,		/* T70-5_DSTOFFSET */	
			.srcoffset = 0,		/* T70-5_SRCOFFSET */	
			.length    = 0,		/* T70-5_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-6_CTRL */		
			.event     = 0,		/* T70-6_EVENT */		
			.objtype   = 0,		/* T70-6_OBJTYPE */	
			.reserved  = 0,		/* T70-6_RESERVED */	
			.objinst   = 0,		/* T70-6_OBJINST */	
			.dstoffset = 0,		/* T70-6_DSTOFFSET */	
			.srcoffset = 0,		/* T70-6_SRCOFFSET */	
			.length    = 0,		/* T70-6_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-7_CTRL */		
			.event     = 0,		/* T70-7_EVENT */		
			.objtype   = 0,		/* T70-7_OBJTYPE */	
			.reserved  = 0,		/* T70-7_RESERVED */	
			.objinst   = 0,		/* T70-7_OBJINST */	
			.dstoffset = 0,		/* T70-7_DSTOFFSET */	
			.srcoffset = 0,		/* T70-7_SRCOFFSET */	
			.length    = 0,		/* T70-7_LENGTH */			    
		},	
	},
	// mode - 2
	{
		{
			.ctrl      = 3,				/* T70-0_CTRL */		
			.event     = 24,		/* T70-0_EVENT */		
			.objtype   = 100,		/* T70-0_OBJTYPE */	
			.reserved  = 0,				/* T70-0_RESERVED */	
			.objinst   = 0,				/* T70-0_OBJINST */	
			.dstoffset = 7,				/* T70-0_DSTOFFSET */	
			.srcoffset = 0,				/* T70-0_SRCOFFSET */	
			.length    = 5,				/* T70-0_LENGTH */			    
		},				 
		{				 
			.ctrl      = 3,				/* T70-1_CTRL */		
			.event     = 26,		/* T70-1_EVENT */		
			.objtype   = 100,		/* T70-1_OBJTYPE */	
			.reserved  = 0,				/* T70-1_RESERVED */	
			.objinst   = 0,				/* T70-1_OBJINST */	
			.dstoffset = 7,				/* T70-1_DSTOFFSET */	
			.srcoffset = 0,				/* T70-1_SRCOFFSET */	
			.length    = 5,				/* T70-1_LENGTH */			    
		},				 
		{				 
			.ctrl      = 3,				/* T70-2_CTRL */		
			.event     = 21,		/* T70-2_EVENT */		
			.objtype   = 100,		/* T70-2_OBJTYPE */	
			.reserved  = 0,				/* T70-2_RESERVED */	
			.objinst   = 0,				/* T70-2_OBJINST */	
			.dstoffset = 7,				/* T70-2_DSTOFFSET */	
			.srcoffset = 6,				/* T70-2_SRCOFFSET */	
			.length    = 5,				/* T70-2_LENGTH */			    
		},
	{
			.ctrl      = 0,		/* T70-3_CTRL */		
			.event     = 0,		/* T70-3_EVENT */		
			.objtype   = 0,		/* T70-3_OBJTYPE */	
			.reserved  = 0,		/* T70-3_RESERVED */	
			.objinst   = 0,		/* T70-3_OBJINST */	
			.dstoffset = 0,		/* T70-3_DSTOFFSET */	
			.srcoffset = 0,		/* T70-3_SRCOFFSET */	
			.length    = 0,		/* T70-3_LENGTH */			    
	},				        
	{
			.ctrl      = 0,		/* T70-4_CTRL */		
			.event     = 0,		/* T70-4_EVENT */		
			.objtype   = 0,		/* T70-4_OBJTYPE */	
			.reserved  = 0,		/* T70-4_RESERVED */	
			.objinst   = 0,		/* T70-4_OBJINST */	
			.dstoffset = 0,		/* T70-4_DSTOFFSET */	
			.srcoffset = 0,		/* T70-4_SRCOFFSET */	
			.length    = 0,		/* T70-4_LENGTH */			    
	},
	{
			.ctrl      = 0,		/* T70-5_CTRL */		
			.event     = 0,		/* T70-5_EVENT */		
			.objtype   = 0,		/* T70-5_OBJTYPE */	
			.reserved  = 0,		/* T70-5_RESERVED */	
			.objinst   = 0,		/* T70-5_OBJINST */	
			.dstoffset = 0,		/* T70-5_DSTOFFSET */	
			.srcoffset = 0,		/* T70-5_SRCOFFSET */	
			.length    = 0,		/* T70-5_LENGTH */			    
	},
		{
			.ctrl      = 0,		/* T70-6_CTRL */		
			.event     = 0,		/* T70-6_EVENT */		
			.objtype   = 0,		/* T70-6_OBJTYPE */	
			.reserved  = 0,		/* T70-6_RESERVED */	
			.objinst   = 0,		/* T70-6_OBJINST */	
			.dstoffset = 0,		/* T70-6_DSTOFFSET */	
			.srcoffset = 0,		/* T70-6_SRCOFFSET */	
			.length    = 0,		/* T70-6_LENGTH */			    
		},
		{
			.ctrl      = 0,		/* T70-7_CTRL */		
			.event     = 0,		/* T70-7_EVENT */		
			.objtype   = 0,		/* T70-7_OBJTYPE */	
			.reserved  = 0,		/* T70-7_RESERVED */	
			.objinst   = 0,		/* T70-7_OBJINST */	
			.dstoffset = 0,		/* T70-7_DSTOFFSET */	
			.srcoffset = 0,		/* T70-7_SRCOFFSET */	
			.length    = 0,		/* T70-7_LENGTH */			    
		},	
	},
};

/* SPT_DYNAMICCONFIGURATIONCONTAINER_T71 */
static spt_dynamicconfigurationcontainer_t71_config_t obj_dynamic_config_container_t71[TOUCH_MODE_MAX_NUM] = 
{
	{
		.data[0] =  128,	/* T71-Data [0]*/
		.data[1] =  0,		/* T71-Data [1]*/
		.data[2] =  30,		/* T71-Data [2]*/
		.data[3] =  0,		/* T71-Data [3]*/
		.data[4] =  30,		/* T71-Data [4]*/
		.data[5] =  248,	/* T71-Data [5]*/
		.data[6] =  136,	/* T71-Data [6]*/
		.data[7] =  0,		/* T71-Data [7]*/
		.data[8] =  30,		/* T71-Data [8]*/
		.data[9] =  0,		/* T71-Data [9]*/
		.data[10] = 5,		/* T71-Data [10]*/
		.data[11] = 252,	/* T71-Data [11]*/
		.data[12] = 0,		/* T71-Data [12]*/
	},	
	{
		.data[0] =  128,	/* T71-Data [0]*/
		.data[1] =  0,		/* T71-Data [1]*/
		.data[2] =  30,		/* T71-Data [2]*/
		.data[3] =  0,		/* T71-Data [3]*/
		.data[4] =  30,		/* T71-Data [4]*/
		.data[5] =  248,	/* T71-Data [5]*/
		.data[6] =  136,	/* T71-Data [6]*/
		.data[7] =  0,		/* T71-Data [7]*/
		.data[8] =  30,		/* T71-Data [8]*/
		.data[9] =  0,		/* T71-Data [9]*/
		.data[10] = 5,		/* T71-Data [10]*/
		.data[11] = 252,	/* T71-Data [11]*/
		.data[12] = 0,		/* T71-Data [12]*/
	},
	{
		.data[0] =  128,	/* T71-Data [0]*/
		.data[1] =  0,		/* T71-Data [1]*/
		.data[2] =  30,		/* T71-Data [2]*/
		.data[3] =  0,		/* T71-Data [3]*/
		.data[4] =  30,		/* T71-Data [4]*/
		.data[5] =  248,	/* T71-Data [5]*/
		.data[6] =  136,	/* T71-Data [6]*/
		.data[7] =  0,		/* T71-Data [7]*/
		.data[8] =  30,		/* T71-Data [8]*/
		.data[9] =  0,		/* T71-Data [9]*/
		.data[10] = 5,		/* T71-Data [10]*/
		.data[11] = 252,	/* T71-Data [11]*/
		.data[12] = 0,		/* T71-Data [12]*/
	},
};
//-- p11309

/* PROCG_NOISESUPPRESSION_T72  */
static procg_noisesuppression_t72_config_t obj_mxt_charger_t72[TOUCH_MODE_MAX_NUM] = {
	{	// mode 0
		.ctrl           = 254, /* T72_CTRL */			
		.calcfg1        = 0,   /* T72_CALCFG1 */		
		.cfg1           = 0,   /* T72_CFG1 */			
		.cfg2           = 17,  /* T72_CFG2 */			
		.reserved_0     = 0,   /* T72_DEBUGCFG */ 		
		.hopcnt         = 20,  /* T72_HOPCNT */ 		
		.hopcntper      = 10,  /* T72_HOPCNTPER */     
		.hopevalto      = 5,   /* T72_HOPEVALTO */     
		.hopst          = 2,   /* T72_HOPST */			
		.nlgaindualx    = 48,  /* T72_NLGAINDUALX */	
		.minnlthr       = 25,   /* T72_MINNLTHR */		
		.incnlthr       = 25,   /* T72_INCNLTHR */		
		.fallnlthr      = 4,   /* T72_FALLNLTHR */		
		.nlthrmargin    = 3,   /* T72_NLTHRMARGIN */	
		.minthradj      = 32,  /* T72_MINTHRADJ */		
		.nlthrlimit     = 40,  /* T72_NLTHRLIMIT */	
		.reserved_1     = 13,  /* T72_BGSCAN */        
		.nlgainsingx    = 80,  /* T72_NLGAINSINGX */   
		.blknlthr       = 0,   /* T72_BLKNLTHR */		
		.reserved_2     = 0,   /* T72_RESERVED */		
		.stabctrl       = 0,   /* T72_STABCTRL */		
		.stabfreq_0     = 1,  /* T72_STABFREQ_0 */	
		.stabfreq_1     = 5,  /* T72_STABFREQ_1 */	
		.stabfreq_2     = 7, /* T72_STABFREQ_2 */	
		.stabfreq_3     = 45,  /* T72_STABFREQ_3 */	
		.stabfreq_4     = 49, /* T72_STABFREQ_4 */	
		.stabtchapx_0   = 40,  /* T72_STABTCHAPX_0 */	
		.stabtchapx_1   = 40,  /* T72_STABTCHAPX_1 */	
		.stabtchapx_2   = 40,  /* T72_STABTCHAPX_2 */	
		.stabtchapx_3   = 40,  /* T72_STABTCHAPX_3 */	
		.stabtchapx_4   = 40,  /* T72_STABTCHAPX_4 */	
		.stabnotchapx_0 = 32,  /* T72_STABNOTCHAPX_0 */
		.stabnotchapx_1 = 32,  /* T72_STABNOTCHAPX_1 */
		.stabnotchapx_2 = 32,  /* T72_STABNOTCHAPX_2 */
		.stabnotchapx_3 = 32,  /* T72_STABNOTCHAPX_3 */
		.stabnotchapx_4 = 32,   /* T72_STABNOTCHAPX_4 */
		.reserved_3     = 0,   /* T72_STABPC */		
		.reserved_4     = 0,   /* T72_STABLOWNLTHR */		
		.stabhighnlthr  = 4,   /* T72_STABHIGHNLTHR */	
		.reserved_5     = 0,  /* T72_STABCNT */		
		.noisctrl       = 15,  /* T72_NOISCTRL */		
		.noisfreq_0     = 1,  /* T72_NOISFREQ_0 */	
		.noisfreq_1     = 2,  /* T72_NOISFREQ_1 */	
		.noisfreq_2     = 5, /* T72_NOISFREQ_2 */	
		.noisfreq_3     = 6,  /* T72_NOISFREQ_3 */	
		.noisfreq_4     = 7, /* T72_NOISFREQ_4 */	
		.noistchapx_0   = 52,  /* T72_NOISTCHAPX_0 */	
		.noistchapx_1   = 52,  /* T72_NOISTCHAPX_1 */	
		.noistchapx_2   = 52,  /* T72_NOISTCHAPX_2 */	
		.noistchapx_3   = 52,  /* T72_NOISTCHAPX_3 */	
		.noistchapx_4   = 52,  /* T72_NOISTCHAPX_4 */	
		.noisnotchapx_0 = 52,  /* T72_NOISNOTCHAPX_0 */
		.noisnotchapx_1 = 52,  /* T72_NOISNOTCHAPX_1 */
		.noisnotchapx_2 = 52,  /* T72_NOISNOTCHAPX_2 */
		.noisnotchapx_3 = 52,  /* T72_NOISNOTCHAPX_3 */
		.noisnotchapx_4 = 52,   /* T72_NOISNOTCHAPX_4 */
		.reserved_6     = 0,   /* T72_NOISPC */		
		.noislownlthr   = 5,   /* T72_NOISLOWNLTHR */	
		.noishighnlthr  = 14,  /* T72_NOISHIGHNLTHR */	
		.noiscnt        = 0,   /* T72_NOISCNT */		
		.vnoictrl       = 15,  /* T72_VNOICTRL */		
		.vnoifreq_0     = 11,  /* T72_VNOIFREQ_0 */	
		.vnoifreq_1     = 14,  /* T72_VNOIFREQ_1 */	
		.vnoifreq_2     = 29, /* T72_VNOIFREQ_2 */	
		.vnoifreq_3     = 44,  /* T72_VNOIFREQ_3 */	
		.vnoifreq_4     = 48, /* T72_VNOIFREQ_4 */	
		.vnoitchapx_0   = 63,  /* T72_VNOITCHAPX_0 */	
		.vnoitchapx_1   = 63,  /* T72_VNOITCHAPX_1 */	
		.vnoitchapx_2   = 63,  /* T72_VNOITCHAPX_2 */	
		.vnoitchapx_3   = 63,  /* T72_VNOITCHAPX_3 */	
		.vnoitchapx_4   = 63,  /* T72_VNOITCHAPX_4 */	
		.vnoinotchapx_0 = 48,  /* T72_VNOINOTCHAPX_0 */
		.vnoinotchapx_1 = 48,  /* T72_VNOINOTCHAPX_1 */
		.vnoinotchapx_2 = 48,  /* T72_VNOINOTCHAPX_2 */
		.vnoinotchapx_3 = 48,  /* T72_VNOINOTCHAPX_3 */
		.vnoinotchapx_4 = 48,  /* T72_VNOINOTCHAPX_4 */
		.reserved_7     = 0,   /* T72_VNOIPC */		
		.vnoilownlthr   = 15,  /* T72_VNOILOWNLTHR */	
		.reserved_8     = 0,   /* T72_VNOIHIGHNLTHR */		
		.vnoicnt        = 52,  /* T72_VNOICNT */		
	},
	{	// mode 0
		.ctrl           = 254, /* T72_CTRL */			
		.calcfg1        = 0,   /* T72_CALCFG1 */		
		.cfg1           = 0,   /* T72_CFG1 */			
		.cfg2           = 17,  /* T72_CFG2 */			
		.reserved_0     = 0,   /* T72_DEBUGCFG */ 		
		.hopcnt         = 20,  /* T72_HOPCNT */ 		
		.hopcntper      = 10,  /* T72_HOPCNTPER */     
		.hopevalto      = 5,   /* T72_HOPEVALTO */     
		.hopst          = 2,   /* T72_HOPST */			
		.nlgaindualx    = 48,  /* T72_NLGAINDUALX */	
		.minnlthr       = 25,   /* T72_MINNLTHR */		
		.incnlthr       = 25,   /* T72_INCNLTHR */		
		.fallnlthr      = 4,   /* T72_FALLNLTHR */		
		.nlthrmargin    = 3,   /* T72_NLTHRMARGIN */	
		.minthradj      = 32,  /* T72_MINTHRADJ */		
		.nlthrlimit     = 40,  /* T72_NLTHRLIMIT */	
		.reserved_1     = 13,  /* T72_BGSCAN */        
		.nlgainsingx    = 80,  /* T72_NLGAINSINGX */   
		.blknlthr       = 0,   /* T72_BLKNLTHR */		
		.reserved_2     = 0,   /* T72_RESERVED */		
		.stabctrl       = 0,   /* T72_STABCTRL */		
		.stabfreq_0     = 1,  /* T72_STABFREQ_0 */	
		.stabfreq_1     = 5,  /* T72_STABFREQ_1 */	
		.stabfreq_2     = 7, /* T72_STABFREQ_2 */	
		.stabfreq_3     = 45,  /* T72_STABFREQ_3 */	
		.stabfreq_4     = 49, /* T72_STABFREQ_4 */	
		.stabtchapx_0   = 40,  /* T72_STABTCHAPX_0 */	
		.stabtchapx_1   = 40,  /* T72_STABTCHAPX_1 */	
		.stabtchapx_2   = 40,  /* T72_STABTCHAPX_2 */	
		.stabtchapx_3   = 40,  /* T72_STABTCHAPX_3 */	
		.stabtchapx_4   = 40,  /* T72_STABTCHAPX_4 */	
		.stabnotchapx_0 = 32,  /* T72_STABNOTCHAPX_0 */
		.stabnotchapx_1 = 32,  /* T72_STABNOTCHAPX_1 */
		.stabnotchapx_2 = 32,  /* T72_STABNOTCHAPX_2 */
		.stabnotchapx_3 = 32,  /* T72_STABNOTCHAPX_3 */
		.stabnotchapx_4 = 32,   /* T72_STABNOTCHAPX_4 */
		.reserved_3     = 0,   /* T72_STABPC */		
		.reserved_4     = 0,   /* T72_STABLOWNLTHR */		
		.stabhighnlthr  = 4,   /* T72_STABHIGHNLTHR */	
		.reserved_5     = 0,  /* T72_STABCNT */		
		.noisctrl       = 15,  /* T72_NOISCTRL */		
		.noisfreq_0     = 1,  /* T72_NOISFREQ_0 */	
		.noisfreq_1     = 2,  /* T72_NOISFREQ_1 */	
		.noisfreq_2     = 5, /* T72_NOISFREQ_2 */	
		.noisfreq_3     = 6,  /* T72_NOISFREQ_3 */	
		.noisfreq_4     = 7, /* T72_NOISFREQ_4 */	
		.noistchapx_0   = 52,  /* T72_NOISTCHAPX_0 */	
		.noistchapx_1   = 52,  /* T72_NOISTCHAPX_1 */	
		.noistchapx_2   = 52,  /* T72_NOISTCHAPX_2 */	
		.noistchapx_3   = 52,  /* T72_NOISTCHAPX_3 */	
		.noistchapx_4   = 52,  /* T72_NOISTCHAPX_4 */	
		.noisnotchapx_0 = 52,  /* T72_NOISNOTCHAPX_0 */
		.noisnotchapx_1 = 52,  /* T72_NOISNOTCHAPX_1 */
		.noisnotchapx_2 = 52,  /* T72_NOISNOTCHAPX_2 */
		.noisnotchapx_3 = 52,  /* T72_NOISNOTCHAPX_3 */
		.noisnotchapx_4 = 52,   /* T72_NOISNOTCHAPX_4 */
		.reserved_6     = 0,   /* T72_NOISPC */		
		.noislownlthr   = 5,   /* T72_NOISLOWNLTHR */	
		.noishighnlthr  = 14,  /* T72_NOISHIGHNLTHR */	
		.noiscnt        = 0,   /* T72_NOISCNT */		
		.vnoictrl       = 15,  /* T72_VNOICTRL */		
		.vnoifreq_0     = 11,  /* T72_VNOIFREQ_0 */	
		.vnoifreq_1     = 14,  /* T72_VNOIFREQ_1 */	
		.vnoifreq_2     = 29, /* T72_VNOIFREQ_2 */	
		.vnoifreq_3     = 44,  /* T72_VNOIFREQ_3 */	
		.vnoifreq_4     = 48, /* T72_VNOIFREQ_4 */	
		.vnoitchapx_0   = 63,  /* T72_VNOITCHAPX_0 */	
		.vnoitchapx_1   = 63,  /* T72_VNOITCHAPX_1 */	
		.vnoitchapx_2   = 63,  /* T72_VNOITCHAPX_2 */	
		.vnoitchapx_3   = 63,  /* T72_VNOITCHAPX_3 */	
		.vnoitchapx_4   = 63,  /* T72_VNOITCHAPX_4 */	
		.vnoinotchapx_0 = 48,  /* T72_VNOINOTCHAPX_0 */
		.vnoinotchapx_1 = 48,  /* T72_VNOINOTCHAPX_1 */
		.vnoinotchapx_2 = 48,  /* T72_VNOINOTCHAPX_2 */
		.vnoinotchapx_3 = 48,  /* T72_VNOINOTCHAPX_3 */
		.vnoinotchapx_4 = 48,  /* T72_VNOINOTCHAPX_4 */
		.reserved_7     = 0,   /* T72_VNOIPC */		
		.vnoilownlthr   = 15,  /* T72_VNOILOWNLTHR */	
		.reserved_8     = 0,   /* T72_VNOIHIGHNLTHR */		
		.vnoicnt        = 52,  /* T72_VNOICNT */		
	},
	{	// mode 0
		.ctrl           = 254, /* T72_CTRL */			
		.calcfg1        = 0,   /* T72_CALCFG1 */		
		.cfg1           = 0,   /* T72_CFG1 */			
		.cfg2           = 17,  /* T72_CFG2 */			
		.reserved_0     = 0,   /* T72_DEBUGCFG */ 		
		.hopcnt         = 20,  /* T72_HOPCNT */ 		
		.hopcntper      = 10,  /* T72_HOPCNTPER */     
		.hopevalto      = 5,   /* T72_HOPEVALTO */     
		.hopst          = 2,   /* T72_HOPST */			
		.nlgaindualx    = 48,  /* T72_NLGAINDUALX */	
		.minnlthr       = 25,   /* T72_MINNLTHR */		
		.incnlthr       = 25,   /* T72_INCNLTHR */		
		.fallnlthr      = 4,   /* T72_FALLNLTHR */		
		.nlthrmargin    = 3,   /* T72_NLTHRMARGIN */	
		.minthradj      = 32,  /* T72_MINTHRADJ */		
		.nlthrlimit     = 40,  /* T72_NLTHRLIMIT */	
		.reserved_1     = 13,  /* T72_BGSCAN */        
		.nlgainsingx    = 80,  /* T72_NLGAINSINGX */   
		.blknlthr       = 0,   /* T72_BLKNLTHR */		
		.reserved_2     = 0,   /* T72_RESERVED */		
		.stabctrl       = 0,   /* T72_STABCTRL */		
		.stabfreq_0     = 1,  /* T72_STABFREQ_0 */	
		.stabfreq_1     = 5,  /* T72_STABFREQ_1 */	
		.stabfreq_2     = 7, /* T72_STABFREQ_2 */	
		.stabfreq_3     = 45,  /* T72_STABFREQ_3 */	
		.stabfreq_4     = 49, /* T72_STABFREQ_4 */	
		.stabtchapx_0   = 40,  /* T72_STABTCHAPX_0 */	
		.stabtchapx_1   = 40,  /* T72_STABTCHAPX_1 */	
		.stabtchapx_2   = 40,  /* T72_STABTCHAPX_2 */	
		.stabtchapx_3   = 40,  /* T72_STABTCHAPX_3 */	
		.stabtchapx_4   = 40,  /* T72_STABTCHAPX_4 */	
		.stabnotchapx_0 = 32,  /* T72_STABNOTCHAPX_0 */
		.stabnotchapx_1 = 32,  /* T72_STABNOTCHAPX_1 */
		.stabnotchapx_2 = 32,  /* T72_STABNOTCHAPX_2 */
		.stabnotchapx_3 = 32,  /* T72_STABNOTCHAPX_3 */
		.stabnotchapx_4 = 32,   /* T72_STABNOTCHAPX_4 */
		.reserved_3     = 0,   /* T72_STABPC */		
		.reserved_4     = 0,   /* T72_STABLOWNLTHR */		
		.stabhighnlthr  = 4,   /* T72_STABHIGHNLTHR */	
		.reserved_5     = 0,  /* T72_STABCNT */		
		.noisctrl       = 15,  /* T72_NOISCTRL */		
		.noisfreq_0     = 1,  /* T72_NOISFREQ_0 */	
		.noisfreq_1     = 2,  /* T72_NOISFREQ_1 */	
		.noisfreq_2     = 5, /* T72_NOISFREQ_2 */	
		.noisfreq_3     = 6,  /* T72_NOISFREQ_3 */	
		.noisfreq_4     = 7, /* T72_NOISFREQ_4 */	
		.noistchapx_0   = 52,  /* T72_NOISTCHAPX_0 */	
		.noistchapx_1   = 52,  /* T72_NOISTCHAPX_1 */	
		.noistchapx_2   = 52,  /* T72_NOISTCHAPX_2 */	
		.noistchapx_3   = 52,  /* T72_NOISTCHAPX_3 */	
		.noistchapx_4   = 52,  /* T72_NOISTCHAPX_4 */	
		.noisnotchapx_0 = 52,  /* T72_NOISNOTCHAPX_0 */
		.noisnotchapx_1 = 52,  /* T72_NOISNOTCHAPX_1 */
		.noisnotchapx_2 = 52,  /* T72_NOISNOTCHAPX_2 */
		.noisnotchapx_3 = 52,  /* T72_NOISNOTCHAPX_3 */
		.noisnotchapx_4 = 52,   /* T72_NOISNOTCHAPX_4 */
		.reserved_6     = 0,   /* T72_NOISPC */		
		.noislownlthr   = 5,   /* T72_NOISLOWNLTHR */	
		.noishighnlthr  = 14,  /* T72_NOISHIGHNLTHR */	
		.noiscnt        = 0,   /* T72_NOISCNT */		
		.vnoictrl       = 15,  /* T72_VNOICTRL */		
		.vnoifreq_0     = 11,  /* T72_VNOIFREQ_0 */	
		.vnoifreq_1     = 14,  /* T72_VNOIFREQ_1 */	
		.vnoifreq_2     = 29, /* T72_VNOIFREQ_2 */	
		.vnoifreq_3     = 44,  /* T72_VNOIFREQ_3 */	
		.vnoifreq_4     = 48, /* T72_VNOIFREQ_4 */	
		.vnoitchapx_0   = 63,  /* T72_VNOITCHAPX_0 */	
		.vnoitchapx_1   = 63,  /* T72_VNOITCHAPX_1 */	
		.vnoitchapx_2   = 63,  /* T72_VNOITCHAPX_2 */	
		.vnoitchapx_3   = 63,  /* T72_VNOITCHAPX_3 */	
		.vnoitchapx_4   = 63,  /* T72_VNOITCHAPX_4 */	
		.vnoinotchapx_0 = 48,  /* T72_VNOINOTCHAPX_0 */
		.vnoinotchapx_1 = 48,  /* T72_VNOINOTCHAPX_1 */
		.vnoinotchapx_2 = 48,  /* T72_VNOINOTCHAPX_2 */
		.vnoinotchapx_3 = 48,  /* T72_VNOINOTCHAPX_3 */
		.vnoinotchapx_4 = 48,  /* T72_VNOINOTCHAPX_4 */
		.reserved_7     = 0,   /* T72_VNOIPC */		
		.vnoilownlthr   = 15,  /* T72_VNOILOWNLTHR */	
		.reserved_8     = 0,   /* T72_VNOIHIGHNLTHR */		
		.vnoicnt        = 52,  /* T72_VNOICNT */		
	},
};

/* PROCI_GLOVEDETECTION_T78  */
static proci_glovedetection_t78_config_t obj_glove_detect_t78[TOUCH_MODE_MAX_NUM] = {
	{
		.ctrl         = 0,  /* T78_CTRL */
		.minarea	  = 4,	 /* T78_MINAREA */
		.confthr	  = 10,	 /* T78_CONFTHR */
		.mindist	  = 15,	 /* T78_MINDIST */
		.glovemodeto  = 0,	 /* T78_GLOVEMODETO */
		.supto		  = 2,	 /* T78_SUPTO */
		.syncsperx	  = 16,	 /* T78_SYNCSPERX */
	},
	{
		.ctrl         = 0,  /* T78_CTRL */
		.minarea	  = 4,	 /* T78_MINAREA */
		.confthr	  = 10,	 /* T78_CONFTHR */
		.mindist	  = 15,	 /* T78_MINDIST */
		.glovemodeto  = 0,	 /* T78_GLOVEMODETO */
		.supto		  = 2,	 /* T78_SUPTO */
		.syncsperx	  = 16,	 /* T78_SYNCSPERX */
	},
	{
		.ctrl         = 0,  /* T78_CTRL */
		.minarea	  = 4,	 /* T78_MINAREA */
		.confthr	  = 10,	 /* T78_CONFTHR */
		.mindist	  = 15,	 /* T78_MINDIST */
		.glovemodeto  = 0,	 /* T78_GLOVEMODETO */
		.supto		  = 2,	 /* T78_SUPTO */
		.syncsperx	  = 16,	 /* T78_SYNCSPERX */
	},
};

/* _TOUCH_MULTITOUCHSCREEN_T100 INSTANCE 0 */
static touch_multitouchscreen_t100_config_t obj_multi_touch_t100[TOUCH_MODE_MAX_NUM] = {
	{	// Mode 0
		.ctrl         = 131,   /* T100_CTRL */
		.cfg1         = 48,   /* T100_CFG1 */
		.scraux       = 0,	   /* T100_SCRAUX */
		.tchaux       = 0,	   /* T100_TCHAUX */
		.tcheventcfg  = 0,	   /* T100_TCHEVENTCFG */
		.akscfg       = 0,	   /* T100_AKSCFG */
		.numtch       = 10,	   /* T100_NUMTCH */
		.xycfg        = 136,   /* T100_XYCFG */
		.xorigin      = 0,	   /* T100_XORIGIN */
		.xsize        = 30,	   /* T100_XSIZE */
		.xpitch       = 0,	   /* T100_XPITCH */
		.xloclip      = 5,	   /* T100_XLOCLIP */
		.xhiclip      = -4,	   /* T100_XHICLIP */
		.xrange       = 2104,  /* T100_XRANGE */
		.xedgecfg     = 20,	   /* T100_XEDGECFG */
		.xedgedist    = 30,	   /* T100_XEDGEDIST */
		.dxxedgecfg   = 20,	   /* T100_DXXEDGECFG */
		.dxxedgedist  = 50,	   /* T100_DXXEDGEDIST */
		.yorigin      = 0,	   /* T100_YORIGIN */
		.ysize        = 16,	   /* T100_YSIZE */
		.ypitch       = 0,	   /* T100_YPITCH */
		.yloclip      = 25,	   /* T100_YLOCLIP */
		.yhiclip      = 18,	   /* T100_YHICLIP */
		.yrange       = 1079,  /* T100_YRANGE */
		.yedgecfg     = 20,	   /* T100_YEDGECFG */
		.yedgedist    = 30,	   /* T100_YEDGEDIST */
		.gain         = 13,	   /* T100_GAIN */
		.dxgain       = 6,	   /* T100_DXGAIN */
		.tchthr       = 100,	   /* T100_TCHTHR */
		.tchhyst      = 25,	   /* T100_TCHHYST */
		.intthr       = 80,	   /* T100_INTTHR */
		.noisesf      = 0,	   /* T100_NOISESF */
		.cutoffthr    = 0,	   /* T100_CUTOFFTHR */
		.mrgthr       = 120,	   /* T100_MRGTHR */
		.mrgthradjstr = 0,	   /* T100_MRGTHRADJSTR */
		.mrghyst      = 30,	   /* T100_MRGHYST */
		.dxthrsf      = 0,	   /* T100_DXTHRSF */
		.tchdidown    = 1,	   /* T100_TCHDIDOWN */
		.tchdiup      = 1,	   /* T100_TCHDIUP */
		.nexttchdi    = 0,	   /* T100_NEXTTCHDI */
		.reserved     = 0,	   /* T100_RESERVED */
		.jumplimit    = 8,	   /* T100_JUMPLIMIT */
		.movfilter    = 68,	   /* T100_MOVFILTER */
		.movsmooth    = 50,   /* T100_MOVSMOOTH */
		.movpred      = 48,	   /* T100_MOVPRED */
		.movhysti     = 30,	   /* T100_MOVHYSTI */
		.movhystn     = 20,	   /* T100_MOVHYSTN */
		.amplhyst     = 0,	   /* T100_AMPLHYST */
		.scrareahyst  = 0,	   /* T100_SCRAREAHYST */
		.intthrhyst   = 12,   /* T100_INTTHRHYST */
	},
	{	// Mode 0
		.ctrl         = 131,   /* T100_CTRL */
		.cfg1         = 48,   /* T100_CFG1 */
		.scraux       = 0,	   /* T100_SCRAUX */
		.tchaux       = 0,	   /* T100_TCHAUX */
		.tcheventcfg  = 0,	   /* T100_TCHEVENTCFG */
		.akscfg       = 0,	   /* T100_AKSCFG */
		.numtch       = 10,	   /* T100_NUMTCH */
		.xycfg        = 136,   /* T100_XYCFG */
		.xorigin      = 0,	   /* T100_XORIGIN */
		.xsize        = 30,	   /* T100_XSIZE */
		.xpitch       = 0,	   /* T100_XPITCH */
		.xloclip      = 5,	   /* T100_XLOCLIP */
		.xhiclip      = -4,	   /* T100_XHICLIP */
		.xrange       = 2104,  /* T100_XRANGE */
		.xedgecfg     = 20,	   /* T100_XEDGECFG */
		.xedgedist    = 30,	   /* T100_XEDGEDIST */
		.dxxedgecfg   = 20,	   /* T100_DXXEDGECFG */
		.dxxedgedist  = 50,	   /* T100_DXXEDGEDIST */
		.yorigin      = 0,	   /* T100_YORIGIN */
		.ysize        = 16,	   /* T100_YSIZE */
		.ypitch       = 0,	   /* T100_YPITCH */
		.yloclip      = 25,	   /* T100_YLOCLIP */
		.yhiclip      = 18,	   /* T100_YHICLIP */
		.yrange       = 1079,  /* T100_YRANGE */
		.yedgecfg     = 20,	   /* T100_YEDGECFG */
		.yedgedist    = 30,	   /* T100_YEDGEDIST */
		.gain         = 13,	   /* T100_GAIN */
		.dxgain       = 6,	   /* T100_DXGAIN */
		.tchthr       = 100,	   /* T100_TCHTHR */
		.tchhyst      = 25,	   /* T100_TCHHYST */
		.intthr       = 80,	   /* T100_INTTHR */
		.noisesf      = 0,	   /* T100_NOISESF */
		.cutoffthr    = 0,	   /* T100_CUTOFFTHR */
		.mrgthr       = 120,	   /* T100_MRGTHR */
		.mrgthradjstr = 0,	   /* T100_MRGTHRADJSTR */
		.mrghyst      = 30,	   /* T100_MRGHYST */
		.dxthrsf      = 0,	   /* T100_DXTHRSF */
		.tchdidown    = 1,	   /* T100_TCHDIDOWN */
		.tchdiup      = 1,	   /* T100_TCHDIUP */
		.nexttchdi    = 0,	   /* T100_NEXTTCHDI */
		.reserved     = 0,	   /* T100_RESERVED */
		.jumplimit    = 8,	   /* T100_JUMPLIMIT */
		.movfilter    = 68,	   /* T100_MOVFILTER */
		.movsmooth    = 50,   /* T100_MOVSMOOTH */
		.movpred      = 48,	   /* T100_MOVPRED */
		.movhysti     = 30,	   /* T100_MOVHYSTI */
		.movhystn     = 20,	   /* T100_MOVHYSTN */
		.amplhyst     = 0,	   /* T100_AMPLHYST */
		.scrareahyst  = 0,	   /* T100_SCRAREAHYST */
		.intthrhyst   = 12,   /* T100_INTTHRHYST */
	},
	{	// Mode 0
		.ctrl         = 131,   /* T100_CTRL */
		.cfg1         = 48,   /* T100_CFG1 */
		.scraux       = 0,	   /* T100_SCRAUX */
		.tchaux       = 0,	   /* T100_TCHAUX */
		.tcheventcfg  = 0,	   /* T100_TCHEVENTCFG */
		.akscfg       = 0,	   /* T100_AKSCFG */
		.numtch       = 10,	   /* T100_NUMTCH */
		.xycfg        = 136,   /* T100_XYCFG */
		.xorigin      = 0,	   /* T100_XORIGIN */
		.xsize        = 30,	   /* T100_XSIZE */
		.xpitch       = 0,	   /* T100_XPITCH */
		.xloclip      = 5,	   /* T100_XLOCLIP */
		.xhiclip      = -4,	   /* T100_XHICLIP */
		.xrange       = 2104,  /* T100_XRANGE */
		.xedgecfg     = 20,	   /* T100_XEDGECFG */
		.xedgedist    = 30,	   /* T100_XEDGEDIST */
		.dxxedgecfg   = 20,	   /* T100_DXXEDGECFG */
		.dxxedgedist  = 50,	   /* T100_DXXEDGEDIST */
		.yorigin      = 0,	   /* T100_YORIGIN */
		.ysize        = 16,	   /* T100_YSIZE */
		.ypitch       = 0,	   /* T100_YPITCH */
		.yloclip      = 25,	   /* T100_YLOCLIP */
		.yhiclip      = 18,	   /* T100_YHICLIP */
		.yrange       = 1079,  /* T100_YRANGE */
		.yedgecfg     = 20,	   /* T100_YEDGECFG */
		.yedgedist    = 30,	   /* T100_YEDGEDIST */
		.gain         = 13,	   /* T100_GAIN */
		.dxgain       = 6,	   /* T100_DXGAIN */
		.tchthr       = 100,	   /* T100_TCHTHR */
		.tchhyst      = 25,	   /* T100_TCHHYST */
		.intthr       = 80,	   /* T100_INTTHR */
		.noisesf      = 0,	   /* T100_NOISESF */
		.cutoffthr    = 0,	   /* T100_CUTOFFTHR */
		.mrgthr       = 120,	   /* T100_MRGTHR */
		.mrgthradjstr = 0,	   /* T100_MRGTHRADJSTR */
		.mrghyst      = 30,	   /* T100_MRGHYST */
		.dxthrsf      = 0,	   /* T100_DXTHRSF */
		.tchdidown    = 1,	   /* T100_TCHDIDOWN */
		.tchdiup      = 1,	   /* T100_TCHDIUP */
		.nexttchdi    = 0,	   /* T100_NEXTTCHDI */
		.reserved     = 0,	   /* T100_RESERVED */
		.jumplimit    = 8,	   /* T100_JUMPLIMIT */
		.movfilter    = 68,	   /* T100_MOVFILTER */
		.movsmooth    = 50,   /* T100_MOVSMOOTH */
		.movpred      = 48,	   /* T100_MOVPRED */
		.movhysti     = 30,	   /* T100_MOVHYSTI */
		.movhystn     = 20,	   /* T100_MOVHYSTN */
		.amplhyst     = 0,	   /* T100_AMPLHYST */
		.scrareahyst  = 0,	   /* T100_SCRAREAHYST */
		.intthrhyst   = 12,   /* T100_INTTHRHYST */
	},
};

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
	{      0,	 500000},	// 0V	
	{1500000,	2000000},	// 1.8V
};
#define number_of_elements(ito_table) sizeof(ito_table)/sizeof(ito_table_element)
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
		struct regulator *reg;
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
	if ( atmel_mxt_avdd.regulator.reg )
		atmel_mxt_avdd.regulator.reg = NULL;

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

	switch ( pp_ctrl.type ) {
	case POWER_NOT_USED:
		break;
	case POWER_GPIO_SETUP:			
		if ( up_down == POWER_UP ) {
			rc = gpio_request(pp_ctrl.gpio.num, pp_ctrl.name);
			if (rc) {
				gpio_free(pp_ctrl.gpio.num);				
				if (rc) {
					dbg_cr("%s: %d failed, rc=%d\n",pp_ctrl.name, pp_ctrl.gpio.num, rc);
				}
			}

			if ( pp_ctrl.gpio.direction == GPIO_INPUT ) {
				rc = gpio_direction_input(pp_ctrl.gpio.num);				
				if (rc) {
					dbg_cr("%s: %d gpio_direction_input failed, rc=%d\n",pp_ctrl.name, pp_ctrl.gpio.num, rc);
				}
			}
			else {
				rc = gpio_direction_output(pp_ctrl.gpio.num, pp_ctrl.gpio.direction);
				if (rc) {
					dbg_cr("%s: %d gpio_direction_output failed, rc=%d\n",pp_ctrl.name, pp_ctrl.gpio.num, rc);
				}
			}			
		}
		else {

			if ( pp_ctrl.gpio.direction == GPIO_OUTPUT_HIGH || pp_ctrl.gpio.direction == GPIO_OUTPUT_LOW) {				
				gpio_set_value(pp_ctrl.gpio.num, !gpio_get_value(pp_ctrl.gpio.num));
				msleep(10);
			}

			gpio_free(pp_ctrl.gpio.num);
		}		

		break;
	case POWER_PM_REGULATOR:

		if ( up_down == POWER_UP ) {

			if ( pp_ctrl.regulator.reg == NULL ) 
			{
				pp_ctrl.regulator.reg = regulator_get(NULL, pp_ctrl.name);
				if( pp_ctrl.regulator.reg == NULL ) {
					dbg_cr("%s: regulator_get failed \n", pp_ctrl.name);
					return -EINVAL;
				}

				rc = regulator_set_voltage(pp_ctrl.regulator.reg, pp_ctrl.regulator.volt, pp_ctrl.regulator.volt);
				if (rc) { 
					dbg_cr("%s: set_voltage %duV failed, rc=%d\n", pp_ctrl.name, pp_ctrl.regulator.volt, rc);
					return rc;
				}
			}

			rc = regulator_enable(pp_ctrl.regulator.reg);
			if (rc) {
				dbg_cr("%s: regulator enable failed (%d)\n", pp_ctrl.name, rc);
				return rc;
			}			
		}
		else {			

			if( pp_ctrl.regulator.reg == NULL ) {
				dbg_cr("%s: No regulator...failed \n", pp_ctrl.name);

				pp_ctrl.regulator.reg = regulator_get(NULL, pp_ctrl.name);
				if( pp_ctrl.regulator.reg == NULL ) {
					dbg_cr("%s: regulator_get failed \n", pp_ctrl.name);
					return -EINVAL;
				}

				rc = regulator_set_voltage(pp_ctrl.regulator.reg, pp_ctrl.regulator.volt, pp_ctrl.regulator.volt);
				if (rc) { 
					dbg_cr("%s: set_voltage %duV failed, rc=%d\n", pp_ctrl.name, pp_ctrl.regulator.volt, rc);
					return rc;
				}
			}

			rc = regulator_disable(pp_ctrl.regulator.reg);
			if (rc) {
				dbg_cr("%s: regulator disable failed (%d)\n", pp_ctrl.name, rc);
				return rc;
			}

			regulator_put(pp_ctrl.regulator.reg);
			pp_ctrl.regulator.reg = NULL;
		}
		break;
	}
	return 0;
}

void TSP_reset_pin_shake(void)
{
	TSP_Power_Pin_Init();

	msleep(10);
	gpio_set_value(atmel_mxt_rst.gpio.num, GPIO_OUTPUT_LOW);	
	msleep(100);
	gpio_set_value(atmel_mxt_rst.gpio.num, GPIO_OUTPUT_HIGH);	

	msleep(10);
}

int TSP_PowerOn(void)
{
	TSP_Power_Pin_Init();

	TSP_PowerSetup(atmel_mxt_rst, POWER_UP);
	TSP_PowerSetup(atmel_mxt_avdd, POWER_UP);
	TSP_PowerSetup(atmel_mxt_dvdd, POWER_UP);
	TSP_PowerSetup(atmel_mxt_vddio, POWER_UP);	
	TSP_reset_pin_shake();

	TSP_PowerSetup(atmel_mxt_int, POWER_UP);	
	
	msleep(100);

	return 0;
}

void TSP_PowerOff(void)
{
	TSP_Power_Pin_Init();

	TSP_PowerSetup(atmel_mxt_int, POWER_DOWN);
	TSP_PowerSetup(atmel_mxt_rst, POWER_DOWN);

	TSP_PowerSetup(atmel_mxt_avdd, POWER_DOWN);
	TSP_PowerSetup(atmel_mxt_dvdd, POWER_DOWN);
	TSP_PowerSetup(atmel_mxt_vddio, POWER_DOWN);
	
	msleep(100);
}
