#!/bin/sh

## bash command to make softlinks:
## $ mkdir ./inData/; cd inData
## $ for file in /afs/desy.de/group/flc/pool/tpc/share/External_Tracker/ProbeStation/24Aug2017/Sensor*; do ln -s $file .; done

## code to compile via:
g++ -o cviv.exe src/CVmeas_IVmeas.cxx -I${ROOTSYS}/include -L${ROOTSYS}/lib -std=gnu++11 $(bash root-config --cflags) $(bash root-config --libs)

#g++ -o sumPlot.exe sumPlot.cxx -I${ROOTSYS}/include -L${ROOTSYS}/lib -std=gnu++11 $(bash root-config --cflags) $(bash root-config --libs)
g++ -o compare.exe src/compare.cxx -I${ROOTSYS}/include -L${ROOTSYS}/lib -std=gnu++11 $(bash root-config --cflags) $(bash root-config --libs)

## before you run:
## $ mkdir outData

## then you can run, for instance:
## $ ./cviv.exe 32 33 55 59
## $ ./cviv.exe v2 33 42 
