VERSION=0.9.1
mkdir -p build
cd build
git clone --branch v$VERSION https://github.com/giuppe/epiphany-game.git epiphany-game-$VERSION-src
rm -rf epiphany-game-$VERSION-src/.git
tar zcvf epiphany-game-$VERSION-src.tar.gz epiphany-game-$VERSION-src
rm -rf epiphany-game-$VERSION-src
cd ..