#
# Copyright (C) 2007-2018 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# column, ionice and fsfreeze packages added, add swapon/swapoff binaries

include $(TOPDIR)/rules.mk

PKG_NAME:=util-linux
PKG_VERSION:=2.32.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@KERNEL/linux/utils/$(PKG_NAME)/v2.32
PKG_HASH:=86e6707a379c7ff5489c218cfaf1e3464b0b95acf7817db0bc5f179e356a67b2
PKG_CPE_ID:=cpe:/a:kernel:util-linux

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=	COPYING					\
			libblkid/COPYING			\
			libmount/COPYING			\
			Documentation/licenses/COPYING.GPLv2	\
			Documentation/licenses/COPYING.LGPLv2.1	\
			libuuid/COPYING				\
			Documentation/licenses/COPYING.BSD-3

PKG_BUILD_PARALLEL:=1

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

DISABLE_NLS:=--disable-nls

include $(INCLUDE_DIR)/package.mk

define Package/util-linux/Default
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:= +librt
  URL:=http://www.kernel.org/pub/linux/utils/util-linux/
endef

define Package/libblkid
$(call Package/util-linux/Default)
  DEPENDS:=+libuuid
  TITLE:=block device id library
  SECTION:=libs
  CATEGORY:=Libraries
endef

define Package/libblkid/description
 The libblkid library is used to identify block devices (disks) as to their
 content (e.g. filesystem type, partitions) as well as extracting additional
 information such as filesystem labels/volume names, partitions, unique
 identifiers/serial numbers...
endef

define Package/libfdisk
$(call Package/util-linux/Default)
  DEPENDS:=+libuuid +libblkid +librt
  TITLE:=partition manipulating library
  SECTION:=libs
  CATEGORY:=Libraries
endef

define Package/libfdisk/description
  The libfdisk library is used for manipulating with partition tables.
endef

define Package/libmount
$(call Package/util-linux/Default)
  DEPENDS:=+libblkid +librt
  TITLE:=mount library
  SECTION:=libs
  CATEGORY:=Libraries
endef

define Package/libmount/description
 The libmount library is used to parse /etc/fstab, /etc/mtab and
 /proc/self/mountinfo files, manage the mtab file, evaluate mount options...
endef

define Package/libuuid
$(call Package/util-linux/Default)
  TITLE:=DCE compatible Universally Unique Identifier library
  SECTION:=libs
  CATEGORY:=Libraries
endef

define Package/libuuid/description
 The UUID library is used to generate unique identifiers for objects
 that may be accessible beyond the local system. This library
 generates UUIDs compatible with those created by the Open Software
 Foundation (OSF) Distributed Computing Environment (DCE) utility.
endef

define Package/libsmartcols
$(call Package/util-linux/Default)
  TITLE:=table or tree library
  SECTION:=libs
  CATEGORY:=Libraries
endef

define Package/libsmartcols/description
 The smartcols library is used to print tables and trees in a pretty way.
endef

define Package/agetty
$(call Package/util-linux/Default)
  TITLE:=alternative Linux getty
  SUBMENU=Terminal
endef

define Package/agetty/description
 agetty opens a tty port, prompts for a login name and invokes the
 /bin/login command
endef

define Package/blkdiscard
$(call Package/util-linux/Default)
  DEPENDS:=+librt
  TITLE:=discard sectors on a device
  SUBMENU=Disc
endef

define Package/blkdiscard/description
 The blkdiscard is used to discard device sectors. This is useful for
 solid-state drivers (SSDs) and thinly-provisioned storage. Unlike fstrim,
 this command is used directly on the block device.
endef

define Package/blkid
$(call Package/util-linux/Default)
  TITLE:=locate and print block device attributes
  DEPENDS:= +libblkid +libuuid
  SUBMENU=Disc
endef

define Package/blkid/description
 The blkid program is the command-line interface to working with the libblkid
 library.
endef

define Package/blockdev
$(call Package/util-linux/Default)
  TITLE:=call block device ioctls from the command line
  SUBMENU=Disc
endef

define Package/blockdev/description
 The blockdev program is the command-line interface to call block device ioctls.
endef

define Package/cal
$(call Package/util-linux/Default)
  TITLE:=display a calendar
  DEPENDS:= +libncurses
endef

define Package/cal/description
 cal displays a simple calendar
endef

