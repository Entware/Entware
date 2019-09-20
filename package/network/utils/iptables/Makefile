#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Entware specific: keep 1.4.21 version
# Do not split extensions into separate packages, do not install dev headers

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=iptables
PKG_VERSION:=1.4.21
PKG_RELEASE:=3

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://www.netfilter.org/projects/iptables/files \
	ftp://ftp.be.netfilter.org/pub/netfilter/iptables/ \
	ftp://ftp.de.netfilter.org/pub/netfilter/iptables/ \
	ftp://ftp.no.netfilter.org/pub/netfilter/iptables/
PKG_HASH:=52004c68021da9a599feed27f65defcfb22128f7da2c0531c0f75de0f479d3e0

PKG_FIXUP:=autoreconf

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1
PKG_LICENSE:=GPL-2.0
PKG_CPE_ID:=cpe:/a:netfilter_core_team:iptables

ifeq ($(CONFIG_PACKAGE_opt-ndmsv2),m)
PATCH_DIR:=./patches_kn
endif

include $(INCLUDE_DIR)/package.mk

define Package/iptables
  TITLE:=IP firewall administration tool
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Firewall
  URL:=http://netfilter.org/
ifeq ($(CONFIG_PACKAGE_opt-ndmsv2),m)
  PKGARCH:=$(BOARD)_kn
endif
endef

define Package/iptables/description
IP firewall administration tool.

 Matches:
  - icmp
  - tcp
  - udp
  - comment
  - conntrack
  - limit
  - mac
  - mark
  - multiport
  - set
  - state
  - time

 Targets:
  - ACCEPT
  - CT
  - DNAT
  - DROP
  - REJECT
  - LOG
  - MARK
  - MASQUERADE
  - REDIRECT
  - SET
  - SNAT
  - TCPMSS

 Tables:
  - filter
  - mangle
  - nat
  - raw

endef

TARGET_CPPFLAGS := \
	-I$(PKG_BUILD_DIR)/include \
	-I$(LINUX_DIR)/user_headers/include \
	$(TARGET_CPPFLAGS)

TARGET_CFLAGS += \
	-I$(PKG_BUILD_DIR)/include \
	-I$(LINUX_DIR)/user_headers/include \
	-ffunction-sections -fdata-sections \
	-DNO_LEGACY

TARGET_LDFLAGS += \
	-lm -Wl,--gc-sections

CONFIGURE_ARGS += \
	--enable-shared \
	--enable-devel \
	--with-kernel="$(LINUX_DIR)/user_headers" \
	--with-xtlibdir=/opt/lib/iptables \
	--enable-static \
	$(if $(CONFIG_IPV6),,--disable-ipv6)

MAKE_FLAGS := \
	$(TARGET_CONFIGURE_OPTS) \
	COPT_FLAGS="$(TARGET_CFLAGS)" \
	KERNEL_DIR="$(LINUX_DIR)/user_headers/" PREFIX=/opt \
	KBUILD_OUTPUT="$(LINUX_DIR)"

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include
	$(INSTALL_DIR) $(1)/opt/include/iptables
	$(INSTALL_DIR) $(1)/opt/include/net/netfilter

	# XXX: iptables header fixup, some headers are not installed by iptables anymore
	$(CP) $(PKG_BUILD_DIR)/include/iptables/*.h $(1)/opt/include/iptables/
	$(CP) $(PKG_BUILD_DIR)/include/iptables.h $(1)/opt/include/
	$(CP) $(PKG_BUILD_DIR)/include/ip6tables.h $(1)/opt/include/
	$(CP) $(PKG_BUILD_DIR)/include/libipulog $(1)/opt/include/
	$(CP) $(PKG_BUILD_DIR)/include/libiptc $(1)/opt/include/

	$(CP) $(PKG_INSTALL_DIR)/opt/include/* $(1)/opt/include/
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libxtables.so* $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libip*tc.so* $(1)/opt/lib/
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/xtables.pc $(1)/opt/lib/pkgconfig/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/libip*tc.pc $(1)/opt/lib/pkgconfig/

	# XXX: needed by firewall3
	$(CP) $(PKG_BUILD_DIR)/extensions/libiptext*.so $(1)/opt/lib/
endef

define Package/iptables/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/iptables-xml $(1)/opt/bin/
	$(INSTALL_DIR) $(1)/opt/sbin
	$(CP) $(PKG_INSTALL_DIR)/opt/sbin/* $(1)/opt/sbin/
	$(INSTALL_DIR) $(1)/opt/lib/iptables
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/*.so* $(1)/opt/lib/
	$(CP) $(PKG_BUILD_DIR)/extensions/*.so $(1)/opt/lib/
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/iptables/*.so* $(1)/opt/lib/iptables/
endef

$(eval $(call BuildPackage,iptables))
