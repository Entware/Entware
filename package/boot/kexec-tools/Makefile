#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=kexec-tools
PKG_VERSION:=2.0.28
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@KERNEL/linux/utils/kernel/kexec
PKG_HASH:=d2f0ef872f39e2fe4b1b01feb62b0001383207239b9f8041f98a95564161d053

PKG_CONFIG_DEPENDS := CONFIG_KEXEC_ZLIB CONFIG_KEXEC_LZMA

PKG_BUILD_FLAGS:=gc-sections

include $(INCLUDE_DIR)/package.mk

define Package/kexec-tools/Default
  SECTION:=utils
  CATEGORY:=Utilities
  URL:=https://github.com/horms/kexec-tools
endef

define Package/kexec-tools
  $(call Package/kexec-tools/Default)
  TITLE:=kexec-tools transition meta package
  DEPENDS:=+kexec
endef

define Package/kexec-tools/description
 kexec is a set of system calls that allows you to load
 another kernel from the currently executing Linux kernel.
 The kexec utility allows to load and boot another kernel.
endef

define Package/kexec
  $(call Package/kexec-tools/Default)
  TITLE:=Kernel boots kernel
  DEPENDS:=\
	@(armeb||arm||i386||x86_64||powerpc64||mipsel||mips) \
	+KEXEC_ZLIB:zlib +KEXEC_LZMA:liblzma @KERNEL_KEXEC
endef

define Package/kexec/description
 The kexec utility allows to load and boot another kernel.
endef

define Package/kdump
  $(call Package/kexec-tools/Default)
  TITLE:=Kernel crash analysis
  DEPENDS:=+kexec @(i386||x86_64||arm) @KERNEL_CRASH_DUMP
endef

define Package/kdump/description
 The kdump package allows to automatically boot into a
 special kernel for analyzing kernel crashes using kdump.
endef

define Package/kexec/config
	source "$(SOURCE)/Config.in"
endef

KEXEC_TARGET_NAME:=$(ARCH)-linux-$(TARGET_SUFFIX)

CONFIGURE_ARGS = \
		--target=$(KEXEC_TARGET_NAME) \
		--host=$(REAL_GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--program-prefix="" \
		--program-suffix="" \
		--prefix=/opt \
		--exec-prefix=/opt \
		--bindir=/opt/bin \
		--sbindir=/opt/sbin \
		--libexecdir=/opt/lib \
		--sysconfdir=/opt/etc \
		$(if $(CONFIG_KEXEC_ZLIB),--with,--without)-zlib \
		$(if $(CONFIG_KEXEC_LZMA),--with,--without)-lzma \
		TARGET_LD="$(TARGET_CROSS)ld"

CONFIGURE_VARS += \
	BUILD_CC="$(HOSTCC)" \
	TARGET_CC="$(TARGET_CC)"

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) DESTDIR="$(PKG_INSTALL_DIR)" all install
endef

define Package/kexec-tools/install
	:
endef

define Package/kexec/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/kexec $(1)/opt/sbin

# make a link for compatability with other distros
#	$(INSTALL_DIR) $(1)/sbin
#	$(LN) ../usr/sbin/kexec $(1)/sbin/kexec
endef

define Package/kdump/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/vmcore-dmesg $(1)/usr/sbin
endef

$(eval $(call BuildPackage,kexec-tools))
$(eval $(call BuildPackage,kexec))
$(eval $(call BuildPackage,kdump))