define Package/cfdisk
$(call Package/util-linux/Default)
  TITLE:=display or manipulate disk partition table
  DEPENDS:= +libblkid +libncurses +libsmartcols +libfdisk +libmount
  SUBMENU:=Disc
endef

define Package/column
$(call Package/util-linux/Default)
  TITLE:=columnate lists
  DEPENDS:= +libsmartcols
endef

define Package/column/description
 The  column  utility  formats  its  input  into  multiple  columns
endef

define Package/cfdisk/description
 cfdisk is a curses-based program for partitioning any hard disk drive
endef

define Package/dmesg
$(call Package/util-linux/Default)
  TITLE:=print or control the kernel ring buffer
  DEPENDS:= +libncursesw
endef

define Package/dmesg/description
 dmesg  is used to examine or control the kernel ring buffer
endef

define Package/fdisk
$(call Package/util-linux/Default)
  TITLE:=manipulate disk partition table
  DEPENDS:= +libblkid +libsmartcols +libfdisk +libncursesw
  SUBMENU=Disc
endef

define Package/fdisk/description
 a menu-driven program for creation and manipulation of partition tables
endef

define Package/findfs
$(call Package/util-linux/Default)
  TITLE:=find a filesystem by label or UUID
  DEPENDS:= +libblkid
  SUBMENU=Disc
endef

define Package/findfs/description
 findfs will search the disks in the system looking for a filesystem which has
 a label matching label or a UUID equal to uuid
endef

define Package/flock
$(call Package/util-linux/Default)
  TITLE:=manage locks from shell scripts
  DEPENDS:= +librt
endef

define Package/flock/description
  manages flock locks from within shell scripts or the command line
endef

define Package/fstrim
$(call Package/util-linux/Default)
  TITLE:=discard unused blocks on a mounted filesystem
  DEPENDS:= +libblkid +libuuid +libsmartcols +libmount
  SUBMENU=Filesystem
endef

define Package/fstrim/description
  fstrim is used on a mounted filesystem to discard (or "trim") blocks
  which are not in use by the filesystem.  This is useful for solid-
  state drives (SSDs) and thinly-provisioned storage.
endef

define Package/getopt
$(call Package/util-linux/Default)
  TITLE:=parse command options (enhanced)
endef

define Package/getopt/description
 getopt is used to break up (parse) options in command lines for easy parsing
 by shell procedures, and to check for legal options
endef

define Package/hwclock
$(call Package/util-linux/Default)
  TITLE:=query or set the hardware clock
endef

define Package/hwclock/description
 hwclock is a tool for accessing the Hardware Clock
endef

define Package/ionice
$(call Package/util-linux/Default)
  TITLE:=ionice - get/set program io scheduling class and priority 
endef

define Package/ionice/description
 This program sets or gets the io scheduling class and priority for a program. If no arguments or just -p is given, ionice will query the current io scheduling class and priority for that process. 
endef

define Package/fsfreeze
$(call Package/util-linux/Default)
  TITLE:=fsfreeze - suspends and resumes access to an filesystem 
endef

define Package/fsfreeze/description
 fsfreeze halts new access to the filesystem and creates a stable image on disk.
 fsfreeze is intended to be used with hardware RAID devices that support the creation of snapshots.
endef

define Package/logger
$(call Package/util-linux/Default)
  TITLE:=a shell command interface to the syslog system log module
endef

define Package/logger/description
 logger makes entries in the system log, it provides a shell command interface
 to the syslog system log module
endef

define Package/look
$(call Package/util-linux/Default)
  TITLE:=display lines beginning with a given string
endef

define Package/look/description
 look utility displays any lines in file which contain string
endef

define Package/losetup
$(call Package/util-linux/Default)
  TITLE:=set up and control loop devices
  DEPENDS:= +libsmartcols
endef

define Package/losetup/description
 losetup is used to associate loop devices with regular files or block devices,
 to detach loop devices and to query the status of a loop device
endef

define Package/lsblk
$(call Package/util-linux/Default)
  TITLE:=list block devices
  DEPENDS:= +libblkid +libmount +libsmartcols
  SUBMENU=Disc
endef

define Package/lsblk/description
 lsblk lists information about all or the specified block devices
endef

define Package/lscpu
$(call Package/util-linux/Default)
  TITLE:=display information about the CPU architecture
  DEPENDS:= +libsmartcols
endef

define Package/lscpu/description
 lscpu displays information about the CPU architecture
