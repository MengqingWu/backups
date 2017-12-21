#!/bin/bash

#------
# 1) Do cviv.exe first to produce all root;
# 2) merge all iv cv root files to a bit one;
# 3) run compare.exe, which get histos from the big final merged root file.
#------

#-----------------Option-Start-----------------#

# Usage info
show_help() {
cat << EOF
Usage: ${0##*/} [-hv] [-f OUTFILE] ...
Do stuff with FILE and write the result to standard output. With no FILE
or when FILE is -, read standard input.

    -h          display this help and exit
    -f OUTFILE  write the result to OUTFILE instead of standard output.
    --default   run cviv.exe over all sensor measurements stored in 
                ./inData/Sensor*
EOF
}

while [[ $# -gt 0 ]];do
    key="$1"
    case $key in
	-e|--extension)
	    EXTENSION="$2"
	    shift # past argument
	    shift # past value
	    ;;
	-s|--searchpath)
	    SEARCHPATH="$2"
	    shift # past argument
	    shift # past value
	    ;;
	-d|--diff)
	    SENSORS2COMPARE="$2"
	    shift # past argument
	    shift # past value
	    ;;
	--default)
	    DEFAULT=YES
	    shift # past argument
	    ;;
	-h|--help)
	    show_help
	    exit 0
	    ;;
	*) # unknown option
	    show_help
	    exit 1
	    ;;
    esac
done

echo DEFAULT         = "${DEFAULT}"

#echo "Number files in SEARCH PATH with EXTENSION:" $(ls -1 "${SEARCHPATH}"/*."${EXTENSION}" | wc -l)

# if [[ -n $1 ]]; then
#     echo "Last line of file specified as non-opt/last argument:"
#     tail -1 "$1"
# fi


#-----------------Option-End-----------------#
#-----------------Variables-Set-----------------#
DEBUG=""
RUN_RAW_SENSOR=0
if [ -n "$DEFAULT" ]; then
    if [ "$DEFAULT" == "YES" ]; then
	echo "default"
	RUN_RAW_SENSOR=1
    fi
fi

if [ -n "$SENSOR2COMPARE" ]; then
    echo sensor to compare = "${SENSORS2COMPARE}"
    IFS=', ' read -r -a diff_arr <<< "$SENSORS2COMPARE"
    for el in "${diff_arr[@]}";do
	echo "$el"
    done
    
fi

#-----------------Variables-End-----------------#

if [ "$RUN_RAW_SENSOR" -eq "1" ]
then
    echo "[cviv.exe] start to plot all virgin sensors... "
    for v in `seq 1 3`;do
	numRaw=''
	numBB=''

	echo version $v
	
	for i in `seq 31 59`; do
	    
	    f_bb='Sensor_BumpBonded_'$i'_IV_'$v
	    if [ ! -f ./inData/$f_bb ]; then
		if [ -n "$DEBUG" ]; then
		    echo $f_bb "not found!"
		fi
	    else
		numBB+=$i' '
	    fi

	    f_raw='Sensor_'$i'_IV_'$v
	    if [ ! -f ./inData/$f_raw ]; then
		if [ -n "$DEBUG" ]; then
		    echo $f_raw "not found!"
		fi
	    else
		numRaw+=$i' '
	    fi
	    
	done
	
	if [ -n "$numRaw" ]; then
	    echo ./cviv.exe v$v $numRaw
	    ./cviv.exe v$v $numRaw
	fi
	if [ -n "$numBB" ]; then
	    echo ./cviv.exe PATN=BumpBonded v$v $numBB
	    ./cviv.exe PATN=BumpBonded v$v $numBB
	fi
    
    done

    rm -f outData/merge_IV_CV.root
    hadd outData/merge_IV_CV.root outData/Sensor*V*.root

fi



for el in "IV" "CV";do
    
    for i in `seq 31 59`;do
	ifile='Sensor_BumpBonded_'$i'_'$el'_1'
	ifile_virgin='Sensor_'$i'_'$el'_1'

	if [ ! -f ./inData/$ifile ] || [ ! -f ./inData/$ifile_virgin ]; then
	    echo $ifile or $ifile_virgin "not found!"
	else
	    #echo $ifile
	    #ls ./inData/$ifile_virgin
	    echo ./compare.exe Sensor$i'_'$el'' BumpBonded_$i'_'$el'_1' $i'_'$el'_1'
	    ./compare.exe Sensor$i'_'$el'' BumpBonded_$i'_'$el'_1' $i'_'$el'_1'
	fi
	
    done
    
done


#------------------------
## before you run:
## $ mkdir outData
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
#./compare.exe Sensor35_IV BumpBonded_35_IV_1 35_IV_1

./compare.exe Sensor31_CV BumpBonded_31_CV_1 31_CV_2
./compare.exe Sensor32_CV BumpBonded_32_CV_1 32_CV_2
./compare.exe Sensor33_CV BumpBonded_33_CV_1 33_CV_2
#./compare.exe Sensor34_CV BumpBonded_34_CV_1 34_CV_1
#./compare.exe Sensor35_CV BumpBonded_35_CV_1 35_CV_1

./compare.exe Sensor36_IV BumpBonded_36_IV_2 36_IV_1
./compare.exe Sensor58_IV BumpBonded_58_IV_1 58_IV_3


