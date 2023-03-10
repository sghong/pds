#!/bin/bash


#usage ~/eng2/Bryan/go_platform_v2.sh ~/eng2/Q5/CONV_ALPACABUILD_Q5Q-USA-SINGLEW_VENDOR_TIGER20230309-112017356238/android

rm -rf *

src_dir=$1
dest_dir=./

element_array=(
external/wpa_supplicant_8
hardware/qcom/wlan
kernel_platform/msm-kernel/include/net/cfg80211.h
kernel_platform/msm-kernel/include/uapi/linux/nl80211.h
vendor/qcom/proprietary/wlan/
)

for hh in "${element_array[@]}"; do
    if [ -d $1/$hh ]; then
        mkdir -p $hh
        cp -ar $1/$hh/* $hh/
    elif [ -f $1/$hh ]; then
        DIRNAME=$(dirname $hh)
        mkdir -p $DIRNAME
        cp $1/$hh $DIRNAME/
    fi
done


