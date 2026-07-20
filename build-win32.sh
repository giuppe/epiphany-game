#!/usr/bin/env bash
VERSION=0.9.2
mkdir -p build-win32
make -f Makefile.cross.win32
mv epiphany-game-win32.exe build-win32
cp -av data build-win32
cp -av README build-win64/README.txt
cp -av ChangeLog build-win64/ChangeLog.txt
cp -av COPYING build-win64/COPYING.txt
cp -av /usr/local/i686-w64-mingw32/bin/SDL2.dll build-win32
cp -av /usr/local/i686-w64-mingw32/bin/SDL2_mixer.dll build-win32
cp -av /usr/lib/gcc/i686-w64-mingw32/10-win32/libstdc++-6.dll \
/usr/lib/gcc/i686-w64-mingw32/10-win32/libgcc_s_dw2-1.dll \
build-win32

mv build-win32 epiphany-win-$VERSION-win32
zip -r epiphany-win-$VERSION-win32.zip epiphany-win-$VERSION-win32
mv epiphany-win-$VERSION-win32.zip build
rm -rf epiphany-win-$VERSION-win32
