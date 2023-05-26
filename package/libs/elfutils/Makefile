#
# Copyright (C) 2010-2019 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=elfutils
PKG_VERSION:=0.189
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://sourceware.org/$(PKG_NAME)/ftp/$(PKG_VERSION)
PKG_HASH:=39bd8f1a338e2b7cd4abc3ff11a0eddc6e690f69578a57478d8179b4148708c8

PKG_MAINTAINER:=Luiz Angelo Daros de Luca <luizluca@gmail.com>
PKG_LICENSE:=GPL-3.0-or-later
PKG_LICENSE_FILES:=COPYING COPYING-GPLV2 COPYING-LGPLV3
PKG_CPE_ID:=cpe:/a:elfutils_project:elfutils

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_BUILD_DEPENDS:=!USE_GLIBC:argp-standalone

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/elfutils/Default
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=ELF manipulation libraries
  URL:=https://fedorahosted.org/elfutils/
  ABI_VERSION:=1
endef

define Package/libasm
  $(call Package/elfutils/Default)
  TITLE+= (libasm)
  DEPENDS:=+libelf +libdw
endef

define Package/libdw
  $(call Package/elfutils/Default)
  DEPENDS:=+libelf +libbz2 +USE_MUSL:musl-fts
  TITLE+= (libdw)
endef

define Package/libelf
  $(call Package/elfutils/Default)
  DEPENDS:=$(INTL_DEPENDS) +zlib
  TITLE+= (libelf)
  PROVIDES:=libelf1
endef

ifeq ($(CONFIG_BUILD_NLS),y)
TARGET_LDFLAGS += -lintl
else
CONFIGURE_ARGS += --disable-nls
endif

HOST_CONFIGURE_ARGS += \
	--disable-shared \
	--disable-nls \
	--disable-debuginfod \
	--disable-libdebuginfod \
	--without-bzlib \
	--without-lzma \
	--without-zstd

CONFIGURE_ARGS += \
	--program-prefix=eu- \
	--disable-debuginfod \
	--disable-libdebuginfod \
	--without-bzlib \
	--without-lzma \
	--without-zstd

HOST_CONFIGURE_VARS += \
	ac_cv_search__obstack_free=yes

CONFIGURE_VARS += \
	ac_cv_search__obstack_free=yes

TARGET_CFLAGS += \
	-D_GNU_SOURCE \
	-Wno-unused-result \
	-Wno-format-nonliteral

# XXX Entware specific: GCC-8.x.x (cc1: error: -Werror=use-after-free: no option -Wuse-after-free)
#ifneq ($(CONFIG_GCC_USE_VERSION_11),y)
TARGET_CFLAGS += \
	$(if $(CONFIG_GCC_USE_VERSION_8),,-Wno-error=use-after-free)
#endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include
	$(CP) $(PKG_INSTALL_DIR)/opt/include/* $(1)/opt/include/
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libasm*.{a,so*} $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libdw*.{a,so*} $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libelf*.{a,so*} $(1)/opt/lib/
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libelf.pc $(1)/opt/lib/pkgconfig/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libdw.pc $(1)/opt/lib/pkgconfig/
endef

define Package/libasm/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libasm{-*.so,*.so.*} $(1)/opt/lib/
endef

define Package/libdw/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libdw{-*.so,*.so.*} $(1)/opt/lib/
endef

define Package/libelf/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libelf{-*.so,*.so.*} $(1)/opt/lib/
endef

# these lines need to be ordered by dependency because of ABI versioning
$(eval $(call BuildPackage,libelf))
$(eval $(call BuildPackage,libdw))
$(eval $(call BuildPackage,libasm))
