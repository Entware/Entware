# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=ent-kernel
PKG_VERSION:=1

PKG_SOURCE:=kernel-a449bfd2b99a2b19fa64c176d385b29432327a12.tgz
PKG_SOURCE_URL:=http://entware.wl500g.info/sources
PKG_MD5SUM:=922640cfbe281688ff61197418f9784f
HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/linux-2.6.22.19

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	$(CP) ./files/utsrelease.h $(HOST_BUILD_DIR)/include/linux
endef

define Host/Install
endef

define Host/Clean
endef

$(eval $(call HostBuild))
