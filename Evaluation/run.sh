#!/bin/sh
IMAGE=../CPU.GLUT/result.bmp

PROGRAM=${PWD##*/}
./$PROGRAM $IMAGE Image/result.bmp
