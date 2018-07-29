#!/bin/bash
flags="-std=c11 -ggdb -D DEBUG"

gcc $flags solution.c -o solution

./solution
