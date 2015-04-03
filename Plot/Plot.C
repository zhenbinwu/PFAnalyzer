// ===========================================================================
// 
//       Filename:  Draw.C
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/26/2015 15:02:42
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================

#include <cstdlib>
#include <iostream>  
#include <string>
#include <vector>
#include <map>

#include "TFile.h"

#include "TPlot.h"
#include "tdrstyle.C"

// ===  FUNCTION  ============================================================
//         Name:  main
//  Description:  
// ===========================================================================
//int main ( int argc, char *argv[] )
int main ()
{
  setTDRStyle();
  // Map : detector to file
  std::map<std::string, TFile*> detFile;
  // Map : algorithm to directory
  std::map<std::string, std::string> algDir;
  // Map : detector to Marker
  std::map<std::string, int> detMark;
  // Map : algorithm to color
  std::map<std::string, int> algColor;

  //int jobtype = 3;  // 1:MET 2:JET 3:Stop
  int jobtype = 1; // 1:MET 2:JET 3:Stop

  if (jobtype == 1) {
    /*detFile["SHCal 140PU"] = new TFile("Typ1MET/DYMM_SHCal_140PU_aged.root", "READ");*/
    /*detFile["SHCal 0PU"] = new TFile("Typ1MET/DYMM_SHCal_0PU_aged.root", "READ");*/
    /*detFile["Phase1 140PU"] = new TFile("Typ1MET/DYMM_Phase1_140PU_aged.root", "READ");*/
    /*detFile["Phase1 50PU"] = new TFile("Typ1MET/DYMM_Phase1_50PU_noaged.root", "READ");*/

    /*detFile["SHCal 140PU"] = new TFile("FullMET/SLHC23p1_SHCal_140PU_MET.root", "READ");*/
    ////detFile["HGCal 140PU"] = new TFile("FullMET/SLHC25_HGCal_140PU_MET.root", "READ");
    /*detFile["Phase1 140PU"] = new TFile("FullMET/SLHC23p1_Aged_140PU_MET.root", "READ");*/
    //detFile["Phase1 0PU"] = new TFile("FullMET/SLHC23p1_NoAged_0PU_MET.root", "READ");
    /*detFile["Phase1 50PU"] = new TFile("FullMET/SLHC23p1_NoAged_50PU_MET.root", "READ");*/

    detFile["SHCal 140PU"] = new TFile("../Draw/SLHC25p2/SLHC23p1_SHCal_140PU_PF.root", "READ");
    detFile["HGCal 140PU"] = new TFile("../Draw/SLHC25p2/SLHC25p2_HGCal_140PU_PF.root", "READ");
    detFile["Phase1 140PU"] = new TFile("../Draw/SLHC25p2/SLHC23p1_Phase1_140PU_PF.root", "READ");
    //
    /*detFile["Phase1 140PU"] = new TFile("Phase1_ZMM_140PU.root", "READ");*/
    /*detFile["QCD NewJEC"] = new TFile("QCD_JEC/QCD_new.root", "READ");*/
    /*detFile["QCD OldJEC"] = new TFile("QCD_JEC/QCD_old.root", "READ");*/
    /*detFile["Phase1 140PU"] = new TFile("Phase1_ZMM_140PU.root", "READ");*/

    // For PFAnalyzier
    algDir["ak4PF"] = "ak4PF";
    algDir["ak4PFCHS"] = "ak4PFchs";
    algDir["ak4Puppi"] = "ak4Puppi";


    algDir["PFRaw"] = "ak4PFRaw";
    algDir["PFJEC10"] = "ak4_10_PFJEC";
    algDir["PFJEC15"] = "ak4_15_PFJEC";
    algDir["PFJEC20"] = "ak4_20_PFJEC";
    algDir["PFJEC30"] = "ak4_30_PFJEC";
    //algDir["PFL1"] = "ak4PFJECL1";
    algDir["CHSRaw"] = "ak4PFCHSRaw";
    algDir["CHSJEC10"] = "ak4_10_PFCHSJEC";
    algDir["CHSJEC15"] = "ak4_15_PFCHSJEC";
    algDir["CHSJEC20"] = "ak4_20_PFCHSJEC";
    algDir["CHSJEC30"] = "ak4_30_PFCHSJEC";
    //algDir["CHSL1"] = "ak4PFCHSJECL1";
    algDir["PuppiRaw"] = "ak4PuppiRaw";

    /*algDir["PFJEC"] = "ak4PFJEC";*/
    /*algDir["CHSJEC"] = "ak4PFCHSJEC";*/
    detMark["SHCal 0PU"]  = 20;
    detMark["SHCal 140PU"]  = 21;
    detMark["Phase1 140PU"] = 22;
    detMark["Phase1 50PU"]  = 23;
    detMark["HGCal 140PU"]  = 25;
    //detMark["QCD NewJEC"]  = 20;
    //detMark["QCD OldJEC"]  = 24;
    detMark["SHCal 10GeV"]  = 20;
    detMark["SHCal 20GeV"]  = 21;

    algColor["PFRaw"] = 1;
    algColor["PFJEC10"] = 2;
    algColor["PFJEC15"] = 3;
    algColor["PFJEC20"] = 4;
    algColor["PFJEC30"] = 5;
    //algColor["PFL1"] = 4;
    algColor["CHSRaw"] = 6;
    algColor["CHSJEC10"] = 7;
    //algColor["CHSL1"] = 8;
    algColor["PuppiRaw"] = 9;
    //algColor["PFJEC"] = 2;
    //algColor["CHSJEC"] = 1;


    // For PFAnalyzier
    algColor["ak4PF"] = 1;
    algColor["ak4PFCHS"] = 1;
    algColor["ak4Puppi"] = 3;
  }
  if (jobtype == 3) {
    /*detFile["TTJet"] = new TFile("Stop/TTJets_PU20bx25_histoutput.root", "READ");*/
    /*detFile["T2tt425_325"] = new TFile("Stop/T2tt425-325_PU20bx25_histoutput.root", "READ");*/
    /*detFile["T2tt500_325"] = new TFile("Stop/T2tt500-325_PU20bx25_histoutput.root", "READ");*/
    /*detFile["T2tt650_325"] = new TFile("Stop/T2tt650-325_PU20bx25_histoutput.root", "READ");*/
    /*detFile["T2tt850_100"] = new TFile("Stop/T2tt850-100_PU20bx25_histoutput.root", "READ");*/
    /*detFile["T1tttt1500-100"] = new TFile("Stop/T1tttt1500-100_PU40bx25_histoutput.root", "READ");*/
    detFile["DYLL"] = new TFile("./TauEff.root", "READ");


    algDir["PatTau"]    = "All";
    algDir["DecayOld"]  = "OldDecay";
    algDir["DecayNew"]  = "NewDecay";
    algDir["Isolation"] = "Isolation";
    algDir["VsMuon"]    = "againstMuon";
    algDir["VsEle"]     = "againstEle";


    detMark["TTJet"] = 20;
    detMark["T2tt850_100"] = 21;
    detMark["T2tt425_325"] = 22;
    detMark["T2tt500_325"] = 23;
    detMark["T2tt650_325"] = 24;
    detMark["T1tttt1500-100"] = 25;

    algColor["PatTau"]    = 1;
    algColor["DecayOld"]  = 2;
    algColor["DecayNew"]  = 3;
    algColor["Isolation"] = 1;
    algColor["VsMuon"]    = 2;
    algColor["VsEle"]     = 4;
  }





  TPlot TP(detFile, algDir);
  TP.SetMarkColor(detMark, algColor);
  TP.AddOutputFormat("png");
  TP.AddOutputFormat("root");

  //for(std::map<std::string, TFile*>::const_iterator it=detFile.begin();
  //it!=detFile.end(); ++it)
  //{
  //if (it->first.find(" 0PU") == std::string::npos) {
  //continue;
  //}
  //[>TP.Add(it->first, "PFRaw");<]
  //[>TP.Add(it->first, "CHSRaw");<]
  //[>TP.Add(it->first, "PFJEC");<]
  //for(std::map<std::string, std::string>::const_iterator ij=algDir.begin();
  //ij!=algDir.end(); ++ij)
  //{
  //TP.Add(it->first, ij->first);
  //}
  //}

  if (jobtype == 1) {
    for(std::map<std::string, TFile*>::const_iterator it=detFile.begin();
        it!=detFile.end(); ++it)
    {
      TP.Add(it->first, "ak4PFCHS");
      /*TP.Add(it->first, "CHSRaw");*/
      /*//TP.Add(it->first, "CHSL1");*/
      /*//TP.Add(it->first, "CHSJEC");*/
      /*TP.Add(it->first, "PFRaw");*/
      /*TP.Add(it->first, "PFJEC10");*/
      /*[>TP.Add(it->first, "PFJEC15");<]*/
      /*[>TP.Add(it->first, "PFJEC20");<]*/
      /*[>TP.Add(it->first, "PFJEC30");<]*/
      /*[>TP.Add(it->first, "PFL1");<]*/
      /*TP.Add(it->first, "PuppiRaw");*/
    }
    /*TP.Add("SHCal 0PU", "PFRaw");*/
    /*// Add the list of plots*/
    /*TP.Add("SHCal 140PU", "PFRaw");*/
    //TP.Add("SHCal 140PU", "PFJEC");
    /*TP.Add("SHCal 140PU", "PFL1");*/
    /*TP.Add("Phase1 140PU", "PFRaw");*/
    /*TP.Add("Phase1 140PU", "PFJEC");*/
    /*TP.Add("Phase1 140PU", "PFL1");*/
    /*TP.Add("Phase1 50PU", "PFRaw");*/

    //TP.Add("Phase1 50PU", "PFJEC");
    //TP.Add("Phase1 50PU", "PFL1");
    /*TP.Add("Phase1 140PU", "PFRaw");*/
    //TP.Add("Phase1 140PU", "PFJEC");
    /*TP.Add("Phase1 50PU", "PFRaw");*/
    //TP.Add("SHCal2", "Ak4PFRaw");
    //TP.Add("SHCal 0PU", "CHSRaw");
    // Add the list of plots
    //TP.Add("SHCal 140PU", "CHSRaw");
    /*TP.Add("SHCal 140PU", "CHSJEC");*/
    /*TP.Add("SHCal 140PU", "PuppiRaw");*/
    //TP.Add("SHCal 140PU", "CHSL1");
    /*TP.Add("Phase1 140PU", "CHSRaw");*/
    /*TP.Add("Phase1 140PU", "CHSJEC");*/
    /*TP.Add("Phase1 140PU", "CHSL1");*/
    //TP.Add("Phase1 50PU", "CHSRaw");
    //
    //TP.AddHist1D("JetEtaPT30");
    /*TP.AddHist1D("h2D_ParrallelZpt_Response");*/
    /*TP.AddHist1D("h2D_Parrallel_Resolution");*/
    /*TP.AddHist1D("h2D_Perperndicular_Resolution");*/
    /*TP.AddEffHist("h2D_MET_Eff", "h2D_Parrallel_Resolution", "h2D_ParrallelZpt_Response");*/

    TP.AddHist1D("PUJetRate_BR_Pt_Deminator");
    TP.AddHist1D("PUJetRate_BR_Pt_Numerator");
    TP.AddHist1D("PUJetRate_EC_Pt_Deminator");
    TP.AddHist1D("PUJetRate_EC_Pt_Numerator");
    TP.AddHist1D("PUJetRate_FW_Pt_Deminator");
    TP.AddHist1D("PUJetRate_FW_Pt_Numerator");
    TP.AddEffHist("PUJetRate_BR_Pt_Eff", "PUJetRate_BR_Pt_Numerator", "PUJetRate_BR_Pt_Deminator");
    TP.AddEffHist("PUJetRate_EC_Pt_Eff", "PUJetRate_EC_Pt_Numerator", "PUJetRate_EC_Pt_Deminator");
    TP.AddEffHist("PUJetRate_FW_Pt_Eff", "PUJetRate_FW_Pt_Numerator", "PUJetRate_FW_Pt_Deminator");


    

    /*TP.AddEffHist("h2D_MET_Eff", "h2D_Parrallel_Resolution", "h2D_ParrallelZpt_Response");*/

    /*TP.AddHist1D("h2D_METx_SumET_Resolution");*/
    /*TP.AddHist1D("h2D_METy_SumET_Resolution");*/
    /*TP.AddHist1D("h2D_METx_BBHT_Resolution");*/
    /*TP.AddHist1D("h2D_METy_BBHT_Resolution");*/
    /*TP.AddHist1D("h2D_METx_ECHT_Resolution");*/
    /*TP.AddHist1D("h2D_METy_ECHT_Resolution");*/
    /*TP.AddHist1D("h2D_METx_FWHT_Resolution");*/
    /*TP.AddHist1D("h2D_METy_FWHT_Resolution");*/

    //TP.AddHist1D("JetPTPerf_Response");
    //TP.AddHist1D("JetPTPerf_Resolution");
    //TP.AddHist1D("JetPTPerf_BB_Response");
    //TP.AddHist1D("JetPTPerf_BB_Resolution");
    //TP.AddHist1D("JetPTPerf_EC_Response");
    //TP.AddHist1D("JetPTPerf_EC_Resolution");
    //TP.AddHist1D("JetPTPerf_FW_Response");
    //TP.AddHist1D("JetPTPerf_FW_Resolution");


  }


  if (jobtype == 3) {

    /*TP.Add("T2tt500_325", "PatTau");*/
    TP.Add("DYLL", "DecayOld");
    TP.Add("DYLL", "Isolation");
    TP.Add("DYLL", "VsMuon");
    TP.Add("DYLL", "VsEle");
    TP.AddEffHist("TauPT_Eff", "TauPT_Num", "TauPT_Dem");
    TP.AddEffHist("TauJetPT_Eff", "TauJetPT_Num", "TauJetPT_Dem");
    TP.AddEffHist("TauEta_Eff", "TauEta_Num", "TauEta_Dem");
    TP.AddEffHist("TauJetEta_Eff", "TauJetEta_Num", "TauJetEta_Dem");
    /*TP.Add("TTJet", "PatTau");*/
    /*TP.Add("TTJet", "DecayOld");*/
    /*TP.Add("TTJet", "Isolation");*/
    /*TP.Add("TTJet", "VsMuon");*/
    /*TP.Add("TTJet", "VsEle");*/
    /*for(std::map<std::string, std::string>::const_iterator ij=algDir.begin();*/
    /*ij!=algDir.end(); ++ij)*/
    /*{*/
    /*TP.Add("TTJet", ij->first);*/
    /*}*/
  }
  // Get all the needed plots
  /*TP.GetAllHist();*/
  TP.PlotAll1D();

  // Plot Performance

  return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
