#
# Copyright (C) 2016-2022 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=go-src
PKG_VERSION:=1.19.3
PKG_RELEASE:=1

PKG_SOURCE:=go$(PKG_VERSION).src.tar.gz
PKG_SOURCE_URL:=https://dl.google.com/go
PKG_HASH:=18ac263e39210bcf68d85f4370e97fb1734166995a1f63fb38b4f6e07d90d212

HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	( cd $(STAGING_DIR_HOST)/go/src; \
		GOROOT_BOOTSTRAP=$(STAGING_DIR_HOST)/go1.4 ./make.bash -no-clean=true; \
	)
endef

define Host/Install
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/go
endef

$(eval $(call HostBuild))