endef

define Package/mcookie
$(call Package/util-linux/Default)
  TITLE:=generate magic cookies for xauth
endef

define Package/mcookie/description
 mcookie generates a 128-bit random hexadecimal number for use with the X
 authority system
endef

define Package/mount-utils
$(call Package/util-linux/Default)
  TITLE:=related (u)mount utilities
  DEPENDS+= +libmount +libsmartcols
endef

define Package/mount-utils/description
 contains: mount, umount, findmnt
endef

define Package/namei
$(call Package/util-linux/Default)
  TITLE:=follow a pathname until a terminal point is found
endef

define Package/namei/description
 namei uses its arguments as pathnames to any type of Unix file (symlinks,
 files, directories, and so forth)
endef

define Package/nsenter
$(call Package/util-linux/Default)
  TITLE:=enter a namespace
endef

define Package/nsenter/description
  run program with namespaces of other processes
endef

define Package/prlimit
$(call Package/util-linux/Default)
  TITLE:=get and set process resource limits
  DEPENDS:= +libsmartcols
endef

define Package/prlimit/description
  Given a process id and one or more resources, prlimit tries to retrieve
  and/or modify the limits.
endef

define Package/rename
$(call Package/util-linux/Default)
  TITLE:=rename files
endef

define Package/rename/description
 rename will rename the specified files by replacing the first occurrence of
 expression in their name by replacement
endef

define Package/partx-utils
$(call Package/util-linux/Default)
  TITLE:=inform kernel about the presence and numbering of on-disk partitions
  DEPENDS:= +libblkid +libsmartcols
  SUBMENU=Disc
endef

define Package/partx-utils/description
 contains partx, addpart, delpart
endef

define Package/script-utils
$(call Package/util-linux/Default)
  TITLE:=make and replay typescript of terminal session
  DEPENDS:= +librt
  SUBMENU=Terminal
endef

define Package/script-utils/description
 contains: script, scriptreplay
endef

define Package/setterm
$(call Package/util-linux/Default)
  TITLE:=set terminal attributes
  DEPENDS:= +libncurses
  SUBMENU:=Terminal
endef

define Package/setterm/description
 setterm writes to standard output a character string that will invoke the
 specified terminal capabilities
endef

define Package/sfdisk
$(call Package/util-linux/Default)
  TITLE:=partition table manipulator for Linux
  SUBMENU=Disc
  DEPENDS:= +libblkid +libfdisk +libsmartcols +libncursesw
endef

define Package/sfdisk/description
 list the size of a partition, list the partitions on a device, check the
 partitions on a device and repartition a device
endef

define Package/swap-utils
$(call Package/util-linux/Default)
  TITLE:=swap space management utilities
  DEPENDS+= +libblkid +libmount +libsmartcols
  SUBMENU:=Filesystem
endef

define Package/swap-utils/description
 contains: mkswap, swaplabel, swapon, swapoff
endef

define Package/unshare
$(call Package/util-linux/Default)
  TITLE:=unshare userspace tool
endef

define Package/unshare/description
  run programs with some namespaces unshared from parent
endef

define Package/uuidd
$(call Package/util-linux/Default)
  TITLE:=UUID generation daemon
  DEPENDS:= +libuuid +librt
endef

define Package/uuidd/description
 The uuidd daemon is used by the UUID library to generate universally unique
 identifiers (UUIDs), especially time-based UUIDs, in a secure and
 guaranteed-unique fashion, even in the face of large numbers of threads
 running on different CPUs trying to grab UUIDs.
endef

define Package/uuidgen
$(call Package/util-linux/Default)
  TITLE:=create a new UUID value
  DEPENDS:= +libuuid
endef

define Package/uuidgen/description
 The uuidgen program creates (and prints) a new universally unique identifier
 (UUID) using the libuuid library. The new UUID can reasonably be considered
 unique among all UUIDs created on the local system, and among UUIDs created on
 other systems in the past and in the future.
endef

define Package/wall
$(call Package/util-linux/Default)
  TITLE:=send a message to everybody's terminal
  SUBMENU=Terminal
endef

define Package/wall/description
 wall sends a message to everybody logged in with their mesg permission
 set to yes
endef

define Package/whereis
$(call Package/util-linux/Default)
  TITLE:=locate the binary, source, and manual page files for a command
endef

