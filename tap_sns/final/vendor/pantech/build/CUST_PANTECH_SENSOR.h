/*                                                                                                                                
 * =================================================================
 *
 *       Filename:  CUCST_PANTECH_DSPS.c
 *
 *    Description:  
 *
 *        Version:  1.2
 *        Created:  03/13/13 16:04:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  LS2 SENSOR, 
 *        Company:  
 *
 * =================================================================
 */

/*
 * =================================================================
 * EDIT HISTORY FOR MODULE

 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order. Please use ISO format for dates.

 *   $DateTime: 03/13/13 16:04:37 $

 * when       who    what, where, wh
  ---------- --- ---------------------------------------------------
  2013-03-13 sgh msm8974 enabled
  2012-10-17 shp Feature seperation by sensor type
  2012-09-18 sgh Global feature be imported for JB
  2012-09-12 sgh Initial revision

 * =================================================================
 */

#ifndef _CUST_PANTECH_DSPS_H_
#define _CUST_PANTECH_DSPS_H_

#if defined(T_EF56S) 
#define H_EF56S
#elif defined(T_EF59S) 
#define H_EF59S
#elif defined(T_EF59K) 
#define H_EF59K
#elif defined(T_EF59L) 
#define H_EF59L
#elif defined(T_EF60S) 
#define H_EF60S
#elif defined(T_EF61K)
#define H_EF61K
#elif defined(T_EF62L) 
#define H_EF62L
#elif defined(T_EF63S) 
#define H_EF63S
#elif defined(T_EF63K) 
#define H_EF63K
#elif defined(T_EF63L)
#define H_EF63L
#endif

//#ifdef CONFIG_PANTECH_DSPS_ENABLE

//#endif // end of CONFIG_PANTECH_DSPS_ENABLE

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_ADD_VALID_GROUP_RADIO
* -----------------------------------------------------------------
*   .Brif          : For issue gyro selftest(SkyTest menu) failed after
                     applied 1025 patch. 
*   .Applied Block : sensordaemon
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/inc/sns_main.h
*                  android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_ADD_VALID_GROUP_RADIO

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_SET_ATTRIB
* -----------------------------------------------------------------
*   .Brif          : to apply sensor attrib at runtime.
*   .Applied Block : adsp_proc
*   .Applied Files :                                                                                              
*                  adsp_proc/Sensors/api/sns_smgr_api_v01.h
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_SET_ATTRIB
#if defined(CONFIG_PANTECH_SNS_SET_ATTRIB)
#define CONFIG_PANTECH_SNS_FACING_ANGLE_PROPERTY "debug.facing.angle"
#define CONFIG_PANTECH_SNS_TAP_PROPERTY "debug.tap.tap"
#define CONFIG_PANTECH_SNS_TAP_Z_PROPERTY "debug.tap.z"
#endif

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_PROXIMITY_5HZ_FIX
* -----------------------------------------------------------------
*   .Brif          : fix proximity sensor max frequency to 5hz (talk back issue)
*   .Applied Block : DD
*   .Applied Files :                                                                                              
*                  adsp_proc/Sensors/dd/qcom/src/sns_dd_pixart_gst.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_PROXIMITY_5HZ_FIX

#if defined(H_EF56S) || defined(H_EF57K) || defined(H_EF58L)
/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_PAJ7620_NAMING
* -----------------------------------------------------------------
*   .Brif          : separate proximity and gesture sensor (PAJ7620/PAC7672)
*   .Applied Block : HAL
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_PAJ7620_NAMING
#endif

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_CHECK_DEVICE_VERSION
* -----------------------------------------------------------------
*   .Brif          : check device version is over 1 (because of CTS test)
*   .Applied Block : HAL
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_CHECK_DEVICE_VERSION

