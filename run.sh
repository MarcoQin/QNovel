#!/bin/bash

mkdir -p build/QNovel.app/Contents/Resources/scripts
yes | cp -rf scripts/*.py build/QNovel.app/Contents/Resources/scripts
cd build
qmake ../QNovel.pro
make
./QNovel.app/Contents/MacOS/QNovel
