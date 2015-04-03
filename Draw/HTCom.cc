// ===========================================================================
// 
//       Filename:  HTCom.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/25/2014 02:14:32 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iomanip>

#include <map>
#include <sstream>
#include "TLegend.h"

#include "TPaveStats.h"
#include <boost/foreach.hpp>
#include "tdrstyle.hh"
//#include "StopStyle.hh"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TLegend.h"
#include "StopStyle.hh"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "TKey.h"
#include "TROOT.h"
#include "TRint.h"
#include "TLine.h"
#include "TStyle.h"

const std::string PATH = "ak4PF";
//const std::string PATH = "ak5PFchsL1";
//const std::string OutType = "png";
const std::string OutType = "root";
std::vector<std::string> GetAllHis (std::string filename);
TGraphErrors* GetPFJetRes(TFile* file, int type, int range, std::string path);
TGraphErrors* GetPFJetResEta(TFile* file, int type, std::string path);
bool DrawJetPerformance(std::vector<std::string> fileIdx, std::map<std::string, TFile*> files, std::vector<std::string> pathnam);
void CMS_lumi_v2( TPad* pad, int iPeriod, int iPosX );

// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  
// =====================================================================================
int main ( int argc, char *argv[] )
{
  std::map<std::string, std::string> fileMap;

  //fileMap["Shashlik_140PU_aged"]="./Shaslik_0PU_aged_AK4.root";
  //fileMap["Shashlik_140PU_aged"]="./Shaslik_140PU_aged_AK4.root";
  //fileMap["Phase1"]="./Phase1_NoJEC.root";
  //fileMap["Phase2"]="./Phase2_NoJEC.root";
  //fileMap["SLHC22"]="./root/Shaslik_140PU_aged_AK4_SLHC22.root";
  //fileMap["SLHC23"]="./root/Shaslik_140PU_aged_AK4_SLHC23.root";
  //fileMap["SLHC23p1"]="./root/Shaslik_140PU_aged_AK4_SLHC23p1.root";
  //fileMap["Phase1_140PU"]="./SLHC23p1/Phase1_140PU_aged_AK4_SLHC23p1.root";
  //fileMap["Phase1_140PU"]="./root/Phase1_140PU_aged_AK4_SLHC23p1.root";
  //fileMap["SHCal_140PU"]="./CHS/Shaslik_140PU_aged_AK4_SLHC23_CHS.root";
  //fileMap["SHCal_140PU"]="./root/Shaslik_140PU_aged_AK4_SLHC23p1.root";
  //fileMap["SHCal_140PUnoOOT"]="./root/Shaslik_140PU_aged_AK4_SLHC23p1_noOOT.root";
  //fileMap["HGCal_140PU"]="./root/HGCal_140PU_aged_AK4_SLHC24.root";
  //fileMap["SHCal_200PU"]="./200PU/Shaslik_200PU_aged_AK4_SLHC23p1_NoMatch.root";
  //fileMap["SHCal_140PU"]="~/LPC/src/UserCode/PFAnalyzer/python/Shaslik_140PU_aged_AK4_SLHC23_CHS.root";
  //"./CHS/Shaslik_140PU_aged_AK4_SLHC23_CHS.root";
  //fileMap["SHCal_140PU"]="./CHS/Shaslik_140PU_aged_AK4_SLHC23_CHS.root";
  //fileMap["SHCal_140PU"]="./SLHC23p1/Shaslik_140PU_aged_AK4_SLHC23_CHS.root";

  //fileMap["HGCal_0PU"]="./Lindsey/HGcal_0PU_aged_AK4_SLHC24_1.root";
  //fileMap["HGCal_140PU"]="./Lindsey/HGCal_140PU_aged_AK4_SLHC24.root";
  //fileMap["HGCal_140PU"]="./Lindsey/HGCal_140PU_aged_AK4_SLHC24.root";
  //fileMap["Phase1_140PU"]="./Lindsey/Phase1_140PU_aged_AK4_SLHC23p1.root";
  //fileMap["SLHC23 140PU"]="./SLHC25/QCD_SLHC23p1_PU_SHcal_PF.root";
  //fileMap["SLHC25 140PU"]="./SLHC25/QCD_SLHC25_PU_SHcal_PF.root";

  fileMap["Phase1_140PU"]="./SLHC25p2/SLHC23p1_Phase1_140PU_PF.root";
  fileMap["SHCal_140PU"]="./SLHC25p2/SLHC23p1_SHCal_140PU_PF.root";
  //fileMap["SHCal2_140PU"]="./SLHC25p2/SLHC25_SHCal_140PU_PF.root";
  fileMap["HGCal_140PU"]="./SLHC25p2/SLHC25p2_HGCal_140PU_PF.root";

  fileMap["SHCal_0PU"]="./SLHC25p2/SLHC23p1_SHCal_0PU_PF.root";
  fileMap["HGCal_0PU"]="./SLHC25p2/SLHC25p2_HGCal_0PU_PF.root";

//SLHC25p2/SLHC23p1_SHCal_0PU_PF.root

//SLHC25p2/SLHC25_SHCal_0PU_PF.root
//
//SLHC25p2/SLHC25p2_HGCal_0PU_PF.root


  std::vector<std::string> fileIdx;
  //fileIdx.push_back("SLHC22");
  //fileIdx.push_back("SLHC23");
  //fileIdx.push_back("SLHC23p1");
  //fileIdx.push_back("Phase1_140PU");
  //fileIdx.push_back("HGCal_0PU");
  //fileIdx.pSLHC23 140PUush_back("HGCal_140PU");
  //fileIdx.push_back("SHCal_140PU");
  //fileIdx.push_back("SHCal_140PUnoOOT");
  //fileIdx.push_back("SLHC23 140PU");
  //fileIdx.push_back("SLHC25 140PU");
  fileIdx.push_back("Phase1_140PU");
  fileIdx.push_back("SHCal_140PU");
  //fileIdx.push_back("SHCal2_140PU");
  fileIdx.push_back("HGCal_140PU");
  fileIdx.push_back("SHCal_0PU");
  fileIdx.push_back("HGCal_0PU");

  std::vector<std::string> hisname; 
  //hisname= GetAllHis(fileMap["SLHC23 140PU"]);
  hisname= GetAllHis(fileMap["Phase1_140PU"]);
  //hisname= GetAllHis(fileMap["SHCal_SLHC23p1"]);
  //hisname= GetAllHis(fileMap["DES17_0PU"]);
  //hisname.push_back("Rechit_energy");
  //hisname.push_back("PFJet_PT");
  //hisname.push_back("PFJet_Eta");
  //hisname.push_back("PFJet_Phi");
  //hisname.push_back("GenJet_PT");
  //hisname.push_back("GenJet_Eta");
  //hisname.push_back("GenJet_Phi");
  //hisname.push_back("CaloJet_PT");
  //hisname.push_back("CaloJet_Eta");
  //hisname.push_back("CaloJet_Phi");
  //hisname.push_back("PFMET_PT");
  //hisname.push_back("PFMET_Phi");
  //hisname.push_back("PFMET_Px");
  //hisname.push_back("PFMET_Py");
  //hisname.push_back("PFJet20_Eta");
  //hisname.push_back("PFJet50_Eta");
  //hisname.push_back("PFJet100_Eta");
  //hisname.push_back("CHz");
  //hisname.push_back("PFJetEff_Eta");
  //hisname.push_back("PFJetEff_Pt");
  //hisname.push_back("GenMET_PT");
  //hisname.push_back("GenMET_Eta");
  //hisname.push_back("CaloMET_PT");
  //hisname.push_back("CaloMET_Eta");

  std::vector<std::string> pathname; 
  //pathname.push_back("ak4PF");
  pathname.push_back("ak4PFchs");
  //pathname.push_back("ak4Puppi");
  //
  ///
  //pathname.push_back("Default_PFchs");
  //pathname.push_back("CHS_dz1_pt5");
  //pathname.push_back("CHS_dz1_pt0");
  //pathname.push_back("CHS_dz1_pt1");
  //pathname.push_back("CHS_dz2_pt5");
  //pathname.push_back("CHS_dz2_pt0");
  //pathname.push_back("CHS_dz2_pt1");
  //pathname.push_back("CHS_dz3_pt5");
  //pathname.push_back("CHS_dz3_pt0");
  //pathname.push_back("CHS_dz3_pt1");



  std::map<std::string, TFile*> files;
  BOOST_FOREACH(std::string file, fileIdx)
  {
    std::cout << "file " << file << std::endl;
    files[file.c_str()] = new TFile(fileMap[file].c_str(), "R");
  }


  //gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //StopStyle();

  TCanvas c1("fsf", "fsdf", 800, 600);
  BOOST_FOREACH(std::string his, hisname)
  {
    
    std::cout << his << std::endl;
    int fcount = 1;
    std::map<std::string, TH1D*> Hits;
    TLegend leg(0.184238,0.6923848,0.4217119,0.9338677,NULL,"brNDC");
    leg.SetBorderSize(0);
    leg.SetFillStyle(0); //transparent hollow?
    leg.SetTextFont(62); 
    leg.SetTextSize(0.045);
    
    double Ymax = 0;
    BOOST_FOREACH(std::string file, fileIdx)
    {
      BOOST_FOREACH(std::string Path, pathname)
      {
        std::stringstream fs;
        fs << file <<"_" << Path;
        std::string filepath = fs.str();
        std::stringstream ss;
        ss << Path << "/"<<his;
        std::cout << ss.str() << std::endl;
        //files[file]->ls();
        //TH1D* temp = (TH1D*)files[file]->Get(ss.str().c_str());
        Hits[filepath] = (TH1D*)files[file]->Get(ss.str().c_str());
        assert(Hits[filepath] != NULL);
        //Hits[filepath]->Scale(1/Hits[filepath]->Integral());

        Hits[filepath]->Rebin(2);
        if (fcount == 1)
        {
          Hits[filepath]->Draw();
        }
        else
          Hits[filepath]->Draw("same");

        Ymax = Hits[filepath]->GetMaximum() > Ymax ? Hits[filepath]->GetMaximum() : Ymax;
        Hits[filepath]->SetMaximum(1.5*Ymax);

        TString xname = Hits[filepath]->GetTitle();
        Hits[filepath]->GetXaxis()->SetTitle(xname.ReplaceAll("_", " "));
        //Hits[filepath]->GetXaxis()->SetRangeUser(-100,100);
        //Hits[filepath]->GetYaxis()->SetTitle("Normalized to unit area");
        Hits[filepath]->GetYaxis()->SetTitleOffset(1.2);
        Hits[filepath]->GetYaxis()->SetTitleSize(0.045);
        Hits[filepath]->GetXaxis()->SetTitleSize(0.045);
        Hits[filepath]->SetTitle("");
        Hits[filepath]->SetLineWidth(3);
        //if (fcount == 3 ) 
        //Hits[filepath]->SetLineColor(fcount+1);
        //else
        Hits[filepath]->SetLineColor(fcount);
        Hits[filepath]->GetListOfFunctions();
        c1.Update();
        //TString legname = Path;
        ////TString legname = file;
        //legname = legname.ReplaceAll("_", " ");
        TString legname;
        if (pathname.size() == 1)
        {
          //leg.SetHeader(Path.c_str());
          legname = file;
        } else if (fileIdx.size() == 1)
        {
          leg.SetHeader(file.c_str());
          legname = Path;
        } else
          legname = file+"_"+Path;

        //std::stringstream legss;
        //legss << legname <<" (#bar{X} = " << std::setprecision(2) <<Hits[filepath]->GetMean() << " #sigma = "<< 
          //std::setprecision(2)<<  Hits[filepath]->GetRMS() <<")";
        //leg.AddEntry(Hits[filepath], legss.str().c_str(), "l");
        leg.AddEntry(Hits[filepath], legname.ReplaceAll("_", " "), "l");
        fcount++;
      }
    }

    leg.Draw();
    std::stringstream ss;
    ss <<"140PU_"<< his<<".png";
    //ss <<"E100_"<< his<<".png";
    //int jetcut = 0;
    //sscanf(his.c_str(), "PFJet%d_Eta", &jetcut);
    if (his.find("PUJetRate") != std::string::npos) c1.SetLogy(1);

    c1.SaveAs(ss.str().c_str());
    ss.str("");
    ss <<"140PU_"<< his<<".root";
    c1.SaveAs(ss.str().c_str());

    //c1.SetLogy(0);
  }

  c1.Clear();
  
  DrawJetPerformance(fileIdx, files, pathname);



  return EXIT_SUCCESS;
////----------------------------------------------------------------------------
////  CaloJet Resolution
////----------------------------------------------------------------------------
  //fcount = 1;
  //Hits.clear();
  //mg->Clear();
  //leg.Clear();
  //BOOST_FOREACH(std::string file, fileIdx)
  //{
    //Hits[file] = GetCaloJetRes(files[file], 2);
    //assert(Hits[file] != NULL);
    //if (fcount == 1)
    //{
      //Hits[file]->Draw("AC*");
    //}
    //else
      //Hits[file]->Draw("sameAC");
    //Hits[file]->SetLineWidth(3);
    //Hits[file]->SetLineColor(fcount);
    //mg->Add(Hits[file]);
    //leg.AddEntry(Hits[file], file.c_str(), "l");
    //fcount++;
  //}
  //mg->Draw("APL");
  //leg.Draw();

  //ss.str("");
  //if (type == 1)
    //ss <<"PU_CaloJet_Respondes.png";
  //else if (type == 2)
    //ss <<"PU_CaloJet_Resolution.png";
  ////ss <<"140PU_"<< his<<".png";
  ////ss <<"0PU_"<< his<<".png";
  ////c1.SetLogy();
  //c1.SaveAs(ss.str().c_str());
  //return EXIT_SUCCESS;
}				// ----------  end of function main  ----------

