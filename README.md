# Analysis of HIJING Output

This programme was developed in scope of the lecture "Scientific computing in high-energy physics". It utilizes Linux, Bash, and ROOT functionalities to fully automate the data analysis of a typical HIJING dataset, generated in 10 separate jobs on a local batch farm.

The compressed HIJING dataset (approximately 170 MB) can be downloaded from the following direct link: https://cernbox.cern.ch/index.php/s/BJern5Ky7ajoULd. Alternatively, one can use the command "wget https://cernbox.cern.ch/index.php/s/BJern5Ky7ajoULd/download -O HIJING_LBF_test.tar.gz" in the terminal. After downloading, extract the dataset using the command "tar xf HIJING_LBF_test.tar.gz". The size after extraction will be around 680 MB.

This dataset corresponds to the HIJING model prediction for the collisions of heavy ions (Pb-Pb) at a collision energy of 2.76 TeV. That was the heavy-ion colliding system and energy used in Run 1 operations (2009-2013) at Large Hadron Collider.

Inside the directory HIJING_LBF_test, there are 10 subdirectories containing various configuration or log files. The most important file is the ASCII file HIJING_LBF_test_small.out, which stores the final output of HIJING. Each HIJING_LBF_test_small.out file contains detailed output for 10 heavy-ion collisions, resulting in a total dataset of 10×10 = 100 heavy-ion collisions for analysis.

The program is divided into four scripts.
1. Splitting: This script splits the large HIJING output file HIJING_LBF_test_small.out in each subdirectory into 10 separate files named event_0.dat, ..., event_9.dat. Each new file contains data for a particular event.
2. Filtering: This script filters out, from each subdirectory, information for primary particles (particles with the label 0 in the 3rd column) from each event_?.dat file obtained in the previous step.
3. Transfering: This script processes all filtered event_?.dat files and stores, for each event and each particle, its PID and kinematics into ROOT's container TTree named HIJING_LBF_test_small.root.
4. Analysis: This script collects all ROOT files HIJING_LBF_test_small.root obtained in the previous step and passes them to dedicated ROOT macros for final analysis.

To execute the program, use the following command line:
source TheFinalTouch.sh (PATH)/HIJING_LBF_test
