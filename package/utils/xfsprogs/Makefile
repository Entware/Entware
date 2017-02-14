#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=xfsprogs
PKG_RELEASE:=1
PKG_VERSION:=3.1.7
PKG_SOURCE_URL:=ftp://oss.sgi.com/projects/xfs/previous/
PKG_HASH:=e150914210ac5fd29c098ef0fd94bdec51d2fb231cf9faa765c16ec6d75c8eaa

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_INSTALL:=1
PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/xfsprogs/default
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Filesystem
  DEPENDS:=+libuuid +libpthread +librt
  URL:=http://oss.sgi.com/projects/xfs
endef

define Package/xfs-mkfs
$(call Package/xfsprogs/default)
  TITLE:=Utility for creating XFS filesystems
endef

define Package/xfs-fsck
$(call Package/xfsprogs/default)
  TITLE:=Utilities for checking and repairing XFS filesystems
endef

define Package/xfs-growfs
$(call Package/xfsprogs/default)
  TITLE:=Utility for increasing the size of XFS filesystems
endef

CONFIGURE_ARGS += \
	--enable-gettext=no \
	--enable-lib64=no \
	--enable-blkid=no

TARGET_CFLAGS += \
	-I$(STAGING_DIR)/opt/include \
	-D_LARGEFILE64_SOURCE \
	-D_FILE_OFFSET_BITS=64 \
	-D_GNU_SOURCE

MAKE_FLAGS += \
	DEBUG= Q= \
	PCFLAGS="-Wall" \
	PKG_PLATFORM=linux \
	ENABLE_GETTEXT=no \
	prefix=$(PKG_INSTALL_DIR)/opt \
	exec_prefix=$(PKG_INSTALL_DIR)/opt \
	PKG_SBIN_DIR=$(PKG_INSTALL_DIR)/opt/sbin \
	PKG_ROOT_SBIN_DIR=$(PKG_INSTALL_DIR)/opt/sbin \
	PKG_MAN_DIR=$(PKG_INSTALL_DIR)/opt/man \
	PKG_LOCALE_DIR=$(PKG_INSTALL_DIR)/opt/share/locale \
	PKG_ROOT_LIB_DIR=$(PKG_INSTALL_DIR)/opt/lib \
	PKG_DOC_DIR=$(PKG_INSTALL_DIR)/opt/share/doc/xfsprogs

define Package/xfs-mkfs/install
	mkdir -p $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/mkfs.xfs $(1)/opt/sbin
endef

define Package/xfs-fsck/install
	mkdir -p $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/xfs_repair $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/xfs_db $(1)/opt/sbin
endef

define Package/xfs-growfs/install
	mkdir -p $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/xfs_growfs $(1)/opt/sbin
endef

$(eval $(call BuildPackage,xfs-mkfs))
$(eval $(call BuildPackage,xfs-fsck))
$(eval $(call BuildPackage,xfs-growfs))
