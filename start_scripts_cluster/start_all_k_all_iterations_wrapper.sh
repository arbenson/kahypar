#!/bin/bash

while getopts 's:i:' OPTION ; do
    case "$OPTION" in
	s)
	    printf "Script:\t $OPTARG \n"
	    START_SCRIPT=$OPTARG;;
	i)
	    printf "Instance:\t $OPTARG \n"
	    INSTANCE=$OPTARG
    esac
done

if [ "x" == "x$START_SCRIPT" ]; then
  echo "-s [option] is required: start script"
  exit
fi

if [ "x" == "x$INSTANCE" ]; then
  echo "-i [option] is required: hypergraph instance"
  exit
fi

source common_setup.sh

###########################
# Experimental Setup
###########################
declare -a kValues=("2" "4" "8" "16" "32" "64" "128")
epsilon=0.03
###########################

for k in "${kValues[@]}"
do
    for reps in `seq 1 10`
    do
        seed=`od -A n -t d -N 4 /dev/urandom | awk '{print $1}'`
	$START_SCRIPT $INSTANCE $k $epsilon $seed >> "$GRAPH_NAME.$k.$epsilon.results"
    done
done
