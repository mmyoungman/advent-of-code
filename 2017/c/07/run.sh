#!/bin/bash
flags="-std=c11 -ggdb -D DEBUG -msse2 -Wno-write-strings"

gcc $flags solution.c -o solution

./solution