/* -----------------------------------------------------------------
* CONFIG_PANTECH_ADSP_LOGGING
* -----------------------------------------------------------------
*   .Brif          : to print the logs we add or to prevent repeating same logs
*   .Applied Block : HAL
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_ADSP_LOGGING

/* -----------------------------------------------------------------
* CONFIG_PANTECH_FACTORY_PROCESS_CMD
* -----------------------------------------------------------------
*   .Brif          : the codes about pantech factory process cmd
*   .Applied Block : pantech_server
*   .Applied Files :                                                                                              
*                  android/vendor/pantech/frameworks/testmenu_server/server/sky_process_cmd_thread.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_FACTORY_PROCESS_CMD

/* -----------------------------------------------------------------
* CONFIG_PANTECH_NO_OEM_HAL
* -----------------------------------------------------------------
*   .Brif          : HAL
*   .Applied Block : to prevent that qcom HAL prints error logs about OEM HAL.
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_NO_OEM_HAL

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNSUTILS
* -----------------------------------------------------------------
*   .Brif          : use snsutils
*   .Applied Block : HAL & pantech_server
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
*                  android/vendor/pantech/frameworks/testmenu_server/server/sky_process_cmd_thread.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNSUTILS
#ifdef CONFIG_PANTECH_SNSUTILS
#define CONFIG_PANTECH_ADSP_SUPPORTED_PROPERTY "sys.sns.supported"
#endif  // CONFIG_PANTECH_SNSUTILS

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SSI
* -----------------------------------------------------------------
*   .Brif          : SSI
*   .Applied Block : SSI init 
*   .Applied Files :                                                                                              
*                   android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/inc/sns_reg_common.h
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SSI

#if defined(H_SVLTE) || defined(H_CSFB) || defined(H_NAMI) || defined(H_EF59S) || defined(H_EF59K) || defined(H_EF59L) || defined(H_EF60S) || defined(H_EF61K) || defined(H_EF62L)
/* -----------------------------------------------------------------
* CONFIG_PANTECH_APDS9930
* -----------------------------------------------------------------
*   .Brif          : apds9930
*   .Applied Block : apds9930 device id 
*   .Applied Files :                                                                                              
*                  adsp_proc/Sensors/dd/qcom/src/sns_dd_apds99xx.c 
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_APDS9930
#endif

/* -----------------------------------------------------------------
* CONFIG_PANTECH_GES_PRX_3AXES
* -----------------------------------------------------------------
*   .Brif          : Pixart gesture and proximity sensor 3axes data streaming
*   .Applied Block : HAL & property_service
*   .Applied Files :                                                                                              
*                  android/system/core/init/property_service.c
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_GES_PRX_ALS_3AXES
#ifdef CONFIG_PANTECH_GES_PRX_ALS_3AXES
#define CONFIG_PANTECH_GES_PRX_ALS_3AXES_PROPERTY "sys.sns.debug"
#endif

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_PIXART_VLED_PWR_CONTROLED_BY_DDF
* -----------------------------------------------------------------
*   .Brif          : PAJ7620 VLED power is controled by paj7620 ddf
*   .Applied Block : kernel / ADSP(DD)
*   .Applied Files :                                                                                              
*                  adsp_proc/Sensors/dd/qcom/src/sns_dd_pixart_gst.c
*                  android/kernel/arch/arm/mach-msm/board-8974.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_PIXART_VLED_PWR_CONTROLED_BY_DDF

/* -----------------------------------------------------------------
* CONFIG_PANTECH_GST_UNKNOWN_ON_HALLIC
* -----------------------------------------------------------------
*   .Brif          : If HALLIC is on, gesture report to HAL with UNKNOWN
*                    And, It must be defined CONFIG_PANTECH_SNS_PIXART_VLED_PWR_CONTROLED_BY_DDF for gpio_handle
*   .Applied Block : ADSP(DD)
*   .Applied Files : adsp_proc/Sensors/dd/qcom/src/sns_dd_pixart_gst.c 
* ---------------------------------------------------------------*/
#ifdef CONFIG_PANTECH_SNS_PIXART_VLED_PWR_CONTROLED_BY_DDF
#define CONFIG_PANTECH_GST_UNKNOWN_ON_HALLIC
#endif

#if defined(H_EF56S) || defined(H_EF57K) || defined(H_EF58L)
/* -----------------------------------------------------------------
* CONFIG_SNS_GESTURE
* -----------------------------------------------------------------
*   .Brif          : porting pixart sensor to DSPS (First Job)
*   .Applied Block : DSPS / sensordaemon / HAL
*   .Applied Files :                                                                                              
*                  adsp_proc/Sensors/
* ---------------------------------------------------------------*/
#define CONFIG_SNS_GESTURE
#endif
/* -----------------------------------------------------------------
* CONFIG_SNS_ALS_LUX
* -----------------------------------------------------------------
*   .Brif          : optimize lux
*   .Applied Block : ADSP
*   .Applied Files : Sensors/dd/qcom/src/sns_dd_pixart_als.c
* ---------------------------------------------------------------*/
#define CONFIG_SNS_ALS_LUX

