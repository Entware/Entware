# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=go-bin
PKG_VERSION:=1.4.2

uname_m=$(shell uname -m)
ifeq ($(uname_m),i386)
bintype=386
endif
ifeq ($(uname_m),x86_64)
bintype=amd64
endif

PKG_SOURCE:=go$(PKG_VERSION).linux-$(bintype).tar.gz
PKG_SOURCE_URL:=https://storage.googleapis.com/golang
HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
endef

define Host/Install
endef

define Host/Clean
endef

$(eval $(call HostBuild))
