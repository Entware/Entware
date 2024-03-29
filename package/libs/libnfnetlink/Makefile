#
# Copyright (C) 2007-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libnfnetlink
PKG_VERSION:=1.0.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:= \
	http://www.netfilter.org/projects/libnfnetlink/files/ \
	ftp://ftp.netfilter.org/pub/libnfnetlink/
PKG_HASH:=b064c7c3d426efb4786e60a8e6859b82ee2f2c5e49ffeea640cfe4fe33cbc376
PKG_MAINTAINER:=Jo-Philipp Wich <jo@mein.io>
PKG_LICENSE:=GPL-2.0+
PKG_CPE_ID:=cpe:/a:netfilter:libnfnetlink

PKG_FIXUP:=autoreconf

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libnfnetlink
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=A low-level library for netfilter related kernel/userspace communication
  URL:=http://netfilter.org/projects/libnfnetlink/
  ABI_VERSION:=0
endef

define Package/libnfnetlink/description
 libnfnetlink is is the low-level library for netfilter related kernel/userspace communication.
 It provides a generic messaging infrastructure for in-kernel netfilter subsystems
 (such as nfnetlink_log, nfnetlink_queue, nfnetlink_conntrack) and their respective users
 and/or management tools in userspace.
endef

CONFIGURE_ARGS += \
	--enable-static \
	--enable-shared

CONFIGURE_VARS += \
	lt_prog_compiler_pic="$(FPIC)"

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include/libnfnetlink
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/include/libnfnetlink/{libnfnetlink,linux_nfnetlink,linux_nfnetlink_compat}.h \
		$(1)/opt/include/libnfnetlink/
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/libnfnetlink.{a,so*} \
		$(1)/opt/lib/
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libnfnetlink.pc \
		$(1)/opt/lib/pkgconfig/
endef

define Package/libnfnetlink/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/opt/lib/libnfnetlink.so.* \
		$(1)/opt/lib/
endef

$(eval $(call BuildPackage,libnfnetlink))
