# SPDX-License-Identifier: GPL-2.0-or-later
#
# Copyright (C) 2006-2021 OpenWrt.org
#
# Entware specific: postinst/prerm

include $(TOPDIR)/rules.mk

PKG_NAME:=busybox
PKG_VERSION:=1.36.1
PKG_RELEASE:=1
PKG_FLAGS:=essential

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://www.busybox.net/downloads \
		http://sources.buildroot.net
PKG_HASH:=b8cc24c9574d809e7279c3be349795c5d5ceb6fdf19ca709f80cde50e47de314

PKG_BUILD_DEPENDS:=BUSYBOX_CONFIG_PAM:libpam
PKG_BUILD_PARALLEL:=1
PKG_BUILD_FLAGS:=lto
PKG_CHECK_FORMAT_SECURITY:=0

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=LICENSE archival/libarchive/bz/LICENSE
PKG_CPE_ID:=cpe:/a:busybox:busybox

BUSYBOX_SYM=$(if $(CONFIG_BUSYBOX_CUSTOM),CONFIG,DEFAULT)
BUSYBOX_IF_ENABLED=$(if $(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_$(1)),$(2))

ifneq ($(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_FEATURE_SUID),)
  PKG_FILE_MODES:=/opt/bin/busybox:root:root:4755
endif

include $(INCLUDE_DIR)/package.mk

ifeq ($(DUMP),)
  STAMP_CONFIGURED:=$(strip $(STAMP_CONFIGURED))_$(shell grep '^CONFIG_BUSYBOX_' $(TOPDIR)/.config | $(MKHASH) md5)
endif

# All files provided by busybox will serve as fallback alternatives by opkg.
# There should be no need to enumerate ALTERNATIVES entries here
define Package/busybox/Default
  SECTION:=base
  CATEGORY:=Base system
  MAINTAINER:=Felix Fietkau <nbd@nbd.name>
  TITLE:=Core utilities for embedded Linux
  URL:=http://busybox.net/
  DEPENDS:=+BUSYBOX_CONFIG_PAM:libpam +BUSYBOX_CONFIG_NTPD:jsonfilter
  USERID:=ntp=123:ntp=123
endef

define Package/busybox
  $(call Package/busybox/Default)
  CONFLICTS:=busybox-selinux
  VARIANT:=default
endef

define Package/busybox-selinux
  $(call Package/busybox/Default)
  TITLE += with SELinux support
  DEPENDS += +libselinux
  VARIANT:=selinux
  PROVIDES:=busybox
endef

define Package/busybox/description
 The Swiss Army Knife of embedded Linux.
 It slices, it dices, it makes Julian Fries.
endef

define Package/busybox/config
	source "$(SOURCE)/Config.in"
endef

ifneq ($(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_FEATURE_SYSLOG)$(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_FEATURE_SYSLOGD_CFG),)
define Package/busybox/conffiles/syslog
/opt/etc/syslog.conf
endef
endif

ifneq ($(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_CROND),)
define Package/busybox/conffiles/crond
/opt/etc/crontabs/
endef
endif

define Package/busybox/conffiles
$(Package/busybox/conffiles/syslog)
$(Package/busybox/conffiles/crond)
endef

Package/busybox-selinux/conffiles = $(Package/busybox/conffiles)

ifndef CONFIG_USE_MUSL
LDLIBS:=m crypt
endif

LDLIBS += $(call BUSYBOX_IF_ENABLED,PAM,pam pam_misc pthread)

ifeq ($(CONFIG_USE_GLIBC),y)
  LDLIBS += $(call BUSYBOX_IF_ENABLED,NSLOOKUP,resolv)
endif

ifeq ($(BUILD_VARIANT),selinux)
  LDLIBS += selinux sepol
endif

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
	rm -f $(PKG_BUILD_DIR)/.config
	touch $(PKG_BUILD_DIR)/.config
ifeq ($(DEVICE_TYPE),nas)
	echo "CONFIG_HDPARM=y" >> $(PKG_BUILD_DIR)/.config
endif
ifeq ($(BUILD_VARIANT),selinux)
	cat $(TOPDIR)/$(SOURCE)/selinux.config >> $(PKG_BUILD_DIR)/.config
endif
	grep 'CONFIG_BUSYBOX_$(BUSYBOX_SYM)' $(TOPDIR)/.config | sed -e "s,\\(# \)\\?CONFIG_BUSYBOX_$(BUSYBOX_SYM)_\\(.*\\),\\1CONFIG_\\2,g" >> $(PKG_BUILD_DIR)/.config
	yes 'n' | $(MAKE) -C $(PKG_BUILD_DIR) $(MAKE_FLAGS) oldconfig
endef

define Build/Compile
	$(call Build/Compile/Default, \
		CONFIG_PREFIX="$(PKG_INSTALL_DIR)/opt" \
		all install \
	)
endef

define Package/busybox/install
	$(INSTALL_DIR) $(1)/opt/etc/init.d
	$(INSTALL_DIR) $(1)/opt/{bin,sbin}
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/busybox $(1)/opt/bin/
	chmod u+s $(1)/opt/bin/busybox
	$(INSTALL_DIR) $(1)/opt/share
	(cd $(PKG_INSTALL_DIR); \
	    find ./opt -lname "*" | sed "s|^./opt/||g" > $(1)/opt/share/busybox_applets.lst.dist)
ifneq ($(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_CROND),)
	$(INSTALL_BIN) ./files/S10crond $(1)/opt/etc/init.d
	$(INSTALL_DIR) $(1)/opt/var/spool/cron/crontabs
endif
endef

# The postinst & prerm scripts will work only when busybox has readlink applet.
# We cannot use readlink directly, it is not yet installed and use 'busybox readlink' instead.
# We convert /opt/bin/busybox to canonical form because /opt is a symlink in some Entware installs
# We remove all symlinks to /opt/bin/busybox in /opt/bin and /opt/sbin before installation and removal.
# It allows to handle applets list change and busybox reinstall in a correct way.
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
         if ! grep -qF -- "/opt/$$applet" /opt/lib/opkg/info/busybox.list; then
           echo "/opt/$$applet" >> /opt/lib/opkg/info/busybox.list
         fi
    else
       echo "Warning: '/opt/$$applet' is already exists, skipping."
    fi
done
endef

define Package/busybox/prerm
#!/opt/bin/busybox sh

/opt/bin/busybox cat > /opt/lib/opkg/info/busybox.list <<EOF
/opt/lib/upgrade/keep.d/busybox
/opt/lib/opkg/info/busybox.list
/opt/bin/busybox
EOF

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

Package/busybox-selinux/install = $(Package/busybox/install)

$(eval $(call BuildPackage,busybox))
$(eval $(call BuildPackage,busybox-selinux))
