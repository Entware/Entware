# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=go-src
PKG_VERSION:=1.4.2

PKG_SOURCE:=go$(PKG_VERSION).src.tar.gz
PKG_SOURCE_URL:=https://storage.googleapis.com/golang
PKG_MD5SUM:=907f85c8fa765d31f7f955836fec4049
HOST_BUILD_DIR=$(BUILD_DIR_HOST)/go.$(PKG_VERSION)
HOST_UNPACK:=gzip -dc $(DL_DIR)/$(PKG_SOURCE) | tar -C $(HOST_BUILD_DIR) --strip-components=1 -xf -

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	(cd $(HOST_BUILD_DIR)/src/cmd/go; \
		GOROOT=$(STAGING_DIR_HOST)/go \
		$(STAGING_DIR_HOST)/go/bin/go build -x -o ego  . \
	)
endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/bin
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/src/cmd/go/ego $(STAGING_DIR_HOST)/bin
endef


$(eval $(call HostBuild))
