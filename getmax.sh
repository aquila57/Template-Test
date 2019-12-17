#!/bin/bash
if [ -z $1 ]
then
echo "Usage: $0 Dieharder_RNG_number"
echo "Example: $0 208"
echo "To find Dieharder_RNG_number, run"
echo "dieharder -g -l"
exit 1
fi
echo "Find maxint among one million numbers"
echo "Dieharder RNG number $1"
dieharder -g $1 -t 1000000 -o | getmax.py
