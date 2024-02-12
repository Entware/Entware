# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2011-2024 Entware

include $(TOPDIR)/rules.mk

ARCH:=aarch64
BOARD:=aarch64-3.10
BOARDNAME:=Entware (aarch64, Linux 3.10.108)
CPU_TYPE:=cortex-a53
FEATURES:=gpio usb audio pci
KERNEL_PATCHVER:=3.10

include $(INCLUDE_DIR)/target.mk

define Target/Description
  Build Software Repository for ARM64 NASes, like QNAP and Synology.
endef

$(eval $(call BuildTarget))
