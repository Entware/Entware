# Entware specifics: added -DHAVE_GETENTROPY=OFF

include $(TOPDIR)/rules.mk

PKG_NAME:=libxml2
PKG_VERSION:=2.15.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@GNOME/libxml2/$(basename $(PKG_VERSION))
PKG_HASH:=98087fd181d9070724f3fbc65c7377db03038eb92bd882374daff44940138821

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=Copyright
PKG_CPE_ID:=cpe:/a:xmlsoft:libxml2
HOST_BUILD_DEPENDS := libiconv-full/host

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk
include $(INCLUDE_DIR)/nls.mk

define Package/libxml2
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Gnome XML library
  URL:=https://gitlab.gnome.org/GNOME/libxml2
  DEPENDS:=+libpthread +zlib $(ICONV_DEPENDS)
  ABI_VERSION:=16
endef

define Package/libxml2/description
 A library for manipulating XML and HTML resources.
endef

define Package/libxml2-dev
  SECTION:=devel
  CATEGORY:=Development
  SUBMENU:=Libraries
  TITLE:=Development files for libxml2
  URL:=https://gitlab.gnome.org/GNOME/libxml2
  DEPENDS:=+libxml2
endef

define Package/libxml2-dev/description
  A library for manipulating XML and HTML resources.

  This package contains the headers and xml2-config binary.
endef

define Package/libxml2-utils
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=XML command line utilities (xmllint...)
  URL:=https://gitlab.gnome.org/GNOME/libxml2
  DEPENDS:=+libxml2
endef

define Package/libxml2-utils/description
  This package contains the binaries xmllint and xmlcatalog
  from libxml2, a library for manipulating XML and HTML resources.
endef

CMAKE_HOST_OPTIONS += \
	-DBUILD_SHARED_LIBS=OFF \
	-DLIBXML2_WITH_ISO8859X=OFF \
	-DLIBXML2_WITH_MODULES=OFF \
	-DLIBXML2_WITH_PROGRAMS=OFF \
	-DLIBXML2_WITH_TESTS=OFF \
	-DLIBXML2_WITH_ZLIB=ON

CMAKE_OPTIONS += \
	-DLIBXML2_WITH_ISO8859X=OFF \
	-DLIBXML2_WITH_MODULES=OFF \
	-DLIBXML2_WITH_TESTS=OFF \
	-DLIBXML2_WITH_ZLIB=ON \
	-DHAVE_GETENTROPY=OFF

define Build/InstallDev
	$(INSTALL_DIR) $(2)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/xml2-config \
		$(2)/bin/$(GNU_TARGET_NAME)-xml2-config
	$(SED) 's,^\(prefix\|exec_prefix\)=.*,\1=$(STAGING_DIR)/opt,g' \
		$(2)/bin/$(GNU_TARGET_NAME)-xml2-config
	$(LN) $(GNU_TARGET_NAME)-xml2-config $(2)/bin/xml2-config

	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/xmlcatalog $(1)/opt/bin/
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/xmllint $(1)/opt/bin/

	$(INSTALL_DIR) $(1)/opt/include
	$(CP) $(PKG_INSTALL_DIR)/opt/include/libxml2 $(1)/opt/include/

	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libxml2.so* $(1)/opt/lib/

	$(INSTALL_DIR) $(1)/opt/lib/cmake/libxml2
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/cmake/libxml2/*.cmake \
		$(1)/opt/lib/cmake/libxml2

	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libxml-2.0.pc $(1)/opt/lib/pkgconfig/
endef

define Host/Install
	$(call Host/Install/Default)
	mv $(1)/bin/xml2-config $(1)/bin/$(GNU_HOST_NAME)-xml2-config
	$(LN) $(GNU_HOST_NAME)-xml2-config $(1)/bin/xml2-config
endef

define Package/libxml2/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libxml2.so.* $(1)/opt/lib/
endef

define Package/libxml2-dev/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/xml2-config $(1)/opt/bin/
	$(SED) "s,$(STAGING_DIR),,g" $(1)/opt/bin/xml2-config

	$(INSTALL_DIR) $(1)/opt/include/
	$(CP) $(PKG_INSTALL_DIR)/opt/include/* $(1)/opt/include/

	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libxml2.so $(1)/opt/lib/

	$(INSTALL_DIR) $(1)/opt/lib/{cmake,pkgconfig}
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/{cmake,pkgconfig} $(1)/opt/lib/
	$(SED) "s,$(STAGING_DIR),,g" $(1)/opt/lib/pkgconfig/*.pc

	# XXX Entware specific: fix paths
	$(SED) 's,/lib/libiconv-full,,g' \
		$(1)/opt/bin/xml2-config $(1)/opt/lib/pkgconfig/*.pc
endef

define Package/libxml2-utils/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/xmllint $(1)/opt/bin/
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/xmlcatalog $(1)/opt/bin/
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libxml2))
$(eval $(call BuildPackage,libxml2-dev))
$(eval $(call BuildPackage,libxml2-utils))
