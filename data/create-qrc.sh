#!/bin/bash
if [ $# -ne 1 ]; then
    echo "You need to supply the prefix dir, e.g.,:"
    echo "$0 data/icons"
    exit
fi

prefix=$1/ # trailing slash important

echo "<RCC>"
echo "  <qresource prefix=\"/\">"

for file in `find $prefix -type f`; do
    # substr on file at position = len(prefix)
    echo "    <file alias=\"${file:${#prefix}}\">./$file</file>"
done

echo "  </qresource>"
echo "</RCC>"
