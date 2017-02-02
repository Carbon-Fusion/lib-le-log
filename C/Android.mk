LOCAL_PATH := $(call my-dir)
ifeq ($(LOG_WRAP_TAGS),true)
	LOCAL_CFLAGS += -DLOG_WRAP_TAGS
endif

ifeq ($(DEFAULT_LOG_LOC),)
	LOCAL_CFLAGS += -DDEFAULT_LOG_LOC=\"$(DEFAULT_LOG_LOC)\"
endif
ifeq ($(ALT_LOG_LOC),)
	LOCAL_CFLAGS += -DALT_LOG_LOC=\"$(ALT_LOG_LOC)\"
endif
LOCAL_SRC_FILES := kmsg_log.c
