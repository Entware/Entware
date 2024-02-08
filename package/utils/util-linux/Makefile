#
# Copyright (C) 2007-2018 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Entware specific: column, ionice, fallocate, fsfreeze and rev packages added, add swapon/swapoff binaries
#	disable nsenter for k2.6 based targets;
#	-Dlibutil/-Dbuild-fallocate enabled;
#	added more ALTERNATIVES

include $(TOPDIR)/rules.mk

PKG_NAME:=util-linux
PKG_VERSION:=2.39.3
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@KERNEL/linux/utils/$(PKG_NAME)/v2.39
PKG_HASH:=7b6605e48d1a49f43cc4b4cfc59f313d0dd5402fa40b96810bd572e167dfed0f
PKG_CPE_ID:=cpe:/a:kernel:util-linux

PKG_LICENSE:=GPL-2.0-only
PKG_LICENSE_FILES:=	COPYING					\
			libblkid/COPYING			\
			libmount/COPYING			\
			Documentation/licenses/COPYING.GPLv2	\
			Documentation/licenses/COPYING.LGPLv2.1	\
			libuuid/COPYING				\
			Documentation/licenses/COPYING.BSD-3

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

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
  ABI_VERSION:=1
endef

define Package/libblkid/description
 The libblkid library is used to identify block devices (disks) as to their
 content (e.g. filesystem type, partitions) as well as extracting additional
 information such as filesystem labels/volume names, partitions, unique
 identifiers/serial numbers...
endef

define Package/libfdisk
$(call Package/util-linux/Default)
  DEPENDS:=+libuuid +libblkid
  TITLE:=partition manipulating library
  SECTION:=libs
  CATEGORY:=Libraries
  ABI_VERSION:=1
endef

define Package/libfdisk/description
  The libfdisk library is used for manipulating with partition tables.
endef

define Package/libmount
$(call Package/util-linux/Default)
  DEPENDS:=+libblkid
  TITLE:=mount library
  SECTION:=libs
  CATEGORY:=Libraries
  ABI_VERSION:=1
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
  ABI_VERSION:=1
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
  ABI_VERSION:=1
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
  TITLE:=discard sectors on a device
  SUBMENU=Disc
  DEPENDS:=libblkid
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
  ALTERNATIVES:=200:/opt/sbin/blkid:/opt/sbin/util-linux-blkid
endef

define Package/blkid/description
 The blkid program is the command-line interface to working with the libblkid
 library.
endef

define Package/blockdev
$(call Package/util-linux/Default)
  TITLE:=call block device ioctls from the command line
  SUBMENU=Disc
  ALTERNATIVES:=200:/opt/sbin/blockdev:/opt/sbin/util-linux-blockdev
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

define Package/cfdisk/description
 cfdisk is a curses-based program for partitioning any hard disk drive
endef

define Package/colrm
$(call Package/util-linux/Default)
  TITLE:=colrm removes selected columns from a file
  DEPENDS:=
endef

define Package/colrm/description
 colrm removes selected columns from a file. Input is taken from
 standard input. Output is sent to standard output.
endef

define Package/column
$(call Package/util-linux/Default)
  TITLE:=columnate lists
  DEPENDS:= +libsmartcols
endef

define Package/column/description
 The  column  utility  formats  its  input  into  multiple  columns
endef

define Package/dmesg
$(call Package/util-linux/Default)
  TITLE:=print or control the kernel ring buffer
  DEPENDS:= +libncursesw
  ALTERNATIVES:=200:/opt/bin/dmesg:/opt/bin/util-linux-dmesg
endef

define Package/dmesg/description
 dmesg  is used to examine or control the kernel ring buffer
endef

define Package/eject
$(call Package/util-linux/Default)
  TITLE:=eject removable media
  DEPENDS:= +libblkid +libmount +libuuid
  SUBMENU=Disc
endef

define Package/eject/description
  eject allows removable media (typically a CD-ROM, floppy disk, tape, or JAZ
  or ZIP disk) to be ejected under software control.
