LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
    com_android_server_AlarmManagerService.cpp \
    com_android_server_AssetAtlasService.cpp \
    com_android_server_ConsumerIrService.cpp \
    com_android_server_input_InputApplicationHandle.cpp \
    com_android_server_input_InputManagerService.cpp \
    com_android_server_input_InputWindowHandle.cpp \
    com_android_server_LightsService.cpp \
    com_android_server_power_PowerManagerService.cpp \
    com_android_server_SerialService.cpp \
    com_android_server_SystemServer.cpp \
    com_android_server_UsbDeviceManager.cpp \
    com_android_server_UsbHostManager.cpp \
    com_android_server_VibratorService.cpp \
    com_android_server_location_GpsLocationProvider.cpp \
    com_android_server_location_FlpHardwareProvider.cpp \
    com_android_server_connectivity_Vpn.cpp \
    onload.cpp

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    frameworks/base/services \
    frameworks/base/core/jni \
    frameworks/native/services \
    external/skia/include/core \
    libcore/include \
    libcore/include/libsuspend \
	$(call include-path-for, libhardware)/hardware \
	$(call include-path-for, libhardware_legacy)/hardware_legacy \

#FEATURE_PANTECH_ERR_CRASH_LOGGING - LS1(p16652)
LOCAL_C_INCLUDES := \
    $(LOCAL_C_INCLUDES) \
    vendor/pantech/frameworks/testmenu_server/inc        

LOCAL_SHARED_LIBRARIES := \
    libandroid_runtime \
    libfingersense \
    libandroidfw \
    libbinder \
    libcutils \
    liblog \
    libhardware \
    libhardware_legacy \
    libnativehelper \
    libutils \
    libui \
    libinput \
    libinputservice \
    libsensorservice \
    libskia \
    libgui \
    libusbhost \
    libsuspend \
    libEGL \
    libGLESv2

#FEATURE_PANTECH_ERR_CRASH_LOGGING - LS1(p16652)
LOCAL_SHARED_LIBRARIES := \
    $(LOCAL_SHARED_LIBRARIES) \
    libskytestclient
    
#+US1-CF2
#Feature : US1_SYS_LOG_SYSTEM
LOCAL_SRC_FILES+=dump.cpp
LOCAL_CFLAGS += -DRESTART_DUMP
LOCAL_C_INCLUDES += vendor/pantech/frameworks/sky_rawdata
LOCAL_SHARED_LIBRARIES += libsky_rawdata
#+US1-CF2

LOCAL_CFLAGS += -DEGL_EGLEXT_PROTOTYPES -DGL_GLEXT_PROTOTYPES

ifeq ($(WITH_MALLOC_LEAK_CHECK),true)
    LOCAL_CFLAGS += -DMALLOC_LEAK_CHECK
endif

LOCAL_MODULE:= libandroid_servers

# QEEXO START
LOCAL_C_INCLUDES += external/fingersense/include
# QEEXO END

include $(BUILD_SHARED_LIBRARY)
