#!/usr/bin/env bash
VERSION=0.9.2
mkdir -p build-win64
make -f Makefile.cross.win64
mv epiphany-game-win64.exe build-win64
cp -av data build-win64
cp -av README build-win64/README.txt
cp -av ChangeLog build-win64/ChangeLog.txt
cp -av COPYING build-win64/COPYING.txt
cp -av /usr/local/x86_64-w64-mingw32/bin/SDL2.dll build-win64
cp -av /usr/local/x86_64-w64-mingw32/bin/SDL2_mixer.dll build-win64
cp -av /usr/lib/gcc/x86_64-w64-mingw32/10-win32/libstdc++-6.dll \
/usr/lib/gcc/x86_64-w64-mingw32/10-win32/libgcc_s_seh-1.dll \
build-win64
mv build-win64 epiphany-win-$VERSION-win64
zip -r epiphany-win-$VERSION-win64.zip epiphany-win-$VERSION-win64
mv epiphany-win-$VERSION-win64.zip build
rm -rf epiphany-win-$VERSION-win64
