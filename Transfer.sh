#!/bin/bash

# Save the current directory
HereAtTheMoment=$(pwd)

# Find the directory specified by the user
#WhereToGo=$(find ~/ -type d -name ${1})
WhereToGo=${1}

# Loop through directories 0 to 9
for (( i=0; i<=9; i++)); do
    {
        # Copy file to working space and navigate there
        cp importASCIIfileIntoTTree.C ${WhereToGo}/${i}
        cd ${WhereToGo}/${i}
        #chmod 744 importASCIIfileIntoTTree.C
        
        # Loop through the 10 event files
        for (( j=1; j<=10; j++)); do
            # -b batch mode without graphics, -l No ROOT banner -q Exit after processing macro files
            root -l -b -q importASCIIfileIntoTTree.C\(\"event_${j}.dat\"\) 
        done
    
        # Cleaning
        rm importASCIIfileIntoTTree.C
        rm event_*.dat
    } &    
done

# Wait for all background processes to finish
wait

# Return to the original directory
cd ${HereAtTheMoment}

return 0
