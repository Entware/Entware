#
# Copyright (C) 2011-2017 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=arm
BOARD:=armv7-2.6
BOARDNAME:=Entware (armv7, soft float, kernel-2.6.36)
FEATURES:=gpio usb audio pci
KERNEL_PATCHVER:=2.6.36
CPU_TYPE:=cortex-a9
DEFAULT_PACKAGES := toolchain

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build Software Repository for ARM NASes, like QNAP and Synology.
endef

$(eval $(call BuildTarget))
