LOCAL_PATH := $(call my-dir)
include $(call all-subdir-makefiles)

include $(CLEAR_VARS)

LOCAL_MODULE    := liblelog
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := C/kmsg_log.c

include $(BUILD_SHARED_LIBRARY)



include $(CLEAR_VARS)
LOCAL_MODULE    := liblelog_test
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := C/test.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES := liblelog

include $(BUILD_EXECUTABLE)



