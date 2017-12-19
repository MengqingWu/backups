#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TAxis.h"
#include "Riostream.h"
#include "TString.h"

#include <fstream>
#include <iostream>
#include <string>

/* Originally from Dimitra Tsionou
 * Modified by Mengqing <mengqing.wu@desy.de> @2017 Aug
 *
 * FUNC:  plot CV curves measured from DESY probe station
 *
 */


void IVmeas(  std::string SensorNum="",
	      std::string Meas_version="1",
	      std::string extraPattern="",
	      TString outdir = "outData",
	      bool printalot = false) {

  std::string dataDir  = ( SensorNum=="" ? "./test/" : "./inData/");
  if ( extraPattern!="") SensorNum=extraPattern+'_'+SensorNum;
  std::string datafile = ( SensorNum=="" ? "dma_0802_SID_IV" : "Sensor_"+SensorNum+"_IV_"+Meas_version);
  dataDir+=datafile;
  
  std::ifstream instream;
  //in.open(Form("dma_0802_SID_CV"));
  std::cout<< "I am working on: "<<dataDir+datafile<<std::endl;
  instream.open(dataDir.c_str(), std::ifstream::in);
  if (instream.fail()){
    perror("\t Exiting: input file not exist! ");
    return;
  }
  // ifstream in;
  //in.open(Form("dma_0802_SID_IV"));
  //  in.open(Form("../20July2015/ivdorA1"));
  //  in.open(Form("cvd1"));
  //  in.open(Form("test1"));
  double x,y,z,a;

  const int max_num_of_char_in_a_line = 100; 
  //Number of header files to skip
  int num_of_header_lines = 36;

  // SKIP ALL THE HEADER LINES
  for(int i = 0; i < num_of_header_lines; ++i)
    instream.ignore(max_num_of_char_in_a_line, '\n');

  double A_nofactor = 1.;
  double A_nA_factor = 1000000000.;
  
  std::vector<double> volt;  
  std::vector<double> temp;  
  std::vector<double> curr;  
  std::vector<double> guardcurr;  

  int nlines= 0;
  //  TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
  //  TNtuple *ntuple= new TNtuple("ntuple","datafrom asciifile","x:y:z");
  
  while(!instream.eof()) {
		    //while (1) {
    if (printalot) std::cout<<nlines<<std::endl;
    instream >> x>> y>> z >> a;
    if (!instream.good()) break;
    if (nlines >= 0) {
      printf("x=%8f, y=%8f, z=%8f, a=%8f\n",x,y,z,a);
    }
      volt.push_back(x);
      curr.push_back(z*A_nA_factor);
      guardcurr.push_back(a*A_nA_factor);


      //    h1->Fill(x);
      //    ntuple->Fill(x,y,z);
    
      nlines++;
  }

  printf(" found %d points\n",nlines);
  
  instream.close();


  if (printalot) std::cout<<"ok1"<<std::endl;
  // double volt_arr[nlines];
  double *volt_arr = new double[nlines];
  double *curr_arr = new double[nlines];
  double *guardcurr_arr = new double[nlines];

  double *volt_arrE = new double[nlines];
  double *curr_arrE = new double[nlines];
  double *guardcurr_arrE = new double[nlines];

  for ( int i=0; i<nlines; i++ ) {
    volt_arr[i] = volt.at(i);
    curr_arr[i] = curr.at(i);
    guardcurr_arr[i] = guardcurr.at(i);

    volt_arrE[i] = 0.;
    curr_arrE[i] = 0.;
    guardcurr_arrE[i] =0.;
    //    std::cout<<" v " << volt_arr[i]<< " cap "<<cap_arr[i]<< " 1/c2 "<<OneOverC2[i]<<std::endl;
  }


  TCanvas *c1=new TCanvas("N1");
  
  /* --- not used:
  TGraphErrors *alpha = new TGraphErrors(nlines, volt_arr, curr_arr, volt_arrE, curr_arrE);
  alpha->SetTitle("");
  alpha->GetXaxis()->SetTitle("V [V]");
  alpha->GetYaxis()->SetTitle("I [nA]");
  alpha->SetMarkerStyle(20);
  alpha->SetMarkerColor(kBlue);
  alpha->SetMarkerSize(1.2);
  alpha->SetFillColor(kBlue);
  alpha->SetLineColor(kBlue);
  alpha->SetFillStyle(3017);
  alpha->Draw("aepsame");
  
  c1->Print(outdir+"/"+datafile+"_i_vs_v.png");
  */
  
  TCanvas *c2=new TCanvas("N2");
  
  TGraphErrors *beta = new TGraphErrors(nlines, volt_arr, guardcurr_arr, volt_arrE, guardcurr_arrE);
  beta->SetTitle("");
  beta->GetXaxis()->SetTitle("V [V]");
  // beta->GetYaxis()->SetTitle("I_{guard} [nA]");
  beta->GetYaxis()->SetTitle("I [nA]");
  beta->SetMarkerStyle(20);
  beta->SetMarkerColor(kBlue);
  beta->SetMarkerSize(1.2);
  beta->SetFillColor(kBlue);
  beta->SetLineColor(kBlue);
  beta->SetFillStyle(3017);
  beta->Draw("aepsame");
  
  c2->Print(outdir+"/"+datafile+"_Iguard_vs_v.png");

  TFile *outf= new TFile(outdir+"/"+datafile+"_PlotsIV.root","RECREATE");

  beta -> Write( (datafile+"_Iguard_V").c_str() );
  //c1 -> Write( (datafile+"_I_V_can").c_str() );
  c2 -> Write( (datafile+"_Iguard_V_can").c_str() );
  outf -> Write();
  outf -> Close();

  delete c1;
  delete c2;
  delete outf;
}


