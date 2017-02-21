#
# Copyright (C) 2011-2016 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=mips
CPU_TYPE:=mips32r2
BOARD:=mips-3x
BOARDNAME:=Entware-3x (mips, soft float, kernel-3.4.112)
FEATURES:=usb audio pci
KERNEL_PATCHVER:=3.4.112
DEFAULT_PACKAGES := toolchain

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build Software Repository for MIPS soft float routers.
endef

$(eval $(call BuildTarget))
