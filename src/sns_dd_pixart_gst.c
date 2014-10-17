
/*============================================================================

                                INCLUDE FILES

============================================================================*/
#include <stdio.h>
#include "fixed_point.h"
#include "sns_ddf_attrib.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_common.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_signal.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_util.h"

#include "sns_debug_str.h"
#include "sns_debug_api.h"

#include "sns_dd_pixart_gst.h"

#define INTERRUPT 0
#define INTERRUPT_GPIO 1
#define VERSION v005

#undef printf
#define printf
/*=======================================================================

                  Preprocessor Definitions and Constants

========================================================================*/

/*=======================================================================

                   INTERNAL ENUMS

========================================================================*/

unsigned char init_sensor_register_array[][2] = {	// initial
{0xEF,0x00}, //select bank 0				
{0x37,0x07}, 
{0x38,0x17}, 
{0x39,0x06}, 
{0x46,0x2D}, 
{0x47,0x0F}, 
{0x4A,0x50}, 
{0x4C,0x20}, 
{0x5E,0x10}, 
//{0x60,0x22}, 
//{0x61,0x28}, 
{0x80,0x42}, 
{0x81,0x44}, 
{0x8B,0x01}, 
{0x90,0x06}, 
{0x95,0x0A}, 
{0x96,0x0C}, 
{0x97,0x05}, 
{0x9A,0x14}, 
{0x9C,0x3F},  
{0xA5,0x19},
{0xCC,0x19},
{0xCD,0x0B},
{0xCE,0x13},
{0xCF,0x64},
{0xD0,0x21},
{0xEF,0x01},  // select bank 1
{0x25,0x01},
{0x27,0x39},
{0x28,0x7F},
{0x29,0x09},
{0x32,0x18},
{0x33,0x18},
{0x3E,0xFF},
{0x5E,0x1D},
{0x72,0x01}, // enable PAJ7620H2
{0x73,0x35},
{0x77,0x01},
{0x7E,0x01},
};


unsigned char change_to_gesture_register_array[][2] = {	// gesture
{0xEF,0x00}, 				
{0x41, 0xFF}, //
{0x42,0x01}, 
{0x48,0xA0}, 
{0x49,0x00}, 
{0x51,0x10}, 
{0x83, 0x20}, //
{0x9f, 0xf9}, //
{0xEF,0x01}, 
{0x01,0x3C},
{0x02, 0x00},//
{0x03, 0x00},//
{0x04,0x9A},
{0x41, 0x40},//
{0x43, 0x30},//
{0x65,0x96},
{0x66, 0x00},//
{0x67,0x97}, // IDLE S1 step low 8 bit
{0x68, 0x01},// IDLE S1 step high 8 bit
{0x69,0xCD}, // ps hysteresis high threshold
{0x6A,0x01}, // ps hysteresis low threshold
{0x6b, 0xb0},// OPtoS1 step low 8 bit
{0x6c, 0x04},// OPtoS1 step high 8 bit
{0x6D,0x2C}, // S1toS2 step low 8 bit
{0x6E,0x01}, // S1toS2 step high 8 bit
{0x74, 0x00},//
};
unsigned char change_to_proximity_register_array[][2] = {
{0xEF,0x00},
{0x41,0x00},
{0x42,0x02},
{0x48,0x20},
{0x49,0x00},
{0x51,0x13},
{0x83,0x00},
{0x9F,0xF8},
{0xEF,0x01},
{0x01,0x1E},
{0x02,0x00},
{0x03,0x00},
{0x04,0x32},
{0x41,0x50},
{0x43,0x34},
{0x65,0xCE},
{0x66,0x0B},
{0x67,0xCE},// IDLE S1 step low 8 bit
{0x68,0x0B},// IDLE S1 step high 8 bit
{0x69,0xE9},// ps hysteresis high threshold
{0x6A,0x05},// ps hysteresis low threshold
{0x6B,0x50},// OPtoS1 step low 8 bit
{0x6C,0xC3},// OPtoS1 step high 8 bit
{0x6D,0x50},// S1toS2 step low 8 bit
{0x6E,0xC3},// S1toS2 step high 8 bit
{0x74,0x05},	
};
unsigned char suspend_register_array[][2] = {
{0xEF,0x01}, 
{0x72,0x00}, // disable PAJ7620H2
{0xEF,0x00},
{0x03,0x00},
};
unsigned char resume_register_array[][2] = {
{0xEF,0x01}, 
{0x72,0x01},
};

#define INIT_SENSOR_REG_ARRAY_SIZE (sizeof(init_sensor_register_array)/sizeof(init_sensor_register_array[0]))
#define CHANGE_TO_GESTURE_REG_ARRAY_SIZE (sizeof(change_to_gesture_register_array)/sizeof(change_to_gesture_register_array[0]))
#define CHANGE_TO_PROXIMITY_REG_ARRAY_SIZE (sizeof(change_to_proximity_register_array)/sizeof(change_to_proximity_register_array[0]))
#define SUSPEND_REG_ARRAY_SIZE (sizeof(suspend_register_array)/sizeof(suspend_register_array[0]))
#define RESUME_REG_ARRAY_SIZE (sizeof(resume_register_array)/sizeof(resume_register_array[0]))

/*=======================================================================

                   INTERNAL FUNCTION PROTOTYPES

========================================================================*/
static sns_ddf_status_e sns_dd_pixart_gst_init(
        sns_ddf_handle_t*        dd_handle_ptr,
        sns_ddf_handle_t         smgr_handle,
        sns_ddf_nv_params_s*     nv_params,
        sns_ddf_device_access_s  device_info[],
        uint32_t                 num_devices,
        sns_ddf_memhandler_s*    memhandler,
        sns_ddf_sensor_e*        sensors[],
        uint32_t*                num_sensors);

static sns_ddf_status_e sns_dd_pixart_gst_get_data(
        sns_ddf_handle_t        dd_handle,
        sns_ddf_sensor_e        sensors[],
        uint32_t                num_sensors,
        sns_ddf_memhandler_s*   memhandler,
        sns_ddf_sensor_data_s*  data[]);

static sns_ddf_status_e sns_dd_pixart_gst_set_attr( 
        sns_ddf_handle_t     dd_handle,
        sns_ddf_sensor_e     sensor,
        sns_ddf_attribute_e  attrib,
        void*                value);

