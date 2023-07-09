#!/bin/sh

echo Make MKMK for Linux

cd $1

if [ $OSTYPE = solaris ]; then
CPP=g++
fi

if [ $OSTYPE = linux-debian-ppc ]; then
CPP=g++-4.1
fi

if [ $OSTYPE = linux ]; then
CPP=gcc
fi

$CPP mkmk.cpp -c -DUNIX -DOSNAME=$OSNAME \
    -I /usr/include \
    -I ../dosdir

$CPP contain.cpp -c -DUNIX \
    -I /usr/include \
    -I ../dosdir

#-std=c++11
$CPP stringtools.cpp -c -DUNIX \
    -I /usr/include \
    -I ../dosdir

$CPP -o mkmk stringtools.o contain.o mkmk.o ../dosdir/match.o ../dosdir/dosdir.o -lstdc++
