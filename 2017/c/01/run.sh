#!/bin/bash
flags="-ggdb -msse2 -Wno-write-strings"

g++ $flags solution.cpp -o solution

./solution
