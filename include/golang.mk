# Strip is not recommended for go binaries. It may make binaries unusable
RSTRIP:="/bin/true"

# Template for GO package 
define Package/gopackage/Default
	SUBMENU:=Go
	SECTION:=lang
	CATEGORY:=Languages
	MAINTAINER:=Entware team, https://entware.net
endef

# use `go get -d` to retrieve  GO package sources when PKG_SOURCE is undefined, patch if patches dir present

ifeq ($(PKG_SOURCE),)
 ifeq ($(PKG_COMMIT),)
  define Build/Prepare
		$(INSTALL_DIR) $(PKG_BUILD_DIR)
		GOPATH=$(PKG_BUILD_DIR) $(GOROOT)/bin/go get -d -x $(PKG_GOGET)
		$(Build/Patch)
  endef
  else
   define Build/Prepare
		$(INSTALL_DIR) $(PKG_BUILD_DIR)
		mkdir -p $(PKG_BUILD_DIR)/src/$(PKG_GOGET)
		( \
			cd $(PKG_BUILD_DIR)/src/$(PKG_GOGET)/..; \
			git clone https://$(PKG_GOGET); \
			cd $(PKG_BUILD_DIR)/src/$(PKG_GOGET); \
			git checkout $(PKG_COMMIT); \
		)
		$(Build/Patch)
  endef
 endif
endif

# use standard procedure to download and unpack GO package sources (stored in https://src.entware.net).
# Do not patch. This allows to fix version

ifneq ($(PKG_SOURCE),)
PKG_SOURCE_URL:=https://src.entware.net
PKG_UNPACK=$(TAR) -C $(PKG_BUILD_DIR) -xf $(DL_DIR)/$(PKG_SOURCE)
 define Build/Patch
 endef
 define Build/Prepare
		$(call Build/Prepare/Default)
 endef
endif

# pack the GO package sources retrieved by go get when PKG_SOURCE is undefined.
# Upload them to https://src.entware.net manually!

ifeq ($(PKG_SOURCE),)
 define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		rm -f $(DL_DIR)/$(GOPKG_SOURCE) ; \
		rm -rf `find . -type d -name .git` ; \
		tar cjf $(DL_DIR)/$(GOPKG_SOURCE) ./src ; \
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
	( \
		cd $(PKG_BUILD_DIR); \
		mkdir -p bin; \
		cd bin; \
		GOOS=linux GOARCH=$(GOARCH) $(GOARM) $(GOMIPS) GOPATH=$(PKG_BUILD_DIR) $(GOROOT)/bin/go build -ldflags="-s -w" -x -v $(PKG_GOGET) ; \
	)
endef
