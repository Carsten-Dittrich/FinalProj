#!/bin/bash

# Save the current directory
HereAtTheMoment=$(pwd)

# Find the directory specified by the user
# WhereToGo=$(find ~/ -type d -name ${1})
WhereToGo=${1}

# Loop over the 10 directories
for (( i=0; i<=9; i++)); do

    {
    # Change to the working space
    cd ${WhereToGo}/${i}
    
    # Write down the lines containing "BEGINNINGOFEVENT"
    grep -n "BEGINNINGOFEVENT" HIJING_LBF_test_small.out | awk 'BEGIN {FS=":"}{print $1}' >> ListOfLines.txt
    
    # Add the number of the last line to the list
    wc -l HIJING_LBF_test_small.out | awk '{print $1}' >> ListOfLines.txt
    
    # Split into 10 event_*.dat files
    for (( j=1; j<=10; j++)); do
        k=$((${j}+1))
        Start=$(sed -n ${j}p ListOfLines.txt)
        End=$(sed -n ${k}p ListOfLines.txt)
        sed -n ${Start},${End}p HIJING_LBF_test_small.out > event_${j}.dat
    done
    
    # Clean up
    rm ListOfLines.txt
    
    } &

done

# Wait for all background processes to finish
wait

# Return to the original directory
cd ${HereAtTheMoment}

return 0

