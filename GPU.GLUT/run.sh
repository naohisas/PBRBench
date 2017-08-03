#!/bin/sh
REPEATS=36
DIMS=512

PROGRAM=${PWD##*/}
./$PROGRAM -repeats $REPEATS -dims $DIMS
