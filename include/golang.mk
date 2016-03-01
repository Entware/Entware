STRIP:=:

define Build/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)
	GOPATH=$(PKG_BUILD_DIR) gcc=$(TARGET_CC) ego get -d -x $(PKG_GOGET)
	$(Build/Patch)
endef

define Build/Configure
endef

define Build/Compile
	GOPATH=$(PKG_BUILD_DIR) gcc=$(TARGET_CC) ego get -x -compiler gccgo -gccgoflags '$(TARGET_GCCGOFLAGS)' $(PKG_GOGET)
endef