endef

define Package/fallocate
$(call Package/util-linux/Default)
  TITLE:=preallocate or deallocate space to a file
  SUBMENU:=Filesystem
endef

define Package/fallocate/description
  fallocate is used to manipulate the allocated disk space for a file
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
  ALTERNATIVES:=200:/opt/bin/flock:/opt/bin/util-linux-flock
endef

define Package/flock/description
  manages flock locks from within shell scripts or the command line
endef

define Package/fsfreeze
$(call Package/util-linux/Default)
  TITLE:=fsfreeze - suspends and resumes access to an filesystem 
endef

define Package/fsfreeze/description
 fsfreeze halts new access to the filesystem and creates a stable image on disk.
 fsfreeze is intended to be used with hardware RAID devices that support the creation of snapshots.
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

define Package/hardlink
$(call Package/util-linux/Default)
  TITLE:=consolidate duplicate files using hardlinks
  DEPENDS:=+libpcre2
  SUBMENU:=Filesystem
endef

define Package/hardlink/description
 Consolidate duplicate files using hardlinks.
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

define Package/ipcs
$(call Package/util-linux/Default)
  TITLE:=show information on IPC facilities
endef

define Package/ipcs/description
  ipcs shows information on the inter-process communication facilities for
  which the calling process has read access. By default it shows information
  about all three resources: shared memory segments, message queues, and
  semaphore arrays.
endef

define Package/logger
$(call Package/util-linux/Default)
  TITLE:=a shell command interface to the syslog system log module
  ALTERNATIVES:=200:/opt/bin/logger:/opt/bin/util-linux-logger
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
  ALTERNATIVES:=200:/opt/sbin/losetup:/opt/sbin/util-linux-losetup
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

define Package/lslocks
$(call Package/util-linux/Default)
  TITLE:=list local system locks
  DEPENDS:= +libmount +libsmartcols
endef

define Package/lslocks/description
 lslocks lists information about all the currently held file locks in a Linux system
endef

define Package/lsns
$(call Package/util-linux/Default)
  TITLE:=list system namespaces
  DEPENDS:= +libblkid +libmount +libsmartcols
endef

define Package/lsns/description
 lsns lists information about all namespaces and their processes
endef

define Package/more
$(call Package/util-linux/Default)
  TITLE:=filter for paging through text one screenful at a time
  DEPENDS:= +libncurses
  ALTERNATIVES:=200:/opt/bin/more:/opt/bin/util-linux-more
endef

define Package/more/description
 more is a filter for paging through text one screenful at a time
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
  ALTERNATIVES:=200:/opt/bin/mount:/opt/bin/util-linux-mount \
		200:/opt/bin/umount:/opt/bin/util-linux-umount
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
  DEPENDS:=@!LINUX_2_6_36
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

define Package/rev
$(call Package/util-linux/Default)
  TITLE:=Reverse lines characterwise
  ALTERNATIVES:=200:/opt/bin/rev:/opt/bin/util-linux-rev
endef

define Package/rev/description
 rev utility copies the specified files to the standard output, reversing the
 order of characters in every line. If no files are specified, the standard
 input is read.
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
  ALTERNATIVES:=200:/opt/sbin/mkswap:/opt/sbin/util-linux-mkswap \
		200:/opt/sbin/swapoff:/opt/sbin/util-linux-swapoff \
		200:/opt/sbin/swapon:/opt/sbin/util-linux-swapon
endef

define Package/swap-utils/description
 contains: mkswap, swaplabel, swapon, swapoff
endef

define Package/taskset
$(call Package/util-linux/Default)
  TITLE:=set or retrieve a process's CPU affinity
  ALTERNATIVES:=200:/opt/bin/taskset:/opt/bin/util-linux-taskset
endef

define Package/taskset/description
 contains: taskset
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
  DEPENDS:= +libuuid
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

