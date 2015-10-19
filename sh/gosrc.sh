#!/bin/sh

rm -rf cscope.files cscope.files cscope.out ncscope.out











find $PWD/hardware/qcom/sensors ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files

find $PWD/hardware/libhardware ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files

find $PWD/kernel/drivers/staging/iio ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
      
find $PWD/kernel/drivers/input/misc ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files

find $PWD/frameworks/base/core/java/android/hardware/ ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files

find $PWD/hardware/ ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
cscope -b -k -i cscope.files

