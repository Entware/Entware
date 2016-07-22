#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Static opkg for MIPS, enable large partitions support, revert 'upgrade all'

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/version.mk
include $(INCLUDE_DIR)/feeds.mk

PKG_NAME:=opkg
PKG_REV:=9c97d5ecd795709c8584e972bfdf3aee3a5b846d
PKG_VERSION:=$(PKG_REV)
PKG_RELEASE:=12

PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_SUBDIR:=opkg-$(PKG_VERSION)
PKG_SOURCE_URL:=http://git.yoctoproject.org/git/opkg
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.gz
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)
PKG_FIXUP:=autoreconf
PKG_REMOVE_FILES = autogen.sh aclocal.m4

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=COPYING

PKG_MAINTAINER:=Jo-Philipp Wich <jow@openwrt.org>

PKG_CONFIG_DEPENDS := CONFIG_SIGNED_PACKAGES

PKG_BUILD_PARALLEL:=1
HOST_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/opkg/Default
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=opkg package manager
  URL:=http://wiki.openmoko.org/wiki/Opkg
  MENU:=1
endef

define Package/opkg/Default/description
  Lightweight package management system
  opkg is the opkg Package Management System, for handling
  installation and removal of packages on a system. It can
  recursively follow dependencies and download all packages
  necessary to install a particular package.

  opkg knows how to install both .ipk and .deb packages.
endef

define Package/opkg/config
config OPKG_SUPPORT_MD5
  bool
  default y
  depends on PACKAGE_opkg
  prompt "Support reading old md5 hashes."
  help
       Old opkg used md5s, new uses sha. This options enables understanding both while prefering sha.
endef

define Package/opkg
  $(call Package/opkg/Default)
  VARIANT:=unsigned
endef

define Package/opkg/description
  $(call Package/opkg/Default/description)
endef

define Package/opkg/conffiles
/opt/etc/opkg.conf
endef


define Package/opkg-smime
  $(call Package/opkg/Default)
  TITLE+= (with S/MIME signature support)
  DEPENDS+=+libopenssl
  VARIANT:=smime
endef

define Package/opkg-smime/description
  $(call Package/opkg/Default/description)

  This package allows the Package index to be verified with S/MIME.
endef

define Package/opkg-smime/config
config OPKG_SMIME_SUPPORT_MD5
  bool
  default y
  depends on PACKAGE_opkg-smime
  prompt "Support reading old md5 hashes."
  help
       Old opkg used md5s, new uses sha. This options enables understanding both while prefering sha.
endef

Package/opkg-smime/conffiles = $(Package/opkg/conffiles)

TARGET_CFLAGS += $(if $(CONFIG_GCC_VERSION_4_3)$(CONFIG_GCC_VERSION_4_4),-Wno-array-bounds)
TARGET_CFLAGS += -ffunction-sections -fdata-sections -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += $(TARGET_CPPFLAGS)
#!!!TARGET_LDFLAGS += --static

CONFIGURE_ARGS += \
	--disable-curl \
	--disable-gpg \
	--enable-sha256 \
	--with-opkgetcdir=/opt/etc \
	--with-opkglibdir=/opt/lib \
	--with-opkglockfile=/opt/var/lock/opkg.lock

ifeq ($(BUILD_VARIANT),smime)
    CONFIGURE_ARGS += --enable-openssl --enable-sha256
  ifeq ($(CONFIG_OPKG_SMIME_SUPPORT_MD5),y)
    CONFIGURE_ARGS += --enable-md5
  else
    CONFIGURE_ARGS += --disable-md5
  endif
endif

MAKE_FLAGS = \
		CC="$(TARGET_CC)" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		HOST_CPU="$(PKGARCH)" \
		LDFLAGS="-Wl,--gc-sections $(TARGET_LDFLAGS)" \

#	$(INSTALL_DATA) ./files/opkg.conf.$(CONFIG_ARCH) $(1)/opt/etc/opkg.conf
define Package/opkg/Default/install
	$(INSTALL_DIR) $(1)/opt/lib/opkg
	$(INSTALL_DIR) $(1)/opt/{bin,etc,tmp}
	$(INSTALL_DIR) $(1)/opt/var/{lock,log,run}
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/opkg-cl $(1)/opt/bin/opkg
endef

Package/opkg/install = $(call Package/opkg/Default/install,$(1),)

define Package/opkg-smime/install
	$(call Package/opkg/Default/install,$(1),-smime)
	$(INSTALL_DIR) $(1)/opt/etc/ssl/certs
	$(if $(CONFIG_OPKGSMIME_CERT),$(INSTALL_DATA) $(call qstrip,$(CONFIG_OPKGSMIME_CERT)) $(1)/opt/etc/ssl/certs/opkg.pem,)
endef

define Build/InstallDev
	mkdir -p $(1)/opt/include
	$(CP) $(PKG_INSTALL_DIR)/opt/include/libopkg $(1)/opt/include/
endef


HOST_CONFIGURE_ARGS+= \
	--disable-curl \
	--disable-gpg \
	--enable-sha256 \
	--with-opkgetcdir=/etc \
	--with-opkglockfile=/tmp/opkg.lock

define Host/Compile
	+$(MAKE) $(HOST_JOBS) -C $(HOST_BUILD_DIR) CC="$(HOSTCC)" all
endef

define Host/Install
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/src/opkg-cl $(STAGING_DIR_HOST)/bin/opkg
endef

$(eval $(call BuildPackage,opkg))
$(eval $(call BuildPackage,opkg-smime))
$(eval $(call HostBuild))
