# Strip is not recommended for go binaries. It may make binaries unusable
RSTRIP:=:
STRIP:=:

GO_BIN:=$(GOROOT)/bin/go

#GO_LDFLAGS:=
GO_TARGET ?= .
GO_VARS ?=

GO_LDFLAGS = -s -w

ifeq ($(PKG_CGO_ENABLED),1)
GO_LDFLAGS += -I /opt/lib/$(DYNLINKER)
GO_VARS += \
	CGO_ENABLED=1 \
	CC=$(TARGET_CC) \
	CXX=$(TARGET_CXX)
else
GO_VARS += \
	CGO_ENABLED=0
endif

GO_VARS += GOOS=linux

ifeq ($(ARCH),aarch64)
GOARCH:=arm64
endif

ifeq ($(ARCH),arm)
GOARCH:=arm
  ifeq ($(ARCH_SUFFIX),_cortex-a9)
    ifeq ($(BUILD_VARIANT),nohf)
	GO_VARS += GOARM=5
    else
	GO_VARS += GOARM=7
    endif
  else
	GO_VARS += GOARM=5
  endif
endif

ifeq ($(ARCH),i386)
GOARCH:=386
endif

ifeq ($(ARCH),mips)
GOARCH:=mips
GO_VARS += GOMIPS=softfloat
endif

ifeq ($(ARCH),mipsel)
GOARCH:=mipsle
GO_VARS += GOMIPS=softfloat
endif

ifeq ($(ARCH),x86_64)
GOARCH:=amd64
endif

GO_VARS += \
	GOARCH=$(GOARCH) \
	GOPATH=$(TMP_DIR)/go-build

GO_BUILD_CMD ?= $(GO_VARS) $(GO_BIN) build
# verbose
GO_BUILD_CMD += $(if $(OPENWRT_VERBOSE),-v -x)
# -some1 -some2
GO_BUILD_CMD += -trimpath $(if $(GO_BUILD_ARGS),$(GO_BUILD_ARGS))
# PKG_INSTALL_DIR
GO_BUILD_CMD += -o $(PKG_INSTALL_DIR)/bin/
# -X '$(PKG_GOGET).some1=some2'
GO_BUILD_CMD += -ldflags="$(GO_LDFLAGS)"
# -tags=some
GO_BUILD_CMD += $(if $(GO_TAGS),$(GO_TAGS))
# ./cmd/... ./dir/path1 ./dir/path2
GO_BUILD_CMD += $(GO_TARGET)

define Build/Configure/Go
endef

define Build/Compile/Go
	( \
		cd $(PKG_BUILD_DIR)$(if $(GO_SRC_SUBDIR),/$(GO_SRC_SUBDIR)); \
		$(GO_BUILD_CMD); \
	)
endef

define Build/Install/Go
endef

Build/Configure=$(call Build/Configure/Go)
Build/Compile=$(call Build/Compile/Go)
Build/Install=$(call Build/Install/Go)
