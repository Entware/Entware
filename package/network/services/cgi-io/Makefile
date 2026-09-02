#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=cgi-io
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/cgi-io.git
PKG_SOURCE_DATE:=2025-12-11
PKG_SOURCE_VERSION:=658b14bda2a0fb617fa456401daee61aae42c805
PKG_MIRROR_HASH:=1fafd6edd7a731427ea8ad1a3b02ebd59a46389e1c7afc8e16d4fd1f79af4659
CMAKE_INSTALL:=1

PKG_LICENSE:=GPL-2.0-or-later
PKG_MAINTAINER:=Entware team, https://entware.net

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/cgi-io
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  DEPENDS:=+libubox +libubus
  TITLE:=CGI utility for handling up/downloading of files
endef

define Package/cgi-io/description
  This package contains an cgi utility that is useful for up/downloading files
endef

define Package/cgi-io/install
	$(INSTALL_DIR) $(1)/opt/libexec $(1)/opt/www/cgi-bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cgi-io $(1)/opt/libexec
	$(LN) /opt/libexec/cgi-io $(1)/opt/www/cgi-bin/cgi-upload
	$(LN) /opt/libexec/cgi-io $(1)/opt/www/cgi-bin/cgi-download
	$(LN) /opt/libexec/cgi-io $(1)/opt/www/cgi-bin/cgi-backup
	$(LN) /opt/libexec/cgi-io $(1)/opt/www/cgi-bin/cgi-exec
endef

$(eval $(call BuildPackage,cgi-io))
