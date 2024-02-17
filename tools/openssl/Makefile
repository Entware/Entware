#
# Copyright (C) 2018-2023 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=openssl
PKG_BASE:=1.1.1
PKG_BUGFIX:=w
PKG_VERSION:=$(PKG_BASE)$(PKG_BUGFIX)
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:= \
	http://www.openssl.org/source/ \
	http://www.openssl.org/source/old/$(PKG_BASE)/ \
	http://ftp.fi.muni.cz/pub/openssl/source/ \
	http://ftp.fi.muni.cz/pub/openssl/source/old/$(PKG_BASE)/ \
	ftp://ftp.pca.dfn.de/pub/tools/net/openssl/source/ \
	ftp://ftp.pca.dfn.de/pub/tools/net/openssl/source/old/$(PKG_BASE)/

PKG_HASH:=cf3098950cb4d853ad95c0841f1f9c6d3dc102dccfcacd521d93925208b76ac8

PKG_LICENSE:=OpenSSL
PKG_LICENSE_FILES:=LICENSE
PKG_CPE_ID:=cpe:/a:openssl:openssl

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

# default target is gcc if we don't know the host system
OPENSSL_TARGET:=gcc
ifeq ($(HOST_OS),Darwin)
OPENSSL_TARGET:=darwin-$(HOST_ARCH)-cc
endif
ifeq ($(HOST_OS),Linux)
OPENSSL_TARGET:=linux-$(HOST_ARCH)
endif

ifneq ($(CONFIG_CCACHE),)
HOSTCC=$(HOSTCC_NOCACHE)
HOSTCXX=$(HOSTCXX_NOCACHE)
endif

HOST_CFLAGS += $(HOST_FPIC)
OPENSSL_OPTIONS := no-shared no-hw no-asm threads

define Host/Configure
	(cd $(HOST_BUILD_DIR); \
		./Configure $(OPENSSL_TARGET) \
		--prefix=$(STAGING_DIR_HOST) \
		--libdir=lib \
		$(HOST_CPPFLAGS) \
		$(HOST_LDFLAGS) \
		$(OPENSSL_OPTIONS) \
	)
endef

define Host/Compile
	+$(MAKE) $(PKG_JOBS) -C $(HOST_BUILD_DIR) \
		CC="$(HOSTCC)" \
		install_dev
endef

define Host/Install
	:
endef

$(eval $(call HostBuild))
