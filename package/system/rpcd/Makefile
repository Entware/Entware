#
# Copyright (C) 2013-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rpcd
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/rpcd.git
PKG_MIRROR_HASH:=1a701b15746f34eb19532f195d738611364a18acaf45c0197626c31ab59976ce
PKG_SOURCE_DATE:=2025-12-03
PKG_SOURCE_VERSION:=ffb9961c1f8bc50830fdd4e144570f11062c2601
PKG_MAINTAINER:=Entware team, https://entware.net

PKG_LICENSE:=ISC
PKG_LICENSE_FILES:=

PKG_ASLR_PIE_REGULAR:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include
	$(CP) $(PKG_BUILD_DIR)/include/rpcd $(1)/opt/include/
endef

define Package/rpcd/default
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=OpenWrt ubus RPC backend server
  DEPENDS:=+libubus +libubox
endef

define Package/rpcd
  $(Package/rpcd/default)
  DEPENDS+= +libuci +libblobmsg-json +libjson-c
endef

define Package/rpcd/description
 This package provides the UBUS RPC backend server to expose various
 functionality to frontend programs via JSON-RPC.
endef

define Package/rpcd/conffiles
/opt/etc/uci-config/rpcd
endef

TARGET_LDFLAGS += -lcrypt

CMAKE_OPTIONS += -DIWINFO_SUPPORT=OFF -DRPCSYS_SUPPORT=OFF

define Package/rpcd/install
	$(INSTALL_DIR) $(1)/opt/etc/init.d
	$(INSTALL_BIN) ./files/S50rpcd $(1)/opt/etc/init.d/
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rpcd $(1)/opt/sbin/rpcd
	$(INSTALL_DIR) $(1)/opt/share/rpcd/acl.d
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/unauthenticated.json $(1)/opt/share/rpcd/acl.d/unauthenticated.json
	$(INSTALL_DIR) $(1)/opt/etc/uci-config
	$(INSTALL_CONF) ./files/rpcd.config $(1)/opt/etc/uci-config/rpcd
	$(INSTALL_DIR) $(1)/opt/etc/uci-defaults
	$(INSTALL_BIN) ./files/40_rpcd-login-username $(1)/opt/etc/uci-defaults/
endef


# 1: plugin name
# 2: additional dependencies
# 3: plugin title/description
# 4: extra dependencies
define BuildPlugin

  PKG_CONFIG_DEPENDS += CONFIG_PACKAGE_rpcd-mod-$(1)

  define Package/rpcd-mod-$(1)
    $(Package/rpcd/default)
    TITLE+= ($(1) plugin)
    DEPENDS+=rpcd $(2)
    EXTRA_DEPENDS:=$(4)
  endef

  define Package/rpcd-mod-$(1)/description
    $(3)
  endef

  define Package/rpcd-mod-$(1)/postinst
#!/bin/sh
[ -n "$$$${IPKG_INSTROOT}" ] || { pidof rpcd >/dev/null && /opt/etc/init.d/S50rpcd reconfigure; true; }
  endef

  define Package/rpcd-mod-$(1)/install
	$(INSTALL_DIR) $$(1)/opt/lib/rpcd
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(1).so $$(1)/opt/lib/rpcd/
  endef

  $$(eval $$(call BuildPackage,rpcd-mod-$(1)))

endef

$(eval $(call BuildPackage,rpcd))
$(eval $(call BuildPlugin,file,,Provides ubus calls for file and directory operations.))
$(eval $(call BuildPlugin,ucode,+libucode,Allows implementing plugins using ucode scripts.))
