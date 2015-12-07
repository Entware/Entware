#
# Copyright (C) 2006-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Downgraded from 3.2.21. The newer versions is incompatible with k2.6.22

include $(TOPDIR)/rules.mk

PKG_NAME:=libnl
PKG_VERSION:=2.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www.infradead.org/~tgr/libnl/files/
PKG_MD5SUM:=6aaf1e9802a17a7d702bb0638044ffa7
PKG_LICENSE:=LGPL-2.1

include $(INCLUDE_DIR)/package.mk

define Package/libnl
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=netlink socket library
  URL:=http://people.suug.ch/~tgr/libnl/
endef

define Package/libnl/description
 This package contains a library for applications dealing with netlink sockets
endef

TARGET_CFLAGS += -ffunction-sections $(FPIC)

define Build/Compile
	$(call Build/Compile/Default)
	make -C $(PKG_BUILD_DIR) \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		install
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
	mkdir -p $(1)/opt/include/libnl
	$(CP) $(PKG_BUILD_DIR)/include/linux $(1)/opt/include/libnl/
endef

define Package/libnl/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libnl-route.so.* $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libnl-genl.so.* $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libnl-nf.so.* $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libnl-route.so.* $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libnl.so.* $(1)/opt/lib/
endef

$(eval $(call BuildPackage,libnl))