static sns_ddf_status_e sns_dd_pixart_gst_get_attr(
        sns_ddf_handle_t       dd_handle,
        sns_ddf_sensor_e       sensor,
        sns_ddf_attribute_e    attrib,
        sns_ddf_memhandler_s*  memhandler,
        void**                 value,
        uint32_t*              num_elems);

static sns_ddf_status_e sns_dd_pixart_gst_reset(sns_ddf_handle_t dd_handle);

//static void gst_irq_handler(sns_ddf_handle_t     dd_handle,
//                       uint32_t gpio_num,
//                       sns_ddf_time_t timestamp);
static void sns_dd_pixart_gst_irq_handler(
    sns_ddf_handle_t dd_handle, 
    //sns_ddf_signal_irq_e irq);
    uint32_t gpio_num, sns_ddf_time_t timestamp);

static sns_ddf_status_e sns_dd_pixart_get_gst_data(sns_ddf_handle_t dd_handle, uint16_t *data

);
static sns_ddf_status_e sns_dd_pixart_get_proximity_data(sns_ddf_handle_t dd_handle, uint8_t *data_raw, uint32_t *proximity_binary);
//static sns_ddf_status_e sns_dd_pixart_get_gst_data(sns_ddf_handle_t dd_handle, q16_t *data);
//static sns_ddf_status_e sns_dd_pixart_get_proximity_data(sns_ddf_handle_t dd_handle, q16_t *data, uint32_t *proximity_binary);
static sns_ddf_status_e sns_dd_pixart_init_sensor(sns_ddf_handle_t dd_handle);
static sns_ddf_status_e sns_dd_pixart_change_to_proximity_mode(sns_ddf_handle_t dd_handle);
static sns_ddf_status_e sns_dd_pixart_change_to_gesture_mode(sns_ddf_handle_t dd_handle);
static sns_ddf_status_e sns_dd_pixart_suspend(sns_ddf_handle_t dd_handle);
static sns_ddf_status_e sns_dd_pixart_resume(sns_ddf_handle_t dd_handle);
static sns_ddf_status_e sns_dd_pixart_gst_set_odr(sns_ddf_handle_t dd_handle, sns_ddf_sensor_e    sensor, uint32_t odr);
static sns_ddf_status_e sns_dd_pixart_enable_sched_data(sns_ddf_handle_t  dd_handle, sns_ddf_sensor_e  sensor, bool enable);
/*=======================================================================

                   STRUCTURE DEFINITIONS

========================================================================*/
sns_ddf_driver_if_s sns_pixart_gst_driver_fn_list =
{
  &sns_dd_pixart_gst_init,
  &sns_dd_pixart_gst_get_data,
  &sns_dd_pixart_gst_set_attr,
  &sns_dd_pixart_gst_get_attr,
  NULL, /* handle timer */
#if INTERRUPT == 1
  &sns_dd_pixart_gst_irq_handler,
#else
  NULL, /* handle irq */
#endif  
  &sns_dd_pixart_gst_reset,
  NULL, /* self test */ 
#if INTERRUPT == 1
	&sns_dd_pixart_enable_sched_data
#endif  
};

/* State struct for pixart_gst driver */
typedef struct {
   sns_ddf_handle_t smgr_hndl;    /* SDDI handle used to notify_data */
   sns_ddf_handle_t port_handle; /* handle used to access the I2C bus */
   uint32_t gst_odr ;
   uint32_t prox_odr ;
   sns_ddf_sensor_e op_mode ;
   sns_ddf_sensor_data_s  sensor_data; /*for DRI*/
   uint8_t gst_int_enable ;
   uint8_t prox_int_enable ;   
   uint32_t interrupt_gpio;
} sns_dd_pixart_gst_state_t;


/*============================================================================

  Global Data Definitions

 ============================================================================*/

static sns_ddf_sensor_e my_sensors[] = 
  {
	SNS_DDF_SENSOR_IR_GESTURE,
    SNS_DDF_SENSOR_PROXIMITY 
  };

static int init_status = 0;
static int loop_check = 0;

