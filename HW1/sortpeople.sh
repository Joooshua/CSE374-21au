#! /bin/bash

# Yuxuan Li
# yxl24
# HW1: Problem #2

# check if the number of input parameter is 1
if [ $# -ne 1 ]; then
    echo "Please enter only one parameter.">& 2
    exit 1
fi

# assign the first input parameter (file name) to var "arg"
arg=$1
# check if the file exists
if [ -f $arg ]; then
    # cut with the delimiter " " , take the second part, and then pipe with a sort command
    cat $arg | cut -d " " -f 2 | sort
    exit 0
else
    echo "Please pass a file name that exists.">& 2
    exit 1
fi
