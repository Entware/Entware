# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2016-2026 Entware

include $(TOPDIR)/rules.mk

ARCH:=x86_64
BOARD:=x64-3.2
BOARDNAME:=Entware (x86-64, Linux 3.2.40)
FEATURES:=gpio usb audio pci
KERNEL_PATCHVER:=3.2

include $(INCLUDE_DIR)/target.mk

define Target/Description
  Build Software Repository for Intel x86-64 NASes, like QNAP and Synology.
endef

DEFAULT_PACKAGES += audio-support dvb-support input-support video-support

$(eval $(call BuildTarget))
