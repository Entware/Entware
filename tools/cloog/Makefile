#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Upgraded from 0.18.1

include $(TOPDIR)/rules.mk

PKG_NAME:=cloog
PKG_VERSION:=0.18.4

PKG_SOURCE_URL:=http://www.bastoul.net/cloog/pages/download/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_MD5SUM:=e531f725244856c92c9bba009ff44faf

HOST_BUILD_PARALLEL:=1
HOST_CONFIGURE_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

unexport CFLAGS

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--with-bits=gm \
	--with-host-libstdcxx=-lstdc++ \
	--with-gmp=system \
	--with-gmp-prefix= $(TOPDIR)/staging_dir/host \
	--with-isl=system \
	--with-isl-prefix= $(TOPDIR)/staging_dir/host \
	--without-osl

$(eval $(call HostBuild))
