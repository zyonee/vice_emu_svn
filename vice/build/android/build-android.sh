#!/bin/sh

VICEVERSION=2.4.2

X64_STATUS_MESSAGE="x64 compiles correctly and runs correctly."
X64SC_STATUS_MESSAGE="x64sc compiles correctly and runs correctly albeit slow, only meant for high end android devices."
X64DTV_STATUS_MESSAGE="x64dtv compiles correctly and runs correctly."
XSCPU64_STATUS_MESSAGE="xscpu64 compiles correctly and runs correctly albeit slow, only meant for high end android devices."
X128_STATUS_MESSAGE="x128 compiles correctly and runs correctly, vdc display is untested and might need work."
XCBM2_STATUS_MESSAGE="xcbm2 compiles correctly and runs correctly, needs a device which can handle 640x200 screen size."
XCBM5X0_STATUS_MESSAGE="xcbm5x0 compiles correctly and runs correctly."
XPET_STATUS_MESSAGE="xcbm2 compiles correctly and runs correctly, needs a device which can handle 640x200 screen size."
XPLUS4_STATUS_MESSAGE="xplus4 compiles correctly and runs correctly."
XVIC_STATUS_MESSAGE="xvic compiles correctly and runs correctly, screen dimensions needs some work."

MACHINE_X64="0"
MACHINE_X64SC="1"
MACHINE_XSCPU64="2"
MACHINE_X64DTV="3"
MACHINE_X128="4"
MACHINE_XCBM2="5"
MACHINE_XCBM5X0="6"
MACHINE_XPET="7"
MACHINE_XPLUS4="8"
MACHINE_XVIC="9"

# see if we are in the top of the tree
if [ ! -f configure.proto ]; then
  cd ../..
  if [ ! -f configure.proto ]; then
    echo "please run this script from the base of the VICE directory"
    exit 1
  fi
fi

curdir=`pwd`

# set all cpu builds to no
armbuild=no
arm7abuild=no
mipsbuild=no
x86build=no

showusage=no

buildrelease=no
builddevrelease=no
builddebug=no

buildemulators=0

# check options
for i in $*
do
  if test x"$i" = "xarmeabi"; then
    armbuild=yes
  fi
  if test x"$i" = "xarmeabi-v7a"; then
    arm7abuild=yes
  fi
  if test x"$i" = "xmips"; then
    mipsbuild=yes
  fi
  if test x"$i" = "xx86"; then
    x86build=yes
  fi
  if test x"$i" = "xall-cpu"; then
    armbuild=yes
    arm7abuild=yes
    mipsbuild=yes
    x86build=yes
  fi
  if test x"$i" = "xhelp"; then
    showusage=yes
  fi
  if test x"$i" = "xrelease"; then
    buildrelease=yes
  fi
  if test x"$i" = "xx64"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="x64"
    emulib="libx64.so"
    emuname="AnVICE_x64"
    STATUS_MESSAGE=$X64_STATUS_MESSAGE
    MACHINE=$MACHINE_X64
  fi
  if test x"$i" = "xx64sc"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="x64sc"
    emulib="libx64sc.so"
    emuname="AnVICE_x64sc"
    STATUS_MESSAGE=$X64SC_STATUS_MESSAGE
    MACHINE=$MACHINE_X64SC
  fi
  if test x"$i" = "xx64dtv"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="x64dtv"
    emulib="libx64dtv.so"
    emuname="AnVICE_x64dtv"
    STATUS_MESSAGE=$X64DTV_STATUS_MESSAGE
    MACHINE=$MACHINE_X64DTV
  fi
  if test x"$i" = "xxscpu64"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="xscpu64"
    emulib="libxscpu64.so"
    emuname="AnVICE_xscpu64"
    STATUS_MESSAGE=$XSCPU64_STATUS_MESSAGE
    MACHINE=$MACHINE_XSCPU64
  fi
  if test x"$i" = "xx128"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="x128"
    emulib="libx128.so"
    emuname="AnVICE_x128"
    STATUS_MESSAGE=$X128_STATUS_MESSAGE
    MACHINE=$MACHINE_X128
  fi
  if test x"$i" = "xxcbm2"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="xcbm2"
    emulib="libxcbm2.so"
    emuname="AnVICE_xcbm2"
    STATUS_MESSAGE=$XCBM2_STATUS_MESSAGE
    MACHINE=$MACHINE_XCBM2
  fi
  if test x"$i" = "xxcbm5x0"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="xcbm5x0"
    emulib="libxcbm5x0.so"
    emuname="AnVICE_xcbm5x0"
    STATUS_MESSAGE=$XCBM5X0_STATUS_MESSAGE
    MACHINE=$MACHINE_XCBM5X0
  fi
  if test x"$i" = "xxpet"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="xpet"
    emulib="libxpet.so"
    emuname="AnVICE_xpet"
    STATUS_MESSAGE=$XPET_STATUS_MESSAGE
    MACHINE=$MACHINE_XPET
  fi
  if test x"$i" = "xxplus4"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="xplus4"
    emulib="libxplus4.so"
    emuname="AnVICE_xplus4"
    STATUS_MESSAGE=$XPLUS4_STATUS_MESSAGE
    MACHINE=$MACHINE_XPLUS4
  fi
  if test x"$i" = "xxvic"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="xvic"
    emulib="libxvic.so"
    emuname="AnVICE_xvic"
    STATUS_MESSAGE=$XVIC_STATUS_MESSAGE
    MACHINE=$MACHINE_XVIC
  fi
  if test x"$i" = "xall-emu"; then
    buildemulators=`expr $buildemulators + 1`
    emulator="all emulators"
    emulib="libvice.so"
    emuname="AnVICE"
  fi
