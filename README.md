# Entware-ng
Entware-ng is an OpenWRT-based repository for embedded devices. It uses a modified OpenWRT Buildroot to build repsitories of  packages directly for different architectures. It does not need external toolchains.
mipsel, armv5, armv7, x86 are now supported. As a system libraries one can use glibc (2.22), uclibc-ng (1.07) or musl (not tested). gcc 4.8.5, 9.8.3 or 5.2.0 compilers can be selected. (uclibc-ng was tested only with gcc 5.2). Linux Kernels 2.6.x are used to build toolchain and packages.
2.6.22.19 (https://github.com/wl500g/wl500g) is used for mipsel feed.
2.6.32.x (long term) is used for armv5 & x86
2.6.36.4 is used for armv7