std::vector<std::string> GetAllHis (std::string filename)
{
  TFile m2File(filename.c_str(),"R");
  gDirectory->cd(PATH.c_str());
  TIter next (gDirectory->GetListOfKeys());
  std::map<std::string, int> variable;
  std::vector<std::string> varVec;
  TKey *key;
  //    std::string name;
  while ((key= (TKey*) next()))
  {

    //if (key->IsA() == TH1::Class())
    //{
      std::string stdname=key->GetName();
      variable.insert(std::pair<std::string, int>(stdname, 1));
    //}
  }
  for (std::map<std::string, int>::iterator it = variable.begin(); 
      it != variable.end(); ++it)
  {
    std::cout << "ff " << it->first << std::endl;
    varVec.push_back(it->first);
  }
  return varVec;
}		// -----  end of method MethodIICalc::GetAllHisFromM2Info  -----


// ===  FUNCTION  ============================================================
//         Name:  GetPFJetRes
//  Description:  
// ===========================================================================
TGraphErrors* GetPFJetRes(TFile* file, int type, int range, std::string path)
{
  std::vector<std::string> RecoHisName;
  //RecoHisName.push_back("PFJet_Gen0_50_Pt");
  //RecoHisName.push_back("PFJet_Gen50_80_Pt");
  //RecoHisName.push_back("PFJet_Gen80_120_Pt");
  //RecoHisName.push_back("PFJet_Gen120_200_Pt");
  //RecoHisName.push_back("PFJet_Gen200_500_Pt");
  //RecoHisName.push_back("PFJet_Gen500_1000_Pt");
  //
  if (range == 0)
  {
    RecoHisName.push_back("PFJetG_Gen10_20_Pt")   ;
    RecoHisName.push_back("PFJetG_Gen20_30_Pt")   ;
    RecoHisName.push_back("PFJetG_Gen30_40_Pt")   ;
    RecoHisName.push_back("PFJetG_Gen40_50_Pt")   ;
    RecoHisName.push_back("PFJetG_Gen50_60_Pt")   ;
    RecoHisName.push_back("PFJetG_Gen60_70_Pt")   ;
    RecoHisName.push_back("PFJetG_Gen70_80_Pt")   ;
    RecoHisName.push_back("PFJetG_Gen80_100_Pt")  ;
    RecoHisName.push_back("PFJetG_Gen100_120_Pt") ;
    RecoHisName.push_back("PFJetG_Gen120_150_Pt") ;
    RecoHisName.push_back("PFJetG_Gen150_200_Pt") ;
    RecoHisName.push_back("PFJetG_Gen200_500_Pt") ;
    RecoHisName.push_back("PFJetG_Gen500_1000_Pt");
  }
  if (range == 1)
  {
    RecoHisName.push_back("PFJetG1_Gen10_20_Pt")   ;
    RecoHisName.push_back("PFJetG1_Gen20_30_Pt")   ;
    RecoHisName.push_back("PFJetG1_Gen30_40_Pt")   ;
    RecoHisName.push_back("PFJetG1_Gen40_50_Pt")   ;
    RecoHisName.push_back("PFJetG1_Gen50_60_Pt")   ;
    RecoHisName.push_back("PFJetG1_Gen60_70_Pt")   ;
    RecoHisName.push_back("PFJetG1_Gen70_80_Pt")   ;
    RecoHisName.push_back("PFJetG1_Gen80_100_Pt")  ;
    RecoHisName.push_back("PFJetG1_Gen100_120_Pt") ;
    RecoHisName.push_back("PFJetG1_Gen120_150_Pt") ;
    RecoHisName.push_back("PFJetG1_Gen150_200_Pt") ;
    RecoHisName.push_back("PFJetG1_Gen200_500_Pt") ;
    RecoHisName.push_back("PFJetG1_Gen500_1000_Pt");
  }
  if (range == 2)
  {
    RecoHisName.push_back("PFJetG2_Gen10_20_Pt")   ;
    RecoHisName.push_back("PFJetG2_Gen20_30_Pt")   ;
    RecoHisName.push_back("PFJetG2_Gen30_40_Pt")   ;
    RecoHisName.push_back("PFJetG2_Gen40_50_Pt")   ;
    RecoHisName.push_back("PFJetG2_Gen50_60_Pt")   ;
    RecoHisName.push_back("PFJetG2_Gen60_70_Pt")   ;
    RecoHisName.push_back("PFJetG2_Gen70_80_Pt")   ;
    RecoHisName.push_back("PFJetG2_Gen80_100_Pt")  ;
    RecoHisName.push_back("PFJetG2_Gen100_120_Pt") ;
    RecoHisName.push_back("PFJetG2_Gen120_150_Pt") ;
    RecoHisName.push_back("PFJetG2_Gen150_200_Pt") ;
    RecoHisName.push_back("PFJetG2_Gen200_500_Pt") ;
    //RecoHisName.push_back("PFJetG2_Gen500_1000_Pt");
  }
  if (range == 3)
  {
    RecoHisName.push_back("PFJetG3_Gen10_20_Pt")   ;
    RecoHisName.push_back("PFJetG3_Gen20_30_Pt")   ;
    RecoHisName.push_back("PFJetG3_Gen30_40_Pt")   ;
    RecoHisName.push_back("PFJetG3_Gen40_50_Pt")   ;
    RecoHisName.push_back("PFJetG3_Gen50_60_Pt")   ;
    RecoHisName.push_back("PFJetG3_Gen60_70_Pt")   ;
    RecoHisName.push_back("PFJetG3_Gen70_80_Pt")   ;
    RecoHisName.push_back("PFJetG3_Gen80_100_Pt")  ;
    RecoHisName.push_back("PFJetG3_Gen100_120_Pt") ;
    RecoHisName.push_back("PFJetG3_Gen120_150_Pt") ;
    RecoHisName.push_back("PFJetG3_Gen150_200_Pt") ;
    RecoHisName.push_back("PFJetG3_Gen200_500_Pt") ;
    RecoHisName.push_back("PFJetG3_Gen500_1000_Pt");
  }
  if (range == 4)
  {
    RecoHisName.push_back("PFJetG4_Gen10_20_Pt")   ;
    RecoHisName.push_back("PFJetG4_Gen20_30_Pt")   ;
    RecoHisName.push_back("PFJetG4_Gen30_40_Pt")   ;
    RecoHisName.push_back("PFJetG4_Gen40_50_Pt")   ;
    RecoHisName.push_back("PFJetG4_Gen50_60_Pt")   ;
    RecoHisName.push_back("PFJetG4_Gen60_70_Pt")   ;
    RecoHisName.push_back("PFJetG4_Gen70_80_Pt")   ;
    RecoHisName.push_back("PFJetG4_Gen80_100_Pt")  ;
    RecoHisName.push_back("PFJetG4_Gen100_120_Pt") ;
    RecoHisName.push_back("PFJetG4_Gen120_150_Pt") ;
    RecoHisName.push_back("PFJetG4_Gen150_200_Pt") ;
    RecoHisName.push_back("PFJetG4_Gen200_500_Pt") ;
    RecoHisName.push_back("PFJetG4_Gen500_1000_Pt");
  }


  int npoints = RecoHisName.size();
  double x[npoints];
  double y[npoints];
  double ex[npoints];
  double ey[npoints];

  for (int k = 0; k < npoints; ++k)
  {
    x[k]=y[k]=ex[k]=ey[k]=0.0;
  }
  //


  TCanvas c1("fsf", "fsdf", 600, 800);
  //StopStyle();
  std::stringstream ss;
  int i =0;

  BOOST_FOREACH(std::string his, RecoHisName)
  {
    ss.str("");
    ss << path << "/"<<his;
    TH1F* th = (TH1F*)file->Get(ss.str().c_str());

    double mean = th->GetMean();
    double RMS = th->GetRMS();
    TF1* fit = new TF1("fdf", "gaus", mean-2*RMS, mean+2*RMS);
    th->Fit(fit);
    int xlow = 0;
    int xhigh = 0;
    sscanf(his.c_str(), "PFJetG_Gen%d_%d_Pt", &xlow, &xhigh);
    if (xlow == 0 && xhigh == 0)
    {
      int temp = -1;
      sscanf(his.c_str(), "PFJetG%d_Gen%d_%d_Pt", &temp, &xlow, &xhigh);
      assert(temp ==range);
    }

    x[i] = (xhigh+xlow)/2;
    ex[i] = (xhigh-xlow)/2;

    if (type == 1)
    {
      y[i] =fit->GetParameter(1);
      ey[i] = fit->GetParError(1);
    }
    if (type == 2)
    {
      y[i] =  fit->GetParameter(2) / fit->GetParameter(1);
      ey[i] = y[i] * sqrt( pow(fit->GetParError(2)/fit->GetParameter(2),2) + pow(fit->GetParError(1)/fit->GetParameter(1),2));
    }
    if (type == 3)
    {
      y[i] =  fit->GetParameter(2);
      ey[i] = fit->GetParError(2);
    }

    //if (type == 1)
      //JetRes[(xhigh+xlow)/2] = th->GetMean();
    //if (type == 2)
      //JetRes[(xhigh+xlow)/2] = th->GetRMS() / th->GetMean();

    th->Draw();


    ss.str(""); 
    ss << file->GetName()<<"_"<<path<<"_" <<his <<".png";
    c1.SaveAs(ss.str().c_str());
    i++;
  }


  for (int j = 0; j < npoints; ++j)
  {
    std::cout << " point " << j << " x " << x[j] << " y " << y[j] << " Ex " << ex[j] << " Ey " << ey[j] << std::endl;
    if (y[j] != y[j]) y[j] = 0;
    if (ey[j] != ey[j]) ey[j] = 0;
    if (ey[j]/ y[j] > 2)
    {
      y[j] = 0;
      ey[j] = 0;
    }
  }

  TGraphErrors* g1 = new TGraphErrors(npoints, x, y, ex, ey);
  g1->Draw("AC*");
  ss.str("");
  ss << file->GetName()<<"_"<<path <<".png";
  c1.SaveAs(ss.str().c_str());
  
  return g1;
}       // -----  end of function GetPFJetRes  -----

