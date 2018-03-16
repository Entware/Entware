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

mirrors="http://sources.lede-project.org \
    http://mirror2.openwrt.org/sources \
    http://downloads.openwrt.org/sources"

echo 'Creating upload mirror...'
mkdir -p dl.2upload
cp dl/* dl.2upload

echo 'Deduplicating local mirror...'
for src in $(ls -1 dl); do
    for mirror in $mirrors; do
        wget --quiet --spider $mirror/$src
        if [ $? -eq 0 ]; then
            echo "$src found @ $mirror"
            rm -f "dl.2upload/$src"
            break
        fi
    done
done
