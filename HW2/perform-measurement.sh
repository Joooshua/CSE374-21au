#! /bin/bash

if [ $# -ne 1 ]; then
    echo "ArgumentError: Please enter only one argument!"
    exit 1
fi

URL="$1"
OUTPUT=$(mktemp -p '/tmp' -t 'tempXXXXX')

wget -O "$OUTPUT" "$URL" 2> /dev/null

wc -c < "$OUTPUT"

rm "$OUTPUT" 2> /dev/null
exit 0