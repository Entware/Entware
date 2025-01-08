# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2016-2024 Entware

include $(TOPDIR)/rules.mk

PKG_NAME:=go-src
PKG_VERSION:=1.23.4
PKG_RELEASE:=1

PKG_SOURCE:=go$(PKG_VERSION).src.tar.gz
PKG_SOURCE_URL:=\
		https://dl.google.com/go/ \
                https://mirrors.ustc.edu.cn/golang/ \
                https://mirrors.nju.edu.cn/golang/
PKG_HASH:=ad345ac421e90814293a9699cca19dd5238251c3f687980bbcae28495b263531

HOST_BUILD_DIR:=$(STAGING_DIR_HOST)/go

BOOTSTRAP_VERSION:= \
	$(shell grep '^PKG_VERSION' ../go-bootstrap/Makefile | cut -b14-17 )

include $(INCLUDE_DIR)/host-build.mk

define Host/Configure
endef

define Host/Compile
	( cd $(STAGING_DIR_HOST)/go/src; \
		GOROOT_BOOTSTRAP=$(STAGING_DIR_HOST)/go$(BOOTSTRAP_VERSION) \
		./make.bash; \
	)
	( cd $(STAGING_DIR_HOST)/bin; \
		for bins in go gofmt; do ln -nsf ../go/bin/$$$$bins $$$$bins; done \
	)
endef

define Host/Install
endef

define Host/Clean
	rm -f $(STAGING_DIR_HOST)/bin/go{,fmt}
	rm -rf $(STAGING_DIR_HOST)/go
endef

$(eval $(call HostBuild))
