#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ebtables
PKG_SOURCE_DATE:=2018-06-27
PKG_RELEASE:=2

PKG_SOURCE_URL:=https://git.netfilter.org/ebtables
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=48cff25dfea5b37e16ba5dc6601e98ab140f5f99
PKG_MIRROR_HASH:=1ee560498e1a047b329eab3dad8425ae51e7f0527e4495efb99481ca11206b37

PKG_LICENSE:=GPL-2.0
PKG_CPE_ID:=cpe:/a:netfilter:ebtables

include $(INCLUDE_DIR)/package.mk

define Package/ebtables-legacy
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Firewall
#  DEPENDS:=+kmod-ebtables
  TITLE:=Ethernet bridge firewall administration utility
  URL:=http://ebtables.sourceforge.net/
  PROVIDES:=ebtables
  ALTERNATIVES:=\
    200:/opt/sbin/ebtables:/opt/sbin/ebtables-legacy
endef

define Package/ebtables-legacy-utils
  $(call Package/ebtables-legacy)
  DEPENDS:=ebtables-legacy
  TITLE:=ebtables save/restore utilities
  PROVIDES:=ebtables-utils
  ALTERNATIVES:=\
    200:/opt/sbin/ebtables-restore:/opt/sbin/ebtables-legacy-restore
endef

define Package/ebtables-legacy/description
	The ebtables program is a filtering tool for a bridging firewall. The
	filtering is focussed on the Link Layer Ethernet frame fields. Apart
	from filtering, it also gives the ability to alter the Ethernet MAC
	addresses and implement a brouter.
endef

define Package/ebtables-legacy-utils/description
	$(call Package/ebtables-legacy/description)
endef

MAKE_VARS += EXT_LIBSI="$(LIBGCC_S)"

MAKE_FLAGS += \
	CFLAGS="$(TARGET_CFLAGS)" \
	LIBDIR="/opt/lib/ebtables"

define Package/ebtables-legacy/install
	$(INSTALL_DIR) $(1)/opt/etc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/ethertypes $(1)/opt/etc/
	$(INSTALL_DIR) $(1)/opt/lib/ebtables
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lib*.so $(1)/opt/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/extensions/*.so $(1)/opt/lib/ebtables/
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ebtables $(1)/opt/sbin/ebtables-legacy
endef

define Package/ebtables-legacy-utils/install
	$(INSTALL_DIR) $(1)/opt/sbin
	#ebtables-save depends on perl and is just broken
	#$(INSTALL_BIN) $(PKG_BUILD_DIR)/ebtables-save $(1)/opt/sbin/ebtables-legacy-save
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ebtables-restore $(1)/opt/sbin/ebtables-legacy-restore
	# Entware specific: fix exec path in scripts
	#$(SED) 's,^#!.*perl,#!/opt/bin/perl,' $(1)/opt/sbin/ebtables-save
endef

$(eval $(call BuildPackage,ebtables-legacy))
$(eval $(call BuildPackage,ebtables-legacy-utils))
