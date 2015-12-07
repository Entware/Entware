#
# Copyright (C) 2009-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Downgraded from 0.14.1

include $(TOPDIR)/rules.mk

PKG_NAME:=isl
PKG_VERSION:=0.14

PKG_SOURCE_URL:=http://isl.gforge.inria.fr/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_MD5SUM:=404d5f4a94491529754c8538bbb238c0

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

unexport CFLAGS

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--with-libgmpxx-prefix=$(STAGING_DIR_HOST) \
	--with-gmp=system \
	--with-gmp-prefix=$(STAGING_DIR_HOST) \
	--with-piplib=no \
	--with-clang=no

$(eval $(call HostBuild))
