#include "TFile.h"
#include "TTree.h"
#include "TList.h"
#include <iostream>
#include <fstream>

// Function to analyze data from a ROOT file and create histograms
int analyze()
{
    // Create histograms to store data
    TH1F *pion = new TH1F("pion", "Pion",200,0.,2.);
    TH1F *kaon = new TH1F("kaon", "Kaon",200,0.,2.);
    TH1F *proton = new TH1F("proton", "Proton",200,0.,2.);
    
    // Set X-axis labels for histograms
    pion->GetXaxis()->SetTitle("P_{t} [GeV/c]");
    kaon->GetXaxis()->SetTitle("P_{t} [GeV/c]");
    proton->GetXaxis()->SetTitle("P_{t} [GeV/c]");
    
    // Set Y-axis labels for histograms
    pion->GetYaxis()->SetTitle("Events / (10 MeV)");
    kaon->GetYaxis()->SetTitle("Events / (10 MeV)");
    proton->GetYaxis()->SetTitle("Events / (10 MeV)");
    
    // Set Y-axis title offsets for histograms
    pion->GetYaxis()->SetTitleOffset(1.45);
    kaon->GetYaxis()->SetTitleOffset(1.45);
    proton->GetYaxis()->SetTitleOffset(1.45);
    
    // Open the input file containing data
    ifstream inp;
    Float_t x,y;
    
    // Read data from the file and fill histograms accordingly
    inp.open("final_merged.dat");
    while(!(inp >> x >> y)==0){
        if(x==111){pion->Fill(y);}
        else if(x==-111){pion->Fill(y);}
        else if(x==311){kaon->Fill(y);}
        else if(x==-311){kaon->Fill(y);}
        else if(x==2212){proton->Fill(y);}
        else if(x==-2212){proton->Fill(y);}
        else{continue;}
    }
    
    // Close the input file
    inp.close();
    
    // Create a canvas to draw histograms
    TCanvas *c = new TCanvas("c","Transverse Momenta",2100,700);
    c->Divide(3,1);
    // Draw histograms on separate pads of the canvas
    c->cd(1);
    pion->Draw();
    c->cd(2);
    kaon->Draw();
    c->cd(3);
    proton->Draw();
    
    // Save the canvas as various formats
    c->SaveAs("TransverseMomentaPlot.pdf"); 
    c->SaveAs("TransverseMomentaPlot.eps");
    c->SaveAs("TransverseMomentaPlot.png");
    c->SaveAs("TransverseMomentaPlot.C");
    
    return 0;
}
