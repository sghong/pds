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

LOGFILE=zip_meta_build.log

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
    package meta build files:
        $0

    package meta build files and show log:
        $0 -l
USAGE
}

PRODUCT=msm8909go
VARIANT=userdebug

TARGETDIR=$meta_dir/turbox/output
TARGETFILE=MetaBuild_$TURBOX_ID

# ==================================================================
assert() {
    if [ $? -ne 0 ]; then
        exit 1
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
        echo "cp -Lrpf --parents $f $TARGETDIR/$TARGETFILE/" 2>&1 | tee -a $log_file
        cp -Lrpf --parents $f $TARGETDIR/$TARGETFILE/
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
common/*
contents.xml
turbox_flash.sh
about.html
"

FILELIST+="
LINUX/android/out/target/product/sm6150/abl.elf
LINUX/android/out/target/product/sm6150/boot.img
LINUX/android/out/target/product/sm6150/dtbo.img
LINUX/android/out/target/product/sm6150/obj/KERNEL_OBJ/vmlinux
LINUX/android/out/target/product/sm6150/persist.img
LINUX/android/out/target/product/sm6150/system.img
LINUX/android/out/target/product/sm6150/vendor.img
LINUX/android/out/target/product/sm6150/userdata.img
LINUX/android/out/target/product/sm6150/vbmeta.img
adsp_proc/build/dynamic_modules/6150.adsp.prod/*
adsp_proc/build/ms/servreg/6150.adsp.prodQ/adspr.jsn
adsp_proc/build/ms/servreg/6150.adsp.prodQ/adsps.jsn
adsp_proc/build/ms/servreg/6150.adsp.prodQ/adspua.jsn
adsp_proc/obj/qdsp6v5_ReleaseG/6150.adsp.prod/adsp.mbn
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/imagefv.elf
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/JtagProgrammer.elf
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/prog_firehose_ddr.elf
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/prog_firehose_lite.elf
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl.elf
boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl_config.elf
boot_images/QcomPkg/SDMPkg/6150/Tools/storage/UFS/JtagProgrammer.cmm
boot_images/QcomPkg/SDMPkg/6150/Tools/storage/eMMC/JtagProgrammer.cmm
boot_images/QcomPkg/Tools/binaries/logfs_ufs_8mb.bin
boot_images/QcomPkg/Tools/storage/fh_loader/*.*
btfm_proc_CMC/btfm_proc/bt/build/ms/bin/WCN3950/cmbtfw10.tlv
btfm_proc_CMC/btfm_proc/bt/build/ms/bin/WCN3950/cmbtfw11.tlv
btfm_proc_CMC/btfm_proc/bt/build/ms/bin/WCN3950/cmbtfw12.tlv
btfm_proc_CMC/btfm_proc/bt/build/ms/bin/WCN3950/cmnv10.bin
btfm_proc_CMC/btfm_proc/bt/build/ms/bin/WCN3950/cmnv11.bin
btfm_proc_CMC/btfm_proc/bt/build/ms/bin/WCN3950/cmnv12.bin
btfm_proc/bt/build/ms/bin/WCN3990/apbtfw10.tlv
btfm_proc/bt/build/ms/bin/WCN3990/apbtfw11.tlv
btfm_proc/bt/build/ms/bin/WCN3990/apnv10.bin
btfm_proc/bt/build/ms/bin/WCN3990/apnv11.bin
btfm_proc/bt/build/ms/bin/WCN3990/crbtfw11.tlv
btfm_proc/bt/build/ms/bin/WCN3990/crbtfw20.tlv
btfm_proc/bt/build/ms/bin/WCN3990/crbtfw21.tlv
btfm_proc/bt/build/ms/bin/WCN3990/crnv11.bin
btfm_proc/bt/build/ms/bin/WCN3990/crnv20.bin
btfm_proc/bt/build/ms/bin/WCN3990/crnv21.bin
cdsp_proc/build/dynamic_modules/6150.cdsp.prod/*
cdsp_proc/build/ms/servreg/6150.cdsp.prodQ/cdspr.jsn
cdsp_proc/obj/qdsp6v5_ReleaseG/6150.cdsp.prod/cdsp.mbn
modem_proc/build/ms/bin/sm6150.gennm.prod/qdsp6m.qdb
modem_proc/build/ms/bin/sm6150.gennm.prod/qdsp6sw.mbn
modem_proc/build/ms/bin/sm6150.gennm.prod/efs1.bin
modem_proc/build/ms/bin/sm6150.gennm.prod/efs2.bin
modem_proc/build/ms/bin/sm6150.gennm.prod/efs3.bin
aop_proc/build/ms/bin/AAAAANAZO/6150/aop.mbn
aop_proc/core/bsp/aop/build/6150/AOP_AAAAANAZO.elf
aop_proc/core/bsp/aop/scripts/*
aop_proc/core/api/debugtrace/tracer_event_tbl.h
aop_proc/core/power/arc/scripts/arc_dump.cmm
trustzone_images/build/ms/bin/PAZAANAA/tz.mbn
trustzone_images/build/ms/bin/PAZAANAA/hyp.mbn
trustzone_images/build/ms/bin/PAZAANAA/devcfg.mbn
trustzone_images/build/ms/bin/PAZAANAA/storsec.mbn
trustzone_images/build/ms/bin/PAZAANAA/km4.mbn
trustzone_images/build/ms/bin/PAZAANAA/cmnlib64.mbn
trustzone_images/build/ms/bin/PAZAANAA/cmnlib.mbn
trustzone_images/build/ms/bin/PAZAANAA/uefi_sec.mbn
trustzone_images/build/ms/bin/PAZAANAA/rtic.mbn
trustzone_images/build/ms/bin/PAZAANAA/smplap32.mbn
trustzone_images/build/ms/bin/PAZAANAA/smplap64.mbn
trustzone_images/build/ms/bin/PAZAANAA/widevine.mbn
trustzone_images/build/ms/bin/PAZAANAA/securemm.mbn
trustzone_images/build/ms/bin/PAZAANAA/gptest.mbn
trustzone_images/build/ms/bin/PAZAANAA/soter64.mbn
trustzone_images/build/ms/bin/PAZAANAA/haventkn.mbn
trustzone_images/build/ms/bin/PAZAANAA/loadalgota64.mbn
venus_proc/build/bsp/asic/build/PROD/mbn/reloc/socCheckV6/signed/venus.mbn
wdsp_proc/build/ms/bin/PIL_IMAGES/*
wlan_proc/build/ms/bin/QCAHNALATDL/signed/wlanmdsp.mbn
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.bin
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.102
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.104
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.105
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.106
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.107
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.108
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.109
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b0a
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b0b
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b0d
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b0e
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b0f
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b04
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.10e
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.10f
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b07
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b09
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b14
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b15
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b30
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b31
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b32
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b33
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b34
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b35
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.202
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b36
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b37
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/bdwlan.b38
wlan_proc/wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/regdb.bin
wlan_proc/build/ms/servreg/QCAHNALATDLQ/modemuw.jsn
wlan_proc/build/ms/6150/Data.msc
wlan_proc/build/ms/M6150*.elf
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