/* -----------------------------------------------------------------
* CONFIG_SNS_PRX_THRESHOLD
* -----------------------------------------------------------------
*   .Brif          : proximity near/far threshold
*   .Applied Block : ADSP
*   .Applied Files : Sensors/dd/qcom/src/sns_dd_pixart_gst.c
* ---------------------------------------------------------------*/
#define CONFIG_SNS_PRX_THRESHOLD

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_DAEMON_LATE_START
* -----------------------------------------------------------------
*   .Brif          : to start daemon more earlier. (system server often can't get sensor list, because daemon is not ready.)
*   .Applied Block : sensordaemon / init script
*   .Applied Files : android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
*                    android/device/qcom/common/rootdir/etc/init.qcom.rc
*                    android/device/qcom/common/rootdir/etc/init.qcom.sh
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_DAEMON_LATE_START
/* -----------------------------------------------------------------
* CONFIG_PANTECH_GYRO_TAP_TAP
* -----------------------------------------------------------------
*   .Brif          : sns.reg update for gyro tap tap
*   .Applied Block : sensor daemon
*   .Applied Files : sensordaemon/apps/common/reg/src/sns_reg_data.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_GYRO_TAP_TAP

#if defined(H_EF56S) || defined(H_EF57K) || defined(H_EF58L)
/* -----------------------------------------------------------------
* CONFIG_PANTECH_GST_FIRST_DATA_CLEAR
* -----------------------------------------------------------------
*   .Brif          : gesture sensor init
*   .Applied Block : gesture ddf
*   .Applied Files : adsp_proc/Sensors/dd/qcom/src/sns_dd_pixart_gst.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_GST_FIRST_DATA_CLEAR
#endif

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_ENCRYPTION
* -----------------------------------------------------------------
*   .Brif          : to prevent Encryption fail issue.
*   .Applied Block : sensordaemon / init script
*   .Applied Files : android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/main/src/sns_main.c
*                    android/device/qcom/common/rootdir/etc/init.qcom.rc
*                    android/vendor/qcom/proprietary/sensors/dsps/sensordaemon/file/inc/sns_file.h
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_ENCRYPTION

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_FIX_BUG_SET_DELAY
* -----------------------------------------------------------------
*   .Brif          : bug of method _hal_sensors_set_delay() after applied 1030A patch is fixed
*   .Applied Block : HAL
*   .Applied Files : android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_FIX_BUG_SET_DELAY

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_FIX_BUG_TIME_SYNC
* -----------------------------------------------------------------
*   .Brif          : bug of the codes 'cd_mutex' on method hal_time_sync() after applied 1031 patch is fixed
*   .Applied Block : HAL
*   .Applied Files : android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_FIX_BUG_TIME_SYNC

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_FIX_BUG_SELF_TEST
* -----------------------------------------------------------------
*   .Brif          : the problem during self-test that sensor does not work after device-busy error rarely.
*   .Applied Block : ADSP (SMGR)
*   .Applied Files : adsp_proc/Sensors/smgr/src/common/sns_smgr_task.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_FIX_BUG_SELF_TEST

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_FIX_BUG_GYRO_TAP
* -----------------------------------------------------------------
*   .Brif          : the wrong codes in SAM(ADSP side) about gyro tap after 1031 patch.
*   .Applied Block : ADSP (SAM)
*   .Applied Files : adsp_proc/Sensors/sam/framework/src/common/sns_sam_ext_dsps.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_FIX_BUG_GYRO_TAP

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_MODIFY_SENSORSERVICE_DUMP
* -----------------------------------------------------------------
*   .Brif          : modify a method dump() in SensorService to print process IDs activating sensors.
*   .Applied Block : SensorService
*   .Applied Files : android/frameworks/native/services/sensorservice/SensorService.cpp
                     android/frameworks/native/services/sensorservice/SensorService.h
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_MODIFY_SENSORSERVICE_DUMP

#if defined(H_EF59S) || defined(H_EF59K) || defined(H_EF59L) || defined(H_EF60S) || defined(H_EF61K) || defined(H_EF62L)
/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_APDS9930_USE_DD_OLD_VERSION
* -----------------------------------------------------------------
*   .Brif          : use old version of APDS9930 dd
*   .Applied Block : ADSP(DD)
*   .Applied Files : adsp_proc/Sensors/dd/qcom/inc/sns_dd.h
*                    adsp_proc/Sensors/smgr/src/common/sns_smgr_init.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_APDS9930_USE_DD_OLD_VERSION

/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_APDS9930_NAMING
* -----------------------------------------------------------------
*   .Brif          : separate proximity and light sensor
*   .Applied Block : HAL
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_APDS9930_NAMING
#endif

#ifdef CONFIG_PANTECH_SNS_APDS9930_USE_DD_OLD_VERSION
/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_APDS9930_SUNLIGHT_CANCELATION
* -----------------------------------------------------------------
*   .Brif          : APDS9930 sunlight cancelation
*   .Applied Block : ADSP(DD)
*   .Applied Files : adsp_proc/Sensors/dd/qcom/src/sns_dd_alsprx_apds9900.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_APDS9930_SUNLIGHT_CANCELATION

/* -----------------------------------------------------------------
* CONFIG_PANCETH_SNS_PROXIMITY_MAX_DISTANCE_METER
* -----------------------------------------------------------------
*   .Brif          : modify proximity max distance to 0.05m from 5m
*   .Applied Block : ADSP(DD)
*   .Applied Files : adsp_proc/Sensors/dd/qcom/src/sns_dd_alsprx_apds9900.c
*                    android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_PROXIMITY_MAX_DISTANCE_METER (0.05)
#endif
#ifdef H_EF63S


/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_AUTO_WAKE_UP
* -----------------------------------------------------------------
*   .Brif          : Add auto wake up sensor
*   .Applied Block :  all
*   .Applied Files : sam, hal
*                    vendor\qcom\proprietary\sensors\dsps\libsensor1\src\libsensor1.c
*                    vendor\qcom\proprietary\sensors\dsps\libhalsensors\inc\sensors_hal.h
*                    vendor\qcom\proprietary\sensors\dsps\libhalsensors\src\sensors_qcom_hal.c
*                    adsp_proc\sensors\common\sam\framework\src\sns_sam.c
*                    adsp_proc\sensors\sam\framework\src\common\sns_sam_dsps.c
*                    adsp_proc\sensors\sam\framework\src\8974\sns_sam_dsps_tgt.c
*                    adsp_proc\sensors\common\sam\framework\inc\sns_sam_priv.h
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_AUTO_WAKE_UP //EF63S auto wake up FEATURE.
/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_NAMING
* -----------------------------------------------------------------
*   .Brif          : modify sensor_info SensorName from (model+ name) to (model)
*   .Applied Block :  adsp (smgr)
*   .Applied Files : adsp_proc/Sensors/smgr/src/common/sns_smgr_task.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_NAMING 
/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_TMD277X_NAMING
* -----------------------------------------------------------------
*   .Brif          : separate proximity and light sensor
*   .Applied Block : HAL
*   .Applied Files :                                                                                              
*                  android/vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_TMD277X_NAMING
/* -----------------------------------------------------------------
* CONFIG_PANTECH_SNS_TMD277X_SUNLIGHT_CANCELATION
* -----------------------------------------------------------------
*   .Brif          : TMD277X sunlight cancelation
*   .Applied Block : ADSP(DD)
*   .Applied Files : adsp_proc/Sensors/dd/qcom/src/sns_dd_alsprx_tmd277x.c
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_SNS_TMD277X_SUNLIGHT_CANCELATION
#endif

/* -----------------------------------------------------------------
* CONFIG_NCPIN_DO_NOT_CONTROL
* -----------------------------------------------------------------
*   .Brif          : do not control nc pin
*   .Applied Block : ADSP(SMGR)
*   .Applied Files : adsp_proc/Sensors/smgr/src/8974/sns_smgr_hw.c
* ---------------------------------------------------------------*/
#define CONFIG_NCPIN_DO_NOT_CONTROL

#if defined(H_EF60S) || defined(H_EF61K) || defined(H_EF62L)
/* -----------------------------------------------------------------
* CONFIG_CHECK_HWREV_FOR_CHANGING_PROXIMITY_THRESHOLD
* -----------------------------------------------------------------
*   .Brif          : check hwrev for changing proximity threshold
*   .Applied Block : ADSP(DDF) / ADSP(DD) / HAL / snsutils / kernel
*   .Applied Files : adsp_proc/Sensors/ddf/inc/sns_ddf_common.h
*                    adsp_proc/Sensors/dd/qcom/src/sns_dd_alsprx_apds9900.c
*                    adsp_proc/Sensors/dd/qcom/src/sns_dd_alsprx_apds9900_priv.h
*                    vendor/qcom/proprietary/sensors/dsps/snsutils/inc/snsutils.h
*                    vendor/qcom/proprietary/sensors/dsps/snsutils/src/snsutils.c
*                    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/sensors_qcom_hal.c
*                    kernel/arch/arm/mach-msm/msm-pm.c // in KK
* ---------------------------------------------------------------*/
#define CONFIG_CHECK_HWREV_FOR_CHANGING_PROXIMITY_THRESHOLD

/* -----------------------------------------------------------------
* CONFIG_PANTECH_ACCELEROMETER_CALIBRATION
* -----------------------------------------------------------------
*   .Brif          : accelerometer calibration
*   .Applied Block : HAL / snsutils / libqctdspstest
*   .Applied Files : 
* ---------------------------------------------------------------*/
#define CONFIG_PANTECH_ACCELEROMETER_CALIBRATION

#define ACCEL_CALIB_PROPERTY "persist.sns.accel_cal"
#endif

#if defined(H_EF56S)
#define PANTECH_TAP_SENSOR
#endif
#endif // _CUST_PANTECH_DSPS_H_
