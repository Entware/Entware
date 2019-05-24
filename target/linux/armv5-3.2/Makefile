#
# Copyright (C) 2011-2015 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=arm
BOARD:=armv5-3.2
BOARDNAME:=Entware (armv5, soft float, kernel-3.2)
FEATURES:=gpio usb audio pci
KERNEL_PATCHVER:=3.2.40
DEFAULT_PACKAGES := toolchain

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build Software Repository for ARM NASes, like QNAP and Synology.
endef

$(eval $(call BuildTarget))
