#!/bin/bash
# Author: Jiao Lining <lining.jiao@thundercomm.com>
# Date: 2020-01-22
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

usage() {
    echo -e "\033[1;37mUsage:\033[0m"
    echo -e "  bash $0 [options] [options]"
    echo -e "  <hlos will be build if no options.>"
    echo

    echo -e "\033[1;37mDescription:\033[0m"
    echo -e "  Build all images."
    echo

    echo -e "\033[1;37mOptions:\033[0m"
    echo -e "\033[1;37m  -h, --help\033[0m
    display this help message"

    echo -e "\033[1;37m  -c, --clean_build\033[0m
    Clean Build"

    echo -e "\033[1;37m  -l, --log\033[0m
    Save the logs to file"

    echo -e "\033[1;37m  -b, --nonhlos\033[0m
    Build all nonhlos subsystems(bl,rpm,aop,tz,adsp,cdsp)."

    echo -e "\033[1;37m  -a, --hlos\033[0m
    build hlos(application system)."

    echo -e "\033[1;37m  -u, --update_common_info\033[0m
    performs task that are common across all builds"

    echo -e "\033[1;37m  -p, --product\033[0m
    Product name(Ex. -v qcs405)"

    echo -e "\033[1;37m  -v, --variant\033[0m
    Build variant (Default: userdebug/debug)"

    echo -e "\033[1;37m  --update_bin_files\033[0m
    update the nonhlos bin files"

    echo -e "\033[1;37m  --all\033[0m
    build all iamges."

    echo -e "\033[1;37m  --bl\033[0m
    build boot_images."

    echo -e "\033[1;37m  --uefi\033[0m
    build uefi."

    echo -e "\033[1;37m  --rpm\033[0m
    build rpm_proc."

    echo -e "\033[1;37m  --aop\033[0m
    build aop_proc."

    echo -e "\033[1;37m  --tz\033[0m
    build trustzone_images."

    echo -e "\033[1;37m  --adsp\033[0m
    build adsp_proc."

    echo -e "\033[1;37m  --cdsp\033[0m
    build cdsp_proc."

    echo -e "\033[1;37m  --mpss\033[0m
    build modem_proc."

    echo -e "\033[1;37m  --zip_ota_package\033[0m
    Copy ota full package and target package"

    echo -e "\033[1;37m  --zip_fastboot_build\033[0m
    Package the fastboot build"

    echo -e "\033[1;37m  --zip_flat_build\033[0m
    Package the flat build"

    echo -e "\033[1;37m  --zip_meta_build\033[0m
    Package the meta build(inlcude all elf files)"

    echo
    echo -e "\033[1;37mBlow options are for Android build, can be used with -a/--hlos:\033[0m"
    echo -e "\033[1;37m  --ap-d\033[0m        Enable debugging - captures all commands while doing Andorid build."
    echo -e "\033[1;37m  --ap-i\033[0m        Specify image to be build/re-build (bootimg/sysimg/usrimg)"
    echo -e "\033[1;37m  --ap-j\033[0m        Specifies the number of jobs to run simultaneously (Default: 8)"
    echo -e "\033[1;37m  --ap-k\033[0m        Specify defconf file to be used for compiling Kernel"
    echo -e "\033[1;37m  --ap-m\033[0m        Module to be build for Android build"
    echo -e "\033[1;37m  --ap-p\033[0m        Project to be build for Android build"
    echo -e "\033[1;37m  --ap-s\033[0m        Set CCACHE for faster incremental builds (true/false - Default: true)"
    echo -e "\033[1;37m  --ap-u\033[0m        Update APIs"

    echo
    echo -e "\033[1;37mBlow options are for update_common_info, can be used with -u/--update_common_info:\033[0m"
    echo -e "\033[1;37m  --uci-cmm\033[0m           Create cmm script"
    echo -e "\033[1;37m  --uci-nonhlos\033[0m       NON HLOS."
    echo -e "\033[1;37m  --uci-hlos\033[0m          HLOS."
    echo -e "\033[1;37m  --uci-imf\033[0m           Ignore path validation"
    echo -e "\033[1;37m  --uci-wflow_filter <WFLOW_FILTER>\033[0m          Workflow Filter"
    echo -e "\033[1;37m  --uci-variant <VARIANT_CONTENTS_XML>\033[0m       build variant"

    echo
    echo -e "\033[1;37mBlow options are for update_bin_files, can be used with --update_bin_files:\033[0m"
    echo -e "\033[1;37m  --ubf-all\033[0m         Update all nonhlos bin files"
    echo -e "\033[1;37m  --ubf-common\033[0m      Update common bin files"
    echo -e "\033[1;37m  --ubf-btfm\033[0m        Update btfm_proc bin files"
    echo -e "\033[1;37m  --ubf-btfm-cmc\033[0m    Update btfm_proc_cmc bin files"
    echo -e "\033[1;37m  --ubf-adsp\033[0m        Update adsp_proc bin files"
    echo -e "\033[1;37m  --ubf-cdsp\033[0m        Update cdsp_proc bin files"
    echo -e "\033[1;37m  --ubf-bl\033[0m          Update boot_images bin files"
    echo -e "\033[1;37m  --ubf-uefi\033[0m        Update uefi bin files"
    echo -e "\033[1;37m  --ubf-mpss\033[0m        Update modem_proc bin files"
    echo -e "\033[1;37m  --ubf-slpi\033[0m        Update slpi_proc bin files"
    echo -e "\033[1;37m  --ubf-rpm\033[0m         Update rpm_proc bin files"
    echo -e "\033[1;37m  --ubf-aop\033[0m         Update aop_proc bin files"
    echo -e "\033[1;37m  --ubf-tz\033[0m          Update trustzone_images bin files"
    echo -e "\033[1;37m  --ubf-venus\033[0m       Update venus_proc bin files"
    echo -e "\033[1;37m  --ubf-wdsp\033[0m        Update wdsp_proc bin files"
    echo -e "\033[1;37m  --ubf-wlan\033[0m        Update wlan_proc bin files"

    echo
    echo -e "\033[1;37mExample:\033[0m"
    echo -e "\033[1;37m  ./turbox_build.sh\033[0m"
    echo -e "      Build android system whit userdebug variant, and performs update_common_info"
    echo
    echo -e "\033[1;37m  ./turbox_build.sh --bl -l\033[0m"
    echo -e "      build boot_images and save the log to file"
    echo
    echo -e "\033[1;37m  ./turbox_flash.sh -b\033[0m"
    echo -e "      Build all nonhlos subsystem and generate NON-HLOS.bin"
    echo
    echo -e "\033[1;37m  ./turbox_flash.sh -a --ap-m bootimage\033[0m"
    echo -e "      make boot.img"
}

