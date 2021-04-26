#!/bin/sh

if [ -e .config ]; then
    read -p 'Please note: .config will be rewriten during downloading! Press Ctrl+C to abort or Enter to continue' i
fi

for entware_target in $(ls -1 configs); do
    echo "Getting $entware_target sources..."
    cp configs/$entware_target .config
    make -j4 download V=s
    if [ $? -ne 0 ]; then
        echo "$openwrt_target download failed for $entware_target:("
        exit 1
    fi
done
