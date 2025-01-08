# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2016-2024 Entware

include $(TOPDIR)/rules.mk

PKG_NAME:=go-bootstrap
PKG_VERSION:=1.20.14
PKG_RELEASE:=1

OS=$(shell uname | tr '[:upper:]' '[:lower:]')
BINTYPE=$(shell uname -m | sed 's/aarch64/arm64/;s/i[3-6]86/386/;s/x86_64/amd64/')

PKG_SOURCE:=go$(PKG_VERSION).$(OS)-$(BINTYPE).tar.gz
PKG_SOURCE_URL:=https://storage.googleapis.com/golang
PKG_HASH:=ff445e48af27f93f66bd949ae060d97991c83e11289009d311f25426258f9c44

BOOTSTRAP_VERSION:=$(subst $(space),.,$(wordlist 1,2,$(subst .,$(space),$(PKG_VERSION))))

HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go$(BOOTSTRAP_VERSION)
HOST_UNPACK:=gzip -dc $(DL_DIR)/$(PKG_SOURCE) | tar -C $(HOST_BUILD_DIR) --strip-components=1 -xf -

include $(INCLUDE_DIR)/host-build.mk

#build go for all architetures - in case gccgo does not work

define Host/Configure
endef

define Host/Compile
endef

define Host/Install
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/go$(BOOTSTRAP_VERSION)
endef

$(eval $(call HostBuild))
