#!/bin/bash
if [ -z $1 ]
then
echo "Usage: $0 Dieharder_RNG_number"
echo "Example: $0 208"
echo "To get Dieharder_RNG_number,"
echo "dieharder -g -l"
exit 1
fi
dieharder -g $1 -t 10000000 -o | dietmplt $1