MESON_ARGS += \
	-Dsystemd=disabled \
	-Dtinfo=disabled \
	-Dcryptsetup=disabled \
	-Dlibutil=$(if $(CONFIG_USE_GLIBC),en,dis)abled \
	-Dlibutempter=disabled \
	-Dlibpcre2-posix=disabled \
	-Dlibuser=disabled \
	-Duse-tty-group=false \
	-Duse-tls=false \
	-Dbuild-python=disabled \
	-Dbuild-zramctl=disabled \
	-Dbuild-fsck=disabled \
	-Dbuild-wipefs=disabled \
	-Dbuild-fallocate=enabled \
	-Dbuild-setpriv=disabled \
	-Dbuild-hardlink=disabled \
	-Dbuild-cramfs=disabled \
	-Dbuild-bfs=disabled \
	-Dbuild-minix=disabled \
	-Dbuild-fdformat=disabled \
	-Dbuild-lslogins=disabled \
	-Dbuild-wdctl=disabled \
	-Dbuild-cal=disabled \
	-Dbuild-switch_root=disabled \
	-Dbuild-pivot_root=disabled \
	-Dbuild-lsmem=disabled \
	-Dbuild-lsirq=disabled \
	-Dbuild-irqtop=disabled \
	-Dbuild-chmem=disabled \
	-Dbuild-ipcrm=disabled \
	-Dbuild-rfkill=disabled \
	-Dbuild-tunelp=disabled \
	-Dbuild-kill=disabled \
	-Dbuild-last=disabled \
	-Dbuild-utmpdump=disabled \
	-Dbuild-line=disabled \
	-Dbuild-mesg=disabled \
	-Dbuild-raw=disabled \
	-Dbuild-vipw=disabled \
	-Dbuild-newgrp=disabled \
	-Dbuild-chfn-chsh=disabled \
	-Dbuild-login=disabled \
	-Dbuild-nologin=disabled \
	-Dbuild-sulogin=disabled \
	-Dbuild-su=disabled \
	-Dbuild-runuser=disabled \
	-Dbuild-ul=disabled \
	-Dbuild-pg=disabled \
	-Dbuild-write=disabled \
	-Dbuild-bash-completion=disabled \
	-Dbuild-pylibmount=disabled \
	-Dreadline=disabled \
	-Dmagic=disabled \
	-Dncursesw=enabled

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
endef


define Package/libfdisk/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libfdisk.so.* $(1)/opt/lib/
endef

define Package/libblkid/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libblkid.so.* $(1)/opt/lib/
endef

define Package/libmount/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libmount.so.* $(1)/opt/lib/
endef

define Package/libsmartcols/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libsmartcols.so.* $(1)/opt/lib/
endef

define Package/libuuid/install
	$(INSTALL_DIR) $(1)/opt/lib
	$(CP) $(PKG_INSTALL_DIR)/opt/lib/libuuid.so.* $(1)/opt/lib/
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
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/blkid $(1)/opt/sbin/util-linux-blkid
endef

define Package/blockdev/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/blockdev $(1)/opt/sbin/util-linux-blockdev
endef

define Package/cal/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/cal $(1)/opt/bin/
endef

define Package/cfdisk/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/cfdisk $(1)/opt/sbin/
endef

define Package/colrm/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/colrm $(1)/opt/bin/
endef

define Package/column/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/column $(1)/opt/bin/
endef

define Package/dmesg/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/dmesg $(1)/opt/bin/util-linux-dmesg
endef

define Package/eject/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/eject $(1)/opt/bin/
endef

define Package/fallocate/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/fallocate $(1)/opt/bin/
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
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/flock $(1)/opt/bin/util-linux-flock
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

define Package/hardlink/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/hardlink $(1)/opt/bin/
endef

define Package/hwclock/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/hwclock $(1)/opt/sbin/
endef

define Package/ionice/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/ionice $(1)/opt/bin/
endef

define Package/ipcs/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/ipcs $(1)/opt/bin/
endef

define Package/logger/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/logger $(1)/opt/bin/util-linux-logger
endef

