include $(TOPDIR)/rules.mk

PKG_NAME:=ubus
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/ubus.git
PKG_SOURCE_DATE:=2025-12-02
PKG_SOURCE_VERSION:=3cc98db1a422dcf560f2d6347fd410f17565a89d
PKG_MIRROR_HASH:=25a204888b41e9a432ee0b8d03c1e0f09ae9aaae6a306c41781d680b632b82ae
PKG_ABI_VERSION:=$(call abi_version_str,$(PKG_SOURCE_DATE))
CMAKE_INSTALL:=1

PKG_LICENSE:=LGPL-2.1
PKG_LICENSE_FILES:=
PKG_MAINTAINER:=Entware team, https://entware.net

PKG_BUILD_FLAGS:=lto
PKG_ASLR_PIE_REGULAR:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/ubus
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+libubus +libblobmsg-json +ubusd
  TITLE:=OpenWrt RPC client utility
endef

define Package/ubusd
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=OpenWrt RPC daemon
  DEPENDS:=+libubox +libblobmsg-json
  USERID:=ubus=81:ubus=81
endef

define Package/libubus
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libubox
  ABI_VERSION:=$(PKG_ABI_VERSION)
  TITLE:=OpenWrt RPC client library
endef

define Package/libubus-lua
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libubus +liblua
  TITLE:=Lua binding for the OpenWrt RPC client
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/opt/include

CMAKE_OPTIONS += \
	-DLUAPATH=/opt/lib/lua \
	-DABIVERSION="$(PKG_ABI_VERSION)"

define Package/ubus/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/ubus $(1)/opt/bin/
endef

define Package/ubusd/install
	$(INSTALL_DIR) $(1)/opt/sbin $(1)/opt/etc/init.d
	$(CP) $(PKG_INSTALL_DIR)/opt/sbin/ubusd $(1)/opt/sbin/
	$(INSTALL_BIN) ./files/S45ubusd $(1)/opt/etc/init.d/
endef

define Package/libubus/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libubus.so.* $(1)/opt/lib/
endef

define Package/libubus-lua/install
	$(INSTALL_DIR) $(1)/opt/lib/lua
	$(CP) $(PKG_BUILD_DIR)/lua/ubus.so $(1)/opt/lib/lua/
endef

$(eval $(call BuildPackage,libubus))
$(eval $(call BuildPackage,libubus-lua))
$(eval $(call BuildPackage,ubus))
$(eval $(call BuildPackage,ubusd))
