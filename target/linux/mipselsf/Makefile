#
# Copyright (C) 2011-2015 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=mipsel
BOARD:=mipselsf
BOARDNAME:=Entware repository (mipsel, soft float)
FEATURES:=
KERNEL_PATCHVER:=2.6.22
#LINUX_VERSION:=2.6.22.19
DEFAULT_PACKAGES := toolchain

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build Software Repository for MIPSEL soft float routers.
endef

$(eval $(call BuildTarget))
