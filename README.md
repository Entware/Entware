## Entware-ng-3x

This is a fork of Entware-ng project: https://github.com/Entware-ng/Entware-ng

The main differences from the original project are
- 3.x kernels are used to build toolchain. 3.4.112 is used for mips(el) and 3.2.40 is used for arm and intel;
- glibc is now a system library for all architectures including mips(el);
- glibc has a patch that allows to use separate (from the original firmware) users and passwords;
- two different installations are possible for most devices: (1) standard, (2) alternative (with serarated from firmware users);
- busybox from Entware is forced instolled;
 
Glibc patch above moves files /etc/passwd, /etc/shaddow, /etc/group, /etc/gshadow, /etc/shells, /etc/localtime to /opt/etc folder. For most devices this allows two different instalation type.

We call standard installation - the installation where /opt/etc folder has symlinks to /etc files (passwd etc.).

We call alternative installation - the installation where /opt/etc/passwd, /opt/etc/group ... are preinstalled. This installation has root user with 12345 password. We recomend to install Entware ssh server (dropbear or openssh) in this case to take full advantages of glibc patch.

---

Most articles from the original Entware-ng wiki are applicale to Entware-ng-3x
(https://github.com/Entware-ng/Entware-ng/wiki)

Entware-ng-3x wiki - https://github.com/Entware-for-kernel-3x/Entware-ng-3x/wiki has only differnt from Entware-ng features described.

Feel free to [ask for new packages](https://github.com/Entware-for-kernel-3x/Entware-ng-3x/issues) or report any bugs you've found.
