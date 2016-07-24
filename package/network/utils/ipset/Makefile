 
# Copyright (C) 2009-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ipset
PKG_VERSION:=6.24
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://ipset.netfilter.org
PKG_MD5SUM:=8831b8f01458bf2abacc222884195a62

PKG_MAINTAINER:=Jo-Philipp Wich <jow@openwrt.org>
PKG_LICENSE:=GPL-2.0

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/ipset
  SECTION:=net
  CATEGORY:=Network
  DEPENDS+= +libmnl
  TITLE:=IPset administration utility
  URL:=http://ipset.netfilter.org/
endef

CONFIGURE_ARGS += \
	--with-kbuild="$(LINUX_DIR)" --with-kmod=no

MAKE_FLAGS += \
	ARCH="$(LINUX_KARCH)" \
	SHELL="$(BASH)"

define Build/Compile
	$(call Build/Compile/Default)
endef

define Package/ipset/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(CP) $(PKG_INSTALL_DIR)/opt/sbin/ipset $(1)/opt/sbin/
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libipset*.so* $(1)/opt/lib/
endef

$(eval $(call BuildPackage,ipset))
