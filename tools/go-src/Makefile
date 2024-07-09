#
# Copyright (C) 2016-2022 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=go-src
PKG_VERSION:=1.22.5
PKG_RELEASE:=1

PKG_SOURCE:=go$(PKG_VERSION).src.tar.gz
PKG_SOURCE_URL:=https://dl.google.com/go
PKG_HASH:=ac9c723f224969aee624bc34fd34c9e13f2a212d75c71c807de644bb46e112f6

HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	( cd $(STAGING_DIR_HOST)/go/src; \
		GOROOT_BOOTSTRAP=$(STAGING_DIR_HOST)/go1.20 ./make.bash; \
	)
endef

define Host/Install
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/go
endef

$(eval $(call HostBuild))
