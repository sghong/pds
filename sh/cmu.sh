#!/bin/sh

CURDIR=`pwd`

if [ $# -ne 1 ]
then
    echo "Usage : gosrc.sh dir [dirlist.txt]"
    exit
fi

if [ ! -d $1 ]
then
  mkdir $1
fi

CM_UPDATE_DIR=$CURDIR/$1/dirlist.txt

RESULT=$CURDIR/$1/changesfile.txt

rm -f $RESULT

cd $1

if [ ! -f $CM_UPDATE_DIR ]
then
    echo "$CM_UPDATE_DIR file not exist"
    exit
fi

#pushd $CURDIR

for word in $(cat $CM_UPDATE_DIR)
do 
#  echo "===>$CURDIR/$word"
#cm fc .
  echo "$word"
  cm fc -R $word >> $CURDIR/$1/changesfile.txt
#  cm fp -R $word >> $CURDIR/$1/changesfile.txt
#cm fc . 2>&1 | tee d.txt
#
# file added is not seen by command `cm fc`
#
  cd $CURDIR

done

#popd