TGraphErrors* GetPFJetResEta(TFile* file, int type, std::string path)
{
  std::vector<std::string> RecoHisName;
  RecoHisName.push_back("PFJetG_Eta_M5_M4");
  RecoHisName.push_back("PFJetG_Eta_M4_M3");
  RecoHisName.push_back("PFJetG_Eta_M3_M2");
  RecoHisName.push_back("PFJetG_Eta_M2_M1");
  RecoHisName.push_back("PFJetG_Eta_M1_M0");
  RecoHisName.push_back("PFJetG_Eta_P5_P4");
  RecoHisName.push_back("PFJetG_Eta_P4_P3");
  RecoHisName.push_back("PFJetG_Eta_P3_P2");
  RecoHisName.push_back("PFJetG_Eta_P2_P1");
  RecoHisName.push_back("PFJetG_Eta_P1_P0");

  TCanvas c1("fsf", "fsdf", 600, 800);
  std::stringstream ss;
  int npoints = RecoHisName.size();
  double x[npoints];
  double y[npoints];
  double ex[npoints];
  double ey[npoints];

  for (int k = 0; k < npoints; ++k)
  {
    x[k]=y[k]=ex[k]=ey[k]=0.0;
  }

  int i=0;
  BOOST_FOREACH(std::string his, RecoHisName)
  {
    ss.str("");
    ss << path << "/"<<his;
    std::cout << ss.str() << std::endl;
    TH1F* th = (TH1F*)file->Get(ss.str().c_str());

    double mean = th->GetMean();
    double RMS = th->GetRMS();
    TF1* fit = new TF1("fdf", "gaus", mean-2*RMS, mean+2*RMS);
    th->Fit(fit);
    int xlow = 0;
    int xhigh = 0;
    sscanf(his.c_str(), "PFJetG_Eta_P%d_P%d_Pt", &xlow, &xhigh);
    if (xlow == 0 && xhigh == 0)
    {
      sscanf(his.c_str(), "PFJetG_Eta_M%d_M%d_Pt", &xlow, &xhigh);
      std::cout << " - " << xlow << " " << xhigh << std::endl;
      int temp = xlow;
      xlow = xhigh * -1;
      xhigh = temp * -1;
    }

    //if (type == 1)
      //JetRes[(xhigh+xlow)/2] = fit->GetParameter(1);
    //if (type == 2)
      //JetRes[(xhigh+xlow)/2] = fit->GetParameter(2) / fit->GetParameter(1);
    x[i] = (xhigh+xlow)/2;
    ex[i] = (xhigh-xlow)/2;
    if (type == 1)
    {
      y[i] =fit->GetParameter(1);
      ey[i] = fit->GetParError(1);
    }
    if (type == 2)
    {
      y[i] =  fit->GetParameter(2) / fit->GetParameter(1);
      ey[i] = y[i] * sqrt( pow(fit->GetParError(2)/fit->GetParameter(2),2) + pow(fit->GetParError(1)/fit->GetParameter(1),2));
    }
    if (type == 3)
    {
      y[i] =  fit->GetParameter(2);
      ey[i] = fit->GetParError(2);
    }

    th->Draw();

    ss.str("");
    ss << file->GetName()<<"_Eta"<< path <<"_" <<his <<".png";
    c1.SaveAs(ss.str().c_str());
    i++;
  }

  for (int j = 0; j < npoints; ++j)
  {
    std::cout << " point " << j << " x " << x[j] << " y " << y[j] << " Ex " << ex[j] << " Ey " << ey[j] << std::endl;
    if (y[j] != y[j]) y[j] = 0;
    if (ey[j] != ey[j]) ey[j] = 0;
  }

  TGraphErrors* g1 = new TGraphErrors(npoints, x, y, ex, ey);
  g1->Draw("AC*");
  ss.str("");
  ss << file->GetName() <<"_Eta"<< path <<".png";
  c1.SaveAs(ss.str().c_str());
  
  return g1;
} 


