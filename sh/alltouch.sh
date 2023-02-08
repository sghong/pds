#!/bin/sh

#find . -name "*" -type f -exec touch {} \;
find . -name "*" -type f -exec dos2unix {} \;

