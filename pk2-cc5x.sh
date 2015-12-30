#!/bin/sh

wine $1Cc5x/CC5X.EXE -I$1/Cc5x $3$4 -o$3$5.hex && $1PK2Cmd/pk2cmdv1-20Linux2-6/pk2cmd -B$1PK2Cmd/pk2cmdv1-20Linux2-6 -P$2 -M -F$3$5.hex