define Package/whereis/description
 whereis locates source/binary and manuals sections for specified files
endef

define Package/wipefs
$(call Package/util-linux/Default)
  TITLE:=wipe a signature from a device
  DEPENDS:= +libblkid +libsmartcols
  SUBMENU:=Disc
endef

define Package/wipefs/description
 wipefs can erase filesystem, raid or partition table signatures (magic
 strings) from the specified device to make the signature invisible for
 libblkid.
endef

CONFIGURE_ARGS += \
	--disable-use-tty-group		\
	--disable-rpath			\
	--disable-tls			\
	--disable-sulogin		\
	--disable-makeinstall-chown	\
	--without-python		\
	--without-udev			\
	--without-readline		\
	--disable-more			\
	--with-ncursesw

TARGET_CFLAGS += $(FPIC) -std=gnu99

define Build/InstallDev
	$(INSTALL_DIR) $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/blkid.pc $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/fdisk.pc $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/mount.pc $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/smartcols.pc $(1)/opt/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/pkgconfig/uuid.pc $(1)/opt/lib/pkgconfig

	$(INSTALL_DIR) $(1)/opt/include/blkid
	$(CP) $(PKG_INSTALL_DIR)/opt/include/blkid/blkid.h $(1)/opt/include/blkid
	$(INSTALL_DIR) $(1)/opt/include/libfdisk
	$(CP) $(PKG_INSTALL_DIR)/opt/include/libfdisk/libfdisk.h $(1)/opt/include/libfdisk
	$(INSTALL_DIR) $(1)/opt/include/libmount
	$(CP) $(PKG_INSTALL_DIR)/opt/include/libmount/libmount.h $(1)/opt/include/libmount
	$(INSTALL_DIR) $(1)/opt/include/uuid
	$(CP) $(PKG_INSTALL_DIR)/opt/include/uuid/uuid.h $(1)/opt/include/uuid
	$(INSTALL_DIR) $(1)/opt/include/libsmartcols
	$(CP) $(PKG_INSTALL_DIR)/opt/include/libsmartcols/libsmartcols.h $(1)/opt/include/libsmartcols

	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libblkid.so* $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libfdisk.so* $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libmount.so* $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libuuid.so* $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libsmartcols.so* $(1)/opt/lib

	$(LN) libblkid.so.1 $(1)/opt/lib/libblkid.so
	$(LN) libfdisk.so.1 $(1)/opt/lib/libfdisk.so
	$(LN) libmount.so.1 $(1)/opt/lib/libmount.so
	$(LN) libuuid.so.1 $(1)/opt/lib/libuuid.so
	$(LN) libsmartcols.so.1 $(1)/opt/lib/libsmartcols.so
endef


define Package/libfdisk/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libfdisk.so* $(1)/opt/lib/
	$(LN) libfdisk.so.1 $(1)/opt/lib/libfdisk.so
endef

define Package/libblkid/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libblkid.so* $(1)/opt/lib/
	$(LN) libblkid.so.1 $(1)/opt/lib/libblkid.so
endef

define Package/libmount/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libmount.so* $(1)/opt/lib/
	$(LN) libmount.so.1 $(1)/opt/lib/libmount.so
endef

define Package/libsmartcols/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libsmartcols.so* $(1)/opt/lib/
	$(LN) libsmartcols.so.1 $(1)/opt/lib/libsmartcols.so
endef

define Package/libuuid/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libuuid.so* $(1)/opt/lib/
	$(LN) libuuid.so.1 $(1)/opt/lib/libuuid.so
endef

define Package/agetty/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/agetty $(1)/opt/sbin/
endef

define Package/blkdiscard/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/blkdiscard $(1)/opt/sbin/
endef

define Package/blkid/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/blkid $(1)/opt/sbin/
endef

define Package/blockdev/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/blockdev $(1)/opt/sbin/
endef

define Package/cal/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/cal $(1)/opt/bin/
endef

define Package/cfdisk/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/cfdisk $(1)/opt/sbin/
endef

define Package/column/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/column $(1)/opt/bin/
endef

define Package/dmesg/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/dmesg $(1)/opt/bin/
endef

define Package/fdisk/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/fdisk $(1)/opt/sbin/
endef

define Package/findfs/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/findfs $(1)/opt/sbin/
endef

define Package/flock/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/flock $(1)/opt/bin/
endef

define Package/fsfreeze/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/fsfreeze $(1)/opt/sbin/
endef