/*===========================================================================

  FUNCTION:   sns_dd_pixart_get_gst_data

===========================================================================*/
/*=========================================================================*/
static sns_ddf_status_e sns_dd_pixart_get_gst_data(sns_ddf_handle_t dd_handle, uint16_t *data_raw)
//static sns_ddf_status_e sns_dd_pixart_get_gst_data(sns_ddf_handle_t dd_handle, q16_t *data)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
  sns_ddf_status_e stat ;
  uint8_t reg[2], out ;  
  
  reg[0] = 0 ;
  if ( (stat = sns_ddf_write_port(state->port_handle,
                              0xef, //bank 0
                              &reg[0],
                              1,
                              &out)) != SNS_DDF_SUCCESS) // 0xef register no 
  {
     return stat;
  } 
    
  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0x43, //INT FLAG1
                              &reg[0],
                              1,
                              &out)) != SNS_DDF_SUCCESS) // 7 gesture value
  {
     return stat;
  } 
  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0x44, //INT FLAG2 
                              &reg[1],
                              1,
                              &out)) != SNS_DDF_SUCCESS) // wave
  {
     return stat;
  }     
  
  //*data_raw = reg[1];

  *data_raw = *((uint16_t*)(&reg[0]));
  //*data = reg[1];
  //*data = (*data) << 8 | reg[0] ;
  SNS_PRINTF_STRING_ID_ERROR_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    reg[0], reg[1], *data_raw);
  printf(">>> sns_dd_pixart_get_gst_data gesture = %d\r\n", *data_raw);
  return SNS_DDF_SUCCESS;  
}
sns_ddf_status_e sns_dd_pixart_get_proximity_data(sns_ddf_handle_t dd_handle, uint8_t *data_raw, uint32_t *proximity_binary)
//static sns_ddf_status_e sns_dd_pixart_get_proximity_data(sns_ddf_handle_t dd_handle, q16_t *data, uint32_t *proximity_binary)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
  sns_ddf_status_e stat ;
  uint8_t proximity, out, int_flag = 0, approach_state  ;  
  
  proximity = 0 ;
  if ( (stat = sns_ddf_write_port(state->port_handle,
                              0xef, //bank 0
                              &proximity,
                              1,
                              &out)) != SNS_DDF_SUCCESS)
  {
     return stat;
  } 
    
  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0x44, //INT FLAG2
                              &int_flag,
                              1,
                              &out)) != SNS_DDF_SUCCESS) // 0x44 PS Gain
  {
     return stat;
  }
  printf(">>> sns_dd_pixart_get_proximity_data int_flag = %d\r\n", int_flag);
  
  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0x6B, //approach status
                              &approach_state,
                              1,
                              &out)) != SNS_DDF_SUCCESS) /*approach 1, 8 bit PS data >= PS high threshold /approach 0, 8 bit PS data <= PS low threshold  */
  {
     return stat;
  }   
  printf(">>> sns_dd_pixart_get_proximity_data approach_state = %d\r\n", approach_state);
 
  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0x6C, //PS data
                              &proximity,
                              1,
                              &out)) != SNS_DDF_SUCCESS) // 8 bit PS data
  {
     return stat;
  } 

  *data_raw = (uint8_t)proximity ;
  //*data = proximity ;
  *proximity_binary = approach_state ;
  printf(">>> sns_dd_pixart_get_proximity_data = %d\r\n", *data_raw);
  return SNS_DDF_SUCCESS;  
}
static sns_ddf_status_e sns_dd_pixart_get_cover_mode_data(sns_ddf_handle_t dd_handle, uint16_t *avg, uint16_t *obj_size)
//static sns_ddf_status_e sns_dd_pixart_get_cover_mode_data(sns_ddf_handle_t dd_handle, q16_t *avg, q16_t *obj_size)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
  sns_ddf_status_e stat ;
  uint8_t y_avg, objsize[2], out ;  
  
  y_avg = 0 ;
  if ( (stat = sns_ddf_write_port(state->port_handle,
                              0xef, //bank 0
                              &y_avg,
                              1,
                              &out)) != SNS_DDF_SUCCESS)
  {
     return stat;
  } 
    
  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0xb0, //Average
                              &y_avg,
                              1,
                              &out)) != SNS_DDF_SUCCESS)
  {
     return stat;
  } 
  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0xb1, //Object Size [7:0]
                              &objsize[0],
                              1,
                              &out)) != SNS_DDF_SUCCESS)
  {
     return stat;
  }     

  if ( (stat = sns_ddf_read_port(state->port_handle,
                              0xb2, //Object Size [11:8]
                              &objsize[1],
                              1,
                              &out)) != SNS_DDF_SUCCESS)
  {
     return stat;
  }  
  
  *avg = (uint16_t)y_avg ;
  //*avg = y_avg ;
  *obj_size = objsize[1] ;
  *obj_size = (*obj_size) << 8 | objsize[0] ;
  printf(">>> sns_dd_pixart_get_proximity_data yavg = %d, obj_size = %d\r\n", *avg, *obj_size);
  SNS_PRINTF_STRING_ID_ERROR_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
                *avg, *obj_size, 5678);
  return SNS_DDF_SUCCESS;  
}

static sns_ddf_status_e sns_dd_pixart_init_sensor(sns_ddf_handle_t dd_handle)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
	sns_ddf_status_e status;
	uint8_t out;
	int i = 0;
 
  printf(">>> sns_dd_pixart_init_sensor\r\n");
  //Initail setting      
  for(i = 0; i < INIT_SENSOR_REG_ARRAY_SIZE;i++){
    if ( (status = sns_ddf_write_port(state->port_handle,
                                init_sensor_register_array[i][0], //bank 0
                                &init_sensor_register_array[i][1],                                
                                1,
                                &out)) != SNS_DDF_SUCCESS)
    {
       return status;
    }
  }
  return SNS_DDF_SUCCESS;
}
static sns_ddf_status_e sns_dd_pixart_change_to_proximity_mode(sns_ddf_handle_t dd_handle)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
  sns_ddf_status_e status;
  uint8_t out;
  int i = 0;   
        
  printf(">>> sns_dd_pixart_change_to_proximity_mode\r\n");
  //Initail setting      
  for(i = 0; i < CHANGE_TO_PROXIMITY_REG_ARRAY_SIZE;i++){
    if ( (status = sns_ddf_write_port(state->port_handle,
                                change_to_proximity_register_array[i][0], //bank 0
                                &change_to_proximity_register_array[i][1],                                
                                1,
                                &out)) != SNS_DDF_SUCCESS)
    {
       return status;
    }
  }

  return SNS_DDF_SUCCESS;
}
static sns_ddf_status_e sns_dd_pixart_change_to_gesture_mode(sns_ddf_handle_t dd_handle)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
  sns_ddf_status_e status;
  uint8_t out;
  int i = 0;

  printf(">>> sns_dd_pixart_change_to_gesture_mode\r\n");
  //Initail setting      
  for(i = 0; i < CHANGE_TO_GESTURE_REG_ARRAY_SIZE;i++){
    if ( (status = sns_ddf_write_port(state->port_handle,
                                change_to_gesture_register_array[i][0], //bank 0
                                &change_to_gesture_register_array[i][1],                                
                                1,
                                &out)) != SNS_DDF_SUCCESS)
    {
       return status;
    }
  }
  
  return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_pixart_suspend(sns_ddf_handle_t dd_handle)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
	sns_ddf_status_e status;
	uint8_t out;
	int i = 0;

  printf(">>> sns_dd_pixart_suspend\r\n");
  //Initail setting      
  for(i = 0; i < SUSPEND_REG_ARRAY_SIZE;i++){
    if ( (status = sns_ddf_write_port(state->port_handle,
                                suspend_register_array[i][0], //bank 0
                                &suspend_register_array[i][1],                                
                                1,
                                &out)) != SNS_DDF_SUCCESS)
    {
       return status;
    }
  }
  
  state-> op_mode = SNS_DDF_SENSOR__NONE ;
 	state->gst_odr = 0 ;
 	state->prox_odr = 0 ;

  return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_pixart_resume(sns_ddf_handle_t dd_handle)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
	sns_ddf_status_e status;
	uint8_t reg, out;
	int i = 0;

  printf(">>> sns_dd_pixart_resume\r\n");
	//dummy read to wake up device	
	sns_ddf_read_port(state->port_handle,
					          0,
					          &reg,
					          1,
					          &out);    
	/*				          
	sns_ddf_read_port(state->port_handle,
					          0,
					          &reg,
					          1,
					          &out); 				
	*/				          	          
  for(i = 0; i < RESUME_REG_ARRAY_SIZE;i++){
    if ( (status = sns_ddf_write_port(state->port_handle,
                                resume_register_array[i][0], //bank 0
                                &resume_register_array[i][1],                                
                                1,
                                &out)) != SNS_DDF_SUCCESS)
    {
       return status;
    }
  }
  return SNS_DDF_SUCCESS;
}
/*===========================================================================

  FUNCTION:   sns_dd_pixart_gst_irq_handler

===========================================================================*/
/*=========================================================================*/