done

if test x"$showusage" = "xyes"; then
  echo "Usage: $0 [release] [<cpu types>] [emulator] [help]"
  echo "release indicates that the binary needs to be build as a official release as opposed to a developent release."
  echo "cpu-types: armeabi, armeabi-v7a, mips, x86 (or all-cpu for all)."
  echo "if no cpu-type is given armeabi will be built by default."
  echo "emulators: x64, x64sc, x64dtv, xscpu64, x128, xcbm2, xcbm5x0, xpet, xplus4, xvic (or all-emu for all emulators)."
  exit 1
fi

if test x"$buildemulators" = "x0"; then
  emulator="x64"
  emulib="libx64.so"
  emuname="AnVICE_x64"
else
  if test x"$buildemulators" != "x1"; then
    echo "Only one emulator option can be given"
    exit 1
  fi
fi

CPUS=""

if test x"$armbuild" = "xyes"; then
  CPUS="armeabi"
fi

if test x"$arm7abuild" = "xyes"; then
  if test x"$CPUS" = "x"; then
    CPUS="armeabi-v7a"
  else
    CPUS="$CPUS armeabi-v7a"
  fi
fi

if test x"$mipsbuild" = "xyes"; then
  if test x"$CPUS" = "x"; then
    CPUS="mips"
  else
    CPUS="$CPUS mips"
  fi
fi

if test x"$x86build" = "xyes"; then
  if test x"$CPUS" = "x"; then
    CPUS="x86"
  else
    CPUS="$CPUS x86"
  fi
fi

if test x"$CPUS" = "x"; then
  CPUS="armeabi"
fi

if test x"$CPUS" = "xarmeabi armeabi-v7a mips x86"; then
  CPULABEL="all"
else
  CPULABEL=$CPUS
fi

if test x"$buildrelease" = "xyes"; then
  if [ ! -f vice-release.keystore ]; then
    echo "vice-release.keystore not found, will fallback on a debug build"
    buildrelease=no
    builddebug=yes
  fi
else
  if [ ! -f vice-dev.keystore ]; then
    echo "vice-dev.keystore not found, will use a debug key instead"
    builddebug=yes
  else
    builddebug=no
    builddevrelease=yes
  fi
fi

cd src

echo generating src/translate_table.h
. ./gentranslatetable.sh <translate.txt >translate_table.h

echo generating src/translate.h
. ./gentranslate_h.sh <translate.txt >translate.h

echo generating src/infocontrib.h
. ./geninfocontrib_h.sh <../doc/vice.texi | sed -f infocontrib.sed >infocontrib.h

cd arch/android/AnVICE/jni

echo generating Application.mk
cp Application.mk.proto Application.mk
echo >>Application.mk "APP_ABI := $CPUS"

echo clearing out all Android.mk files
for i in `find . -name "Android.mk"`
do
  rm -f $i
done

echo generating Android.mk files for $emulator

if test x"$emulator" = "xx64"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-x64.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_c64cart/Android.mk.proto vice_c64cart/Android.mk
  cp vice_c64exp/Android.mk.proto vice_c64exp/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_commoncart/Android.mk.proto vice_commoncart/Android.mk
  cp vice_iec/Android.mk.proto vice_iec/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_vicii/Android.mk.proto vice_vicii/Android.mk
  cp vice_x64/Android.mk.proto vice_x64/Android.mk
fi

if test x"$emulator" = "xx64sc"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-x64sc.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_c64cart/Android.mk.proto vice_c64cart/Android.mk
  cp vice_c64exp/Android.mk.proto vice_c64exp/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_commoncart/Android.mk.proto vice_commoncart/Android.mk
  cp vice_iec/Android.mk.proto vice_iec/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_viciisc/Android.mk.proto vice_viciisc/Android.mk
  cp vice_x64sc/Android.mk.proto vice_x64sc/Android.mk
fi