define Package/fstrim/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/fstrim $(1)/opt/sbin/
endef

define Package/getopt/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/getopt $(1)/opt/bin/
endef

define Package/ionice/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/ionice $(1)/opt/bin/
endef

define Package/hwclock/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/hwclock $(1)/opt/sbin/
endef

define Package/logger/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/logger $(1)/opt/bin/
endef

define Package/look/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/look $(1)/opt/bin/
endef

define Package/losetup/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/losetup $(1)/opt/sbin/
endef

define Package/lsblk/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/lsblk $(1)/opt/bin/
endef

define Package/lscpu/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/lscpu $(1)/opt/bin/
endef

define Package/mcookie/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/mcookie $(1)/opt/bin/
endef

define Package/mount-utils/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/{u,}mount $(1)/opt/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/mountpoint $(1)/opt/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/findmnt $(1)/opt/bin/
endef

define Package/namei/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/namei $(1)/opt/bin/
endef

define Package/nsenter/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/nsenter $(1)/opt/bin/
endef

define Package/prlimit/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/prlimit $(1)/opt/bin/
endef

define Package/rename/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/rename $(1)/opt/bin/
endef

define Package/partx-utils/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/partx $(1)/opt/sbin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/addpart $(1)/opt/sbin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/delpart $(1)/opt/sbin/
endef

define Package/script-utils/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/script $(1)/opt/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/scriptreplay $(1)/opt/bin/
endef

define Package/setterm/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/setterm $(1)/opt/bin/
endef

define Package/sfdisk/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/sfdisk $(1)/opt/sbin/
endef

define Package/swap-utils/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/mkswap $(1)/opt/sbin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/swaplabel $(1)/opt/sbin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/swap{on,off} $(1)/opt/sbin/
endef

define Package/unshare/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/unshare $(1)/opt/bin/
endef

define Package/uuidd/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/uuidd $(1)/opt/sbin/
endef

define Package/uuidgen/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/uuidgen $(1)/opt/bin/
endef

define Package/wall/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/wall $(1)/opt/bin/
endef

define Package/whereis/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/whereis $(1)/opt/bin/
endef

define Package/wipefs/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/wipefs $(1)/opt/sbin/
endef

$(eval $(call BuildPackage,libblkid))
$(eval $(call BuildPackage,libfdisk))
$(eval $(call BuildPackage,libmount))
$(eval $(call BuildPackage,libsmartcols))
$(eval $(call BuildPackage,libuuid))
$(eval $(call BuildPackage,agetty))
$(eval $(call BuildPackage,blkdiscard))
$(eval $(call BuildPackage,blkid))
$(eval $(call BuildPackage,blockdev))
$(eval $(call BuildPackage,cal))
$(eval $(call BuildPackage,cfdisk))
$(eval $(call BuildPackage,column))
$(eval $(call BuildPackage,dmesg))
$(eval $(call BuildPackage,fdisk))
$(eval $(call BuildPackage,findfs))
$(eval $(call BuildPackage,flock))
$(eval $(call BuildPackage,fsfreeze))
$(eval $(call BuildPackage,fstrim))
$(eval $(call BuildPackage,getopt))
$(eval $(call BuildPackage,ionice))
$(eval $(call BuildPackage,hwclock))
$(eval $(call BuildPackage,logger))
$(eval $(call BuildPackage,look))
$(eval $(call BuildPackage,losetup))
$(eval $(call BuildPackage,lsblk))
$(eval $(call BuildPackage,lscpu))
$(eval $(call BuildPackage,mcookie))
$(eval $(call BuildPackage,mount-utils))
$(eval $(call BuildPackage,namei))
$(eval $(call BuildPackage,nsenter))
$(eval $(call BuildPackage,prlimit))
$(eval $(call BuildPackage,rename))
$(eval $(call BuildPackage,partx-utils))
$(eval $(call BuildPackage,script-utils))
$(eval $(call BuildPackage,setterm))
$(eval $(call BuildPackage,sfdisk))
$(eval $(call BuildPackage,swap-utils))
$(eval $(call BuildPackage,unshare))
$(eval $(call BuildPackage,uuidd))
$(eval $(call BuildPackage,uuidgen))
$(eval $(call BuildPackage,wall))
$(eval $(call BuildPackage,whereis))
$(eval $(call BuildPackage,wipefs))