static void sns_dd_pixart_gst_irq_handler(sns_ddf_handle_t     dd_handle,
//                            sns_ddf_signal_irq_e irq)
                          uint32_t gpio_num,
                          sns_ddf_time_t timestamp)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;


  SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    777, 777, 777);
  if ( state->op_mode == SNS_DDF_SENSOR_IR_GESTURE)
  {
    q16_t gst = 0 ;
    q16_t y_avg = 0 ;
    q16_t obj_size = 0 ;      
	
    if(state->gst_int_enable == 0) //interrupt is not enabled
      return ;
					
    if(sns_dd_pixart_get_gst_data(dd_handle, &gst) != SNS_DDF_SUCCESS)
    {
      return ;
    }   
    if(sns_dd_pixart_get_cover_mode_data(dd_handle, &y_avg, &obj_size) != SNS_DDF_SUCCESS)
    {
      return ;
    }    
	        
    state->sensor_data.sensor = SNS_DDF_SENSOR_IR_GESTURE;
    state->sensor_data.status = SNS_DDF_SUCCESS;
    state->sensor_data.timestamp = sns_ddf_get_timestamp();		 		 
    state->sensor_data.num_samples = 3;
    state->sensor_data.samples[0].sample = FX_FLTTOFIX_Q16(gst);
    state->sensor_data.samples[0].status = SNS_DDF_SUCCESS ;
    state->sensor_data.samples[1].sample = FX_FLTTOFIX_Q16(y_avg);
    state->sensor_data.samples[1].status = SNS_DDF_SUCCESS ;
    state->sensor_data.samples[2].sample = FX_FLTTOFIX_Q16(obj_size);
    state->sensor_data.samples[2].status = SNS_DDF_SUCCESS ;
	
    sns_ddf_smgr_notify_data(state->smgr_hndl, &state->sensor_data, 1);
  }
  else
  {
    q16_t proximity = 0 ;
    uint32_t proximity_binary = 0 ;

    if(state->prox_int_enable == 0) //interrupt is not enabled
    return ;
    if(sns_dd_pixart_get_proximity_data(dd_handle, &proximity, &proximity_binary) !=  SNS_DDF_SUCCESS)
    return;

    state->sensor_data.sensor = SNS_DDF_SENSOR_PROXIMITY;
    state->sensor_data.status = SNS_DDF_SUCCESS;
    state->sensor_data.timestamp = sns_ddf_get_timestamp();
    state->sensor_data.num_samples = 1;
    state->sensor_data.samples[0].status = SNS_DDF_SUCCESS ;
    state->sensor_data.samples[0].sample = FX_FLTTOFIX_Q16(proximity);

    sns_ddf_smgr_notify_data(state->smgr_hndl, &state->sensor_data, 1);

  }
}

/*===========================================================================

  FUNCTION:   sns_dd_pixart_gst_reset

===========================================================================*/
/*=========================================================================*/
static sns_ddf_status_e sns_dd_pixart_gst_reset(sns_ddf_handle_t dd_handle)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
  sns_ddf_status_e status;
  uint8_t reg = 0 , out;
  uint32_t  reset_wait_loop;
  //TODO - RESET

  printf(">>> sns_dd_pixart_gst_reset\r\n");
  reg = 0 ;
  init_status = 5;
  SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				777, 777, 777);
  if ( (status = sns_ddf_write_port(state->port_handle,
                              0xef, //bank 0
                              &reg,
                              1,
                              &out)) != SNS_DDF_SUCCESS)
  {
  
    // return status;  IGNORe the return value becauase first operation
  }   
 
#if 0
  //reset
  reg = 1 ;
  if ( (status = sns_ddf_write_port(state->port_handle,
                              0xee,
                              &reg,
                              1,
                              &out)) != SNS_DDF_SUCCESS)
  {
     return status;
  }   
#endif    
  

    // Wait for the device to come back up
    for (reset_wait_loop = 0; reset_wait_loop < 100; reset_wait_loop++)
    {
      //uint8_t bytes_read;
      status = sns_ddf_read_port(state->port_handle,
                              0,
                              &reg,
                              1,
                              &out);
      if ( SNS_DDF_SUCCESS == status )
      {
		init_status = 6;
		loop_check = 2;
        break;
      }
      sns_ddf_delay(5000);
    }

  /*
  //read id, just for check
  if ( (status = sns_ddf_read_port(state->port_handle,
                         0,
                         &reg,
                         1,
                         &out)) != SNS_DDF_SUCCESS)
  {
    return status;
  }
   */
  printf(">>> reg0 = 0x%x\r\n", reg);  
   
   //read id, just for check
   if ( (status = sns_ddf_read_port(state->port_handle,
                         1,
                         &reg,
                         1,
                         &out)) != SNS_DDF_SUCCESS)
  {
	init_status = 7;
    return status;
  }
   
  printf(">>> reg1 = 0x%x\r\n", reg);     

  //initialize register setting
	if ( (status = sns_dd_pixart_init_sensor(dd_handle)) != SNS_DDF_SUCCESS)
  {
	init_status = 8;
    return status;
  }

	//goto suspend state
	if ( (status = sns_dd_pixart_suspend(dd_handle)) != SNS_DDF_SUCCESS)
  {
	init_status = 9;
    return status;
  }
  
    SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				888, 888, loop_check);
  return SNS_DDF_SUCCESS ;
}

