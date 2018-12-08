#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dante
PKG_VERSION:=1.4.1
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www.inet.no/dante/files/
PKG_HASH:=b6d232bd6fefc87d14bf97e447e4fcdeef4b28b16b048d804b50b48f261c4f53

PKG_MAINTAINER:=Jo-Philipp Wich <jo@mein.io>
PKG_LICENSE:=BSD-4-Clause

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_CFLAGS += -D_GNU_SOURCE -std=gnu89

CONFIGURE_ARGS += \
	--without-upnp \
	--without-pam \
	--disable-libwrap \
	--with-socks-conf=/opt/etc/socks.conf \
	--with-sockd-conf=/opt/etc/sockd.conf \
	--with-pidfile=/opt/var/run/sockd.pid

CONFIGURE_VARS += \
	ac_cv_search_pam_start=""

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include
	$(CP) $(PKG_INSTALL_DIR)/opt/include/* $(1)/opt/include/
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/*.{a,so*,la} $(1)/opt/lib/
endef


define Package/dante/default
  TITLE:=Dante SOCKS
  URL:=http://www.inet.no/dante/
endef

define Package/dante/default/description
Dante is a circuit-level firewall/proxy that can be used to provide convenient
and secure network connectivity, requiring only that the server Dante runs on
has external network connectivity. Dante is used daily by Fortune 100 companies
and large international organizations, either as a standard SOCKS server or as
a "reverse proxy".
endef

define Package/libsocks
  $(call Package/dante/default)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE+= Library
endef

define Package/libsocks/description
$(call Package/dante/default/description)
This package provides the shared libsocks library.
endef

define Package/libsocks/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libsocks.so* $(1)/opt/lib/
endef


define Package/sockd
  $(call Package/dante/default)
  SUBMENU:=Web Servers/Proxies
  SECTION:=net
  CATEGORY:=Network
  TITLE+= Daemon
endef

define Package/sockd/description
$(call Package/dante/default/description)
This package provides the Dante sockd daemon.
endef

define Package/sockd/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(CP) $(PKG_INSTALL_DIR)/opt/sbin/sockd $(1)/opt/sbin/
endef


define Package/socksify
  $(call Package/dante/default)
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE+= Client
endef

define Package/socksify/description
$(call Package/dante/default/description)
This package provides the Dante socksify client.
endef

define Package/socksify/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/socksify $(1)/opt/bin/

ifeq ($(CONFIG_USE_GLIBC),y)
	$(SED) 's|libdl.so|libdl.so.2|g' $(1)/opt/bin/socksify
endif

	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libdsocks.so* $(1)/opt/lib/
endef


$(eval $(call BuildPackage,libsocks))
$(eval $(call BuildPackage,sockd))
$(eval $(call BuildPackage,socksify))
