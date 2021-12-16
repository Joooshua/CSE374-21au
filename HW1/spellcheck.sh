#! /bin/bash
# Yuxuan Li
# yxl24
# HW1: Problem #3

# check if the command takes the correct number of arguments
arg=$1
if [ $# -ne 1 ]; then
    echo "Please only enter one argument">& 2
    exit 1
fi

# keep counting the word
count=0
# check if the file exists
if [ -f $arg ]; then
    # read the file word by word, and then trim the punctuation and digits
    for word in $(cat $arg); do    
        # grep the number of the word
        number=$(grep -iwc "$word" /usr/share/dict/words)
        # if the word doesn't exist, then append it into the spelling text
        if [ $number -eq 0 ]; then 
            echo "$word" >> "$arg".spelling
            count=$(($count+1))
        fi
    done < $arg

    # print out the output info and counting result
    echo "./spellcheck replacing $arg.spelling file"
    echo "./spellcheck found $count spelling errors, output to file $arg.spelling"
    exit 0
else
    echo "Please enter a valid file name">& 2
    exit 1
fi