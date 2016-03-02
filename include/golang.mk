STRIP:=:
ifneq ($(PKG_SOURCE),)
	PATCH_DIR=
endif

ifeq ($(PKG_SOURCE),)
 define Build/Prepare
		$(INSTALL_DIR) $(PKG_BUILD_DIR)
		GOPATH=$(PKG_BUILD_DIR) gcc=$(TARGET_CC) ego get -d -x $(PKG_GOGET)
		$(Build/Patch)
 endef
endif

ifneq ($(PKG_SOURCE),)
PKG_SOURCE_URL:=http://pkg.entware.net/sources/go
 define Build/Prepare
		$(call Build/Prepare/Default)
 endef
endif

ifeq ($(PKG_SOURCE),)
 define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		rm -f $(DL_DIR)/GOARCH-$(PKG_NAME)-$(shell date +%Y-%m-%d).tar.bz ; \
		tar cjf $(DL_DIR)/GOARCH-$(PKG_NAME)-$(shell date +%Y-%m-%d).tar.bz2 ./src --exclude-vcs ; \
	)
 endef
endif

define Build/Compile
	GOPATH=$(PKG_BUILD_DIR) gcc=$(TARGET_CC) ego get -x -compiler gccgo -gccgoflags '$(TARGET_GCCGOFLAGS)' $(PKG_GOGET)
endef
