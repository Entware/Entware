#
# Copyright (C) 2006-2015 OpenWrt.org
# Copyright (C) 2016 LEDE Project
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
PKG_RELEASE:=17c

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=http://git.yoctoproject.org/git/opkg
PKG_SOURCE_DATE:=2011-04-08
PKG_SOURCE_VERSION:=9c97d5ecd795709c8584e972bfdf3aee3a5b846d
PKG_MIRROR_HASH:=55e05270f3eb2f3aff5d3791463ce3d13b8197ca7b301cd58e731a249552c48f
PKG_FIXUP:=autoreconf
PKG_REMOVE_FILES = autogen.sh aclocal.m4

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=COPYING

PKG_MAINTAINER:=Jo-Philipp Wich <jo@mein.io>

PKG_FLAGS := nonshared
PKG_CONFIG_DEPENDS := CONFIG_SIGNED_PACKAGES

PKG_BUILD_PARALLEL:=1
HOST_BUILD_PARALLEL:=1
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/opkg
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=opkg package manager
#  DEPENDS:=+libpthread
  URL:=http://wiki.openmoko.org/wiki/Opkg
  MENU:=1
endef

define Package/opkg/description
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
  default n
  depends on PACKAGE_opkg
  prompt "Support reading old md5 hashes."
  help
	Old opkg used md5s, new uses sha. This options enables understanding both while prefering sha.
endef

#define Package/opkg/conffiles
#/opt/etc/opkg.conf
#endef

TARGET_CFLAGS += -ffunction-sections -fdata-sections -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += $(TARGET_CPPFLAGS)
#!!!TARGET_LDFLAGS + =$(if $(CONFIG_TARGET_mipselsf),--static)

CONFIGURE_ARGS += \
	--disable-curl \
	--disable-gpg \
	--enable-sha256 \
	--with-opkgetcdir=/opt/etc \
	--with-opkglibdir=/opt/lib \
	--with-opkglockfile=/opt/var/lock/opkg.lock

ifndef CONFIG_SIGNED_PACKAGES
  CONFIGURE_ARGS += --disable-usign
endif
ifeq ($(CONFIG_OPKG_SUPPORT_MD5),y)
  CONFIGURE_ARGS += --enable-md5
else
  CONFIGURE_ARGS += --disable-md5
endif

MAKE_FLAGS = \
		CC="$(TARGET_CC)" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		HOST_CPU="$(PKGARCH)" \
		LDFLAGS="-Wl,--gc-sections $(TARGET_LDFLAGS)" \

define Package/opkg/Default/install
	$(INSTALL_DIR) $(1)/opt/lib/opkg $(1)/opt/{bin,etc,tmp} $(1)/opt/var/{lock,log,run}
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/opkg-cl $(1)/opt/bin/opkg
endef

define Package/opkg/install
	$(call Package/opkg/Default/install,$(1),)
#  ifneq ($(CONFIG_SIGNED_PACKAGES),)
#	echo "option check_signature 1" >> $(1)/etc/opkg.conf
#  endif
#	mkdir $(1)/opt/sbin
#	$(INSTALL_BIN) ./files/opkg-key $(1)/opt/sbin/
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
$(eval $(call HostBuild))
