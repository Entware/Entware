#
# Copyright (C) 2010-2015 Jo-Philipp Wich <jo@mein.io>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=uhttpd
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/uhttpd.git
PKG_SOURCE_DATE:=2025-10-03
PKG_SOURCE_VERSION:=ebb92e6b339b88bbc6b76501b6603c52d4887ba1
PKG_MIRROR_HASH:=2d00da72db0ec08132bb169f2bad0b153bd998ea1eee0700b4ec01e65c35127d
PKG_MAINTAINER:=Entware team, https://entware.net
PKG_LICENSE:=ISC

PKG_ASLR_PIE_REGULAR:=1
PKG_BUILD_DEPENDS = ustream-ssl

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk
include $(INCLUDE_DIR)/version.mk

define Package/uhttpd/default
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=uHTTPd - tiny, single threaded HTTP server
endef

define Package/uhttpd
  $(Package/uhttpd/default)
  DEPENDS:= +libubox +libblobmsg-json +libjson-script +libjson-c
endef

define Package/uhttpd/description
 uHTTPd is a tiny single threaded HTTP server with TLS, CGI and Lua
 support. It is intended as a drop-in replacement for the Busybox
 HTTP daemon.
endef

define Package/uhttpd/conffiles
/opt/etc/uci-config/uhttpd
/opt/etc/uhttpd.crt
/opt/etc/uhttpd.key
endef


define Package/uhttpd-mod-lua
  $(Package/uhttpd/default)
  TITLE+= (Lua plugin)
  DEPENDS:=uhttpd +liblua
endef

define Package/uhttpd-mod-lua/description
 The Lua plugin adds a CGI-like Lua runtime interface to uHTTPd.
endef


define Package/uhttpd-mod-ubus
  $(Package/uhttpd/default)
  TITLE+= (ubus plugin)
  DEPENDS:=uhttpd +libubus +libblobmsg-json
endef

define Package/uhttpd-mod-ubus/description
 The ubus plugin adds a HTTP/JSON RPC proxy for ubus and publishes the
 session.* namespace and procedures.
endef


define Package/uhttpd-mod-ucode
  $(Package/uhttpd/default)
  TITLE+= (ucode plugin)
  DEPENDS:=uhttpd +libucode
endef

define Package/uhttpd-mod-ucode/description
 The ucode plugin adds a CGI-like ucode runtime interface to uHTTPd.
endef


ifneq ($(CONFIG_USE_GLIBC),)
  TARGET_CFLAGS += -D_DEFAULT_SOURCE
endif

define Package/uhttpd/install
	$(INSTALL_DIR) $(1)/opt/etc/init.d $(1)/opt/etc/uci-config $(1)/opt/sbin $(1)/opt/www
	$(INSTALL_BIN) ./files/S55uhttpd $(1)/opt/etc/init.d/
	$(INSTALL_CONF) ./files/uhttpd.config $(1)/opt/etc/uci-config/uhttpd
	$(VERSION_SED_SCRIPT) $(1)/opt/etc/uci-config/uhttpd
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uhttpd $(1)/opt/sbin/uhttpd
endef

define Package/uhttpd-mod-lua/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uhttpd_lua.so $(1)/opt/lib/
endef

define Package/uhttpd-mod-ubus/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uhttpd_ubus.so $(1)/opt/lib/
endef

define Package/uhttpd-mod-ubus/postinst
#!/bin/sh
if [ -z "$${IPKG_INSTROOT}" ] && pidof uhttpd >/dev/null; then
	/opt/etc/init.d/S55uhttpd reconfigure
fi
exit 0
endef

define Package/uhttpd-mod-ucode/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uhttpd_ucode.so $(1)/opt/lib/
endef


$(eval $(call BuildPackage,uhttpd))
$(eval $(call BuildPackage,uhttpd-mod-lua))
$(eval $(call BuildPackage,uhttpd-mod-ubus))
$(eval $(call BuildPackage,uhttpd-mod-ucode))
