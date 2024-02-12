# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2011-2024 Entware

include $(TOPDIR)/rules.mk

ARCH:=arm
BOARD:=armv7-3.2
BOARDNAME:=Entware (armv7, Linux 3.2.40)
CPU_TYPE:=cortex-a9
FEATURES:=gpio usb audio pci
KERNEL_PATCHVER:=3.2

include $(INCLUDE_DIR)/target.mk

define Target/Description
  Build Software Repository for ARM NASes, like QNAP and Synology.
endef

$(eval $(call BuildTarget))
