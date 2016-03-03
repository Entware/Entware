# Strip is not recommended for go binaries. It may make binaries unusable
STRIP:=:

# Template for GO package 
define Package/gopackage/Default
	SECTION:=Go
	CATEGORY:=Go
	DEPENDS:=@INSTALL_GCCGO +libgo +libpthread
	MAINTAINER:=Entware team, http://entware.net
endef

# use `go get -d` to retrieve  GO package sources when PKG_SOURCE is undefined, patch if patches dir present

ifeq ($(PKG_SOURCE),)
 define Build/Prepare
		$(INSTALL_DIR) $(PKG_BUILD_DIR)
		GOPATH=$(PKG_BUILD_DIR) ego get -d -x $(PKG_GOGET)
		$(Build/Patch)
 endef
endif

# use standard procedure to download and unpack GO package sources (stored in http://pkg.entware.net/sources/go).
# Do not patch. This allows to fix version

ifneq ($(PKG_SOURCE),)
PKG_SOURCE_URL:=http://pkg.entware.net/sources/go
PKG_UNPACK=$(TAR) -C $(PKG_BUILD_DIR) -xf $(DL_DIR)/$(PKG_SOURCE)
 define Build/Patch
 endef
 define Build/Prepare
		$(call Build/Prepare/Default)
 endef
endif

# pack the GO package sources retrieved by go get when PKG_SOURCE is undefined.
# Upload them to http://pkg.entware.net/sources/go manually!

ifeq ($(PKG_SOURCE),)
 define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		rm -f $(DL_DIR)/$(GOARCH) ; \
		tar cjf $(DL_DIR)/$(GOARCH) ./src --exclude-vcs ; \
	)
 endef
endif

# Do nothing if PKG_SOURCE is defined
ifneq ($(PKG_SOURCE),)
 define Build/Configure
 endef
endif

# Compile with gccgo using special patched ego version of go

define Build/Compile
	GOPATH=$(PKG_BUILD_DIR) gcc=$(TARGET_CC) ego get -x -compiler gccgo -gccgoflags '$(TARGET_GCCGOFLAGS)' $(PKG_GOGET)
endef