void CVmeas(std::string SensorNum = "",
	    std::string Meas_version="1",
	    std::string extraPattern="",
	    TString outdir="outData",
	    bool printalot = false) {
  
  std::string dataDir  = ( SensorNum=="" ? "./test/" : "./inData/");
  if ( extraPattern!="") SensorNum=extraPattern+'_'+SensorNum;
  std::string datafile = ( SensorNum=="" ? "dma_0802_SID_CV" : "Sensor_"+SensorNum+"_CV_"+Meas_version);
  
  std::ifstream instream;
  //in.open(Form("dma_0802_SID_CV"));
  dataDir+=datafile;
  std::cout<< "I am working on: "<<dataDir<<std::endl;
  instream.open(dataDir.c_str(), std::ifstream::in);
  if (instream.fail()){
    perror("\t Exiting: input file not exist! ");
    return;
  }
  //  in.open(Form("../20July2015_2/cvdorA1"));
  //  in.open(Form("../20July2015/cvdorB1"));
  //  in.open(Form("cvd1"));
  //  in.open(Form("test1"));
  double x,y,z,a;
  
  const int max_num_of_char_in_a_line = 100; 
  //Lines to skip to get to columns with measurements
  int num_of_header_lines = 38;
  
  // SKIP ALL THE HEADER LINES
  for(int i = 0; i < num_of_header_lines; ++i) {
    instream.ignore(max_num_of_char_in_a_line, '\n');
  }
  
  double F_nofactor = 1.;
  double F_muF_factor = 1000000.;
  double F_nF_factor = 1000000000.;
  double F_pF_factor = 1000000000000.;
  
  std::vector<double> volt;  
  std::vector<double> temp;  
  std::vector<double> cap;  
  std::vector<double> conductance;  
  
  int nlines= 0;
  
  while(!instream.eof()) {
    //while (1) {
    if (printalot) std::cout << nlines << std::endl;
    instream >> x>> y>> z >> a;
    if (!instream.good()) break;
    if (nlines >= 0) {
      printf("x=%8f, y=%8f, z=%8f, a=%8f\n",x,y,z,a);
    }
    
    volt.push_back(x);
    cap.push_back(z*F_nofactor);
    conductance.push_back(a);
    
    
    nlines++;
  }
  
  printf(" found %d points\n",nlines);
  
  instream.close();
  
  
  if (printalot) std::cout << "ok1" << std::endl;
  double *volt_arr = new double[nlines];
  double *cap_arr = new double[nlines];
  double *conductance_arr = new double[nlines];
  double *OneOverC2 = new double[nlines];
  
  double *volt_arrE = new double[nlines];
  double *cap_arrE = new double[nlines];
  double *OneOverC2_E = new double[nlines];
  double *conductance_arrE = new double[nlines];

  for ( int i=0; i<nlines; i++ ) {
    volt_arr[i] = volt.at(i);
    cap_arr[i] = cap.at(i);
    OneOverC2[i] = 1./(cap.at(i)*cap.at(i));
    conductance_arr[i] = conductance.at(i);

    volt_arrE[i] = 0.;
    cap_arrE[i] = 0.;
    OneOverC2_E[i] = 0.;
    conductance_arrE[i] =0.;


    std::cout<<" v " << volt_arr[i]<< " cap "<<cap_arr[i]<< " 1/c2 "<<OneOverC2[i]<< std::endl;
    
  }


  TLegend *l = new TLegend(0.65,0.75,0.85,0.85); //0.25,0.60,0.35,0.45);
  // l->Paint(kWhite); 
  l->SetTextSize(0.04); 
  l->SetTextFont(42); 
  l->SetTextColor(1);
  l->SetBorderSize(0);  //no border for legend 
  l->SetFillColor(0); 


  TCanvas *c1=new TCanvas("N1");

  TGraphErrors *alpha = new TGraphErrors(nlines, volt_arr, cap_arr, volt_arrE, cap_arrE);
  alpha->SetTitle("");
  alpha->GetXaxis()->SetTitle("V [V]");
  alpha->GetYaxis()->SetTitle("C [nF]");
  alpha->SetMarkerStyle(20);
  alpha->SetMarkerColor(kBlue);
  alpha->SetMarkerSize(1.2);
  alpha->SetFillColor(kBlue);
  alpha->SetLineColor(kBlue);
  alpha->SetFillStyle(3017);
  alpha->Draw("aepsame");
  
  l->AddEntry(alpha,"Silc8","lep");  
  l->Draw();

  c1->Print(outdir+"/"+datafile+"_c_vs_v.png");
  
  
  TCanvas *c2=new TCanvas("N2");
  
  TGraphErrors *beta = new TGraphErrors(nlines, volt_arr, OneOverC2, volt_arrE, OneOverC2_E);
  beta->SetTitle("");
  beta->GetXaxis()->SetTitle("V [V]");
  beta->GetYaxis()->SetTitle("1/C^{2} [1/F^{2}]");
  beta->SetMarkerStyle(20);
  beta->SetMarkerColor(kBlue);
  beta->SetMarkerSize(1.2);
  beta->SetFillColor(kBlue);
  beta->SetLineColor(kBlue);
  beta->SetFillStyle(3017);
  beta->Draw("aepsame");
  
  c2->Print(outdir+"/"+datafile+"_1OverC2_vs_v.png");
  
  TCanvas *c3=new TCanvas("N3");
  /*
  // if you want to plot R instead of G use this
  for ( int i=0; i<nlines; i++ ) {
    conductance_arr[i] = 1./conductance_arr[i];
  }
  */
  TGraphErrors *gamma = new TGraphErrors(nlines, volt_arr, conductance_arr, volt_arrE, conductance_arrE);
  gamma->SetTitle("");
  gamma->GetXaxis()->SetTitle("V [V]");
  // gamma->GetYaxis()->SetTitle("G [S]");
  gamma->GetYaxis()->SetTitle("R [#Omega]");
  gamma->SetMarkerStyle(20);
  gamma->SetMarkerColor(kBlue);
  gamma->SetMarkerSize(1.2);
  gamma->SetFillColor(kBlue);
  gamma->SetLineColor(kBlue);
  gamma->SetFillStyle(3017);
  gamma->Draw("aepsame");
  
  c3->Print(outdir+"/"+datafile+"_G_vs_v.png");

  TFile *outf= new TFile(outdir+"/"+datafile+"_PlotsCV.root","RECREATE");

  alpha -> Write ( (datafile+"_C_V").c_str() );
  beta ->  Write ( (datafile+"_1OverC2_V").c_str() );
  gamma -> Write ( (datafile+"G_V_can").c_str() );
  c1 -> Write ( (datafile+"_C_V_can").c_str() );
  c2 -> Write ( (datafile+"_1OverC2_V_can").c_str() );
  c3 -> Write ( (datafile+"_G_V_can").c_str() );
  outf -> Write();
  outf -> Close();

  /* delete pointers due to duplicate names */
  delete c1;
  delete c2;
  delete c3;
  delete outf;

}


