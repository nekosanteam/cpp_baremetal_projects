
MODULES = peek.o

ifneq ($(KERNELRELEASE),)
obj-m := $(MODULES)
else

ROOTDIR ?= /usr/src/linux/
include $(ROOTDIR)/.config
include $(ROOTDIR)/config.arch

MAKEARCH = $(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
LINUXDIR = $(CONFIG_LINUXDIR)
KERNELRELEASE = ${shell make -sC $(ROOTDIR)/$(LINUXDIR) kernelrelease}

all: modules

modules:
	$(MAKEARCH) -C $(ROOTDIR)/$(LINUXDIR) M=${shell pwd} modules

endif
