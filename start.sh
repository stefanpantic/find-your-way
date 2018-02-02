#!/bin/sh

# make (-j tells make to run concurrently)
make -j

# run program with some default arguments
exec ./build/find-your-way ./resource/map/01.json ./resource/texture/wall.bmp ./resource/texture/ceil.bmp ./resource/texture/floor.bmp
