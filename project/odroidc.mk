# top level project rules for the armemu-test project
#
LOCAL_DIR := $(GET_LOCAL_DIR)

TARGET := odroidc
MODULES += \
	lib/bio \
	lib/partition \
	lib/bcache \
	lib/fs \
	lib/fs/ext2 \
	lib/evlog

GLOBAL_DEFINES += \
	WITH_KERNEL_EVLOG=1

include project/virtual/test.mk