if test x"$emulator" = "xx64dtv"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-x64dtv.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_c64exp/Android.mk.proto vice_c64exp/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_iec/Android.mk.proto vice_iec/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_vicii/Android.mk.proto vice_vicii/Android.mk
  cp vice_x64dtv/Android.mk.proto vice_x64dtv/Android.mk
fi

if test x"$emulator" = "xxscpu64"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-xscpu64.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_c64cart/Android.mk.proto vice_c64cart/Android.mk
  cp vice_c64exp/Android.mk.proto vice_c64exp/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_commoncart/Android.mk.proto vice_commoncart/Android.mk
  cp vice_iec/Android.mk.proto vice_iec/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_viciisc/Android.mk.proto vice_viciisc/Android.mk
  cp vice_xscpu64/Android.mk.proto vice_xscpu64/Android.mk
fi

if test x"$emulator" = "xxvic"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-xvic.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_commoncart/Android.mk.proto vice_commoncart/Android.mk
  cp vice_iec/Android.mk.proto vice_iec/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_xvic/Android.mk.proto vice_xvic/Android.mk
fi

if test x"$emulator" = "xxplus4"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-xplus4.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_iec/Android.mk.proto vice_iec/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_xplus4/Android.mk.proto vice_xplus4/Android.mk
fi

if test x"$emulator" = "xxcbm5x0"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-xplus4.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_xcbm5x0/Android.mk.proto vice_xcbm5x0/Android.mk
  cp vice_cbm2common/Android.mk.proto vice_cbm2common/Android.mk
  cp vice_vicii/Android.mk.proto vice_vicii/Android.mk
fi

if test x"$emulator" = "xx128"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-x128.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_c64cart/Android.mk.proto vice_c64cart/Android.mk
  cp vice_c64exp/Android.mk.proto vice_c64exp/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_commoncart/Android.mk.proto vice_commoncart/Android.mk
  cp vice_iec/Android.mk.proto vice_iec/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_vicii/Android.mk.proto vice_vicii/Android.mk
  cp vice_x128/Android.mk.proto vice_x128/Android.mk
fi

if test x"$emulator" = "xxcbm2"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-xcbm2.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_xcbm2/Android.mk.proto vice_xcbm2/Android.mk
  cp vice_cbm2common/Android.mk.proto vice_cbm2common/Android.mk
  cp vice_crtc/Android.mk.proto vice_crtc/Android.mk
fi

if test x"$emulator" = "xxpet"; then
  cp Android.mk.proto Android.mk
  cp locnet/Android-xpet.mk.proto locnet/Android.mk
  cp locnet_al/Android.mk.proto locnet_al/Android.mk
  cp vice_common/Android.mk.proto vice_common/Android.mk
  cp vice_commonall/Android.mk.proto vice_commonall/Android.mk
  cp vice_ieeepar/Android.mk.proto vice_ieeepar/Android.mk
  cp vice_tape/Android.mk.proto vice_tape/Android.mk
  cp vice_xpet/Android.mk.proto vice_xpet/Android.mk
  cp vice_crtc/Android.mk.proto vice_crtc/Android.mk
fi

echo building $emulib
cd ..

if test x"$emulator" = "xx64"; then
   sed -e 's/@VICE@/AnVICE_x64/g' -e 's/@VICE_ROM@/C64 ROM \(KERNAL\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-x64 assets/sdl-vicerc
   cp ../../../../data/C64/sdl_sym.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xx64sc"; then
   sed -e 's/@VICE@/AnVICE_x64sc/g' -e 's/@VICE_ROM@/C64SC ROM \(KERNAL\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-x64sc assets/sdl-vicerc
   cp ../../../../data/C64/sdl_sym.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xx64dtv"; then
   sed -e 's/@VICE@/AnVICE_x64dtv/g' -e 's/@VICE_ROM@/C64DTV ROM \(KERNAL\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-x64dtv assets/sdl-vicerc
   cp ../../../../data/C64DTV/sdl_sym.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xxscpu64"; then
   sed -e 's/@VICE@/AnVICE_xscpu64/g' -e 's/@VICE_ROM@/SCPU64 ROM \(SCPU64\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-xscpu64 assets/sdl-vicerc
   cp ../../../../data/SCPU64/sdl_sym.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xxvic"; then
   sed -e 's/@VICE@/AnVICE_xvic/g' -e 's/@VICE_ROM@/VIC20 ROM \(KERNAL\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-xvic assets/sdl-vicerc
   cp ../../../../data/VIC20/sdl_sym.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xxplus4"; then
   sed -e 's/@VICE@/AnVICE_xplus4/g' -e 's/@VICE_ROM@/PLUS4 ROM \(KERNAL\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-xplus4 assets/sdl-vicerc
   cp ../../../../data/PLUS4/sdl_sym.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xxcbm5x0"; then
   sed -e 's/@VICE@/AnVICE_xcbm5x0/g' -e 's/@VICE_ROM@/CBM5X0 ROM \(KERNAL.500\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-xcbm5x0 assets/sdl-vicerc
   cp ../../../../data/CBM-II/sdl_buks.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xx128"; then
   sed -e 's/@VICE@/AnVICE_x128/g' -e 's/@VICE_ROM@/C128 ROM \(KERNAL\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-x128 assets/sdl-vicerc
   cp ../../../../data/C128/sdl_sym.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xxcbm2"; then
   sed -e 's/@VICE@/AnVICE_xcbm2/g' -e 's/@VICE_ROM@/CBM2 ROM \(KERNAL\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-xcbm2 assets/sdl-vicerc
   cp ../../../../data/CBM-II/sdl_buks.vkm assets/sdl_sym.vkm
