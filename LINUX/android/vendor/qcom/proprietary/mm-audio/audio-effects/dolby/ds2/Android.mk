LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := src/dap_hal_api.c \
                   src/dap_hal_util.c

ifneq ($(filter apq8084,$(TARGET_BOARD_PLATFORM)),)
  LOCAL_CFLAGS := -DPLATFORM_APQ8084
endif

ifneq ($(filter msm8916 msm8909 msm8952 msm8937 titanium,$(TARGET_BOARD_PLATFORM)),)
  LOCAL_CFLAGS := -DPLATFORM_MSM8916
endif

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    liblog \
    libdl \

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/inc \
    external/tinyalsa/include \
    $(TARGET_OUT_INTERMEDIATES)/include/mm-audio/audio-effects/ds2 \
    $(BOARD_KERNEL_HEADER_DIR)

LOCAL_ADDITIONAL_DEPENDENCIES += $(BOARD_KERNEL_HEADER_DEPENDENCIES)

ifeq ($(strip $(AUDIO_FEATURE_ENABLED_PROXY_DEVICE)),true)
    LOCAL_CFLAGS += -DAFE_PROXY_ENABLED
endif

LOCAL_COPY_HEADERS_TO := mm-audio/audio-effects/ds2
LOCAL_COPY_HEADERS := inc/dap_hal_api.h

LOCAL_MODULE := libhwdaphal
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)
