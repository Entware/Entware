#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libsepol
PKG_VERSION:=3.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/SELinuxProject/selinux/releases/download/3.2
PKG_HASH:=dfc7f662af8000116e56a01de6a0394ed79be1b34b999e551346233c5dd19508

PKG_MAINTAINER:=Thomas Petazzoni <thomas.petazzoni@bootlin.com>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/libsepol
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=SELinux binary policy manipulation library
  URL:=http://selinuxproject.org/page/Main_Page
endef

define Package/libsepol/description
	Libsepol is the binary policy manipulation library. It doesn't
	depend upon or use any of the other SELinux components.
endef

define Package/chkcon
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libsepol
  TITLE:=libsepol chkcon security context validation tool
  URL:=http://selinuxproject.org/page/Main_Page
endef

define Package/chkcon/description
	chkcon - determine if a security context is valid for a given binary policy
endef

HOST_MAKE_FLAGS += \
	PREFIX=$(STAGING_DIR_HOSTPKG) \
	SHLIBDIR=$(STAGING_DIR_HOSTPKG)/lib


MAKE_FLAGS := \
        $(TARGET_CONFIGURE_OPTS) \
        CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
        LDFLAGS="$(TARGET_LDFLAGS)" \
        COPTS="$(COPTS)" \
        PREFIX="/opt" \
	SHLIBDIR=/opt/lib \
	OS=Linux

define Build/Compile
	$(call Build/Compile/Default,all)
endef

define Build/Install
	$(call Build/Install/Default,install)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include
	$(CP) $(PKG_INSTALL_DIR)/opt/include/* $(1)/opt/include/
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/* $(1)/opt/lib/
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libsepol.pc $(1)/opt/lib/pkgconfig/
	$(SED) 's,/opt/include,$$$${prefix}/include,g' $(1)/opt/lib/pkgconfig/libsepol.pc
	$(SED) 's,/opt/lib,$$$${exec_prefix}/lib,g' $(1)/opt/lib/pkgconfig/libsepol.pc
endef

define Package/libsepol/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libsepol.so.* $(1)/opt/lib/
endef

define Package/chkcon/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/chkcon $(1)/opt/bin/
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libsepol))
$(eval $(call BuildPackage,chkcon))
