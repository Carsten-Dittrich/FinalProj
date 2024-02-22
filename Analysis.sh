#!/bin/bash

# Save the current directory
HereAtTheMoment=$(pwd)

# Find the directory specified by the user
#WhereToGo=$(find ~/ -type d -name ${1})
WhereToGo=${1}


# Define particle IDs
pid=( 111 311 2212 )

# Create output folder
mkdir outputs

# Read the Entries of the Trees and fill PID and pT into final.dat
for (( i=0; i<=9; i++)); do
    {
        # Copy the ROOT script to the working space and navigate there
        cp reader.C ${WhereToGo}/${i}
        cd ${WhereToGo}/${i}
        
        # Execute ROOT script to read entries from the ROOT file and extract PID and pT information
        root -l -b -q reader.C\(\"HIJING_LBF_test_small.root\"\) | grep -E "${pid[0]}|${pid[1]}|${pid[2]}" >> final.dat
    
        # Cleaning
        rm reader.C
    } &
done

# Wait for all background processes to finish
wait

# Merge every final.dat into one file
for (( i=0; i<=9; i++)); do
    cd ${WhereToGo}/${i}
    cat final.dat >> ${HereAtTheMoment}/outputs/final_merged.dat
done

# Cleaning
for (( i=0; i<=9; i++)); do
    cd ${WhereToGo}/${i}
    rm final.dat
done

# Plotting
cp ${HereAtTheMoment}/analyze.C ${HereAtTheMoment}/outputs
cd ${HereAtTheMoment}/outputs

# Ask user if they want to see the plots
while true; do
    read -p "Do you wanna see the plots? [Y/n]"
    [[ ${REPLY} == [Yy] ]] && echo "OK, plotting!" && root analyze.C && break
    [[ ${REPLY} == [Nn] ]] && echo "Okay, just watch the generated ones!" && root -l -b -q analyze.C && break
    echo "Sorry, that option is not supported (yet). I'm going to generate the plots anyway." && root -l -b -q analyze.C && break
done

# Final cleaning
rm analyze.C


return 0
