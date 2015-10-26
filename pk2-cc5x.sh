#!/bin/sh

wine $1cc5x/CC5X.EXE -I$1/cc5x $3 -o$1hex.out && $1pk2cmdv1-20Linux2-6/pk2cmd -B$1pk2cmdv1-20Linux2-6 -P$2 -M -F$1out.hex
