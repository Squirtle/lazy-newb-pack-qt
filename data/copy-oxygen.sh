#!/bin/bash

OXYGEN=/usr/share/icons/oxygen

if [ $# -ne 2 ]; then
    echo "You need to supply two arguments, e.g.:"
    echo "$0 actions/configure dest_dir/"
    exit
fi

# Split the argument into the category and icon name parts.
src="$1"
src_category=${src%/*}
src_icon=${src#*/}

dest="$2"

# Copy the rendered PNGs.
for dir in 16x16 22x22 32x32 48x48 64x64 128x128; do
  src_path=$OXYGEN/$dir/$src_category/$src_icon.png
  dest_path=$dest/$dir/$src_icon.png
  if [ -f $src_path ]; then
    echo "Copying $src_path to $dest_path"
    mkdir -p `dirname $dest_path`
    cp $src_path $dest_path
    echo
  fi
done
