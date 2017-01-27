LOCAL_PATH := $(call my-dir)
ifeq ($(LOG_WRAP_TAGS),true)
	LOCAL_CFLAGS += -DLOG_WRAP_TAGS
endif
LOCAL_SRC_FILES := kmsg_log.c
