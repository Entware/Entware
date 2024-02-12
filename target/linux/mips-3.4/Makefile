# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2021-2024 Entware

include $(TOPDIR)/rules.mk

ARCH:=mips
BOARD:=mips-3.4
BOARDNAME:=Entware (mips, Linux 3.4.112)
CPU_TYPE:=mips32r2
FEATURES:=audio gpio pci usb
KERNEL_PATCHVER:=3.4

include $(INCLUDE_DIR)/target.mk

define Target/Description
  Build Software Repository for MIPS (big-endian) soft float routers.
endef

$(eval $(call BuildTarget))
