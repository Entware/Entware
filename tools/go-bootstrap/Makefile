#
# Copyright (C) 2016-2022 Entware
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=go-bootstrap
PKG_VERSION:=1.20.6
PKG_RELEASE:=1

OS=$(shell uname | tr 'A-Z' 'a-z')
BINTYPE=$(shell uname -m | sed 's/i[3-9]86/386/;s/x86_64/amd64/')

PKG_SOURCE:=go$(PKG_VERSION).$(OS)-$(BINTYPE).tar.gz
PKG_SOURCE_URL:=https://storage.googleapis.com/golang
PKG_HASH:=b945ae2bb5db01a0fb4786afde64e6fbab50b67f6fa0eb6cfa4924f16a7ff1eb

HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go1.20
HOST_UNPACK:=gzip -dc $(DL_DIR)/$(PKG_SOURCE) | tar -C $(HOST_BUILD_DIR) --strip-components=1 -xf -

include $(INCLUDE_DIR)/host-build.mk

#build go for all architetures - in case gccgo does not work

define Host/Compile
endef

define Host/Install
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/go1.17
endef

$(eval $(call HostBuild))
