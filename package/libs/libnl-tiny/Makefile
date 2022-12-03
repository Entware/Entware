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
PKG_SOURCE_DATE:=2022-11-01
PKG_SOURCE_VERSION:=db3b2cdbca5277723326a2720024a59fb821ae36
PKG_MIRROR_HASH:=f6f9e2cb5366cda3be6d27a6320aa6cf3681c0b10df07b29ab4e4005e9f04f1c
CMAKE_INSTALL:=1

PKG_LICENSE:=LGPL-2.1
PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libnl-tiny
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=netlink socket library
  ABI_VERSION:=$(PKG_SOURCE_DATE)
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
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/libnl-tiny.so $(1)/opt/lib/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libnl-tiny.pc $(1)/opt/lib/pkgconfig
endef

define Package/libnl-tiny/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/libnl-tiny.so $(1)/opt/lib/
endef

$(eval $(call BuildPackage,libnl-tiny))
