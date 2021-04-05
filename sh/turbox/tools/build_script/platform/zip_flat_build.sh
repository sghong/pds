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

LOGFILE=zip_flat_build.log

usage() {
cat <<USAGE

Usage:
    bash $0 [OPTIONS] [OPTIONS]

Description:
    package meta build files.

OPTIONS:
    -l, --log        Put build log to file
    -h, --help       Display this help message
    -p, --product <product name>  set product name.
    -v, --variant <build variant> set build variant.

Example:
    package flat build files:
        $0

    package flat build files and show log:
        $0 -l
USAGE
}

PRODUCT=msm8909go
VARIANT=userdebug

TARGETDIR=$meta_dir/turbox/output
TARGETFILE=FlatBuild_$TURBOX_ID

# ==================================================================
assert() {
    if [ $? -ne 0 ];then
        exit 1;
    fi
}

copy_files() {
    if [ -d $TARGETDIR/$TARGETFILE ]; then
        echo "rm -fr $TARGETDIR/$TARGETFILE" 2>&1 | tee -a $log_file
        rm -fr $TARGETDIR/$TARGETFILE
    fi

    echo "mkdir -p $TARGETDIR/$TARGETFILE" 2>&1 | tee -a $log_file
    mkdir -p $TARGETDIR/$TARGETFILE

    cd $meta_dir

    for f in ${FILELIST} ; do
        echo "cp -rpf $f $TARGETDIR/$TARGETFILE/" 2>&1 | tee -a $log_file
        cp -rpf $f $TARGETDIR/$TARGETFILE/
        assert
    done
}

zip_package() {
    cd $TARGETDIR

    echo "zip -r $TARGETFILE.zip $TARGETFILE" 2>&1 | tee -a $log_file
    zip -r $TARGETFILE.zip $TARGETFILE
    assert
}

# ======================Setup getopt================================
while true; do
    case "$1" in
      -l|--log)   BUILD_LOG="true";OPTS="true";;
      -h|--help)  usage; exit 0;;
      -p|--product)           PRODUCT=$2;;
      -v|--variant)           VARIANT=$2;;
      --)         break;;
    esac
    shift

    if [ "$1" = "" ]; then
        break
    fi
done

FILELIST="
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/prog_firehose_ddr.elf
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/prog_firehose_lite.elf
common/build/emmc/bin/asic/sparse_images/rawprogram_unsparse0.xml
common/build/emmc/patch0.xml
common/config/emmc/partition_External.xml
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl.elf
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl_config.elf
trustzone_images/build/ms/bin/PAZAANAA/tz.mbn
aop_proc/build/ms/bin/AAAAANAZO/6150/aop.mbn
trustzone_images/build/ms/bin/PAZAANAA/hyp.mbn
LINUX/android/out/target/product/sm6150/boot.img
common/build/emmc/bin/asic/sparse_images/*
trustzone_images/build/ms/bin/PAZAANAA/km4.mbn
trustzone_images/build/ms/bin/PAZAANAA/cmnlib.mbn
trustzone_images/build/ms/bin/PAZAANAA/cmnlib64.mbn
common/build/emmc/bin/asic/NON-HLOS.bin
common/build/emmc/bin/asic/dspso.bin
LINUX/android/out/target/product/sm6150/abl.elf
common/build/emmc/bin/BTFM.bin
LINUX/android/out/target/product/sm6150/dtbo.img
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/imagefv.elf
trustzone_images/build/ms/bin/PAZAANAA/uefi_sec.mbn
LINUX/android/out/target/product/sm6150/persist.img
trustzone_images/build/ms/bin/PAZAANAA/devcfg.mbn
common/core_qupv3fw/sm6150/qupv3fw.elf
boot_images/QcomPkg/Tools/binaries/logfs_ufs_8mb.bin
LINUX/android/out/target/product/sm6150/vbmeta.img
trustzone_images/build/ms/bin/PAZAANAA/storsec.mbn
common/build/emmc/bin/asic/multi_image.mbn
common/build/emmc/gpt_main0.bin
common/build/emmc/gpt_backup0.bin
turbox/tools/flash_tools/qdl/qdl
"

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

copy_files
zip_package

cd $meta_dir
