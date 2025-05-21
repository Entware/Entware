#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Entware specific: TARGET_CFLAGS += -Wno-error=sign-compare on k2.6 toolchains

include $(TOPDIR)/rules.mk

PKG_NAME:=libnl-tiny
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/libnl-tiny.git
PKG_SOURCE_DATE:=2025-03-19
PKG_SOURCE_VERSION:=c0df580adbd4d555ecc1962dbe88e91d75b67a4e
PKG_MIRROR_HASH:=1064a27824d99a93cbf8dbc808caf2cb277f1825b378ec6076d2ecfb8866a81f
CMAKE_INSTALL:=1

PKG_LICENSE:=LGPL-2.1
PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libnl-tiny
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=netlink socket library
  ABI_VERSION:=1
endef

define Package/libnl-tiny/description
 This package contains a stripped down version of libnl
endef

ifeq ($(CONFIG_LINUX_2_6_36),y)
TARGET_CFLAGS += -Wno-error=sign-compare
endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig $(1)/opt/include/libnl-tiny
	$(CP) $(PKG_INSTALL_DIR)/opt/include/libnl-tiny/* $(1)/opt/include/libnl-tiny
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libnl-tiny.so* $(1)/opt/lib/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libnl-tiny.pc $(1)/opt/lib/pkgconfig
endef

define Package/libnl-tiny/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libnl-tiny.so.* $(1)/opt/lib/
endef

$(eval $(call BuildPackage,libnl-tiny))
