
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
include $(call all-subdir-makefiles)

LOCAL_MODULE    := liblelog
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)

include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
include $(call all-subdir-makefiles)

LOCAL_MODULE    := liblelog
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_CLASS := RECOVERY_EXECUTABLES

LOCAL_MODULE_PATH := $(TARGET_RECOVERY_ROOT_OUT)/sbin

include $(BUILD_EXECUTABLE)
