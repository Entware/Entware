include $(TOPDIR)/rules.mk

PKG_NAME:=libubox
PKG_VERSION:=2016-11-29
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(LEDE_GIT)/project/libubox.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=77a629375d7387a33a59509d9d751a8798134cab
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.xz
PKG_MIRROR_MD5SUM:=686a0078da3ada68fc9d39f62df07be52589afce79969ec4039f38f85ccedd3c
CMAKE_INSTALL:=1

PKG_LICENSE:=ISC
PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>

PKG_BUILD_DEPENDS:=lua

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libubox
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Basic utility library
  ABI_VERSION:=$(PKG_VERSION)
  DEPENDS:=
endef

define Package/libblobmsg-json
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=blobmsg <-> json conversion library
  DEPENDS:=+libjson-c +libubox
endef

define Package/jshn
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libjson-c +libubox +libblobmsg-json
  TITLE:=JSON SHell Notation
endef

define Package/jshn/description
  Library for parsing and generating JSON from shell scripts
endef

define Package/libjson-script
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libubox
  TITLE:=Minimalistic JSON based scripting engine
endef

define Package/libubox-lua
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libubox +liblua
  TITLE:=Lua binding for the OpenWrt Basic utility library
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/opt/include
CMAKE_OPTIONS = \
	-DLUAPATH=/opt/lib/lua

define Package/libubox/install
	$(INSTALL_DIR) $(1)/opt/lib/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/libubox.so $(1)/opt/lib/
endef

define Package/libblobmsg-json/install
	$(INSTALL_DIR) $(1)/opt/lib/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/libblobmsg_json.so $(1)/opt/lib/
endef

define Package/jshn/install
	$(INSTALL_DIR) $(1)/opt/bin $(1)/opt/share/libubox
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/jshn $(1)/opt/bin
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/share/libubox/jshn.sh $(1)/opt/share/libubox
endef

define Package/libjson-script/install
	$(INSTALL_DIR) $(1)/opt/lib/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/libjson_script.so $(1)/opt/lib/
endef

define Package/libubox-lua/install
	$(INSTALL_DIR) $(1)/opt/lib/lua
	$(CP) $(PKG_BUILD_DIR)/lua/uloop.so $(1)/opt/lib/lua/
endef

$(eval $(call BuildPackage,libubox))
$(eval $(call BuildPackage,libblobmsg-json))
$(eval $(call BuildPackage,jshn))
$(eval $(call BuildPackage,libjson-script))
$(eval $(call BuildPackage,libubox-lua))
