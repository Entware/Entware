#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libtool
PKG_VERSION:=2.4.7
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNU/libtool
PKG_HASH:=4f7f217f057ce655ff22559ad221a0fd8ef84ad1fc5fcb6990cecc333aa1635d

PKG_LICENSE:=GPL-2.0+
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:gnu:libtool

PKG_BUILD_PARALLEL:=0

include $(INCLUDE_DIR)/package.mk

CONFIGURE_PREFIX=$(STAGING_DIR_HOSTPKG)
export GLOBAL_LIBDIR=$(STAGING_DIR)/opt/lib

define Package/libltdl
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=A generic dynamic object loading library
  URL:=http://www.gnu.org/software/libtool/
  ABI_VERSION:=7
endef

define Build/InstallDev
	$(MAKE) -C $(PKG_BUILD_DIR) \
		bindir="$(2)/libltdl/bin" \
		datadir="$(2)/libltdl/share" \
		prefix="$(2)/libltdl" \
		exec_prefix="$(2)/libltdl" \
		install
	$(INSTALL_DIR) $(1)/opt/lib $(1)/opt/include
	mv $(2)/libltdl/lib/* $(1)/opt/lib/
	mv $(2)/libltdl/include/* $(1)/opt/include/
endef

define Package/libltdl/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_BUILD_DIR)/libltdl/.libs/libltdl.so.* $(1)/opt/lib/
endef

$(eval $(call BuildPackage,libltdl))
