#
# Copyright (C) 2011-2017 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=i386
BOARD:=x86-2.6
BOARDNAME:=Entware (intel x86,kernel-2.6)
FEATURES:=gpio usb audio pci
KERNEL_PATCHVER:=2.6.36
DEFAULT_PACKAGES := toolchain

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build Software Repository for ARM NASes, like QNAP and Synology.
endef

$(eval $(call BuildTarget))
