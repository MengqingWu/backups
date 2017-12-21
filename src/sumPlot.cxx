#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLegend.h"

#include <iostream>

using namespace std;


void sumPlot(int n2plot=10,
	     bool printalot = true){
  // <n2plot>: sensors to plot from 31 to 31+n2plot-1;

  int revised_sensors=[31, 32, 33, 42, 43, 58]; // version=2 for them
  
  /*START: Legend definition*/
  TLegend *leg = new TLegend(0.65,0.25,0.85, 0.55);
  leg->SetTextSize(0.04); 
  leg->SetTextFont(42); 
  leg->SetTextColor(1);
  leg->SetBorderSize(0);  //no border for legend 
  leg->SetFillColor(0);  // white
  /*END: Legend definition*/
  
  TFile* dataf=TFile::Open("test/test_sum_CV.root");
  TGraphErrors* gra_arr[n2plot];

  Double_t  maxY = 0.;
  int       maxY_key = 0;
  int       version = 1;
  
  for (int isid=0; isid<n2plot; isid++){
    int sid_num = 31+isid;
 
    string isid_name = "Sensor_"+to_string(sid_num)+"_CV_"+ to_string(version) +"_1OverC2_V";
    
    gra_arr[isid]=(TGraphErrors*)dataf->Get(isid_name.c_str());
    gra_arr[isid]->SetMarkerColor(kOrange+isid);

    auto iymax = gra_arr[isid]->GetYaxis()->GetXmax();
    
    if (iymax>maxY){
      maxY = iymax;
      maxY_key = isid;
    }
    
    auto toprint = gra_arr[isid]->GetName();
    if (printalot )
      cout<<"[info] I am #"<< isid
	  <<"\n\t TGraph title ==> "<< toprint <<endl;
  }
  dataf->Close();
  if (printalot)  cout<<"max Y is ==> sensor "<<maxY_key<<endl;
  
  //--> to plot:
  TCanvas can;
  gra_arr[maxY_key]->Draw("ape");
  for (int igra=0; igra<n2plot; igra++){
    if (igra==maxY_key) continue;
    gra_arr[igra]->Draw("pesame");

    string graName = "Sensor "+to_string(igra+31);
    leg->AddEntry(gra_arr[igra], graName.c_str(), "lep");
  }
  
  leg->Draw("same");
  can.SaveAs("sumPlot.png");

  //-> clean pointers:
  delete dataf;
  for (TGraphErrors* igra_p: gra_arr) delete igra_p;
}


void drawDerivatives(){

  TFile* dataf=TFile::Open("test/test_sum_CV.root");
  dataf->Close();
}

int main(){
  sumPlot();
  return 1;
}
