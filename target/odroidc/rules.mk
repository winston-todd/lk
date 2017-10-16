LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

PLATFORM := aml-s805

MEMBASE := 0x0
MEMSIZE := 0x40000000


MODULE_SRCS += \
    $(LOCAL_DIR)/init.c \
    
GLOBAL_DEFINES += \
	TARGET_HAS_DEBUG_LED=1 \
    

$(BUILDDIR)/lk.img: $(OUTBIN)
	@echo generating u-boot image: $@
	$(NOECHO)mkimage -A arm -T kernel -C none -a 0x20000000 -e 0x20000000 -d $(OUTBIN) $@
	$(NOECHO)cp $@ /var/lib/tftpboot/odroidc/lk.img
	
/var/lib/tftpboot/odroidc/lk.bin: $(OUTBIN)
	@echo coping bin to tftp directory
	@cp $(OUTBIN) $@

EXTRA_BUILDDEPS += $(BUILDDIR)/lk.img /var/lib/tftpboot/odroidc/lk.bin
GENERATED += $(BUILDDIR)/lk.img /var/lib/tftpboot/odroidc/lk.bin

include make/module.mk