# ============================ functions ======================================
assert() {
    if [ $? -ne 0 ];then
        echo "`date +%Y%m%d_%H:%M:%S` [TURBOX BUILD ERROR]: $1 Error****" | tee -a $log_file
        exit 1;
    fi
}

path_config=""
check_path_config() {
    local pf_path=$1
    local dev_path=$2

    if [ "$dev_path" = "true" ]; then
        path_config="device"
    elif [ "$pf_path" = "true" ]; then
        path_config="platform"
    else
        path_config="N/A"
    fi
}

build_bl() {
    local l_script_file="build_bl.sh"
    local l_pf_path=$PF_BL
    local l_dev_path=$DEV_BL

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_uefi() {
    local l_script_file="build_uefi.sh"
    local l_pf_path=$PF_UEFI
    local l_dev_path=$DEV_UEFI

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_rpm() {
    local l_script_file="build_rpm.sh"
    local l_pf_path=$PF_RPM
    local l_dev_path=$DEV_RPM

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_aop() {
    local l_script_file="build_aop.sh"
    local l_pf_path=$PF_AOP
    local l_dev_path=$DEV_AOP

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}


build_tz() {
    local l_script_file="build_tz.sh"
    local l_pf_path=$PF_TZ
    local l_dev_path=$DEV_TZ

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_adsp() {
    local l_script_file="build_adsp.sh"
    local l_pf_path=$PF_ADSP
    local l_dev_path=$DEV_ADSP

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_cdsp() {
    local l_script_file="build_cdsp.sh"
    local l_pf_path=$PF_CDSP
    local l_dev_path=$DEV_CDSP

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_mpss() {
    local l_script_file="build_mpss.sh"
    local l_pf_path=$PF_MPSS
    local l_dev_path=$DEV_MPSS

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_slpi() {
    local l_script_file="build_slpi.sh"
    local l_pf_path=$PF_SLPI
    local l_dev_path=$DEV_SLPI

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS 2>&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

build_hlos() {
    local l_script_file="build_hlos.sh"
    local l_pf_path=$PF_HLOS
    local l_dev_path=$DEV_HLOS

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS $APOPTIONS >&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS $APOPTIONS
    assert $FUNCNAME
}

update_common_info() {
    local l_script_file="update_common_info.sh"
    local l_pf_path=$PF_UCI
    local l_dev_path=$DEV_UCI

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS $UCIOPTIONS >&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS $UCIOPTIONS
    assert $FUNCNAME
}

zip_fastboot_build() {
    local l_script_file="zip_fastboot_build.sh"
    local l_pf_path=$PF_ZFB
    local l_dev_path=$DEV_ZFB

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS >&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

zip_flat_build() {
    local l_script_file="zip_flat_build.sh"
    local l_pf_path=$PF_ZQFB
    local l_dev_path=$DEV_ZQFB

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS >&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

zip_meta_build() {
    local l_script_file="zip_meta_build.sh"
    local l_pf_path=$PF_ZMB
    local l_dev_path=$DEV_ZMB

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $COMOPTIONS >&1 | tee -a $log_file
    ${l_script_path} $COMOPTIONS
    assert $FUNCNAME
}

update_bin_files() {
    local l_script_file="update_bin_files.sh"
    local l_pf_path=$PF_UBF
    local l_dev_path=$DEV_UBF

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi


    if [ ! -n "$UBFOPTIONS" ]; then
        echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} --all >&1 | tee -a $log_file
        ${l_script_path} --all
        assert $FUNCNAME
    else
        echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $UBFOPTIONS >&1 | tee -a $log_file
        ${l_script_path} $UBFOPTIONS
        assert $FUNCNAME
    fi
}

zip_ota_package(){
    local l_script_file="zip_ota_package.sh"
    local l_pf_path=$PF_OTA
    local l_dev_path=$DEV_OTA

    if [ -z "$l_pf_path" ]; then
        l_pf_path=false
    fi

    if [ -z "$l_dev_path" ]; then
        l_dev_path=false
    fi

    check_path_config ${l_pf_path} ${l_dev_path}
    local l_script_path=turbox/tools/build_script/${path_config}/${l_script_file}

    echo "" 2>&1 | tee -a $log_file
    if [ ! -f "${l_script_path}" ]; then
        echo "`date +%Y%m%d_%H:%M:%S` INFO: Skip-- ${l_script_file}, path_config is ${path_config}" 2>&1 | tee -a $log_file
        return 0
    fi

    echo `date +%Y%m%d_%H:%M:%S` ${l_script_path} $OTAOPTIONS $COMOPTIONS >&1 | tee -a $log_file
    ${l_script_path} $OTAOPTIONS $COMOPTIONS
    assert $FUNCNAME
}

build_all(){
    build_bl
    build_uefi
    build_rpm
    build_aop
    build_tz
    build_adsp
    build_cdsp
    build_mpss
    build_slpi
    build_hlos
    update_common_info
}


# ====================== Set local variables =============================

COMOPTIONS=""
APOPTIONS=""
UCIOPTIONS=""
OTAOPTIONS=""
BUILD_LOG_FLAG=""

# ======================Setup getopt================================
long_opts="help,clean_build,log,hlos,update_common_info,variant:,product:,"
long_opts+="update_bin_files,all,bl,uefi,rpm,aop,tz,adsp,cdsp,mpss,slpi,"
long_opts+="zip_ota_package,zip_fastboot_build,zip_flat_build,zip_meta_build,"
long_opts+="ap-d,ap-i:,ap-j:,ap-k:,ap-m:,ap-p:,ap-s:,ap-u,"
long_opts+="uci-cmm,uci-hlos,uci-nonhlos,uci-imf,uci-wflow_filter:,wcn-chip:,"
long_opts+="ota-nonhlos,ubf-all,ubf-common,ubf-btfm,ubf-btfm-cmc,ubf-adsp,ubf-cdsp,ubf-bl,ubf-uefi,ubf-mpss,ubf-slpi,ubf-rpm,ubf-aop,ubf-tz,ubf-venus,ubf-wdsp,ubf-wlan,"
long_opts+="user-opt-1:,user-opt-2:,user-opt-3:,user-opt-4:,user-opt-5:"
getopt_cmd=$(getopt -o hclbauv:p: --long "$long_opts" \
            -n $(basename $0) -- "$@") || \
            { echo -e "\nERROR: Getopt failed. Extra args\n"; usage; exit 1;}

eval set -- "$getopt_cmd"

while true; do
    case "$1" in
        -h|--help)                        usage; exit 0;;
        -c|--clean_build)                 COMOPTIONS="$COMOPTIONS -c";;
        -l|--log)                         COMOPTIONS="$COMOPTIONS -l";BUILD_LOG_FLAG="true";;
        -b|--nonhlos)                     NONHLOS="true";OPTS="true";;
        -a|--hlos)                        HLOS="true";OPTS="true";;
        -u|--update_common_info)          UPDATE_COMMON_INFO="true";OPTS="true";;
        -v|--variant)                     UCIOPTIONS="$UCIOPTIONS -v $2";
                                          COMOPTIONS="$COMOPTIONS -v $2";
                                          BuildVariant=$2;;
        -p|--product)                     COMOPTIONS="$COMOPTIONS -p $2";HardWareVersion=$2;;
        --update_bin_files)               UPDATE_BIN_FILE="true";OPTS="true";;
        --zip_ota_package)                ZIP_OTA_PACKAGE="true";OPTS="true";;
        --all)                            ALL="true";OPTS="true";;
        --bl)                             XBL="true";OPTS="true";;
        --uefi)                           UEFI="true";OPTS="true";;
        --rpm)                            RPM="true";OPTS="true";;
        --aop)                            AOP="true";OPTS="true";;
        --tz)                             TZ="true";OPTS="true";;
        --adsp)                           ADSP="true";OPTS="true";;
        --cdsp)                           CDSP="true";OPTS="true";;
        --mpss)                           MPSS="true";OPTS="true";;
        --slpi)                           SLPI="true";OPTS="true";;
        --zip_fastboot_build)             FASTBOOT_BUILD="true";OPTS="true";;
        --zip_flat_build)                 FLAT_BUILD="true";OPTS="true";;
        --zip_meta_build)                 META_BUILD="true";OPTS="true";;
        --ap-d)                           APOPTIONS="$APOPTIONS -d";;
        --ap-i)                           APOPTIONS="$APOPTIONS -i $2";;
        --ap-j)                           APOPTIONS="$APOPTIONS -j $2";;
        --ap-k)                           APOPTIONS="$APOPTIONS -k $2";;
        --ap-m)                           APOPTIONS="$APOPTIONS -m $2";;
        --ap-p)                           APOPTIONS="$APOPTIONS -p $2";;
        --ap-s)                           APOPTIONS="$APOPTIONS -s $2";;
        --ap-u)                           APOPTIONS="$APOPTIONS -u";;
        --uci-cmm)                        UCIOPTIONS="$UCIOPTIONS --cmm";;
        --uci-nonhlos)                    UCIOPTIONS="$UCIOPTIONS --nonhlos";;
        --uci-hlos)                       UCIOPTIONS="$UCIOPTIONS --hlos";;
        --uci-imf)                        UCIOPTIONS="$UCIOPTIONS --imf";;
        --uci-wflow_filter)               UCIOPTIONS="$UCIOPTIONS --wflow_filter=$2";;
        --wcn-chip)                       UCIOPTIONS="$UCIOPTIONS --wcn-chip $2";;
        --ubf-all)                        UBFOPTIONS="$UBFOPTIONS --all";;
        --ubf-common)                     UBFOPTIONS="$UBFOPTIONS --common";;
        --ubf-btfm)                       UBFOPTIONS="$UBFOPTIONS --btfm";;
        --ubf-btfm-cmc)                   UBFOPTIONS="$UBFOPTIONS --btfm-cmc";;
        --ubf-adsp)                       UBFOPTIONS="$UBFOPTIONS --adsp";;
        --ubf-cdsp)                       UBFOPTIONS="$UBFOPTIONS --cdsp";;
        --ubf-bl)                         UBFOPTIONS="$UBFOPTIONS --bl";;
        --ubf-uefi)                       UBFOPTIONS="$UBFOPTIONS --uefi";;
        --ubf-mpss)                       UBFOPTIONS="$UBFOPTIONS --mpss";;
        --ubf-slpi)                       UBFOPTIONS="$UBFOPTIONS --slpi";;
        --ubf-rpm)                        UBFOPTIONS="$UBFOPTIONS --rpm";;
        --ubf-aop)                        UBFOPTIONS="$UBFOPTIONS --aop";;
        --ubf-tz)                         UBFOPTIONS="$UBFOPTIONS --tz";;
        --ubf-venus)                      UBFOPTIONS="$UBFOPTIONS --venus";;
        --ubf-wdsp)                       UBFOPTIONS="$UBFOPTIONS --wdsp";;
        --ubf-wlan)                       UBFOPTIONS="$UBFOPTIONS --wlan";;
        --ota-nonhlos)                    OTAOPTIONS="$OTAOPTIONS --nonhlos";;
        --user-opt-1)                     COMOPTIONS="$COMOPTIONS $1 $2";;
        --user-opt-2)                     COMOPTIONS="$COMOPTIONS $1 $2";;
        --user-opt-3)                     COMOPTIONS="$COMOPTIONS $1 $2";;
        --user-opt-4)                     COMOPTIONS="$COMOPTIONS $1 $2";;
        --user-opt-5)                     COMOPTIONS="$COMOPTIONS $1 $2";;
        --)                               break;;
    esac
    shift

    if [ "$1" = "" ]; then
        break
    fi
