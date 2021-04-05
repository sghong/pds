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

LOGFILE=update_bin_files.log

usage() {
cat <<USAGE

Usage:
    bash $0 [OPTIONS] [OPTIONS]

Description:
    update nonhlos bin files.

OPTIONS:
    -l, --log    Put build log to file
    -h, --help   Display this help message
    --all        Update all bin files
    --common     Update common bin files
    --btfm       Update btfm_proc bin files
    --btfm-cmc   Update btfm_proc_cmc bin files
    --adsp       Update adsp_proc bin files
    --cdsp       Update cdsp_proc bin files
    --mpss       Update mpss_proc bin files
    --slpi       Update slpi_proc bin files
    --bl         Update boot_images bin files
    --rpm        Update rpm_proc bin files
    --aop        Update aop_proc bin files
    --tz         Update trustzone_proc bin files
    --venus      Update venus_proc bin files
    --wdsp       Update wdsp_proc bin files
    --wlan       Update wlan_proc bin files

Example:
    build all bin files:
        $0 -a

    build modem_proc and save the log:
        $0 -m -l

USAGE
}

#COMMON_F="true"
BTFM_F="true"
BTFM_CMC_F="true"
ADSP_F="true"
BL_F="true"
MPSS_F="true"
CDSP_F="true"
#SLPI_F="true"
#RPM_F="true"
AOP_F="true"
TZ_F="true"
VENUS_F="true"
#WDSP_F="true"
WLAN_F="true"

ADSP_PATH="adsp_proc"
ADSP_LIST="
build/ms/servreg/6150.adsp.prodQ/adspr.jsn
build/ms/servreg/6150.adsp.prodQ/adsps.jsn
build/ms/servreg/6150.adsp.prodQ/adspua.jsn
obj/qdsp6v5_ReleaseG/6150.adsp.prod/adsp.mbn
"

BL_PATH="boot_images"
BL_LIST="
QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/imagefv.elf
QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/prog_firehose_ddr.elf
QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/prog_firehose_lite.elf
QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl_config.elf
QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl.elf
QcomPkg/SDMPkg/6150/Tools/storage/eMMC/JtagProgrammer.cmm
QcomPkg/Tools/binaries/logfs_ufs_8mb.bin
"

MPSS_PATH="modem_proc"
MPSS_LIST="
build/ms/bin/sm6150.gennm.prod/efs1.bin
build/ms/bin/sm6150.gennm.prod/efs2.bin
build/ms/bin/sm6150.gennm.prod/efs3.bin
build/ms/bin/sm6150.gennm.prod/qdsp6m.qdb
build/ms/bin/sm6150.gennm.prod/qdsp6sw.mbn
"

CDSP_PATH="cdsp_proc"
CDSP_LIST="
build/ms/servreg/6150.cdsp.prodQ/cdspr.jsn
obj/qdsp6v5_ReleaseG/6150.cdsp.prod/cdsp.mbn
"

SLPI_PATH=""
SLPI_LIST=""

