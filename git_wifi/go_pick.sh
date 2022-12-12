#!/bin/bash

git checkout $1
git format-patch -1
mv 0001*  ~/tos/r0q_patch/