done

# ======================Set platform/device env================================
DEVICE_RC="config_dev.rc"
PLATFORM_RC="config_pf.rc"
BUILDTOOL_PATH="turbox/tools/build_script"

if [ -f $BUILDTOOL_PATH/platform/${PLATFORM_RC} ]; then
    source $BUILDTOOL_PATH/platform/${PLATFORM_RC}
    init_platform_env
else
    echo -e "\nERROR: Found no ${PLATFORM_RC}\n"
    exit 1
fi

if [ -f $BUILDTOOL_PATH/device/${DEVICE_RC} ]; then
    source $BUILDTOOL_PATH/device/${DEVICE_RC}
    init_device_env
else
    echo  "\n: Found no ${DEVICE_RC}\n"
fi

# ======================Set TurboxId================================
if [ ! -n "$ProjectName" ]; then
    ProjectName="NA"
fi
if [ ! -n "$HardWareVersion" ]; then
    HardWareVersion="xx.xx"
fi
if [ ! -n "$BaseLine" ]; then
    BaseLine="NA"
fi
if [ ! -n "$BuildType" ]; then
    BuildType="l"
fi
if [ ! -n "$BuildVariant" ]; then
    BuildVariant="userdebug"
fi
if [ ! -n "$MajorVersion" ]; then
    MajorVersion=`date +%Y%m%d`
