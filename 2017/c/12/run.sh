#!/bin/bash
flags="-std=c11 -ggdb -D DEBUG"

rm solution
gcc $flags solution.c -o solution
./solution
