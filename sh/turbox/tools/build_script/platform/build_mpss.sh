#!/bin/bash
# Author: Tang Zibo <tangzb0114@thundersoft.com>
# Date: 2020-01-16
# Copyright (c) 2020, Thundercomm All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
#       copyright notice, this list of conditions and the following
#       disclaimer in the documentation and/or other materials provided
#       with the distribution.
#     * Neither the name of The Linux Foundation nor the names of its
#       contributors may be used to endorse or promote products derived
#       from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
# ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
# BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
# IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

LOGFILE=build_mpss.log

usage() {
cat <<USAGE

Usage:
    bash $0 [OPTIONS] [OPTIONS]

Description:
    Builds modem_proc.

OPTIONS:
    -l, --log        Put build log to file
    -c, --clean      Claen the build
    -h, --help       Display this help message

Example:
    build modem_proc:
        $0

    clean build:
        $0 -c

    build modem_proc and save build log:
        $0  -l

    clean build and save build log:
        $0 -c -l
USAGE
}

ARMTOOLPATH=/pkg/qct/software/arm/RVDS/5.05bld106
HEXAGONTOOLPATH=/pkg/qct/software/hexagon/releases/tools
LLVMROOT_PATH=/pkg/qct/software/llvm/release/arm/3.5.2.1
GNUROOT_PATH=/pkg/qct/software/arm/linaro-toolchain/aarch64-none-elf/4.9-2014.07
GNUARM7_PATH=/pkg/qct/software/arm/linaro-toolchain/aarch64-none-elf/arm-linux-gnueabihf-4.8-2014.02
BUILD_MODEM_CMD="./build.sh 8996.gen.prod BUILD_VER=xxxx"

SRC_PATH="modem_proc/build/ms"
BUILD_CMD="./build_variant.py sm6150.gen.prod bparams=-k"
CLEAN_CMD="./build_variant.py sm6150.gen.prod –clean"

# ==================================================================
assert() {
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        exit 1;
    fi
}

set_env_modem()
{
    export ARMLMD_LICENSE_FILE=8224@localhost
    ARM_COMPILER_PATH=/pkg/qct/software/arm/ADS1.2/bin
    PYTHON_PATH=/pkg/qct/software/python/2.7.5/bin MAKE_PATH=/pkg/gnu/make/3.81/bin
    export ARMTOOLS=RVCT221
    export ARMROOT=/pkg/asw/compilers/arm/ADS1.2
    export ARMLIB=/pkg/asw/compilers/arm/ADS1.2/lib
    export ARMINCLUDE=/pkg/asw/compilers/arm/ADS1.2/common/include
    export ARMINC=/pkg/asw/compilers/arm/ADS1.2/common/include
    export ARMCONF=/pkg/asw/compilers/arm/ADS1.2/bin
    export ARMDLL = /pkg/asw/compilers/arm/ADS1.2/bin
    export PATH=$MAKE_PATH:$PYTHON_PATH:$ARM_COMPILER_PATH:$PATH
    export ARMHOME = /pkg/asw/compilers/arm/ADS1.2
    export ARMROOT = /pkg/asw/compilers/arm/ADS1.2
    export HAVANA_TOOLCHAIN = /pkg/qct/software/arm/Sourcery_G++_Lite/bin
    export HEXAGON_ROOT=/pkg/qct/software/hexagon/releases/tools
}

build_modem() {
    cd $SRC_PATH

    if [ "$BUILD_CLEAN" = "true" ]; then
        CMD=$CLEAN_CMD
    else
        CMD=$BUILD_CMD
    fi

    set_env_modem

    echo "$CMD" 2>&1 | tee -a $log_file
    echo "" 2>&1 | tee -a $log_file
    echo "" 2>&1 | tee -a $log_file

    $CMD 2>&1 | tee -a $log_file
    assert
}

# ======================Setup getopt================================
BUILD_CLEAN="false"
while true; do
    case "$1" in
        -c|--clean)   BUILD_CLEAN="true";OPTS="true";;
        -l|--log)     BUILD_LOG="true";OPTS="true";;
        -h|--help)    usage; exit 0;;
        --)           break;;
    esac
    shift

    if [ "$1" = "" ]; then
        break
    fi
done

if [ "$(type -t set_log)" = "function" ] ; then
    set_log $BUILD_LOG $LOGFILE
else
    if [ "$BUILD_LOG" = "true" ]; then
        log_file=$LOGFILE
    else
        log_file=/dev/null
    fi
fi

if [ ! -n "$meta_dir" ]; then
    meta_dir=`pwd`
fi

build_modem
cd $meta_dir
