include $(TOPDIR)/rules.mk

PKG_NAME:=uqmi
PKG_RELEASE:=2

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/uqmi.git
PKG_SOURCE_DATE:=2024-08-25
PKG_SOURCE_VERSION:=28b48a10dbcd1177095b73c6d8086d10114f49b8
PKG_MIRROR_HASH:=ca4c07775185b873da572d973b9bbce86198d41d921a8d32b990da34e5ffd65d
PKG_MAINTAINER:=Matti Laakso <malaakso@elisanet.fi>

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=

PKG_FLAGS:=nonshared
PKG_BUILD_FLAGS:=gc-sections

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/uqmi
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=WWAN
  DEPENDS:=+libubox +libblobmsg-json
  TITLE:=Control utility for mobile broadband modems
endef

define Package/uqmi/description
  uqmi is a command line tool for controlling mobile broadband modems using
  the QMI-protocol.
endef

# XXX Entware specific: GCC-8.x.x (cc1: error: -Werror=dangling-pointer: no option -Wdangling-pointer)
TARGET_CFLAGS += \
	-I$(STAGING_DIR)/opt/include \
	$(if $(CONFIG_GCC_USE_VERSION_8),,-Wno-error=dangling-pointer) \
	-Wno-error=maybe-uninitialized

CMAKE_OPTIONS += \
	-DDEBUG=1

define Package/uqmi/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uqmi/uqmi $(1)/opt/sbin/
#	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,uqmi))