define Package/look/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/look $(1)/opt/bin/
endef

define Package/losetup/install
	$(INSTALL_DIR) $(1)/opt/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/losetup $(1)/opt/sbin/util-linux-losetup
endef

define Package/lsblk/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/lsblk $(1)/opt/bin/
endef

define Package/lscpu/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/lscpu $(1)/opt/bin/
endef

define Package/lslocks/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/lslocks $(1)/opt/bin/
endef

define Package/lsns/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/lsns $(1)/opt/bin/
endef

define Package/more/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/more $(1)/opt/bin/util-linux-more
endef

define Package/mcookie/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/mcookie $(1)/opt/bin/
endef

define Package/mount-utils/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/mount $(1)/opt/bin/util-linux-mount
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/umount $(1)/opt/bin/util-linux-umount
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

define Package/rev/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/rev $(1)/opt/bin/util-linux-rev
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
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/mkswap $(1)/opt/sbin/util-linux-mkswap
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/swaplabel $(1)/opt/sbin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/swapoff $(1)/opt/sbin/util-linux-swapoff
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/sbin/swapon $(1)/opt/sbin/util-linux-swapon
endef

define Package/taskset/install
	$(INSTALL_DIR) $(1)/opt/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/opt/bin/taskset $(1)/opt/bin/util-linux-taskset
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

# these lines need to be ordered by dependency because of ABI versioning
$(eval $(call BuildPackage,libuuid))
$(eval $(call BuildPackage,libblkid))
$(eval $(call BuildPackage,libfdisk))

$(eval $(call BuildPackage,libmount))
$(eval $(call BuildPackage,libsmartcols))
$(eval $(call BuildPackage,agetty))
$(eval $(call BuildPackage,blkdiscard))
$(eval $(call BuildPackage,blkid))
$(eval $(call BuildPackage,blockdev))
$(eval $(call BuildPackage,cal))
$(eval $(call BuildPackage,cfdisk))
$(eval $(call BuildPackage,colrm))
$(eval $(call BuildPackage,column))
$(eval $(call BuildPackage,dmesg))
$(eval $(call BuildPackage,eject))
$(eval $(call BuildPackage,fallocate))
$(eval $(call BuildPackage,fdisk))
$(eval $(call BuildPackage,findfs))
$(eval $(call BuildPackage,flock))
$(eval $(call BuildPackage,fsfreeze))
$(eval $(call BuildPackage,fstrim))
$(eval $(call BuildPackage,getopt))
$(eval $(call BuildPackage,hardlink))
$(eval $(call BuildPackage,hwclock))
$(eval $(call BuildPackage,ionice))
$(eval $(call BuildPackage,ipcs))
$(eval $(call BuildPackage,logger))
$(eval $(call BuildPackage,look))
$(eval $(call BuildPackage,losetup))
$(eval $(call BuildPackage,lsblk))
$(eval $(call BuildPackage,lscpu))
$(eval $(call BuildPackage,lslocks))
$(eval $(call BuildPackage,lsns))
$(eval $(call BuildPackage,more))
$(eval $(call BuildPackage,mcookie))
$(eval $(call BuildPackage,mount-utils))
$(eval $(call BuildPackage,namei))
$(eval $(call BuildPackage,nsenter))
$(eval $(call BuildPackage,prlimit))
$(eval $(call BuildPackage,rename))
$(eval $(call BuildPackage,rev))
$(eval $(call BuildPackage,partx-utils))
$(eval $(call BuildPackage,script-utils))
$(eval $(call BuildPackage,setterm))
$(eval $(call BuildPackage,sfdisk))
$(eval $(call BuildPackage,swap-utils))
$(eval $(call BuildPackage,taskset))
$(eval $(call BuildPackage,unshare))
$(eval $(call BuildPackage,uuidd))
$(eval $(call BuildPackage,uuidgen))
$(eval $(call BuildPackage,wall))
$(eval $(call BuildPackage,whereis))
$(eval $(call BuildPackage,wipefs))
