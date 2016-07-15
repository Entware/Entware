# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=wl500g-kernel
PKG_VERSION:=20160709
PKG_REV:=4164297511fb63af279cdade148f340f7947eedd

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=https://github.com/wl500g/wl500g.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=$(PKG_REV)

include $(INCLUDE_DIR)/host-build.mk

define Host/Prepare
	$(call Host/Prepare/Default)
	sed -i -e 's|^\(TOOLCHAINDIR\)=.*|\1=$(TOOLCHAIN_DIR)|g' $(HOST_BUILD_DIR)/gateway/config/defconfig
endef

define Host/Compile
	$(MAKE) -C "$(HOST_BUILD_DIR)/gateway" config
	touch $(HOST_BUILD_DIR)/linux/linux-2.6.22.19/include/linux/utsrelease.h
endef

define Host/Install
	$(CP) $(HOST_BUILD_DIR)/linux/linux-2.6.22.19 $(BUILD_DIR_HOST)
endef

define Host/Clean
	rm -fr $(BUILD_DIR_HOST)/linux-2.6.22.19
endef

$(eval $(call HostBuild))