int main(int argc, char* argv[]){

  /* temperarily, concentrated on measurement version 1*/
  std::cout<<"[Main:Info] Start IV & CV plotting ... "
	   <<""
	   <<std::endl;

  bool printalot = false;
  std::string meas_version = "1";
  std::string extra_patn = "";
  
  if (argc<2) {
    throw std::range_error("\n[Usage]:\n\t ./cviv.exe [PATN=$pattern] [version] $sensor_num \n\t -- [PATN] extra pattern in name 'Sensor_[PATN_]$SensorNum_v$version' \n\t -- [version] is optional: v2, v3 or default is v1 \n[Example]:\n\t ./cviv.exe 31 32 34 46 (sensor numbers provided)\n\t ./cviv.exe v2 33 42 (v2 stands for the version of 'inData/Sensor_xx_xV_2')\n");
  }

  /* Check which arg starting to be sensor_num: */
  int iarg = 1;
  /* check the version from the first parameter */
  if ( argv[1][0]=='P' && argv[1][1]=='A' && argv[1][2]=='T' && argv[1][3]=='N'){
    extra_patn = argv[1];
    extra_patn.erase(0,5);
    iarg++;
    if (printalot) std::cout<< extra_patn<<"\n";
  }
    
  if ( argv[iarg][0]=='v' ){
    meas_version=argv[iarg];
    meas_version.erase(0,1);
    iarg++; // sensor number starting from second parameter then
    if (printalot)
      std::cout<< "[Main:Info] You are checking measure version == " << meas_version <<std::endl;
  }
  
  
  while(iarg<argc){  
    if (std::stoi(argv[iarg])<31 || std::stoi(argv[iarg])>59) {
      std::cout << "[Warning] non-sense input ==> " << argv[iarg] 
		<< "\n\t must in range of [31, 59]!" << std::endl;
      iarg++;
      continue;
    }
    std::cout << "check: " << iarg <<", "
	      << argv[iarg] << std::endl;  
    CVmeas(std::string(argv[iarg]), meas_version, extra_patn);
    IVmeas(std::string(argv[iarg]), meas_version, extra_patn);
    iarg++;
  } 
  
  std::cout<<" ===  Done :) === \n"
	   <<"[Next]: \n $ hadd outData/merg_CV.root outData/Sensor*CV*.root"
	   <<"\n $ hadd outData/merg_IV.root outData/Sensor*IV*.root"
	   <<std::endl;
  
  return 1;
}