/*===========================================================================

  FUNCTION:   sns_dd_pixart_gst_init

===========================================================================*/
/*=========================================================================*/                                             
static sns_ddf_status_e sns_dd_pixart_gst_init(
  sns_ddf_handle_t*        dd_handle_ptr,
  sns_ddf_handle_t         smgr_handle,
  sns_ddf_nv_params_s*     nv_params,
  sns_ddf_device_access_s  device_info[],
  uint32_t                 num_devices,
  sns_ddf_memhandler_s*    memhandler,
  sns_ddf_sensor_e*        sensors[],
  uint32_t*                num_sensors
)                                  
{                                                            
  sns_ddf_status_e stat;
  sns_dd_pixart_gst_state_t *ptr;
  
  printf(">>> sns_dd_pixart_gst_init\r\n");

  init_status = 1;
  loop_check = 1;
  
  if(sns_ddf_malloc((void **)&ptr, sizeof(sns_dd_pixart_gst_state_t)) != SNS_DDF_SUCCESS) 
  { 
	init_status = 2;
    return SNS_DDF_ENOMEM;
  }

  stat = sns_ddf_malloc((void**)&(ptr->sensor_data.samples),sizeof(sns_ddf_sensor_sample_s)*(3)); /* +1 for temperature */
  if(stat != SNS_DDF_SUCCESS){
	  init_status  = 2;
      return stat;  
  }
  ptr->smgr_hndl = smgr_handle;

  if((stat = sns_ddf_open_port(&(ptr->port_handle) , &(device_info->port_config)))!= SNS_DDF_SUCCESS)
  {
	init_status = 3;
    return stat;
  }
 
  /* Fill out supported sensor info */
  *num_sensors = 2;
  *sensors = my_sensors;
  *dd_handle_ptr = (sns_ddf_handle_t)ptr;
#if INTERRUPT == 1
  ptr->interrupt_gpio = device_info->first_gpio ;
#endif  
	ptr->gst_int_enable = 0 ;
	ptr->prox_int_enable = 0 ;
  stat = sns_dd_pixart_gst_reset(ptr);
  
  init_status = 10;
  return stat;
}

/*===========================================================================

  FUNCTION:   sns_dd_pixart_gst_set_attr

===========================================================================*/
/*=========================================================================*/
static sns_ddf_status_e sns_dd_pixart_gst_set_attr 
( 
  sns_ddf_handle_t     dd_handle,
  sns_ddf_sensor_e     sensor,
  sns_ddf_attribute_e  attrib,
  void*                value
)
{
	//TODO -
  //sns_ddf_status_e ret_val = SNS_DDF_SUCCESS;
  printf(">>> sns_dd_pixart_gst_set_attr\r\n");  
  SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    444, attrib, sensor);
  switch(attrib)
  {
    case SNS_DDF_ATTRIB_POWER_STATE:
    {
    	sns_ddf_powerstate_e *mode = (sns_ddf_powerstate_e *)value ;
		   switch (*mode)
		   {
		   case SNS_DDF_POWERSTATE_ACTIVE:
		     {
					  sns_dd_pixart_resume(dd_handle);                        	
					}		      
		      break;
		   case SNS_DDF_POWERSTATE_LOWPOWER:
		     	{
						sns_dd_pixart_suspend(dd_handle);
					}		
		      break;
		   default:
		      return SNS_DDF_EINVALID_PARAM;
		
		   }    	
		}
    break;

    case SNS_DDF_ATTRIB_RANGE:
      break;
    
    case SNS_DDF_ATTRIB_LOWPASS:
      break;

    case SNS_DDF_ATTRIB_RESOLUTION_ADC:
      break;

    case SNS_DDF_ATTRIB_MOTION_DETECT:
      break;
	case SNS_DDF_ATTRIB_ODR:
				return sns_dd_pixart_gst_set_odr(dd_handle, sensor, *(uint32_t *)value);
       break;	
	  
  default:
      return SNS_DDF_EINVALID_PARAM;
  }

  return SNS_DDF_SUCCESS;
}


/*===========================================================================

  FUNCTION:   sns_dd_pixart_gst_get_data

===========================================================================*/
/*!
  @brief Called by the SMGR to get data
 
  @detail
  - Requests a single sample of sensor data from each of the specified
    sensors. Data is returned immediately after being read from the
    sensor, in which case data[] is populated in the same order it was
    requested,
 
  @param[in]  dd_handle    Handle to a driver instance.
  @param[in] sensors       List of sensors for which data isrequested.
  @param[in] num_sensors   Length of @a sensors.
  @param[in] memhandler    Memory handler used to dynamically allocate
                           output parameters, if applicable.
  @param[out] data         Sampled sensor data. The number of elements
                           must match @a num_sensors.

  @return
    The error code definition within the DDF 
    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 
  $TODO: Update the each sample status after a check for bound is done
*/
/*=========================================================================*/
static sns_ddf_status_e sns_dd_pixart_gst_get_data
(
  sns_ddf_handle_t        dd_handle,
  sns_ddf_sensor_e        sensors[],
  uint32_t                num_sensors,
  sns_ddf_memhandler_s*   memhandler,
  sns_ddf_sensor_data_s*  data[]
)
{
	sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
  sns_ddf_status_e status;
  sns_ddf_sensor_data_s *data_ptr;
  int i ;

  printf(">>> sns_dd_pixart_gst_get_data\r\n");
  SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    111, 111, num_sensors);
  /* Sanity check*/
  for (i = 0; i < num_sensors; i++)
  {
  	printf(">>> sensors[%d] = %d\r\n", i, sensors[i]); 
	SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    222, i, sensors[i]);
    if (sensors[i] != SNS_DDF_SENSOR_IR_GESTURE &&
        sensors[i] != SNS_DDF_SENSOR_PROXIMITY)
    {
      return SNS_DDF_EINVALID_PARAM;
    }
  }
	if( (data_ptr = sns_ddf_memhandler_malloc(memhandler, 
	      (num_sensors)*(sizeof(sns_ddf_sensor_data_s)))) == NULL)
	{
	    return SNS_DDF_ENOMEM;
	}
		
	*data = data_ptr;   
  /* The filling of the data doen in reverse order to avoid extra checks
  to fill up the logging structure
  */

