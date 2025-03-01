LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# Build lib for MPQ targets
ifeq ($(call is-board-platform-in-list, mpq8092), true)
LOCAL_MODULE_TAGS       := optional
LOCAL_C_INCLUDES        := \
                           $(BOARD_KERNEL_HEADER_DIR) \
                           $(TARGET_OUT_HEADERS)/common/inc \
                           $(BOARD_DISPLAY_HAL)/libqdutils \
                           $(BOARD_DISPLAY_HAL)/libgralloc \
                           $(BOARD_DISPLAY_HAL)/libqservice

LOCAL_SHARED_LIBRARIES  := liblog libutils libcutils libdl libc libbinder \
                            libmemalloc libhardware
ifneq ($(TARGET_SUPPORTS_WEARABLES), true)
common_flags += -DVENUS_COLOR_FORMAT
endif
common_flags += -DVPU_DRIVER_AVAILABLE
common_flags += -UMPQ_VPU_DRIVER_EXTENSIONS

LOCAL_CFLAGS            := -Wno-missing-field-initializers -Werror \
                           $(common_flags) \
                           -DLOG_TAG=\"VFM\" \
                           -DDBG_MD=0 \
                           -DDBG_DISABLE_IOCTL=0 \
                           -DDBG_VPUOUT_HOST=0 \

LOCAL_ADDITIONAL_DEPENDENCIES := $(BOARD_KERNEL_HEADER_DEPENDENCIES)
LOCAL_SRC_FILES               := vpu.cpp \
                                 vfm.cpp \
                                 vfm_videoflow.cpp \
                                 vfm_vpusession.cpp \
                                 vfm_vpuinterface.cpp \
                                 vfm_utils.cpp \
                                 vfm_bufqueue.cpp \
                                 vfm_eventthread.cpp

LOCAL_MODULE                := libvpu
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO       := vpu
LOCAL_COPY_HEADERS          := vpu.h \
                               vfm_defs.h \
                               vfm_cmds.h \
                               vfm_metadata.h \
                               vfm_surface.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_ADDITIONAL_DEPENDENCIES := $(BOARD_KERNEL_HEADER_DEPENDENCIES)
LOCAL_MODULE_TAGS           := optional
LOCAL_C_INCLUDES            := $(TARGET_OUT_HEADERS)/common/inc \
                               $(TARGET_OUT_HEADERS)/qcom/display \
                               $(BOARD_KERNEL_HEADER_DIR)

LOCAL_SHARED_LIBRARIES      := liblog libutils libcutils libdl libc libbinder \
                               libhardware libgui libqservice libmemalloc

LOCAL_CFLAGS                := -DLOG_TAG=\"vfmclientutils\" \
                                -DDBG_MD=0
LOCAL_SRC_FILES             := vfm_clientutils.cpp \
                               vfm_surface.cpp
LOCAL_MODULE                := libvfmclientutils
include $(BUILD_SHARED_LIBRARY)
endif # mpq targets