fi

if test x"$emulator" = "xxpet"; then
   sed -e 's/@VICE@/AnVICE_xpet/g' -e 's/@VICE_ROM@/PET ROM \(KERNAL4\)/g' <res-proto/values/strings.xml >res/values/strings.xml
   cp assets-proto/sdl-vicerc-xpet assets/sdl-vicerc
   cp ../../../../data/CBM-II/sdl_buks.vkm assets/sdl_sym.vkm
fi

ndk-build

echo generating needed java files

sed s/@VICE_MACHINE@/$MACHINE/g <src-proto/com/locnet/vice/PreConfig.java >src/com/locnet/vice/PreConfig.java

if test x"$emulator" = "xx64"; then
   sed -e s/@VICE@/x64/g -e s/@VICE_DATA_PATH@/c64/g -e s/@VICE_DATA_FILE@/kernal/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xx64sc"; then
   sed -e s/@VICE@/x64sc/g -e s/@VICE_DATA_PATH@/c64/g -e s/@VICE_DATA_FILE@/kernal/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xx64dtv"; then
   sed -e s/@VICE@/x64dtv/g -e s/@VICE_DATA_PATH@/c64dtv/g -e s/@VICE_DATA_FILE@/kernal/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xxscpu64"; then
   sed -e s/@VICE@/xscpu64/g -e s/@VICE_DATA_PATH@/scpu64/g -e s/@VICE_DATA_FILE@/scpu64/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xxvic"; then
   sed -e s/@VICE@/xvic/g -e s/@VICE_DATA_PATH@/vic20/g -e s/@VICE_DATA_FILE@/kernal/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xxplus4"; then
   sed -e s/@VICE@/xplus4/g -e s/@VICE_DATA_PATH@/plus4/g -e s/@VICE_DATA_FILE@/kernal/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xxcbm5x0"; then
   sed -e s/@VICE@/xcbm5x0/g -e s/@VICE_DATA_PATH@/cbm-ii/g -e s/@VICE_DATA_FILE@/kernal.500/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xx128"; then
   sed -e s/@VICE@/x128/g -e s/@VICE_DATA_PATH@/c128/g -e s/@VICE_DATA_FILE@/kernal/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xxcbm2"; then
   sed -e s/@VICE@/xcbm2/g -e s/@VICE_DATA_PATH@/cbm-ii/g -e s/@VICE_DATA_FILE@/kernal/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

if test x"$emulator" = "xxpet"; then
   sed -e s/@VICE@/xpet/g -e s/@VICE_DATA_PATH@/pet/g -e s/@VICE_DATA_FILE@/kernal4/g <src-proto/com/locnet/vice/DosBoxLauncher.java >src/com/locnet/vice/DosBoxLauncher.java
fi

echo generating apk

if test x"$buildrelease" = "xyes"; then
  cp $curdir/vice-release.keystore ./
  echo >ant.properties "key.store=vice-release.keystore"
  echo >>ant.properties "key.alias=vice_release"
fi

if test x"$builddevrelease" = "xyes"; then
  cp $curdir/vice-dev.keystore ./
  echo >ant.properties "key.store=vice-dev.keystore"
  echo >>ant.properties "key.alias=vice_dev"
fi

if test x"$builddebug" = "xyes"; then
  rm -f ant.properties
  ant debug
  cd ../../../..
  mv src/arch/android/AnVICE/bin/PreConfig-debug.apk ./$emuname-\($CPULABEL\)-$VICEVERSION.apk
else
  ant release
  rm -f vice-*.keystore
  rm -f ant.properties
  cd ../../../..
  mv src/arch/android/AnVICE/bin/PreConfig-release.apk ./$emuname-\($CPULABEL\)-$VICEVERSION.apk
fi

if [ ! -f $emuname-\($CPULABEL\)-$VICEVERSION.apk ]; then
  echo build not completed, check for errors in the output
else
  echo Android port binary generated as $emuname-\($CPULABEL\)-$VICEVERSION.apk
  echo $STATUS_MESSAGE
fi
