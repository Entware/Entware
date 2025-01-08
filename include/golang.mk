# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2016-2024 Entware

include $(TOPDIR)/feeds/golang/go_env.mk

# Strip is not recommended for go binaries. It may make binaries unusable.
RSTRIP:=:
STRIP:=:

GO_BIN:=$(STAGING_DIR_HOST)/go/bin/go
#GO_BIN:=go
GO_BUILD_DIR ?= $(PKG_BUILD_DIR)$(if $(GO_SRC_SUBDIR),/$(GO_SRC_SUBDIR))

GO_BIN_GENERATE:= \
	$(GO_ENV_COMMON) \
	$(GO_BIN) generate

GO_BIN_GET:= \
	$(GO_ENV_COMMON) \
	$(GO_BIN) get $(if $(findstring s,$(OPENWRT_VERBOSE)),-v)

GO_BIN_MOD_DOWNLOAD:= \
	$(GO_ENV_COMMON) \
	$(GO_BIN) mod download

GO_BIN_MOD_TIDY:= \
	$(GO_ENV_COMMON) \
	$(GO_BIN) mod tidy $(if $(findstring s,$(OPENWRT_VERBOSE)),-v)

# strip bins
GO_LDFLAG:=-s -w -buildid=

GO_BUILD_CMD ?= build

# path to install bins
GO_BUILD_CMD += -o $(PKG_INSTALL_DIR)/bin/
# enable verbose
GO_BUILD_CMD += $(if $(findstring s,$(OPENWRT_VERBOSE)),-v -x)
# build args: -arg1 -arg2
GO_BUILD_CMD += $(if $(strip $(GO_BUILD_ARGS)),$(GO_BUILD_ARGS))
# disable VCS & strip FS paths
GO_BUILD_CMD += -buildvcs=false -trimpath
# add ext ldflags: -X '$(XIMPORTPATH).name1=value1'
GO_BUILD_CMD += -ldflags $(if $(strip $(GO_LDFLAGS)),"$(GO_LDFLAGS) $(GO_LDFLAG)","$(GO_LDFLAG)")
# add tags: -tags "tag1,tag2"
GO_BUILD_CMD += $(if $(strip $(GO_TAGS)),-tags "$(subst $(space),,$(GO_TAGS))")
# add targets: ./path1/to/target1 ./path2/to/target2
GO_BUILD_CMD += $(if $(strip $(GO_TARGET)),$(GO_TARGET))

define Build/Configure/Go
endef

define Build/Compile/Go
	( cd $(GO_BUILD_DIR); $(GO_VARS) $(GO_BIN) $(GO_BUILD_CMD); )
endef

define Build/Install/Go
endef

Build/Configure=$(call Build/Configure/Go)
Build/Compile=$(call Build/Compile/Go)
Build/Install=$(call Build/Install/Go)
