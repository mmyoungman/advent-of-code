#!/bin/bash
flags="-std=c11 -ggdb -D DEBUG"

rm solution 2> /dev/null
gcc $flags solution.c -o solution
./solution
