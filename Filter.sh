#!/bin/bash

# Save the current directory
HereAtTheMoment=$(pwd)

# Find the directory specified by the user
#WhereToGo=$(find ~/ -type d -name ${1})
WhereToGo=${1}

# Loop through directories
for (( i=0; i<=9; i++ )); do
    {
        # Change to the working space
        cd ${WhereToGo}/${i}
        
        # Loop through each file matching the pattern "event_*.dat"
        while read -r File; do
            # Loop through the 10 event files
            for (( j=1; j<=10; j++ )); do
                # Make a backup copy of each event file
                cp event_${j}.dat backup_${j}.dat
                #filter lines where the third column equals 0, and overwrite the original event file
                awk '{if ($3 == 0) print $0}' < backup_${j}.dat 1> event_${j}.dat
            done
        done < <(find ${WhereToGo} -type f -name "event_*.dat")

        # Clean up backup files
        rm backup_*.dat
    } &
done

# Wait for all background processes to finish
wait

# Return home
cd ${HereAtTheMoment}

return 0
