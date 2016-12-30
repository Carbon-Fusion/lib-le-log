##############################################

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := liblelog_c
LOCAL_SRC_FILES := kmsg_log.c
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)

include $(BUILD_SHARED_LIBRARY)

##############################################

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := liblelog_c
LOCAL_SRC_FILES := kmsg_log.c
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

LOCAL_MODULE_PATH := $(TARGET_RECOVERY_ROOT_OUT)/sbin

include $(BUILD_SHARED_LIBRARY)
###############################################
