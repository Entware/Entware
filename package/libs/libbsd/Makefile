include $(TOPDIR)/rules.mk

PKG_NAME:=libbsd
PKG_VERSION:=0.11.8
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://libbsd.freedesktop.org/releases
PKG_HASH:=55fdfa2696fb4d55a592fa9ad14a9df897c7b0008ddb3b30c419914841f85f33

PKG_LICENSE:=BSD-4-Clause
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:freedesktop:libbsd

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1
PKG_BUILD_DEPENDS := libmd
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

define Package/libbsd
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=common BSD library
  ABI_VERSION:=0
endef

define Package/libbsd/description
 This library provides useful functions commonly found on BSD systems, and lacking on others like GNU systems, thus making it easier to port projects with strong BSD origins, without needing to embed the same code over and over again on each project.
endef

TARGET_CFLAGS += -D_LARGEFILE64_SOURCE

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/lib
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(INSTALL_DIR) $(1)/opt/include
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libbsd.{la,so*} $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libbsd*.pc $(1)/opt/lib/pkgconfig/
	$(CP) $(PKG_INSTALL_DIR)/opt/include/* $(1)/opt/include/
endef

define Package/libbsd/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libbsd.so.* $(1)/opt/lib/
endef

$(eval $(call BuildPackage,libbsd))
