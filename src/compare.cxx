#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLegend.h"

#include <iostream>
#include <vector>
#include <regex>
using namespace std;

/*
 * Created by Mengqing <mengqing.wu@desy.de> in Summer 2017
 * Updated @Jun2019: iterated by $Outname, either 'outData/merge_IV_CV.root' for sensor data, or 'outData/mergeTS_IV_CV.root' for TestStructures;
 */

/*declare the functions for main() first*/
void compare(vector<string>, string, bool);

int main(int argc, char* argv[]){
  
    
  if (argc<2) {
    throw std::range_error("\n[Usage]:\n\t ./compare.exe $Outname $Plot1 $Plot2 \n\t -- $Plot#: e.g. from outData/merge_IV_CV.root you will see 'Sensor_BumpBonded_33_CV_1_1OverC2_V', $Plot1 is 'BumpBonded_33_CV_1' \n");
  }
  
  //vector<string> cans = {"BumpBonded_31_IV_1",
  //			  "31_IV_2"};
  vector<string> cans;
  for (int ii=2; ii<argc; ii++) cans.push_back(argv[ii]);
  
  compare(cans, argv[1], true);
  return 0;
}

void compare(vector<string> candidates ,
	     string outname,
	     bool printalot = true){
  // <n2plot>: sensors to plot from 31 to 31+n2plot-1;
  //int revised_sensors=[31, 32, 33, 42, 43, 58]; // version=2 for them

  //-- Prepare to deal with Sensor or TS:
  string datatype, dataDir;
  if (outname.substr(0,4)=="Test"){
    datatype = "TestStructure";
    dataDir = "outData/mergeTS_IV_CV.root";
  }
  else{
    datatype = "Sensor";
    dataDir = "outData/merge_IV_CV.root";
  }
    
  /*START: Legend definition*/
  TLegend *leg = new TLegend(0.55,0.30,0.85, 0.55);// was: 0.65,0.25,0.85,0.55 (change for tri-plot)
  leg->SetTextSize(0.04); 
  leg->SetTextFont(42); 
  leg->SetTextColor(1);
  leg->SetBorderSize(0);  //no border for legend 
  leg->SetFillColor(0);  // white
  leg->SetFillStyle(0); // transparent
  /*END: Legend definition*/

  TFile* dataf = TFile::Open(dataDir.c_str());
  
  TGraphErrors* graph_arr[candidates.size()];

  Double_t  maxY = 0., minY = 0.;
  int       maxY_key = 0, minY_key = 0;

  // for (auto&& var : candidates){
  // for (auto var = begin(candidates), igraph = begin(s_graph_arr), eoc=end(candidates), ++var, ++igraph){
  for (int icand=0; icand<candidates.size(); icand++){
    regex exIV("IV");
    regex exCV("CV");
    auto var = candidates[icand];
    
    string histo_name = datatype+"_"+ var ;
    if (regex_search(var, exIV)) histo_name+="_Iguard_V";
    else if (regex_search(var, exCV)) histo_name+="_1OverC2_V";
    else {
      perror("Existing: Wrong name to compare, check the input!");
      return;
    }

    cout<<"Hist name: "<< histo_name<<endl;
    graph_arr[icand]=(TGraphErrors*)dataf->Get(histo_name.c_str());
    cout<< "igraph object: "<<graph_arr[icand] <<endl;
    
    graph_arr[icand]->SetMarkerColor(kOrange+icand);

    auto iymax = graph_arr[icand]->GetYaxis()->GetXmax();
    if (iymax>maxY){
      maxY = iymax;
      maxY_key = icand;
    }
    
    auto iymin = graph_arr[icand]->GetYaxis()->GetXmin();
    if (icand==0 ) minY = iymin;
    else{
      if (iymin<minY){
	minY = iymin;
	minY_key = icand;
      }
    }
    
    if (printalot ){
      auto toprint = graph_arr[icand]->GetName();
      cout<<"[info] I am #"<< icand
	  <<"\n\t TGraph title ==> "<< toprint <<endl;
    }
  }
  //  dataf->Close();
  if (printalot)  cout<<"max Y is ==>  "<< candidates[maxY_key] <<endl;
  
  //--> to plot:
  TCanvas can;
  //can.SetLogy(); 
  puts("\n\tdebug 11\n");
  graph_arr[maxY_key]->Draw("ape");
  graph_arr[maxY_key]->GetYaxis()->SetRangeUser(minY, maxY);
  puts("\n\tdebug 22\n");
  
  for (int igra=0; igra<candidates.size(); igra++){
    string graName = candidates[igra];
    leg->AddEntry(graph_arr[igra], graName.c_str(), "lep");
    //cout<< candidates[igra].erase(candidates[igra].end()-4,candidates[igra].end());

    if (igra==maxY_key) continue;
    graph_arr[igra]->Draw("pesame");
  }
  
  leg->Draw("same");
  outname="outData/"+outname+".png";
  gPad->RedrawAxis();
  can.SaveAs(outname.c_str());

  //-> clean pointers:
  dataf->Close();
  delete dataf;
  for (TGraphErrors* igra_p: graph_arr) delete igra_p;
}

