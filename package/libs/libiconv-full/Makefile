#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Entware specific: Stripped charset are added back

include $(TOPDIR)/rules.mk

PKG_NAME:=libiconv-full
PKG_VERSION:=1.16
PKG_RELEASE:=1

PKG_SOURCE:=libiconv-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@GNU/libiconv
PKG_HASH:=e6a1b1b589654277ee790cce3734f07876ac4ccfaecbee8afa0b649cf529cc04
PKG_BUILD_DIR:=$(BUILD_DIR)/libiconv-$(PKG_VERSION)

PKG_MAINTAINER:=Jo-Philipp Wich <jo@mein.io>
PKG_LICENSE:=LGPL-2.1-or-later
PKG_LICENSE_FILES:=COPYING.LIB

PKG_FIXUP:=patch-libtool
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libiconv-full/Default
  URL:=https://www.gnu.org/software/libiconv/
  TITLE:=Character set conversion
endef

define Package/libiconv-full
  $(call Package/libiconv-full/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE+= library
  ABI_VERSION:=2
endef

define Package/libcharset
  $(call Package/libiconv-full/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE+= library
  ABI_VERSION:=1
endef

define Package/iconv
  $(call Package/libiconv-full/Default)
  DEPENDS:=+libiconv-full +libcharset
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE+= utility
endef

CONFIGURE_ARGS += \
	--enable-shared \
	--enable-static \
	--disable-rpath \
	--enable-relocatable

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/lib/libiconv-full/include
	$(CP) $(PKG_INSTALL_DIR)/opt/include/iconv.h $(1)/opt/lib/libiconv-full/include/

	$(INSTALL_DIR) $(1)/opt/lib/libiconv-full/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libcharset.{a,so*} $(1)/opt/lib/libiconv-full/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libiconv.{a,so*} $(1)/opt/lib/libiconv-full/lib/
endef

define Package/libcharset/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libcharset.so.* $(1)/opt/lib/
endef

define Package/libiconv-full/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libiconv.so.* $(1)/opt/lib/
endef

define Package/iconv/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/iconv $(1)/opt/bin/
endef

$(eval $(call BuildPackage,libcharset))
$(eval $(call BuildPackage,libiconv-full))
$(eval $(call BuildPackage,iconv))