#if 1
  for (i=0; i <num_sensors; i++) 
  {
    if (sensors[i] == SNS_DDF_SENSOR_IR_GESTURE) 
    {   
      uint32_t gst = SNS_DDF_IR_GESTURE_NONE;
      uint16_t gst_raw = 0;
	  uint16_t y_avg = 0 ;
      uint16_t obj_size = 0 ;      
      if(state->op_mode != SNS_DDF_SENSOR_IR_GESTURE)
      {
				//Gesture mode is not enabled
      }
      else
      {
      	if((status = sns_dd_pixart_get_gst_data(dd_handle, &gst_raw)) != SNS_DDF_SUCCESS)
	    {
	      return status;
		}   
        if((status = sns_dd_pixart_get_cover_mode_data(dd_handle, &y_avg, &obj_size)) != SNS_DDF_SUCCESS)
        {
          return status;
        }
      }     
      if( (data_ptr[i].samples = sns_ddf_memhandler_malloc(memhandler, 3*sizeof(sns_ddf_sensor_sample_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      } 
        /* The filling of the data doen in reverse order to avoid extra checks
        to fill up the logging structure
        */		  
			data_ptr[i].sensor = SNS_DDF_SENSOR_IR_GESTURE;
			data_ptr[i].num_samples = 3;
			switch(gst_raw){
			case 0:
				gst = SNS_DDF_IR_GESTURE_NONE;
				break;
#if defined(H_EF56S) || defined(H_EF57K) || defined(H_EF58L)
#if (BOARD_VER < WS10)
			case 1:
				gst = SNS_DDF_IR_GESTURE_RIGHT;
				break;
			case 2:
				gst = SNS_DDF_IR_GESTURE_LEFT;
				break;
			case 4:
				gst = SNS_DDF_IR_GESTURE_UP;
				break;
			case 8:
				gst = SNS_DDF_IR_GESTURE_DOWN;
				break;
#else
			case 1:
				gst = SNS_DDF_IR_GESTURE_LEFT;
				break;
			case 2:
				gst = SNS_DDF_IR_GESTURE_RIGHT;
				break;
			case 4:
				gst = SNS_DDF_IR_GESTURE_DOWN;
				break;
			case 8:
				gst = SNS_DDF_IR_GESTURE_UP;
				break;
#endif
#else
            case 1:
				gst = SNS_DDF_IR_GESTURE_LEFT;
				break;
			case 2:
				gst = SNS_DDF_IR_GESTURE_RIGHT;
				break;
			case 4:
				gst = SNS_DDF_IR_GESTURE_DOWN;
				break;
			case 8:
				gst = SNS_DDF_IR_GESTURE_UP;
				break;
#endif
			case 16:
				gst = SNS_DDF_IR_GESTURE_FORWARD;
				break;
			case 32:
				gst = SNS_DDF_IR_GESTURE_BACKWARD;
				break;
			case 64:
				gst = SNS_DDF_IR_GESTURE_CLOCKWISE;
				break;
			case 128:
				gst = SNS_DDF_IR_GESTURE_COUNTER_CLOCKWISE;
				break;
			case 256:
				gst = SNS_DDF_IR_GESTURE_WAVE;
				break;
			default:
				gst = SNS_DDF_IR_GESTURE_UNKNOWN;
			}
			SNS_PRINTF_STRING_ID_ERROR_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    666, gst_raw, gst);
			data_ptr[i].samples[0].sample = (uint32_t)gst; //FX_FLTTOFIX_Q16(gst);
			data_ptr[i].samples[0].status = SNS_DDF_SUCCESS ;
			data_ptr[i].samples[1].sample = (uint32_t)y_avg; //FX_FLTTOFIX_Q16(y_avg);
			data_ptr[i].samples[1].status = SNS_DDF_SUCCESS ;
			data_ptr[i].samples[2].sample = (uint32_t)obj_size; //FX_FLTTOFIX_Q16(obj_size);
			data_ptr[i].samples[2].status = SNS_DDF_SUCCESS ;
			data_ptr[i].status = SNS_DDF_SUCCESS;
			data_ptr[i].timestamp = sns_ddf_get_timestamp();		   
	
    }
    else
    {
      uint8_t proximity_raw = 0 ;
      uint32_t proximity_binary = 0 ;

	  SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    333, 333, 333);

      if(state->op_mode != SNS_DDF_SENSOR_PROXIMITY)
      {
  			//Proximity mode is not enabled
	  } 
	  else
	  {
	    if((status = sns_dd_pixart_get_proximity_data(dd_handle, &proximity_raw, &proximity_binary)) != SNS_DDF_SUCCESS)
		{
	   	  return status;
		}
	  }

	    SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    444, 444, proximity_raw);
              	
	    if( (data_ptr[i].samples = sns_ddf_memhandler_malloc(memhandler, 2*sizeof(sns_ddf_sensor_sample_s))) == NULL) //slace -- changed the size of memory being allocated
		{
      	  return SNS_DDF_ENOMEM;
		} 
		/* The filling of the data doen in reverse order to avoid extra checks
			to fill up the logging structure
		*/		  
		data_ptr[i].sensor = SNS_DDF_SENSOR_PROXIMITY;
		data_ptr[i].samples[0].sample = FX_FLTTOFIX_Q16(proximity_binary);	//proximity_binary is 0 or 1
		data_ptr[i].samples[0].status = SNS_DDF_SUCCESS ;
		data_ptr[i].samples[1].sample = (uint32_t)proximity_raw;
		data_ptr[i].samples[1].status = SNS_DDF_SUCCESS ;
		data_ptr[i].num_samples = 2;
		data_ptr[i].status = SNS_DDF_SUCCESS;
		data_ptr[i].timestamp = sns_ddf_get_timestamp();		  
    } //else
  } // for
#endif

  return SNS_DDF_SUCCESS;
}

/*===========================================================================

  FUNCTION:   sns_dd_pixart_gst_get_attr

===========================================================================*/
/*!
  @brief Called by the SMGR to retrieves the value of an attribute of
  the sensor.
 
  @detail
  - range and resolution info is from the device data sheet.
 
  @param[in]  dd_handle   Handle to a driver instance.
  @param[in] sensor       Sensor whose attribute is to be retrieved.
  @param[in]  attrib      Attribute to be retrieved.
  @param[in] memhandler  Memory handler used to dynamically allocate
                         output parameters, if applicable.
  @param[out] value      Pointer that this function will allocate or set
                         to the attribute's value.
  @param[out] num_elems  Number of elements in @a value.

  @return
    The error code definition within the DDF 
    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 
  $TODO: 
*/
/*=========================================================================*/

