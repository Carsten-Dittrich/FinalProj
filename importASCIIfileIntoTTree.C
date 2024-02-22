#include "TFile.h"
#include "TTree.h"

// Function to import data from an ASCII file into a TTree
int importASCIIfileIntoTTree(const char *filename)
{
    // open ROOT file named 'HIJING_LBF_test_small.root', where TTree will be saved
    TFile *file = new TFile("HIJING_LBF_test_small.root","update");
    
    // make the new TTree for each event 
    TTree *tree = new TTree("event","data from ascii file");
    
    // Specification for TTree branches
    Long64_t nlines = tree->ReadFile(filename,"PLabel:PID:PrimP:DecayID:px:py:pz:E");
    
    // save TTree to 'HIJING_LBF_test_small.root' file
    tree->Write();
    
    // Close the ROOT file
    file->Close();
    
    return 0;   
}
