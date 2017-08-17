#!/bin/sh
REPEATS=36
DIMS=512

PROGRAM=${PWD##*/}

for NTHREADS in 1 2 4 8
do
    echo "OMP_NUM_THREADS: $NTHREADS"
    OMP_NUM_THREADS=$NTHREADS ./$PROGRAM -repeats $REPEATS -dims $DIMS
    echo ""
done