static sns_ddf_status_e sns_dd_pixart_gst_get_attr
(
  sns_ddf_handle_t       dd_handle,
  sns_ddf_sensor_e       sensor,
  sns_ddf_attribute_e    attrib,
  sns_ddf_memhandler_s*  memhandler,
  void**                 value,
  uint32_t*              num_elems
)
{
  printf("sns_dd_pixart_gst_get_attr\r\n");
  SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    loop_check, init_status, attrib);
  SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    1, 1, sensor);
  switch(attrib)
  {
    case SNS_DDF_ATTRIB_POWER_INFO:
    {
      sns_ddf_power_info_s* power_attrib;
      if( (*value = sns_ddf_memhandler_malloc(memhandler, 
                    sizeof(sns_ddf_power_info_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }
      power_attrib = *value;
      power_attrib->active_current = 200;
      power_attrib->lowpower_current = 1;
      *num_elems = 1;
    }
    break;

    case SNS_DDF_ATTRIB_RANGE:
    {
      sns_ddf_range_s *device_ranges;
            
      if (sensor == SNS_DDF_SENSOR_IR_GESTURE) 
      {
        if( (*value = sns_ddf_memhandler_malloc(memhandler, 
                      3*sizeof(sns_ddf_range_s))) 
            == NULL)
        {
          return SNS_DDF_ENOMEM;
        }
        device_ranges = *value;
        *num_elems = 3;
        device_ranges[0].min = 0;
        device_ranges[0].max = 511;	//Gesture
        device_ranges[1].min = 0;
        device_ranges[1].max = 255; //Brightness Average
        device_ranges[2].min = 0;
        device_ranges[2].max = 900;	//Object Size
      }
      else 
      { // Proximity sensor
        if( (*value = sns_ddf_memhandler_malloc(memhandler,
                      sizeof(sns_ddf_range_s))) == NULL)
        {
          return SNS_DDF_ENOMEM;
        }
        device_ranges = *value;
        *num_elems = 1;
        device_ranges->min = FX_FLTTOFIX_Q16(0);
        device_ranges->max = FX_FLTTOFIX_Q16(0.05);	//Proximity

		/*device_ranges->min = 0;
        device_ranges->max = 0.05;	//Proximity*/
      }
    }    	

    break;

    case SNS_DDF_ATTRIB_RESOLUTION_ADC:
    {
      sns_ddf_resolution_adc_s *device_res;
      if( (*value = sns_ddf_memhandler_malloc(memhandler,sizeof(sns_ddf_resolution_adc_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }
     
      device_res = *value;

      *num_elems = 1;
      if (sensor == SNS_DDF_SENSOR_IR_GESTURE) 
      {
        device_res->bit_len = 9;
        device_res->max_freq = 120;
      }
      else 
      { // TEMPER Sensor
        device_res->bit_len = 8;
        device_res->max_freq = 10;
      }      
    }
    break;

    case SNS_DDF_ATTRIB_RESOLUTION:
    {
      sns_ddf_resolution_t *device_res;
      if( (*value = sns_ddf_memhandler_malloc(memhandler,sizeof(sns_ddf_resolution_t))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }

      device_res = *value;

      *num_elems = 1;      
      *device_res = 1;	
    }
    break;

    case SNS_DDF_ATTRIB_LOWPASS:
    {
      //TODO -
	return SNS_DDF_EINVALID_PARAM;  
    }
    break;

    case SNS_DDF_ATTRIB_DELAYS:
    {
      sns_ddf_delays_s *device_delay;
      if( (*value = sns_ddf_memhandler_malloc(memhandler,
                    sizeof(sns_ddf_delays_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }
      device_delay = *value;
      *num_elems = 1;
      //Not clear what this should be!
      //TODO - 

	    SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    5, 5, sensor);

      if (sensor == SNS_DDF_SENSOR_IR_GESTURE) 
      {
      	//GESTURE
      	device_delay->time_to_data = 8333;       //120Hz, 8333us
      }
      else 
      { 
      	device_delay->time_to_data = 100000;       //10Hz, 100000us
      }       
      device_delay->time_to_active = 700; // 700us is the startup time
    }
    break;

    case SNS_DDF_ATTRIB_DRIVER_INFO:
    {
      sns_ddf_driver_info_s *driver_info;
      if( (*value = sns_ddf_memhandler_malloc(memhandler,sizeof(sns_ddf_driver_info_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }
      driver_info = *value;
      *num_elems = 1;
      driver_info->name = "Pixart Gesture Sensor Driver";
      driver_info->version = 1;
    }
    break;

    case SNS_DDF_ATTRIB_DEVICE_INFO:
    {
      sns_ddf_device_info_s *device_info;
      if( (*value = sns_ddf_memhandler_malloc(memhandler,sizeof(sns_ddf_device_info_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }
      device_info = *value;
      *num_elems = 1;
      device_info->model = "PAC7620";
      device_info->vendor = "Pixart";
      device_info->name = "Gesture Sensor";
      device_info->version = 1;
    }
    break;

    case SNS_DDF_ATTRIB_ODR:
    {
					sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;
          uint32_t *odr_ptr;
          switch(sensor)
          {
            case SNS_DDF_SENSOR_IR_GESTURE:
              odr_ptr = &state->gst_odr;
              break;
            case SNS_DDF_SENSOR_PROXIMITY:
              odr_ptr = &state->prox_odr;
              break;
            default:
              odr_ptr = &state->gst_odr;
              break;
          }
          *value = odr_ptr;
          *num_elems = 1;
          return SNS_DDF_SUCCESS;
    }
    break;
     default:


    return SNS_DDF_EINVALID_PARAM;
  }

   SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    2222, 2222, 2222);
  return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_pixart_gst_set_odr(sns_ddf_handle_t dd_handle, sns_ddf_sensor_e    sensor, uint32_t odr)
{
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;

  if(sensor == SNS_DDF_SENSOR_PROXIMITY)
  {
  	if(odr != 0)
  	{
	  	//try to enable proximity function
	  	if(state->prox_odr != 0)
	  	{
	  		//already done.
	  		return SNS_DDF_SUCCESS;
	  	}
	  	else
	  	{
	  		sns_ddf_status_e status ;
	  		if ( (status = sns_dd_pixart_change_to_proximity_mode(dd_handle)) != SNS_DDF_SUCCESS)
		  	{
		    	return status;
		  	}  
		  	state->prox_odr = 120 ;
		  	state->op_mode = SNS_DDF_SENSOR_PROXIMITY ;
		  	return SNS_DDF_SUCCESS;
	  	}
	  }
	  else
	  {
	  	//try to disable proximity function
	  	if(state->prox_odr == 0)
	  	{
	  		//already done.
	  		return SNS_DDF_SUCCESS;
	  	}
	  	else
	  	{
	  		if(state->gst_odr != 0)
	  		{
	  			//gesture function is still enabled, change the register setting to gesture mode
	  			sns_ddf_status_e status ;
	  			if ( (status = sns_dd_pixart_change_to_gesture_mode(dd_handle)) != SNS_DDF_SUCCESS)
		  		{
		    		return status;
		  		}  
		  		state->op_mode = SNS_DDF_SENSOR_IR_GESTURE ;
		  	}
		  	else
		  	{
		  		state->op_mode = SNS_DDF_SENSOR__NONE ;
		  	}
		  	state->prox_odr = 0 ;
		  	
		  	return SNS_DDF_SUCCESS;
	  	}	  	
	  }
  }  
  else if(sensor == SNS_DDF_SENSOR_IR_GESTURE)
  {
  	if(odr != 0)
  	{
	  	//try to enable gesture function
	  	if(state->gst_odr != 0)
	  	{
	  		//already done.
	  		return SNS_DDF_SUCCESS;
	  	}
	  	else
	  	{
	  		if(state->prox_odr != 0)
	  		{
	  			//if proximity function is enabled, do nothing due to proximity function has higher priority
	  			state->gst_odr = 120 ;
	  			return SNS_DDF_SUCCESS;
	  		}
	  		else
	  		{	  			
	  			//if proximity function is not enabled, change the register setting to gesture mode
		  		sns_ddf_status_e status ;
		  		if ( (status = sns_dd_pixart_change_to_gesture_mode(dd_handle)) != SNS_DDF_SUCCESS)
			  	{
			    	return status;
			  	}  
			  	state->gst_odr = 120 ;
			  	state->op_mode = SNS_DDF_SENSOR_IR_GESTURE ;
	
			  	return SNS_DDF_SUCCESS;
		  	}
	  	}
	  }
	  else
	  {
	  	//try to disable gesture function
	  	if(state->gst_odr == 0)
	  	{
	  		//already done.
	  		return SNS_DDF_SUCCESS;
	  	}
	  	else
	  	{
	  		if(state->prox_odr != 0)
	  		{
	  			//proximity function is still enabled, change the register setting to proximity mode
	  			
	  			//Maybe we do not need the following code. 
	  			//The register setting and operation mode are already for proximity mode due to proximity function has higher priority
	  			sns_ddf_status_e status ;
	  			if ( (status = sns_dd_pixart_change_to_proximity_mode(dd_handle)) != SNS_DDF_SUCCESS)
		  		{
		    		return status;
		  		}  
		  		state->op_mode = SNS_DDF_SENSOR_PROXIMITY ;
		  	}
		  	else
		  	{
		  		state->op_mode = SNS_DDF_SENSOR__NONE ;
		  	}
		  	state->gst_odr = 0 ;
		  	
		  	return SNS_DDF_SUCCESS;
	  	}	  	
	  }
  }  
  	
    
  if(sensor == SNS_DDF_SENSOR_IR_GESTURE && state->gst_odr != 0)
  {
  	//already done
  	return SNS_DDF_SUCCESS;
  }
  
  if(sensor == SNS_DDF_SENSOR_PROXIMITY && state->prox_odr != 0)
  {
  	//already done
  	return SNS_DDF_SUCCESS;
  }  
 
  return SNS_DDF_SUCCESS;  	
}

sns_ddf_status_e sns_dd_pixart_enable_sched_data(
    sns_ddf_handle_t  dd_handle,
    sns_ddf_sensor_e  sensor,
    bool              enable)
{
#if INTERRUPT == 1		  
	
  sns_dd_pixart_gst_state_t *state = (sns_dd_pixart_gst_state_t *)dd_handle;

  	 SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    111, 111, 111);

  if(enable)
  {
  	if(state->gst_int_enable == 0 && state->gst_int_enable == 0)
  	{
  		sns_ddf_status_e stat = SNS_DDF_SUCCESS;
		  if(!sns_ddf_signal_irq_enabled())
		  {
		    return SNS_DDF_EFAIL ;
		  }
		  stat = sns_ddf_signal_register(state->interrupt_gpio, state, &sns_pixart_gst_driver_fn_list, SNS_DDF_SIGNAL_IRQ_FALLING);
		  //stat = sns_ddf_signal_register(SNS_DDF_SIGNAL_IRQ_MOTION_DETECT, SNS_DDF_SIGNAL_IRQ_FALLING, &sns_dd_pixart_gst_irq_handler, state);
		  if(stat != SNS_DDF_SUCCESS)
		    return stat ;  	
		}
		
  	if ( SNS_DDF_SENSOR_IR_GESTURE  == sensor)
		{
			state->gst_int_enable = 1 ;
		}
		else if( SNS_DDF_SENSOR_PROXIMITY == sensor)
		{
			state->prox_int_enable = 1 ;
		}
  }
  else
  {
  	if ( SNS_DDF_SENSOR_IR_GESTURE  == sensor)
		{
			state->gst_int_enable = 0 ;
		}
		else if( SNS_DDF_SENSOR_PROXIMITY == sensor)
		{
			state->prox_int_enable = 0 ;
		}
		
		if(state->gst_int_enable == 0 && state->gst_int_enable == 0)
		{
			sns_ddf_signal_deregister(state->interrupt_gpio);
		}
  }
#endif
  	 SNS_PRINTF_STRING_ID_FATAL_3(SNS_DBG_MOD_DSPS_SMGR,
			    DBG_SMGR_GENERIC_STRING3,
				    222, 222, 222);
  return SNS_DDF_SUCCESS;
}
