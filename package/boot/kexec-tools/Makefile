#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=kexec-tools
PKG_VERSION:=2.0.9
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@KERNEL/linux/utils/kernel/kexec
PKG_MD5SUM:=6681319934e22e74c532bd392ccb1bbb

PKG_FIXUP:=autoreconf

PKG_CONFIG_DEPENDS := CONFIG_KEXEC_ZLIB CONFIG_KEXEC_LZMA

include $(INCLUDE_DIR)/package.mk

define Package/kexec-tools
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+KEXEC_ZLIB:zlib +KEXEC_LZMA:liblzma
  TITLE:=Kernel boots kernel
  URL:=http://kernel.org/pub/linux/kernel/people/horms/kexec-tools/
  MAINTAINER:=Florian Fainelli <florian@openwrt.org>
  MENU:=1
endef

define Package/kexec-tools/description
 kexec is a set of systems call that allows you to load
 another kernel from the currently executing Linux kernel.
endef

define Package/kexec-tools/config
	source "$(SOURCE)/Config.in"
endef

KEXEC_TARGET_NAME:=$(call qstrip,$(CONFIG_KEXEC_TOOLS_TARGET_NAME))-linux-gnu

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
		$(if $(CONFIG_KEXEC_LZMA),--with,--without)-lzma

TARGET_CFLAGS += -ffunction-sections -fdata-sections
TARGET_LDFLAGS += -Wl,--gc-sections

CONFIGURE_VARS += \
	BUILD_CC="$(HOSTCC)" \
	TARGET_CC="$(TARGET_CC)"

kexec-extra-sbin-$(CONFIG_KEXEC_TOOLS_kdump) += kdump

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) DESTDIR="$(PKG_INSTALL_DIR)" all install
endef

define Package/kexec-tools/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) \
		$(addprefix $(PKG_INSTALL_DIR)/opt/sbin/, \
			$(kexec-extra-sbin-y)) \
		$(kexec-extra-bin-y) \
		$(PKG_INSTALL_DIR)/opt/sbin/kexec \
		$(1)/opt/sbin
endef

$(eval $(call BuildPackage,kexec-tools))