// ===  FUNCTION  ============================================================
//         Name:  DrawJetPerformance
//  Description:  
// ===========================================================================
bool DrawJetPerformance(std::vector<std::string> fileIdx, std::map<std::string, TFile*> files, std::vector<std::string> pathname)
{
  
  TCanvas c1("Jets", "Jets", 800, 600);
  setTDRStyle();
  CMS_lumi_v2(&c1, 14, 11);
//----------------------------------------------------------------------------
//  PFJet Resolution
//---------------------------------------------------------------------------- 
  for (int type = 1; type < 4; ++type)
  {
    for (int range = 0; range < 5; ++range)
    {
      int fcount = 1;
      std::map<std::string, TGraph*> Hits;
      TMultiGraph *mg = new TMultiGraph();
      TLegend leg(0.5665829,0.6463415,0.8027638,0.9407666,NULL,"brNDC");
      leg.SetBorderSize(0);
      leg.SetFillStyle(0); //transparent hollow?
      leg.SetTextFont(62); 
      leg.SetTextSize(0.045);
      TLine l(0,1, 800, 1);
      TLatex tex;
      tex.SetNDC();
      tex.SetTextSize(0.06);

      BOOST_FOREACH(std::string file, fileIdx)
      {
        BOOST_FOREACH(std::string path, pathname)
        {
          std::stringstream fs;
          fs << file <<"_" << path;
          std::cout << fs.str() << std::endl;
          std::string filepath = fs.str();
          Hits[filepath] = GetPFJetRes(files[file], type, range, path);
          assert(Hits[filepath] != NULL);
          //Hits[file]->SetLineWidth(3);
        //if (fcount == 3 ) 
        //{
        //Hits[filepath]->SetLineColor(fcount+1);
        //Hits[filepath]->SetMarkerColor(fcount+1);
        //}
        //else
          Hits[filepath]->SetLineStyle(1);
          if (fcount == 1)
          {
          Hits[filepath]->SetLineColor(fcount);
          Hits[filepath]->SetMarkerColor(fcount);
          Hits[filepath]->SetMarkerStyle(21);
          }

          if (fcount == 2)
          {
          Hits[filepath]->SetLineColor(fcount);
          Hits[filepath]->SetMarkerColor(fcount);
          Hits[filepath]->SetMarkerStyle(22);
          }

          if (fcount == 3)
          {
          Hits[filepath]->SetLineColor(4);
          Hits[filepath]->SetMarkerColor(4);
          Hits[filepath]->SetMarkerStyle(23);
          }

          if (fcount == 4)
          {
          Hits[filepath]->SetLineColor(2);
          Hits[filepath]->SetMarkerColor(2);
          Hits[filepath]->SetMarkerStyle(26);
          }

          if (fcount == 5)
          {
          Hits[filepath]->SetLineColor(4);
          Hits[filepath]->SetMarkerColor(4);
          Hits[filepath]->SetMarkerStyle(32);
          }
          //Hits[filepath]->SetLineColor(fcount);
          //Hits[filepath]->SetMarkerColor(fcount);
          //Hits[filepath]->SetMarkerStyle(20+fcount);
          Hits[filepath]->SetMarkerSize(2);
          mg->Add(Hits[filepath]);

          //TString legname = path;
          //TString legname = file;
          //std::cout << legname.ReplaceAll("_", " ") << std::endl;
          TString legname;
          if (pathname.size() == 1)
          {
            leg.SetHeader(path.c_str());
            legname = file;
          } else if (fileIdx.size() == 1)
          {
            leg.SetHeader(file.c_str());
            legname = path;
          } else
            legname = file+"_"+path;
          leg.AddEntry(Hits[filepath], legname.ReplaceAll("_", " "), "p");
          fcount++;
          if (type == 1)
          {
            Hits[filepath]->GetYaxis()->SetTitle("Response");
          }
          else if (type == 2)
            Hits[filepath]->GetYaxis()->SetTitle("Resolution");
          else if (type == 2)
            Hits[filepath]->GetYaxis()->SetTitle("Sigma");
        }
      }
      //if (type == 1)
        //l.Draw("same");
      //mg->GetYaxis()->SetRangeUser(0.5, 1.2);
      c1.cd();
      mg->Draw("AP"); 
      mg->GetXaxis()->SetTitle("p_{T}^{gen} [GeV]");
      if (type == 1)
      {
        mg->GetYaxis()->SetTitle("< p_{T}/p_{T}^{gen} >");
        mg->GetXaxis()->SetRangeUser(30, 1000);
        mg->GetXaxis()->SetMoreLogLabels();
        mg->GetYaxis()->SetRangeUser(0.8, 2.5);
      }
      if (type == 2)
      {
        mg->GetYaxis()->SetTitle("#sigma( p_{T}/p_{T}^{gen} )/< p_{T}/p_{T}^{gen} >");
        mg->GetXaxis()->SetRangeUser(30, 1000);
        mg->GetXaxis()->SetMoreLogLabels();
        mg->GetYaxis()->SetRangeUser(0, 0.7);
      }
      if (type == 3)
      {
        mg->GetYaxis()->SetTitle("#sigma( p_{T}/p_{T}^{gen} )");
        mg->GetXaxis()->SetRangeUser(30, 1000);
        mg->GetXaxis()->SetMoreLogLabels();
        mg->GetYaxis()->SetRangeUser(0, 0.7);
      }
      //mg->GetYaxis()->SetTitleOffset( 1.2);
      leg.Draw("same");
      if (range == 1)  tex.DrawLatex(0.20,0.85, "|#eta^{gen}| < 1.3");
      if (range == 2)  tex.DrawLatex(0.20,0.85, "1.5 <|#eta^{gen}| < 3.0");
      if (range == 3)  tex.DrawLatex(0.20,0.85, "3.0 <|#eta^{gen}| < 5.0");
      if (range == 4)  tex.DrawLatex(0.20,0.85, "1.7 <|#eta^{gen}| < 2.7");
      tex.SetTextColor(2);
      tex.DrawLatex(0.25,0.75, "NO JEC");


      std::stringstream ss;
      if (type == 1)
        ss <<"PU_PFJet_PT_Respondes_"<<range<<"." << OutType;
      else if (type == 2)
        ss <<"PU_PFJet_PT_Resolution_"<<range<<"." << OutType;
      else if (type == 3)
        ss <<"PU_PFJet_PT_Sigma_"<<range<<"." << OutType;
      //ss <<"PU_PFJet_Resolution.png";
      //ss <<"140PU_"<< his<<".png";
      //ss <<"0PU_"<< his<<".png";
      //c1.SetLogy();
      c1.SetLogx(1);
      c1.SaveAs(ss.str().c_str());
      //c1.Update();
      //c1.Clear();
      //c1.SetLogx(0);
      delete mg;
    }

    int fcount = 1;
    std::map<std::string, TGraphErrors*> Hits;
    TMultiGraph *mg2 = new TMultiGraph();
    TLegend leg(0.6708543,0.6503497,0.9070352,0.9458042,NULL,"brNDC");
    leg.SetBorderSize(0);
    leg.SetFillStyle(0); //transparent hollow?
    leg.SetTextFont(62); 
    leg.SetTextSize(0.045);
    TLine l(0,1, 800, 1);
    TLatex tex;
    tex.SetNDC();
    tex.SetTextSize(0.06);
    BOOST_FOREACH(std::string file, fileIdx)
    {
      BOOST_FOREACH(std::string path, pathname)
      {
        std::stringstream fs;
        fs << file <<"_" << path;
        std::string filepath = fs.str();
        Hits[filepath] = GetPFJetResEta(files[file], type, path);
        assert(Hits[filepath] != NULL);
        Hits[filepath]->SetLineWidth(3);

        //if (fcount == 3 ) 
        //{
        //Hits[filepath]->SetLineColor(fcount+1);
        //Hits[filepath]->SetMarkerColor(fcount+1);
        //}
        //else
        {

          Hits[filepath]->SetLineColor(fcount);
          Hits[filepath]->SetMarkerColor(fcount);
        }
        Hits[filepath]->SetMarkerStyle(20+fcount);
        Hits[filepath]->SetMarkerSize(1.5);
        mg2->Add(Hits[filepath]);
        //TString legname = path;
        TString legname;
        if (pathname.size() == 1)
        {
          leg.SetHeader(path.c_str());
          legname = file;
        } else if (fileIdx.size() == 1)
        {
          leg.SetHeader(file.c_str());
          legname = path;
        } else
          legname = file+"_"+path;
        //std::cout << legname.ReplaceAll("_", " ") << std::endl;
        leg.AddEntry(Hits[filepath], legname.ReplaceAll("_", " "), "p");
        fcount++;
      }
    }
    c1.cd();
    c1.Clear();
    c1.SetLogx(0);
    mg2->Draw("AP");
    tex.DrawLatex(0.20,0.85, "p_{T}^{gen} > 15GeV");
    mg2->GetXaxis()->SetTitle("#eta^{gen}");
    if (type == 1)
    {
      mg2->GetYaxis()->SetTitle("< p_{T}/p_{T}^{gen} >");
      mg2->GetYaxis()->SetRangeUser(1.5, 3);
    }
    if (type == 2)
    {
      mg2->GetYaxis()->SetTitle("#sigma( p_{T}/p_{T}^{gen} )/< p_{T}/p_{T}^{gen} >");
      mg2->GetYaxis()->SetRangeUser(0, 0.7);
    }
    if (type == 3)
    {
      mg2->GetYaxis()->SetTitle("#sigma( p_{T}/p_{T}^{gen} )");
      mg2->GetYaxis()->SetRangeUser(0, 0.5);
    }
    //mg2->GetYaxis()->SetTitleOffset( 1.2);
    leg.Draw("same");

    std::stringstream ss;
    if (type == 1)
      ss <<"PU_PFJet_Eta_Respondes." << OutType;
    else if (type == 2)
      ss <<"PU_PFJet_Eta_Resolution." << OutType;
    else if (type == 3)
      ss <<"PU_PFJet_Eta_Sigma." << OutType;
    c1.SaveAs(ss.str().c_str());
  }
  return true;
}       // -----  end of function DrawJetPerformance  -----


