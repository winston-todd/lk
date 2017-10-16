LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ARCH := arm
ARM_CPU := cortex-a9-neon

WITH_SMP := 1
SMP_MAX_CPUS := 4
SMP_CPU_ID_BITS := 2

MODULE_SRCS += \
	$(LOCAL_DIR)/debug.c \
	$(LOCAL_DIR)/platform.c \
	$(LOCAL_DIR)/gpio.c \
	$(LOCAL_DIR)/uart.c \
	$(LOCAL_DIR)/timer.c \

GLOBAL_DEFINES += \
	WITH_DEV_INTERRUPT_ARM_GIC=1 \
	ARM_ARCH_WAIT_FOR_SECONDARIES=1 \

MODULE_DEPS += \
	dev/interrupt/arm_gic \
	dev/gpio \

LINKER_SCRIPT += \
	$(BUILDDIR)/system-onesegment.ld

include make/module.mk
