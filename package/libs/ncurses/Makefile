#
# Copyright (C) 2006-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ncurses
PKG_VERSION:=6.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@GNU/ncurses
#PKG_MD5SUM:=8cb9c412e5f2d96bc6f459aa8c6282a1

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=README

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

PKG_BUILD_DEPENDS:=ncurses/host

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define Package/libncurses
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Terminal handling library
  URL:=http://www.gnu.org/software/ncurses/
  DEPENDS:= +terminfo
  VARIANT:=libncurses
endef

define Package/terminfo
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Terminal Info Database (ncurses)
  URL:=http://www.gnu.org/software/ncurses/
  VARIANT:=libncurses
endef

define Package/libncursesw
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Terminal handling library (Unicode)
  URL:=http://www.gnu.org/software/ncurses/
  VARIANT:=libncursesw
endef

define Package/ncurses-bin
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Terminal
  DEPENDS:=+libncurses
  TITLE:=Terminal-related programs
  URL:=http://www.gnu.org/software/ncurses/
  VARIANT:=libncurses
endef

TARGET_CFLAGS += $(FPIC)

CONFIGURE_ARGS += \
	--enable-echo \
	--enable-const \
	--enable-overwrite \
	--enable-rpath \
	--disable-rpath-hack \
	--without-ada \
	--without-debug \
	--without-manpages \
	--without-profile \
	--without-tests \
	--disable-big-core \
	--disable-home-terminfo \
	--with-normal \
	--with-shared \
	--with-terminfo-dirs=/opt/share/terminfo \
	--with-default-terminfo-dir=/opt/share/terminfo

HOST_CONFIGURE_ARGS += \
	--without-cxx \
	--without-cxx-binding \
	--without-ada \
	--without-debug \
	--without-manpages \
	--without-profile \
	--without-tests \
	--without-curses-h


ifeq ($(HOST_OS),FreeBSD)
	CONFIGURE_ARGS +=
		--with-terminfo=/opt/share/terminfo.db 
endif

ifeq ($(BUILD_VARIANT),libncursesw)
	CONFIGURE_ARGS += \
		--enable-widec \
		--with-build-cppflags=-D_GNU_SOURCE
endif

MAKE_FLAGS += \
	BUILD_CC="$(HOSTCC)" \
	HOSTCC="$(HOSTCC)" \
	HOSTCCFLAGS="" \
	libs \
	progs

define Build/Install/Default
	$(MAKE_VARS) \
	$(MAKE) -C $(PKG_BUILD_DIR)/$(MAKE_PATH) \
		$(MAKE_INSTALL_FLAGS) \
		$(1) install.libs install.data install.progs;
endef

define Package/ncurses-bin/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/* $(1)/opt/bin/
	$(RM) $(1)/opt/bin/ncurses6-config
endef

define Package/terminfo/install
	echo ""
ifneq ($(HOST_OS),FreeBSD)
	$(INSTALL_DIR) $(1)/opt/share/terminfo
	(cd $(PKG_INSTALL_DIR)/opt/share/terminfo; \
		for dir in ??; do \
			[ -d "$$$$dir" ] || continue; \
			mv $$$$dir $$$$(echo -ne "\x$$$$dir"); \
		done \
	)
	for file in a/ansi d/dumb l/linux r/rxvt r/rxvt-unicode s/screen s/screen-256color v/vt100 v/vt102 x/xterm x/xterm-color x/xterm-256color x/xterm-utf8; do \
		$(INSTALL_DIR) $(1)/opt/share/terminfo/`dirname $$$$file`; \
		$(CP) $(PKG_INSTALL_DIR)/opt/share/terminfo/$$$$file \
			$(1)/opt/share/terminfo/$$$$file; \
	done
endif
endef

define Package/terminfo/postinst
#!/bin/sh

grep -q "^export TERMINFO" /opt/etc/profile || echo "export TERMINFO=/opt/share/terminfo" >> /opt/etc/profile
endef

define Package/libncurses/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/lib{curses,ncurses,panel,menu,form}.so* $(1)/opt/lib/
endef

define Package/libncursesw/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/lib{ncurses,panel,menu,form}w.so* $(1)/opt/lib/
endef

ifeq ($(BUILD_VARIANT),libncursesw)
define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include/ncursesw/
	$(CP) $(PKG_INSTALL_DIR)/opt/include/*.h $(1)/opt/include/ncursesw/

	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/lib{ncurses,panel,menu,form}w.{a,so*} $(1)/opt/lib/

	$(INSTALL_DIR) $(1)/opt/bin $(2)/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/ncursesw6-config $(2)/bin/
	$(SED) 's,^\(prefix\|exec_prefix\)=.*,\1=$(STAGING_DIR)/opt,g' -e 's/$$$$INCS //g' \
		$(2)/bin/ncursesw6-config
	$(LN) $(2)/bin/ncursesw6-config $(1)/opt/bin/ncursesw6-config
endef
else
define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/include
	$(CP) $(PKG_INSTALL_DIR)/opt/include/*.h $(1)/opt/include/

	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/lib{curses,ncurses,panel,menu,form}.{a,so*} $(1)/opt/lib/

	$(INSTALL_DIR) $(1)/opt/bin $(2)/bin
	$(CP) $(PKG_INSTALL_DIR)/opt/bin/ncurses6-config $(2)/bin/
	$(SED) 's,^\(prefix\|exec_prefix\)=.*,\1=$(STAGING_DIR)/opt,g' \
		$(2)/bin/ncurses6-config
	$(LN) $(STAGING_DIR)/host/bin/ncurses6-config $(1)/opt/bin/ncurses6-config
endef
endif


define Host/Compile
	$(MAKE) -C $(HOST_BUILD_DIR) libs
	$(MAKE) -C $(HOST_BUILD_DIR)/progs tic
endef

define Host/Install
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/progs/tic $(STAGING_DIR_HOST)/bin/tic
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,terminfo))
$(eval $(call BuildPackage,libncurses))
$(eval $(call BuildPackage,libncursesw))
$(eval $(call BuildPackage,ncurses-bin))
