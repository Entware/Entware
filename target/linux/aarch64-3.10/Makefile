#
# Copyright (C) 2011-2015 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=aarch64
BOARD:=aarch64-3.10
BOARDNAME:=Entware (aarch64,kernel-3.10)
FEATURES:=gpio usb audio pci
KERNEL_PATCHVER:=3.10
CPU_TYPE:=cortex-a53
DEFAULT_PACKAGES := toolchain

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build Software Repository for ARM NASes, like QNAP and Synology.
endef

$(eval $(call BuildTarget))
