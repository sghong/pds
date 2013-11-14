#!/bin/sh

rm -rf cscope.files cscope.files cscope.out ncscope.out

find $PWD/adsp_proc ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

find $PWD/LINUX/android/vendor/pantech/ ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

find $PWD/LINUX/android/vendor/qcom/proprietary/sensors ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

find $PWD/LINUX/android/kernel/arch/arm/mach-msm ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

find $PWD/LINUX/android/kernel/init ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files

find $PWD/LINUX/android/kernel/kernel ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files

find $PWD/LINUX/android/kernel/include ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files

find $PWD/boot_images ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

find $PWD/rpm_proc ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

find $PWD/LINUX/android/bootable ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

find $PWD/LINUX/android/system ! \( -type d \) ! \( -type d -path '*.svn' -prune \) \
       \( -name '*.[cChHsS]' -o -name '*.cpp' -o -name 'Makefile*' -o \
      -name 'makefile*' -o -name '*.cc' -o -name '*.mk' -o -name '*.sh' -o -name 'Kconfig' \
      -o -name 'KConfig' -o -name '*.mak' -o -name '*.min' -o -name '*.cmm' -o -name '*.txt' -o -name '*Sconscript*' -o -name '*scons' \
      -o -name '*config' -o -name '*.rc' -o -name '*.ld' -o -name '*.java' -o -name '*.cmd' -o -name '*.pm' -o -name '*.py' \
      -o -name '*.pl' -o -name '*.pds' -o -name '*.cfg' -o -name '*.scl' -o -name '*.xml' -o -name '*SConscript' -o -name '*SConstruct' \) -print >> cscope.files
#find . \( -name '*.*' -o -name '*' \) ! \( -name '*.o' -o -name 'cscope.files' \
#-o -name 'cscope.out' -o -name 'tags' \) ! -type d -print > cscope.files 

cscope -b -k -i cscope.files

