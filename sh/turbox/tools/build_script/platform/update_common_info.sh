#!/bin/bash
# Author: Jiao Lining <lining.jiao@thundercomm.com>
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

LOGFILE=update_common_info.log

usage() {
cat <<USAGE

Usage:
    bash $0 [OPTIONS] [OPTIONS]

Description:
    This script performs task that are common across all builds, and which must be done after all builds are complete.

OPTIONS:
    -l, --log                          Put build log to file
    -h, --help                         show this help message and exit
    -v, --variant VARIANT_CONTENTS_XML     build variant
    --cmm                              Create cmm script
    --nonhlos                          NON HLOS
    --hlos                             HLOS
    --wflow_filter=WFLOW_FILTER        Workflow Filter
    --clean                            Clean binaries
    --imf                              Ignore path validation

Example:
    all build:
        $0

    clean build:
        $0 --clean

    all build save build log:
        $0 -l

    clean build and save build log:
        $0 -c -l

    only nonhlos build:
        $0 --nonhlos

    only hlos build:
        $0 --hlos
USAGE
}

OPTIONS=""
SRC_PATH="common/build"

# ==================================================================
assert() {
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        exit 1;
    fi
}

update_common() {
    cd $SRC_PATH

    python build.py $OPTIONS 2>&1 | tee $log_file
    assert
}

#===========================================================
if [ $# != 0 ]; then
    while true; do
        case "$1" in
            -l|--log)               BUILD_LOG="true";OPTS="true";;
            -h|--help)              usage; exit 0;;
#            -v|--variant)           OPTIONS="$OPTIONS --variant=$2";;
            --cmm)                  OPTIONS="$OPTIONS $1";;
            --nonhlos)              OPTIONS="$OPTIONS $1";;
            --hlos)                 OPTIONS="$OPTIONS $1";;
            --wflow_filter=*)       OPTIONS="$OPTIONS $1";;
            --clean)                OPTIONS="$OPTIONS $1";;
            --imf)                  OPTIONS="$OPTIONS $1";;
            --)                     break;;
        esac
        shift

        if [ "$1" = "" ]; then
            break
        fi
    done
fi


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

update_common
cd $meta_dir
