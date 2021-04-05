#!/bin/bash

# Author: Jiao Lining <lining.jiao@thundercomm.com>
# Date: 2020-02-03
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

LOGFILE=build_hlos.log

usage() {
cat <<USAGE

Usage:
    bash $0 [OPTIONS] [OPTIONS]

Description:
    Builds apps_proc

OPTIONS:
    -h, --help
        Display this help message

    -l, --log
        Log file to store build logs

    -p, --product <product name>
        set product name.

    -v, --variant <build variant>
        set build variant.

Example:
    userdebug build and save build log:
        $0 -l

USAGE
}

OPTIONS=""

PRODUCT="sm6150"
VARIANT="userdebug"

SRC_PATH="LINUX/android"

# ==================================================================
assert() {
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        exit 1;
    fi
}

build_ap() {
    cd $SRC_PATH

    echo "source build/envsetup.sh" 2>&1 | tee -a $log_file
    source build/envsetup.sh

    echo "lunch ${PRODUCT}-${VARIANT}" 2>&1 | tee -a $log_file
    lunch ${PRODUCT}-${VARIANT}

    echo "bash build.sh" 2>&1 | tee -a $log_file
    bash build.sh -j${JOBS} dist 2>&1 | tee -a $log_file
    assert
}

#===========================================================
UPDATAPI="false"
JOBS=`cat /proc/cpuinfo| grep "processor"| wc -l`

while true; do
    case "$1" in
        -l|--log)               BUILD_LOG="true";;
        -h|--help)              usage; exit 0;;
        -c|--clean_build)       OPTIONS="$OPTIONS $1";;
        -d|--debug)             OPTIONS="$OPTIONS $1";;
        -i|--image)             OPTIONS="$OPTIONS $1 $2";;
        -j|--jobs)              OPTIONS="$OPTIONS $1 $2"; JOBS=$2;;
        -k|--kernel_defconf)    OPTIONS="$OPTIONS $1 $2";;
        -m|--module)            OPTIONS="$OPTIONS $1 $2";;
        -p|--product)           PRODUCT=$2;;
        -s|--setup_ccache)      OPTIONS="$OPTIONS $1";;
        -u|--update-api)        OPTIONS="$OPTIONS $1"; UPDATAPI="true";;
        -v|--variant)           VARIANT=$2;;
        --)                     break;;
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

build_ap
cd $meta_dir
