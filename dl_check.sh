#!/bin/sh

if [ -e .config ]; then
    read -p 'Please note: .config will be rewriten during downloading! Press Ctrl+C to abort or Enter to continue' i
fi

for entware_target in $(ls -1 configs); do
    echo "Checking $entware_target downloads..."
    cp configs/$entware_target .config
    for openwrt_target in tools toolchain target package; do
	make -j4 $openwrt_target/download
	if [ $? -ne 0 ]; then
	    echo "$openwrt_target downloads failed for $entware_target:("
	    exit 1
	fi
    done
done
