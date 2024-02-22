#include "TFile.h"
#include "TTree.h"
#include "TList.h"

// Function to read data from TTrees in a ROOT file
int reader(const char *filename)
{
    // Open the ROOT file for updating
    TFile *file = new TFile(filename,"update");
    
    // Get the list of keys (i.e., TTrees) in the file
    TList *lofk = file->GetListOfKeys();
    
    // Define particle IDs
    // Pions: pi0 = 111, pi+ = 211, antiparticles negative
    // Kaons: K0 = 311, K+ = 321, antiparticles negative
    // Protons: p = 2212
    Int_t PIDs[6]={111,-111,311,-311,2212,-2212};
    
    // Loop over all TTrees in the file
    for(Int_t i=0; i<lofk->GetEntries(); i++) {
        // Get the TTree
        TTree *tree = (TTree*) file->Get(Form("%s;%d",lofk->At(i)->GetName(),i+1));
        
         // make sure the pointer is valid, and it points to TTree
        if(!tree || strcmp(tree->ClassName(),"TTree")) {
            cout<<Form("%s is not TTree!",lofk->At(i)->GetName())<<endl; 
            continue;
        }
        //tree->Print();  //from this printout, you can for instance inspect the names of the TTree's branches
        // Print the name and pointer of the TTree
        cout<<Form("Accessing TTree named: %s",tree->GetName())<<": "<<tree<<endl;
    
        // Get the number of particles in the TTree
        Int_t nParticles = (Int_t)tree->GetEntries();
        cout<<Form("=> It has %d particles.",nParticles)<<endl;
    
        // Attach local variables to branches:
        Float_t PID=0., pT=0., px = 0., py = 0., pz = 0., E = 0.;
        tree->SetBranchAddress("PID",&PID);
        tree->SetBranchAddress("px",&px);
        tree->SetBranchAddress("py",&py);
        tree->SetBranchAddress("pz",&pz);
        tree->SetBranchAddress("E",&E);
    
        // Loop over all particles in the current TTree
        for(Int_t p = 0; p < nParticles; p++) {
            tree->GetEntry(p);
            if(PID==PIDs[0] || PID==PIDs[1] || PID==PIDs[2] || PID==PIDs[3] || PID==PIDs[4] || PID==PIDs[5]) {
	        pT=sqrt(pow(px,2)+pow(py,2));
	        cout<<Form("%f %f",PID,pT)<<endl; 
	    }
   // cout<<Form("%d: %f %f %f %f",p,px,py,pz,E)<<endl;
        }
    
        // Print message when finished with the current event
        cout<<"Done with this event, marching on...\n"<<endl;  

    }

    // Close the file
    file->Close(); 

    return 0;
}
