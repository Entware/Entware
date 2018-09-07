#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=busybox
PKG_VERSION:=1.29.2
PKG_RELEASE:=1
PKG_FLAGS:=essential

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://www.busybox.net/downloads \
		http://sources.buildroot.net
PKG_HASH:=67d2fa6e147a45875fe972de62d907ef866fe784c495c363bf34756c444a5d61

PKG_BUILD_DEPENDS:=BUSYBOX_CONFIG_PAM:libpam
PKG_BUILD_PARALLEL:=1
PKG_CHECK_FORMAT_SECURITY:=0

#Busybox use it's own PIE config flag and LDFLAGS are used with ld, not gcc.
PKG_ASLR_PIE:=0

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=LICENSE archival/libarchive/bz/LICENSE
PKG_CPE_ID:=cpe:/a:busybox:busybox

include $(INCLUDE_DIR)/package.mk

ifeq ($(DUMP),)
  STAMP_CONFIGURED:=$(strip $(STAMP_CONFIGURED))_$(shell grep '^CONFIG_BUSYBOX_' $(TOPDIR)/.config | mkhash md5)
endif

BUSYBOX_SYM=$(if $(CONFIG_BUSYBOX_CUSTOM),CONFIG,DEFAULT)
BUSYBOX_IF_ENABLED=$(if $(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_$(1)),$(2))

define Package/busybox
  SECTION:=base
  CATEGORY:=Base system
  MAINTAINER:=Felix Fietkau <nbd@nbd.name>
  TITLE:=Core utilities for embedded Linux
  URL:=http://busybox.net/
  DEPENDS:=+BUSYBOX_CONFIG_PAM:libpam
  MENU:=1
endef

define Package/busybox/description
 The Swiss Army Knife of embedded Linux.
 It slices, it dices, it makes Julian Fries.
endef

define Package/busybox/config
	source "$(SOURCE)/Config.in"
endef

# don't create a version string containing the actual timestamp
export KCONFIG_NOTIMESTAMP=1


LDLIBS:=m crypt

LDLIBS += $(call BUSYBOX_IF_ENABLED,PAM,pam pam_misc pthread)
ifdef CONFIG_BUSYBOX_USE_LIBRPC
  LDLIBS += rpc
endif
ifeq ($(CONFIG_USE_GLIBC),y)
  LDLIBS += $(call BUSYBOX_IF_ENABLED,NSLOOKUP_OPENWRT,resolv)
endif

TARGET_CFLAGS += -flto
TARGET_LDFLAGS += -flto=jobserver -fuse-linker-plugin

MAKE_VARS :=
MAKE_FLAGS += \
	EXTRA_CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
	EXTRA_LDFLAGS="$(TARGET_LDFLAGS)" \
	LDLIBS="$(LDLIBS)" \
	LD="$(TARGET_CC)" \
	SKIP_STRIP=y
ifneq ($(findstring c,$(OPENWRT_VERBOSE)),)
  MAKE_FLAGS += V=1
endif

define Build/Configure
	grep 'CONFIG_BUSYBOX_$(BUSYBOX_SYM)' $(TOPDIR)/.config | sed -e "s,\\(# \)\\?CONFIG_BUSYBOX_$(BUSYBOX_SYM)_\\(.*\\),\\1CONFIG_\\2,g" > $(PKG_BUILD_DIR)/.config
	yes 'n' | $(MAKE) -C $(PKG_BUILD_DIR) $(MAKE_FLAGS) oldconfig
endef

define Build/Compile
	$(call Build/Compile/Default, \
		CONFIG_PREFIX="$(PKG_INSTALL_DIR)/opt" \
		all install \
	)
endef

define Package/busybox/install
	$(INSTALL_DIR) $(1)/opt/{bin,sbin}
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/busybox $(1)/opt/bin/
	chmod u+s $(1)/opt/bin/busybox
	$(INSTALL_DIR) $(1)/opt/share
	(cd $(PKG_INSTALL_DIR); \
	    find ./opt -lname "*" | sed "s|^./opt/||g" > $(1)/opt/share/busybox_applets.lst.dist)
endef


# The postinst & prerm scripts will work only when busybox has readlink applet.
# We cannot use readlink directly, it is not yet installed and use 'busybox readlink' instead.
# We convert /opt/bin/busybox to canonical form because /opt is a simpink in some Entware installs
# We remove all symlinks to /opt/bin/busybox in /opt/bin and /opt/sbin before installation and removal.
# It alows to handle applets list change and busybox reinstall in a correct way.
# /opt/share/busybox_applets.lst is not needed any more

define Package/busybox/postinst
#!/opt/bin/busybox sh

bb_fc=`/opt/bin/busybox readlink -f /opt/bin/busybox`
for file in /opt/bin/*; do
    if [ -L $$file  -a "`/opt/bin/busybox readlink -f $$file`" = $$bb_fc ]; then
       /opt/bin/busybox rm -f $$file
    fi
done

for file in /opt/sbin/*; do
    if [ -L $$file  -a "`/opt/bin/busybox readlink -f $$file`" = $$bb_fc ]; then
       /opt/bin/busybox rm -f $$file
    fi
done

cd /opt
for applet in $$(/opt/bin/busybox cat share/busybox_applets.lst.dist)
do
    if [ ! -e $$applet ]
    then
       /opt/bin/busybox ln -s /opt/bin/busybox $$applet
    else
       echo "Warning: '/opt/$$applet' is already exists, skipping."
    fi
done
endef

define Package/busybox/prerm
#!/opt/bin/busybox sh

bb_fc=`/opt/bin/busybox readlink -f /opt/bin/busybox`
for file in /opt/bin/*; do
    if [ -L $$file  -a "`/opt/bin/busybox readlink -f $$file`" = $$bb_fc ]; then
       /opt/bin/busybox rm -f $$file
    fi
done

for file in /opt/sbin/*; do
    if [ -L $$file  -a "`/opt/bin/busybox readlink -f $$file`" = $$bb_fc ]; then
       /opt/bin/busybox rm -f $$file
    fi
done
endef

$(eval $(call BuildPackage,busybox))