fi
if [ ! -n "$SubVersion" ]; then
    SubVersion=`date +%H%M%S`
fi

if [ ! -n "$TURBOX_ID" ]; then
    TURBOX_ID="${ProjectName}.${BaseLine}.${BuildType}.${BuildVariant}.${MajorVersion}.${SubVersion}"
fi


# ======================Set global variables and function =============================
meta_dir=`pwd`
LOGDIR="$meta_dir/build_log/BuildLog_${TURBOX_ID}"
DEF_LOG_FILE=/dev/null
log_file=$DEF_LOG_FILE

set_log() {
    if [ "$1" = "true" ]; then
        if [ ! -d $LOGDIR ]; then
            mkdir -p $LOGDIR
        fi

        log_file=$LOGDIR/$2
    else
        log_file=$DEF_LOG_FILE
    fi
}

export LOGDIR
export DEF_LOG_FILE
export -f set_log
export meta_dir
export log_file
export TURBOX_ID
export BuildVariant
export MajorVersion
export SubVersion

# ========================== Start ========================================
LOGFILE=turbox_build.log

if [ "$OPTS" != "true" ]; then
   HLOS="true"
   COMOPTIONS="$COMOPTIONS -l"
   APOPTIONS=""
   UCIOPTIONS=""
   UPDATE_COMMON_INFO="true"
   BUILD_LOG_FLAG="true"
