#
# Copyright (C) 2011-2015 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

ARCH:=arm
BOARD:=armv5soft
BOARDNAME:=Board with armv5 (armv5te) SoC
FEATURES:=
#LINUX_VERSION:=2.6.32.68 (LT)
KERNEL_PATCHVER:=2.6.32
DEFAULT_PACKAGES := toolchain

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build Software Repository for ARM NASes, like QNAP and Synology.
endef

$(eval $(call BuildTarget))
