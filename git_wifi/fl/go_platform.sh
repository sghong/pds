#!/bin/bash

#usage
#
#qcom2@qcom2:~/eng2/Bryan/0705/ss_source/dm3q/ss_source_dm3q_SS_CNSS2_OEMSS$ ~/go_platform.sh ~/eng2/Bryan/0705/ss_source/dm3q/dm3q_fc_version ~/eng2/DM3Q/220713_DM3Q/CONN_D4_DM3Q-USA-SINGLEW_VENDOR_TIGER-TEMP_V2/android
#

find ./ -not -path "./.git*" -name "*" -type f > ~/copyfiles.txt

for word in $(cat ~/copyfiles.txt)
do
	DIRNAME=$(dirname $word)
	FILENAME=$(basename $word)
	if [ -f $2/$DIRNAME/$FILENAME ]; then
		mkdir -p $1/$DIRNAME
		cp $2/$DIRNAME/* $1/$DIRNAME
	fi

done
#`basename $word`