// ===  FUNCTION  ============================================================
//         Name:  CMS_lumi_v2
//  Description:  
// ===========================================================================
void CMS_lumi_v2( TPad* pad, int iPeriod, int iPosX )
{
  //
  // Global variables
  //
  TString cmsText     = "CMS Simulation";
  float cmsTextFont   = 61;  // default is helvetic-bold

  bool writeExtraText = true;
  TString extraText   = "Preliminary";
  float extraTextFont = 52;  // default is helvetica-italics

  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  float lumiTextSize     = 0.6;
  float lumiTextOffset   = 0.2;
  float cmsTextSize      = 0.75;
  float cmsTextOffset    = 0.1;  // only used in outOfFrame version

  float relPosX    = 0.045;
  float relPosY    = 0.035;
  float relExtraDY = 1.2;

  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;

  TString lumi_13TeV = "20.1 fb^{-1}";
  TString lumi_8TeV  = "19.7 fb^{-1}";
  TString lumi_7TeV  = "5.1 fb^{-1}";
  TString lumi_14TeV = "3000 fb^{-1}, PU = 140";

  bool drawLogo      = false;

  bool outOfFrame    = false;
  if( iPosX/10==0 ) 
  {
    outOfFrame = true;
  }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
  {
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
  }
  else if ( iPeriod==2 )
  {
    lumiText += lumi_8TeV;
    lumiText += " (8 TeV)";
  }
  else if( iPeriod==3 ) 
  {
    lumiText = lumi_8TeV; 
    lumiText += " (8 TeV)";
    lumiText += " + ";
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
  }
  else if ( iPeriod==4 )
  {
    lumiText += lumi_13TeV;
    lumiText += " (13 TeV)";
  }
  else if ( iPeriod==7 )
  { 
    if( outOfFrame ) lumiText += "#scale[0.85]{";
    lumiText += lumi_13TeV; 
    lumiText += " (13 TeV)";
    lumiText += " + ";
    lumiText += lumi_8TeV; 
    lumiText += " (8 TeV)";
    lumiText += " + ";
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
    if( outOfFrame) lumiText += "}";
  }
  else if ( iPeriod==12 )
  {
    lumiText += "8 TeV";
  }
  else if ( iPeriod==14 )
  {
    lumiText += "14 TeV";  
    //lumiText += lumi_14TeV;
  }


  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(lumiTextSize*t);    
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
  {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
  }

  pad->cd();

  float posX_;
  if( iPosX%10<=1 )
  {
    posX_ =   l + relPosX*(1-l-r);
  }
  else if( iPosX%10==2 )
  {
    posX_ =  l + 0.5*(1-l-r);
  }
  else if( iPosX%10==3 )
  {
    posX_ =  1-r - relPosX*(1-l-r);
  }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
  {
    if( drawLogo )
    {
      posX_ =   l + 0.045*(1-l-r)*W/H;
      posY_ = 1-t - 0.045*(1-t-b);
      float xl_0 = posX_;
      float yl_0 = posY_ - 0.15;
      float xl_1 = posX_ + 0.15*H/W;
      float yl_1 = posY_;
      /*TASImage* CMS_logo = new TASImage("CMS-BW-label.png");*/
      TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
      pad_logo->Draw();
      pad_logo->cd();
      /*CMS_logo->Draw("X");*/
      pad_logo->Modified();
      pad->cd();
    }
    else
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextSize(cmsTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, cmsText);
      if( writeExtraText ) 
      {
        latex.SetTextFont(extraTextFont);
        latex.SetTextAlign(align_);
        latex.SetTextSize(extraTextSize*t);
        latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
      }
    }
  }
  else if( writeExtraText )
  {
    if( iPosX==0) 
    {
      posX_ =   l +  relPosX*(1-l-r);
      posY_ =   1-t+lumiTextOffset*t;
    }
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, extraText);      
  }

  return ;
}       // -----  end of function CMS_lumi_v2  -----
