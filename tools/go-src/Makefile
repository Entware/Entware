#
# Copyright (C) 2016-2019 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=go-src
PKG_VERSION:=1.19.2

PKG_SOURCE:=go$(PKG_VERSION).src.tar.gz
PKG_SOURCE_URL:=https://dl.google.com/go
HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go
PKG_HASH:=2ce930d70a931de660fdaf271d70192793b1b240272645bf0275779f6704df6b

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	(cd $(STAGING_DIR_HOST)/go/src ; \
		GOROOT_BOOTSTRAP=$(STAGING_DIR_HOST)/go1.4 ./make.bash --no-clean ; \
	)
endef

define Host/Install
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/go
endef

$(eval $(call HostBuild))