fi

set_log $BUILD_LOG_FLAG $LOGFILE

echo "" 2>&1 | tee -a $log_file
echo "" 2>&1 | tee -a $log_file
echo "`date +%Y%m%d_%H:%M:%S` TURBOX_ID:${TURBOX_ID}" 2>&1 | tee -a $log_file
echo "" 2>&1 | tee -a $log_file

if [ "$ALL" = "true" ]; then
    build_all
else
    if [ "$HLOS" = "true" ]; then
        build_hlos
    fi
    if [ "$NONHLOS" = "true" ]; then
        UPDATE_COMMON_INFO="true"
        if [ ! -n "$UCIOPTIONS" ]; then
            UCIOPTIONS="--nonhlos --imf"
        fi
        build_bl
        build_uefi
        build_rpm
        build_aop
        build_tz
        build_adsp
        build_cdsp
        build_mpss
        build_slpi
    else
        if [ "$XBL" = "true" ]; then
            build_bl
        fi
        if [ "$UEFI" = "true" ]; then
            build_uefi
        fi
        if [ "$RPM" = "true" ]; then
            build_rpm
        fi
        if [ "$AOP" = "true" ]; then
            build_aop
        fi
        if [ "$TZ" = "true" ]; then
            build_tz
        fi
        if [ "$ADSP" = "true" ]; then
            build_adsp
        fi
        if [ "$CDSP" = "true" ]; then
            build_cdsp
        fi
        if [ "$MPSS" = "true" ]; then
            build_mpss
        fi
        if [ "$SLPI" = "true" ]; then
            build_slpi
        fi
    fi
fi

if [ "$UPDATE_BIN_FILE" = "true" ]; then
    update_bin_files
fi

if [ "$UPDATE_COMMON_INFO" = "true" ]; then
    update_common_info
fi

if [ "$ZIP_OTA_PACKAGE" = "true" ]; then
    zip_ota_package
fi

if [ "$FASTBOOT_BUILD" = "true" ]; then
    zip_fastboot_build
fi
if [ "$FLAT_BUILD" = "true" ]; then
    zip_flat_build
fi
if [ "$META_BUILD" = "true" ]; then
    zip_meta_build
fi