COMMON_PATH="common"
COMMON_LIST="
contents.xml
about.html
build/app/fat_creation.py
build/app/gen_cmm_data3.py
build/build.py
build/emmc/bin/asic/dspso.bin
build/ufs/bin/asic/dspso.bin
build/lib/*
config/emmc/*
config/pil-splitter.py
config/ufs/partition.xml
config/storage/*
core_qupv3fw/*
sectools/config/nicobar/*
sectools/sectools.py
sectools/sectools/*
sectools/ext/*
sectools/resources/data_prov_assets/*
sectools/resources/build/fileversion2/sec.elf
"

BTFM_PATH="btfm_proc"
BTFM_LIST="
bt/build/ms/bin/WCN3990/*
"

BTFM_CMC_PATH="btfm_proc_CMC"
BTFM_CMC_LIST="
btfm_proc/bt/build/ms/bin/WCN3950/*
"

RPM_PATH="rpm_proc"
RPM_LIST="
build/ms/bin/nicobar/sdm_ddr4/rpm.mbn
core/bsp/rpm/build/nicobar/sdm_ddr4/RPM_AAAAANAZR.elf
core/bsp/rpm/scripts/*
"

AOP_PATH="aop_proc"
AOP_LIST="
build/ms/bin/AAAAANAZO/6150/aop.mbn
core/api/debugtrace/tracer_event_tbl.h
core/power/arc/scripts/arc_dump.cmm
core/bsp/aop/scripts/*
"

TZ_PATH="trustzone_images"
TZ_LIST="
build/ms/bin/PAZAANAA/tz.mbn
build/ms/bin/PAZAANAA/hyp.mbn
build/ms/bin/PAZAANAA/devcfg.mbn
build/ms/bin/PAZAANAA/storsec.mbn
build/ms/bin/PAZAANAA/km4.mbn
build/ms/bin/PAZAANAA/cmnlib64.mbn
build/ms/bin/PAZAANAA/cmnlib.mbn
build/ms/bin/PAZAANAA/uefi_sec.mbn
build/ms/bin/PAZAANAA/rtic.mbn
build/ms/bin/PAZAANAA/smplap32.mbn
build/ms/bin/PAZAANAA/smplap64.mbn
build/ms/bin/PAZAANAA/widevine.mbn
build/ms/bin/PAZAANAA/securemm.mbn
build/ms/bin/PAZAANAA/gptest.mbn
build/ms/bin/PAZAANAA/soter64.mbn
build/ms/bin/PAZAANAA/haventkn.mbn
build/ms/bin/PAZAANAA/loadalgota64.mbn
"

VENUS_PATH="venus_proc"
VENUS_LIST="
build/bsp/asic/build/PROD/mbn/reloc/socCheckV6/signed/venus.mbn
"

WDSP_PATH="wdsp_proc"
WDSP_LIST="
build/ms/bin/PIL_IMAGES/*
"

WLAN_PATH="wlan_proc"
WLAN_LIST="
build/ms/6150/Data.msc
build/ms/bin/QCAHNALATDL/signed/wlanmdsp.mbn
build/ms/servreg/QCAHNALATDLQ/modemuw.jsn
wlan/halphy_tools/host/bdfUtil/qca61x0/bdf/*
build/ms/*.elf
"


# ==================================================================
assert() {
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

update_bin_files() {
    local srcdir=$l_meta_dir/$1
    local destdir=$l_meta_dir/../$1
    local filelist=$2

    echo "destdir:$destdir"
    echo "srcdir:$srcdir"

    if [ ! -d "$srcdir" ]; then
        echo "No src dir: $srcdir" 2>&1 | tee -a $log_file
        exit 1
    fi

    if [ ! -d "$destdir" ]; then
        echo "No dest dir: $destdir" 2>&1 | tee -a $log_file
        exit 1
    fi

    echo "" 2>&1 | tee -a $log_file
    echo "==Update $destdir file==" 2>&1 | tee -a $log_file
    echo "" 2>&1 | tee -a $log_file

    cd $srcdir
    for file in $filelist; do
        echo "cp -frp --parents $file $destdir" 2>&1 | tee -a $log_file
        cp -frp --parents $file $destdir
	assert
    done
}

change_l_meta_dir() {
    if [ -d "BP-CODE" ]; then
        l_meta_dir=$meta_dir/BP-CODE
    fi
}

# ======================Setup getopt================================
while true; do
    case "$1" in
        -l|--log)      BUILD_LOG="true";;
        -h|--help)     usage; exit 0;;
        --all)         ALL="true";OPTS="true";;
        --common)      COMMON="true";OPTS="true";;
        --btfm)        BTFM="true";OPTS="true";;
        --btfm-cmc)    BTFM_CMC="true";OPTS="true";;
        --adsp)        ADSP="true";OPTS="true";;
        --bl)          BL="true";OPTS="true";;
        --cdsp)        CDSP="true";OPTS="true";;
        --mpss)        MPSS="true";OPTS="true";;
        --slpi)        SLPI="true";OPTS="true";;
        --rpm)         RPM="true";OPTS="true";;
        --aop)         AOP="true";OPTS="true";;
        --tz)          TZ="true";OPTS="true";;
        --venus)       VENUS="true";OPTS="true";;
        --wdsp)        WDSP="true";OPTS="true";;
        --wlan)        WLAN="true";OPTS="true";;
        --)            break;;
    esac
    shift

    if [ "$1" = "" ]; then
        break
    fi
done

if [ "$OPTS" != "true" ]; then
    usage
    exit 1
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

l_meta_dir=$meta_dir

change_l_meta_dir

if [[ "$COMMON_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$COMMON" = "true" ]]; then
        update_bin_files $COMMON_PATH "${COMMON_LIST[*]}"
    fi
fi

if [[ "$BTFM_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$BTFM" = "true" ]]; then
        update_bin_files $BTFM_PATH "${BTFM_LIST[*]}"
    fi
fi

if [[ "$BTFM_CMC_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$BTFM_CMC" = "true" ]]; then
        update_bin_files $BTFM_CMC_PATH "${BTFM_CMC_LIST[*]}"
    fi
fi

if [[ "$ADSP_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$ADSP" = "true" ]]; then
        update_bin_files $ADSP_PATH "${ADSP_LIST[*]}"
    fi
fi

if [[ "$BL_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$BL" = "true" ]]; then
        update_bin_files $BL_PATH "${BL_LIST[*]}"
    fi
fi

if [[ "$MPSS_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$MPSS" = "true" ]]; then
        update_bin_files $MPSS_PATH "${MPSS_LIST[*]}"
    fi
fi

if [[ "$CDSP_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$CDSP" = "true" ]]; then
        update_bin_files $CDSP_PATH "${CDSP_LIST[*]}"
    fi
fi

if [[ "$SLPI_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$SLPI" = "true" ]]; then
        update_bin_files $SLPI_PATH "${SLPI_LIST[*]}"
    fi
fi

if [[ "$RPM_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$RPM" = "true" ]]; then
        update_bin_files $RPM_PATH "${RPM_LIST[*]}"
    fi
fi

if [[ "$AOP_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$AOP" = "true" ]]; then
        update_bin_files $AOP_PATH "${AOP_LIST[*]}"
    fi
fi

if [[ "$TZ_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$TZ" = "true" ]]; then
        update_bin_files $TZ_PATH "${TZ_LIST[*]}"
    fi
fi

if [[ "$VENUS_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$VENUS" = "true" ]]; then
        update_bin_files $VENUS_PATH "${VENUS_LIST[*]}"
    fi
fi

if [[ "$WDSP_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$WDSP" = "true" ]]; then
        update_bin_files $WDSP_PATH "${WDSP_LIST[*]}"
    fi
fi

if [[ "$WLAN_F" = "true" ]]; then
    if [[ "$ALL" = "true" ]] || [[ "$WLAN" = "true" ]]; then
        update_bin_files $WLAN_PATH "${WLAN_LIST[*]}"
    fi
fi

cd $meta_dir
