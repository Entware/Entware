#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=godep
PKG_VERSION:=2016-03-02

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/tools/godep.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=b32db8cfcaad4ba20d85667d0978d02e68a6207f
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/$(PKG_NAME)-$(PKG_VERSION)

HOST_UNPACK:=gzip -dc $(DL_DIR)/$(PKG_SOURCE) | tar -C $(HOST_BUILD_DIR)/src/github.com/tools/godep --strip-components=1 -xf -

include $(INCLUDE_DIR)/host-build.mk

define Host/Prepare
	mkdir -p $(HOST_BUILD_DIR)/src/github.com/tools/godep
	$(call Host/Prepare/Default)
endef

define Host/Compile
	GOPATH=$(HOST_BUILD_DIR) GOROOT=$(STAGING_DIR_HOST)/go $(STAGING_DIR_HOST)/go/bin/go get -x github.com/tools/godep
endef

define Host/Install
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/bin/godep $(STAGING_DIR_HOST)/bin/
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/bin/godep
endef

$(eval $(call HostBuild))
