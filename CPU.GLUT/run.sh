#!/bin/sh
REPEATS=108
DIMS=1024

PROGRAM=${PWD##*/}
./$PROGRAM -repeats $REPEATS -dims $DIMS
