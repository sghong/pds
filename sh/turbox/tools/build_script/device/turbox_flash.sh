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
    echo -e "\033[1;37m  Images except gpt,userdata,persist will be flashed if no options input\033[0m"
    echo

    echo -e "\033[1;37mDescription:\033[0m"
    echo -e "  flash images with fasboot"
    echo

    echo -e "\033[1;37mOptions:\033[0m"
    echo -e "\033[1;37m  -h, --help\033[0m   display this help message"
    echo -e "\033[1;37m  -v, --variant <debug/perf/user>\033[0m    set the build variant.(default: debug)"

    echo -e "\033[1;37m  -f, --force\033[0m  forcibly flash gpt,persist and userdata without confirmation."
    echo -e "\033[31m               User data and calibration data(BT/WIFI MAC address, etc..) will be ereased. \033[0m"
    echo -e "\033[1;37m  -r, --reboot\033[0m      reboot the device automatically after flashing completes."
    echo -e "\033[1;37m  -b, --nonhlos\033[0m     flash all bp images(xbl,aop,ftfm,tz,dsp,modem,pmic)."
    echo -e "\033[1;37m  -a, --hlos\033[0m        flash all ap images(aboot,bootimage,recovery,system,vendor,cache,mdtp,userdata,persist)."
    echo -e "\033[1;37m  --all\033[0m        flash all images"
    echo

    echo -e "\033[1;37mExample:\033[0m"
    echo -e "\033[1;37m  ./turbox_flash.sh\033[0m"
    echo -e "      Flash the images except gpt,userdata,persist."
    echo
    echo -e "\033[1;37m  ./turbox_flash.sh --force\033[0m"
    echo -e "      Flash all images."
    echo
    echo -e "\033[1;37m  ./turbox_flash.sh --hlos\033[0m"
    echo -e "      Flash all ap images."
    echo
}

# ==================================================================
flash_gpt() {
    local select
    local execution

    if [ "$FORCE" = "" ]; then
        echo -e "\033[31m User data and the calibration data(BT/WIFI MAC address, etc..) will be ereased. Are you sure to flash the gpt.(Y/yes)? \033[0m"

        read select

        case $select in
            yes|Yes|Y|y)   execution="true";;
            *)             execution="false";;
        esac

    elif [ "$FORCE" = "true" ]; then
        execution="true"
    else
        execution="false"
    fi

    if [ "$execution" = "true" ]; then
        fastboot flash partition:0 common/build/emmc/gpt_both0.bin
    fi
}

flash_persist() {
    local select
    local execution

    if [ "$FORCE" = "" ]; then
        echo -e "\033[31m Calibration data(BT/WIFI MAC address, etc..) will be ereased. Are you sure to flash the persist image(Y/yes)? \033[0m"

        read select

        case $select in
            yes|Yes|Y|y)   execution="true";;
            *)             execution="false";;
        esac

    elif [ "$FORCE" = "true" ]; then
        execution="true"
    else
        execution="false"
    fi

    if [ "$execution" = "true" ]; then
        fastboot flash persist LINUX/android/out/target/product/sm6150/persist.img
    fi
}

flash_userdata() {
    local select
    local execution

    if [ "$FORCE" = "" ]; then
        echo -e "\033[31m User data will be ereased. Are you sure to flash the userdata image(Y/yes)? \033[0m"

        read select

        case $select in
            yes|Yes|Y|y)   execution="true";;
            *)             execution="false";;
        esac

    elif [ "$FORCE" = "true" ]; then
        execution="true"
    else
        execution="false"
    fi

    if [ "$execution" = "true" ]; then
        fastboot flash userdata LINUX/android/out/target/product/sm6150/userdata.img
    fi
}

flash_hlos() {
    fastboot flash abl_a LINUX/android/out/target/product/sm6150/abl.elf
    fastboot flash boot_a LINUX/android/out/target/product/sm6150/boot.img
    fastboot flash dtbo_a LINUX/android/out/target/product/sm6150/dtbo.img
    fastboot flash vbmeta_a LINUX/android/out/target/product/sm6150/vbmeta.img
    fastboot flash vendor_a LINUX/android/out/target/product/sm6150/vendor.img
    fastboot flash system_a LINUX/android/out/target/product/sm6150/system.img
}

flash_nonhlos() {
    fastboot flash bluetooth_a common/build/emmc/bin/BTFM.bin
    fastboot flash cmnlib64_a trustzone_images/build/ms/bin/PAZAANAA/cmnlib64.mbn
    fastboot flash cmnlib_a trustzone_images/build/ms/bin/PAZAANAA/cmnlib.mbn
    fastboot flash devcfg_a trustzone_images/build/ms/bin/PAZAANAA/devcfg.mbn
    fastboot flash dsp_a common/build/emmc/bin/asic/dspso.bin
    fastboot flash multiimgoem common/build/emmc/bin/asic/multi_image.mbn
    fastboot flash hyp_a trustzone_images/build/ms/bin/PAZAANAA/hyp.mbn
    fastboot flash imagefv_a boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/imagefv.elf
    fastboot flash keymaster_a trustzone_images/build/ms/bin/PAZAANAA/km4.mbn
    fastboot flash logfs boot_images/QcomPkg/Tools/binaries/logfs_ufs_8mb.bin
    fastboot flash modem_a common/build/emmc/bin/asic/NON-HLOS.bin
    fastboot flash qupfw_a common/core_qupv3fw/sm6150/qupv3fw.elf
    fastboot flash aop_a aop_proc/build/ms/bin/AAAAANAZO/6150/aop.mbn
    fastboot flash storsec trustzone_images/build/ms/bin/PAZAANAA/storsec.mbn
    fastboot flash tz_a trustzone_images/build/ms/bin/PAZAANAA/tz.mbn
    fastboot flash uefisecapp_a trustzone_images/build/ms/bin/PAZAANAA/uefi_sec.mbn
    fastboot flash xbl_a boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl.elf
    fastboot flash xbl_config_a boot_images/QcomPkg/SDMPkg/6150/Bin/LA/RELEASE/xbl_config.elf
}

# ======================Setup getopt================================
long_opts="help,force,reboot,all,nonhlos,hlos,variant:"
getopt_cmd=$(getopt -o hfrabv: --long "$long_opts" \
           -n $(basename $0) -- "$@") || \
           { echo -e "\nERROR: Getopt failed. Extra args\n"; usage; exit 1;}

eval set -- "$getopt_cmd"

VARIANT="debug"

while true; do
    case "$1" in
        -h|--help)       usage; exit 0;;
        -f|--force)      FORCE="true";;
        -r|--reboot)     REBOOT="true";;
        -v|--variant)    VARIANT=$2;;
        -a|--hlos)       HLOS="true";OPTS="true";;
        -b|--nonhlos)    NONHLOS="true";OPTS="true";;
        --all)           ALL="true";OPTS="true";;
        --)              break;;
    esac
    shift

    if [ "$1" = "" ]; then
        break
    fi
done

if [ "$OPTS" != "true" ]; then
   FORCE="false"
   flash_nonhlos
   flash_hlos

fi

if [ "$ALL" = "true" ]; then
   flash_gpt
   flash_nonhlos
   flash_hlos
   flash_persist
   flash_userdata
else
    if [ "$HLOS" = "true" ]; then
       flash_hlos
       flash_persist
       flash_userdata
    fi
    if [ "$NONHLOS" = "true" ]; then
        flash_nonhlos
    fi
fi

if [ "$REBOOT" = "true" ]; then
    echo "Loading complete, Device rebooting ..."
    fastboot reboot
    sleep 5
else
    echo "Loading complete, please reboot the device"
fi
