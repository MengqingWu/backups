#!/bin/sh

## bash command to make softlinks:
## $ mkdir ./inData/; cd inData
## $ for file in /afs/desy.de/group/flc/pool/tpc/share/External_Tracker/ProbeStation/24Aug2017/Sensor*; do ln -s $file .; done

## code to compile via:
g++ -o cviv.exe CVmeas_IVmeas.cxx -I${ROOTSYS}/include -L${ROOTSYS}/lib -std=gnu++11 $(bash root-config --cflags) $(bash root-config --libs)

#g++ -o sumPlot.exe sumPlot.cxx -I${ROOTSYS}/include -L${ROOTSYS}/lib -std=gnu++11 $(bash root-config --cflags) $(bash root-config --libs)
g++ -o compare.exe compare.cxx -I${ROOTSYS}/include -L${ROOTSYS}/lib -std=gnu++11 $(bash root-config --cflags) $(bash root-config --libs)        

## before you run:
## $ mkdir outData

## then you can run, for instance:
## $ ./cviv.exe 32 33 55 59
## $ ./cviv.exe v2 33 42
#./cviv.exe 31 32 33 34 35 36 37 38 39
#./cviv.exe 40 41 42 43 44 45 46 47 48 49
#./cviv.exe 50 51 52 53 54 55 56 57 58 59
#./cviv.exe v2 31 32 33 42 43 58
#./cviv.exe v3 58

#./cviv.exe PATN=BumpBonded 31 32 33 34 35
#./cviv.exe v2 31 32 33
#./cviv.exe v3 34
#./cviv.exe 34 35
 

./compare.exe Sensor31_IV BumpBonded_31_IV_1 31_IV_2
./compare.exe Sensor32_IV BumpBonded_32_IV_1 32_IV_2
./compare.exe Sensor33_IV BumpBonded_33_IV_1 33_IV_2
./compare.exe Sensor34_IV BumpBonded_34_IV_1 34_IV_3
./compare.exe Sensor35_IV BumpBonded_35_IV_1 35_IV_1

./compare.exe Sensor31_CV BumpBonded_31_CV_1 31_CV_2
./compare.exe Sensor32_CV BumpBonded_32_CV_1 32_CV_2
./compare.exe Sensor33_CV BumpBonded_33_CV_1 33_CV_2
./compare.exe Sensor34_CV BumpBonded_34_CV_1 34_CV_1
./compare.exe Sensor35_CV BumpBonded_35_CV_1 35_CV_1

