#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libselinux
PKG_VERSION:=3.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/SELinuxProject/selinux/releases/download/20200710
PKG_HASH:=ea5dcbb4d859e3f999c26a13c630da2f16dff9462e3cc8cb7b458ac157d112e7
HOST_BUILD_DEPENDS:=libsepol/host pcre/host

PKG_MAINTAINER:=Thomas Petazzoni <thomas.petazzoni@bootlin.com>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/libselinux
  SECTION:=libs
  DEPENDS:=+libsepol +libpcre +USE_MUSL:musl-fts
  CATEGORY:=Libraries
  TITLE:=Runtime SELinux library
  URL:=http://selinuxproject.org/page/Main_Page
endef

define Package/libselinux/description
	libselinux is the runtime SELinux library that provides
	interfaces (e.g. library functions for the SELinux kernel
	APIs like getcon(), other support functions like
	getseuserbyname()) to SELinux-aware applications. libselinux
	may use the shared libsepol to manipulate the binary policy
	if necessary (e.g. to downgrade the policy format to an
	older version supported by the kernel) when loading policy.
endef

define Package/libselinux-utils
  SECTION:=utils
  DEPENDS:=+libselinux
  CATEGORY:=Utilities
  TITLE:=Runtime SELinux utilities
  URL:=http://selinuxproject.org/page/Main_Page
endef

# Needed to link libselinux utilities, which link against
# libselinux.so, which indirectly depends on libpcre.so, installed in
# $(STAGING_DIR_HOSTPKG).
HOST_LDFLAGS += -Wl,-rpath="$(STAGING_DIR_HOSTPKG)/lib"

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

ifdef CONFIG_USE_MUSL
MAKE_FLAGS += FTS_LDLIBS=-lfts
endif


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
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libselinux.pc $(1)/opt/lib/pkgconfig/
	$(SED) 's,/opt/include,$$$${prefix}/include,g' $(1)/opt/lib/pkgconfig/libselinux.pc
	$(SED) 's,/opt/lib,$$$${exec_prefix}/lib,g' $(1)/opt/lib/pkgconfig/libselinux.pc
endef

define Package/libselinux/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libselinux.so.* $(1)/opt/lib/
endef

define Package/libselinux-utils/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(CP) $(PKG_INSTALL_DIR)/opt/sbin/* $(1)/opt/sbin
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libselinux))
$(eval $(call BuildPackage,libselinux-utils))
