#
# Copyright (C) 2006-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=comgt
PKG_VERSION:=0.32
PKG_RELEASE:=32

PKG_SOURCE:=$(PKG_NAME).$(PKG_VERSION).tgz
PKG_SOURCE_URL:=@SF/comgt
PKG_HASH:=0cedb2a5aa608510da66a99aab74df3db363df495032e57e791a2ff55f1d7913

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>
PKG_LICENSE:=GPL-2.0+

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME).$(PKG_VERSION)
PKG_CHECK_FORMAT_SECURITY:=0

PKG_FLAGS:=nonshared

include $(INCLUDE_DIR)/package.mk

define Package/comgt/Default
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=WWAN
endef

define Package/comgt
$(call Package/comgt/Default)
  TITLE:=Option/Vodafone 3G/GPRS control tool
  DEPENDS:=+chat
  URL:=http://manpages.ubuntu.com/manpages/trusty/man1/comgt.1.html
endef

define Package/comgt-directip
$(call Package/comgt/Default)
  TITLE:=Sierra Wireless Direct-IP support
  DEPENDS:=+comgt
endef

define Package/comgt-ncm
$(call Package/comgt/Default)
  TITLE+=NCM 3G/4G Support
  DEPENDS:=+comgt
endef

define Package/comgt/description
 comgt is a scripting language interpreter useful for establishing 
 communications on serial lines and through PCMCIA modems as well as GPRS 
 and 3G datacards.
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" \
		comgt
endef

define Package/comgt/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/comgt $(1)/opt/bin/
	$(LN) comgt $(1)/opt/bin/gcom
	$(INSTALL_DIR) $(1)/opt/etc/chatscripts
	$(INSTALL_DATA) ./files/3g.chat $(1)/opt/etc/chatscripts/3g.chat
	$(INSTALL_DATA) ./files/evdo.chat $(1)/opt/etc/chatscripts/evdo.chat
	$(INSTALL_DIR) $(1)/opt/etc/gcom
	$(INSTALL_DATA) ./files/setpin.gcom $(1)/opt/etc/gcom/setpin.gcom
	$(INSTALL_DATA) ./files/setmode.gcom $(1)/opt/etc/gcom/setmode.gcom
	$(INSTALL_DATA) ./files/getcardinfo.gcom $(1)/opt/etc/gcom/getcardinfo.gcom
	$(INSTALL_DATA) ./files/getstrength.gcom $(1)/opt/etc/gcom/getstrength.gcom
	$(INSTALL_DATA) ./files/getcarrier.gcom $(1)/opt/etc/gcom/getcarrier.gcom
	$(INSTALL_DATA) ./files/getcnum.gcom $(1)/opt/etc/gcom/getcnum.gcom
	$(INSTALL_DATA) ./files/getimsi.gcom $(1)/opt/etc/gcom/getimsi.gcom
endef

define Package/comgt-directip/install
	$(INSTALL_DIR) $(1)/opt/etc/gcom
	$(INSTALL_DATA) ./files/directip.gcom $(1)/opt/etc/gcom/directip.gcom
	$(INSTALL_DATA) ./files/directip-stop.gcom $(1)/opt/etc/gcom/directip-stop.gcom
endef

define Package/comgt-ncm/install
	$(INSTALL_DIR) $(1)/opt/etc/gcom
	$(INSTALL_DATA) ./files/ncm.json $(1)/opt/etc/gcom/ncm.json
	$(INSTALL_DATA) ./files/runcommand.gcom $(1)/opt/etc/gcom/runcommand.gcom
endef

$(eval $(call BuildPackage,comgt))
$(eval $(call BuildPackage,comgt-directip))
$(eval $(call BuildPackage,comgt-ncm))
