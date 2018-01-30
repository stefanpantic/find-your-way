#!/bin/sh

# run make if build directory doesn't exist ( -j flag will tell make to run concurrently )
if [ ! -d 'build' ]
then
	make -j
fi

# run program with some default arguments
exec ./build/find-your-way ./resource/01.json ./resource/texture/wall.bmp ./resource/texture/ceil.bmp ./resource/texture/floor.bmp
