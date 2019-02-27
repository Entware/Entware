#
# Copyright (C) 2006-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=valgrind
PKG_VERSION:=3.14.0
PKG_RELEASE:=1a

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://sourceware.org/pub/valgrind/
PKG_HASH:=037c11bfefd477cc6e9ebe8f193bb237fe397f7ce791b4a4ce3fa1c6a520baa5

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>
PKG_LICENSE:=GPL-2.0+
PKG_CPE_ID:=cpe:/a:valgrind:valgrind

PKG_FIXUP = autoreconf
PKG_INSTALL := 1
PKG_BUILD_PARALLEL := 1
PKG_USE_MIPS16:=0
PKG_SSP:=0

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/valgrind
  SECTION:=devel
  CATEGORY:=Development
  DEPENDS:=+libpthread +librt
  TITLE:=debugging and profiling tools for Linux
  URL:=http://www.valgrind.org
endef

define Package/valgrind/default
  $(Package/valgrind)
  DEPENDS := valgrind
endef

define Package/valgrind-cachegrind
  $(Package/valgrind/default)
  TITLE += (cache profiling)
endef

define Package/valgrind-callgrind
  $(Package/valgrind/default)
  TITLE += (callgraph profiling)
endef

define Package/valgrind-drd
  $(Package/valgrind/default)
  TITLE += (thread error detection)
endef

define Package/valgrind-massif
  $(Package/valgrind/default)
  TITLE += (heap profiling)
endef

define Package/valgrind-helgrind
  $(Package/valgrind/default)
  TITLE += (thread debugging)
endef

define Package/valgrind-vgdb
  $(Package/valgrind/default)
  TITLE += (GDB interface)
endef

define Package/valgrind/description
	Valgrind is an award-winning suite of tools for debugging and
	profiling Linux programs. With the tools that come with Valgrind,
	you can automatically detect many memory management and threading
	bugs, avoiding hours of frustrating bug-hunting, making your
	programs more stable. You can also perform detailed profiling,
	to speed up and reduce memory use of your programs.
endef

CPU := $(patsubst x86_64,amd64,$(patsubst x86,i386,$(patsubst um,$(ARCH),$(LINUX_KARCH))))

CONFIGURE_VARS += \
	UNAME_R=$(LINUX_VERSION)

ifeq ($(CONFIG_ARCH_64BIT),y)
	CONFIGURE_ARGS += \
		--enable-only64bit
	BITS := 64bit
else
	CONFIGURE_ARGS += \
		--enable-only32bit
	BITS := 32bit
endif

ifeq ($(CONFIG_mips)$(CONFIG_mipsel),y)
TARGET_CFLAGS:=$(filter-out -mips32r2 ,$(TARGET_CFLAGS))
TARGET_CFLAGS += -march=mips32r2

CONFIGURE_VARS += \
	LTO_AR=$(TOOLCHAIN_DIR)/bin/$(TARGET_CROSS)ar \
	LTO_RANLIB=$(TOOLCHAIN_DIR)/bin/$(TARGET_CROSS)ranlib
endif

CONFIGURE_ARGS += \
	--enable-tls \
	--enable-lto \
	--with-tmpdir=/opt/tmp \
	--without-mpicc

define Package/valgrind/install	
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/valgrind* $(1)/opt/bin/
	$(INSTALL_DIR) $(1)/opt/lib/valgrind
	$(CP) \
		./files/default.supp \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/none-* \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/vgpreload_core*.so \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/$(BITS)-core*.xml \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/$(BITS)-linux*.xml \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/memcheck-* \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/vgpreload_memcheck*.so \
		$(1)/opt/lib/valgrind/
	$(SED) 's,:/lib,:/opt/lib,g' $(1)/opt/lib/valgrind/default.supp

ifneq ($(ARCH),aarch64)
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/$(CPU)-*.xml \
		$(1)/opt/lib/valgrind/
endif
endef

define Package/valgrind-cachegrind/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/cg_* $(1)/opt/bin/
	$(INSTALL_DIR) $(1)/opt/lib/valgrind
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/cachegrind-* \
		$(1)/opt/lib/valgrind/
	$(SED) 's,^#!.*,#!/opt/bin/perl,' $(1)/opt/bin/cg_{annotate,diff}
endef

define Package/valgrind-callgrind/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/callgrind* $(1)/opt/bin/
	$(INSTALL_DIR) $(1)/opt/lib/valgrind
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/callgrind-* \
		$(1)/opt/lib/valgrind/
	$(SED) 's,^#!.*,#!/opt/bin/perl -w,' $(1)/opt/bin/callgrind_{annotate,control}
endef

define Package/valgrind-drd/install
	$(INSTALL_DIR) $(1)/opt/lib/valgrind
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/drd-* \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/vgpreload_drd*.so \
		$(1)/opt/lib/valgrind/
endef

define Package/valgrind-massif/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/ms_print $(1)/opt/bin/
	$(INSTALL_DIR) $(1)/opt/lib/valgrind
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/massif-* \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/vgpreload_massif*.so \
		$(1)/opt/lib/valgrind/
	$(SED) 's,^#!.*,#!/opt/bin/perl,' $(1)/opt/bin/ms_print
endef

define Package/valgrind-helgrind/install
	$(INSTALL_DIR) $(1)/opt/lib/valgrind
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/helgrind-* \
		$(PKG_INSTALL_DIR)/opt/lib/valgrind/vgpreload_helgrind*.so \
		$(1)/opt/lib/valgrind/
endef

define Package/valgrind-vgdb/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/vgdb $(1)/opt/bin/
endef

$(eval $(call BuildPackage,valgrind))
$(eval $(call BuildPackage,valgrind-cachegrind))
$(eval $(call BuildPackage,valgrind-callgrind))
$(eval $(call BuildPackage,valgrind-drd))
$(eval $(call BuildPackage,valgrind-massif))
$(eval $(call BuildPackage,valgrind-helgrind))
$(eval $(call BuildPackage,valgrind-vgdb))
