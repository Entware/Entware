#
# Copyright (C) 2007-2015 OpenWrt.org
# Copyright (C) 2010 Vertical Communications
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=base-files
PKG_RELEASE:=168

PKG_FILE_DEPENDS:=$(PLATFORM_DIR)/ $(GENERIC_PLATFORM_DIR)/base-files/
PKG_BUILD_DEPENDS:=opkg/host usign/host
PKG_LICENSE:=GPL-2.0

PKG_CONFIG_DEPENDS := CONFIG_SIGNED_PACKAGES CONFIG_TARGET_INIT_PATH

include $(INCLUDE_DIR)/package.mk

ifneq ($(DUMP),1)
  STAMP_CONFIGURED:=$(strip $(STAMP_CONFIGURED))_$(shell $(SH_FUNC) echo $(CONFIG_TARGET_INIT_PATH) | md5s)
  TARGET:=-$(BOARD)
  ifneq ($(wildcard $(PLATFORM_DIR)/base-files-$(PROFILE) $(PLATFORM_SUBDIR)/base-files-$(PROFILE)),)
    TARGET:=$(TARGET)-$(PROFILE)
  endif
endif

define Package/base-files
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=Base filesystem for Entware
  VERSION:=$(PKG_RELEASE)-$(REVISION)
endef

define Package/base-files/conffiles
/opt/etc/crontabs/
$(call $(TARGET)/conffiles)
endef

define Package/base-files/description
 This package contains a base filesystem and system scripts for OpenWrt.
endef

define ImageConfigOptions
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default

endef
Build/Compile = $(Build/Compile/Default)

define Package/base-files/install
	$(CP) ./files/* $(1)/
endef

ifneq ($(DUMP),1)
  -include $(PLATFORM_DIR)/base-files.mk
endif

$(eval $(call BuildPackage,base-files))
