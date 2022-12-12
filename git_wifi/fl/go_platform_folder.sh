#!/bin/bash

#usage
#
# go_platform.sh $1 $2
#현재 폴더에 있는 파일을 $2 에서 찾는다. 있다면 $1 으로 복사한다.
#이때 $2 에 파일 추가되어 있으면 $1로 복사가 안된다.
#그래서 cp -ar 을 한다. 중복된 작업을 각 ㅍ폴더마다 해도 어쩔수 없다. 
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
		cp -ar $2/$DIRNAME/ $1/$DIRNAME
	fi

done
#`basename $word`
