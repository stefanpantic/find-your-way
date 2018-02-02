#!/bin/sh

# make
make -j

# run program with some default arguments
exec ./build/find-your-way ./resource/01.json ./resource/texture/wall.bmp ./resource/texture/ceil.bmp ./resource/texture/floor.bmp
