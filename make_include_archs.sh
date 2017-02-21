#!/bin/sh

tar czvf bin/targets/armv7-3x/generic-glibc/packages/include.tar.gz -C ./staging_dir/target-arm_cortex-a9_glibc-2.25_eabi/opt/include/ .
tar czvf bin/targets/armv5-3x/generic-glibc/packages/include.tar.gz -C ./staging_dir/target-arm_xscale_glibc-2.25_eabi/opt/include/ .
tar czvf bin/targets/x64-3x/generic-glibc/packages/include.tar.gz    -C ./staging_dir/target-x86_64_glibc-2.25/opt/include/ .
tar czvf bin/targets/mips-3x/generic-glibc/packages/include.tar.gz -C ./staging_dir/target-mips_mips32r2_glibc-2.25/opt/include/ .
tar czvf bin/targets/mipsel-3x/generic-glibc/packages/include.tar.gz -C ./staging_dir/target-mipsel_mips32r2_glibc-2.25/opt/include/ .
