#!/bin/sh

CURDIR=`pwd`

if [ $# -ne 2 ]
then
    echo "On the top dir"
    echo "~/gitsghong/pds/sh/gosrc.sh /home/p12791/dirlist.txt ctag/"
    echo "Usage : gosrc.sh dirlist-file ctag-dir "
    exit
fi

#if [ ! -d $1 ]
#then
#  mkdir $1
#fi

CSCOPEFILENAME=$1

cd $2

rm -rf cscope.files cscope.files cscope.out ncscope.out

if [ ! -f $CSCOPEFILENAME ]
then
    echo "$CSCOPEFILENAME file not exist "
    exit
fi


for word in $( cat $CSCOPEFILENAME )
do 
  echo "===>$CURDIR/$word"
  find $CURDIR/$word ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name '*.conf' -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
done
cscope -b -k -i cscope.files
