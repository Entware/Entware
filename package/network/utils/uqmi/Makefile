include $(TOPDIR)/rules.mk

PKG_NAME:=uqmi
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(PROJECT_GIT)/project/uqmi.git
PKG_SOURCE_DATE:=2024-04-24
PKG_SOURCE_VERSION:=e7207bec95f02f2f7a98254d642186a082af838d
PKG_MIRROR_HASH:=53e83720472f07cb9bb3e2b68ea6c379fc8c43ed8f93227bcb3d06c94a32a669
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
