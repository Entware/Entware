#
# Copyright (C) 2009-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=isl
PKG_VERSION:=0.14

PKG_SOURCE_URL:=http://isl.gforge.inria.fr/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_MD5SUM:=3d6b6a1cddd165fae2af5487c5531b09

HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

unexport CFLAGS

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--with-libgmpxx-prefix=$(TOPDIR)/staging_dir/host \
	--with-gmp=system \
	--with-gmp-prefix=$(TOPDIR)/staging_dir/host \
	--with-piplib=no \
	--with-clang=no \
	--with-gmp-prefix=$(TOPDIR)/staging_dir/host

$(eval $(call HostBuild))
