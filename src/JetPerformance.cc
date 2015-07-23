// ===========================================================================
// 
//       Filename:  JetPerformance.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/08/2015 04:22:07 PM
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


#include "UserCode/PFAnalyzer/interface/JetPerformance.h"

//
// constructors and destructor
//
JetPerformance::JetPerformance(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  GetInputTag(iConfig);
  BookHistogram();
}

JetPerformance::~JetPerformance()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
  void
JetPerformance::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif

  GetHandleByLabel(iEvent);
  CleanPerEvent();
  
  GetCorrectedJets();
  JetMatching();
  JetPTMassPerf();
  PlotJets();

}



// ------------ method called once each job just before starting event loop  ------------
  void 
JetPerformance::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
  void 
JetPerformance::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
  void 
JetPerformance::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
  void 
JetPerformance::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
  void 
JetPerformance::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
  void 
JetPerformance::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
  void
JetPerformance::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::GetHandleByLabel
//  Description:  
// ===========================================================================
bool JetPerformance::GetHandleByLabel(const edm::Event& iEvent)
{
  iEvent.getByLabel(GenJetInputTag_, GenJetHdl); 
  iEvent.getByLabel(PFJetInputTag_, PFJetHdl); 
  iEvent.getByLabel(srcRhoInputTag_, srcRhoHdl); 
  iEvent.getByLabel(PileupInputTag_, PileupHdl); 
  return true;
}       // -----  end of function JetPerformance::GetHandleByLabel  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::GetInputTag
//  Description:  
// ===========================================================================
bool JetPerformance::GetInputTag(const edm::ParameterSet& iConfig)
{
  GenJetInputTag_ = iConfig.getParameter<edm::InputTag>("GenJetInputTag");
  PFJetInputTag_ = iConfig.getParameter<edm::InputTag>("PFJetInputTag");
  srcRhoInputTag_ = iConfig.getParameter<edm::InputTag>("srcRhoTag");
  PileupInputTag_ =  iConfig.getParameter<edm::InputTag>("PileUpInfoTag");

  L1JECTag_ = iConfig.getParameter<std::string>("L1JECTag");
  L2JECTag_ = iConfig.getParameter<std::string>("L2JECTag");
  L3JECTag_ = iConfig.getParameter<std::string>("L3JECTag");

  return true;
}       // -----  end of function JetPerformance::GetInputTag  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::JetMatching
//  Description:  
// ===========================================================================
bool JetPerformance::JetMatching()
{
  PFGenJet_deltaR.clear();

  for(unsigned int i=0; i < GenJetHdl->size(); ++i)
  {
    reco::GenJet gjet = GenJetHdl->at(i);
    for(unsigned int j=0; j < CorredJets.size(); ++j)
    {
      reco::PFJet pjet = CorredJets.at(j);
      double delR = deltaR(pjet, gjet);
      if ( delR <= 0.2)
      {
        PFGenJet_deltaR[i].push_front(std::make_pair(delR, j));
      }
    }
  }

  PFGenJet.clear();
  //Get the index ;of the cloest jet to the GenJet
  for(std::map<unsigned int, std::list<std::pair<double, unsigned int> > >::iterator it=PFGenJet_deltaR.begin();
    it!=PFGenJet_deltaR.end(); it++)
  {
    reco::GenJet gjet = GenJetHdl->at(it->first);
    it->second.sort();
    reco::PFJet jet = CorredJets.at(it->second.front().second);
    PFGenJet[it->first] = it->second.front().second;
  }

  return true;
}       // -----  end of function JetPerformance::JetMatching  -----


// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::GetCorrectedJets
//  Description:  /* cursor */
// ===========================================================================
std::vector<reco::PFJet> JetPerformance::GetCorrectedJets()
{
  CorredJets.clear();

  double rho = 0.0;
  if (srcRhoHdl.isValid())
  {
    rho = *srcRhoHdl.product();
  }
  //  Load the JetCorrectorParameter objects into a vector, IMPORTANT: THE ORDER MATTERS HERE !!!! 
  std::vector<JetCorrectorParameters> vPar;
  char* CMSPath = getenv("CMSSW_BASE");
  if (L1JECTag_ != "")
  {
    std::stringstream ss;
    ss << CMSPath <<"/src/UserCode/PFAnalyzer/data/"<< L1JECTag_;
    JetCorrectorParameters L1JetPar(ss.str());

    //std::cout << " L1 " << ss.str() << std::endl;
    vPar.push_back(L1JetPar);
  }
  if (L2JECTag_ != "")
  {
    assert(L1JECTag_ != "");
    std::stringstream ss;
    ss << CMSPath <<"/src/UserCode/PFAnalyzer/data/"<< L2JECTag_;
    JetCorrectorParameters L2JetPar(ss.str());
    vPar.push_back(L2JetPar);
  }
  if (L3JECTag_ != "")
  {
    assert(L1JECTag_ != "");
    assert(L2JECTag_ != "");
    std::stringstream ss;
    ss << CMSPath <<"/src/UserCode/PFAnalyzer/data/"<< L3JECTag_;
    JetCorrectorParameters L3JetPar(ss.str());
    vPar.push_back(L3JetPar);
  }

  FactorizedJetCorrector *JetCorrector = new FactorizedJetCorrector(vPar);

  for(reco::PFJetCollection::const_iterator it=PFJetHdl->begin();
      it!=PFJetHdl->end(); it++)
  {

    reco::PFJet  correctedJet = *it;
    double jec  = 1.0;
    if (vPar.size() != 0)
    {
      jec = GetCorrFactor(JetCorrector, correctedJet, rho);
    }
    correctedJet.scaleEnergy(jec);

    CorredJets.push_back(correctedJet);
  }

  return CorredJets;
}       // -----  end of function JetPerformance::GetCorrectedJets  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::CleanPerEvent
//  Description:  
// ===========================================================================
bool JetPerformance::CleanPerEvent()
{
  
  CorredJets.clear();
  PFGenJet_deltaR.clear();

  return true;
}       // -----  end of function JetPerformance::CleanPerEvent  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::BookHistogram
//  Description:  
// ===========================================================================
bool JetPerformance::BookHistogram()
{
  const int NPtBins = 18;
  const double vpt[NPtBins+1] = {20, 25, 30,35,40,45,57,72,90,120,150,200,300,400,550,750,1000,1500,2000};

  // Jet response and resolution
  JetPTPerf = fs->make<TH2D>("JetPTPerf" , "2D for Jet PT Performance", NPtBins, vpt, 300, -3, 3);
  JetPTPerf_BB = fs->make<TH2D>("JetPTPerf_BB" , "2D for Jet PT Performance", NPtBins, vpt, 300, -3, 3);
  JetPTPerf_EC = fs->make<TH2D>("JetPTPerf_EC" , "2D for Jet PT Performance", NPtBins, vpt, 300, -3, 3);
  JetPTPerf_FW = fs->make<TH2D>("JetPTPerf_FW" , "2D for Jet PT Performance", NPtBins, vpt, 300, -3, 3);
  JetPTPerf_NPU_LowBB = fs->make<TH2D>("JetPTPerf_NPU_LowBB" , "2D for Jet PT Performance vs NPU", 50, 0, 250, 300, -3, 3);
  JetPTPerf_NPU_LowEC = fs->make<TH2D>("JetPTPerf_NPU_LowEC" , "2D for Jet PT Performance vs NPU", 50, 0, 250, 300, -3, 3);
  JetPTPerf_NPU_LowFW = fs->make<TH2D>("JetPTPerf_NPU_LowFW" , "2D for Jet PT Performance vs NPU", 50, 0, 250, 300, -3, 3);

  JetMassPerf = fs->make<TH2D>("JetMassPerf" , "2D for Jet Mass Performance", 60, 0, 60, 300, -3, 3);

  JetEtaPT30 = fs->make<TH1D>("JetEtaPT30" , "JetEtaPT30", 120, -6, 6);
  // Jet Efficiency and PU Rate
  PFJetEff_Pt_Numerator  = fs->make<TH1D>("PFJetEff_Pt_Numerator ", "PFJet Pt (1.5 < GenJetEta < 3.0);Number of GenJet;GenJet PT", 100, 0, 500);
  PFJetEff_Pt_Deminator  = fs->make<TH1D>("PFJetEff_Pt_Deminator ", "PFJet Pt (1.5 < GenJetEta < 3.0);Number of GenJet;GenJet PT", 100, 0, 500);

  PFJetEff_PtBB_Numerator  = fs->make<TH1D>("PFJetEff_PtBB_Numerator ", "PFJet Pt Barrel;Number of GenJe;GenJet PT ( 0 < GenJet Eta < 1.5)", 100, 0, 500);
  PFJetEff_PtBB_Deminator  = fs->make<TH1D>("PFJetEff_PtBB_Deminator ", "PFJet Pt Barrel;Number of GenJe;GenJet PT ( 0 < GenJet Eta < 1.5)", 100, 0, 500);

  PFJetEff_PtEC_Numerator  = fs->make<TH1D>("PFJetEff_PtEC_Numerator ", "PFJet Pt Endcap;Number of GenJe;GenJet PT ( 1.5 < GenJet Eta < 3)", 100, 0, 500);
  PFJetEff_PtEC_Deminator  = fs->make<TH1D>("PFJetEff_PtEC_Deminator ", "PFJet Pt Endcap;Number of GenJe;GenJet PT ( 1.5 < GenJet Eta < 3)", 100, 0, 500);

  PFJetEff_PtFW_Numerator  = fs->make<TH1D>("PFJetEff_PtFW_Numerator ", "PFJet Pt Forward;Number of GenJet;GenJet PT ( 3 < GenJet Eta < 5)", 100, 0, 500);
  PFJetEff_PtFW_Deminator  = fs->make<TH1D>("PFJetEff_PtFW_Deminator ", "PFJet Pt Forward;Number of GenJe;GenJet PT ( 3 < GenJet Eta < 5)", 100, 0, 500);

  PFJetEff_Eta_Numerator = fs->make<TH1D>("PFJetEff_Eta_Numerator", "PFJet Eta ;Number of GenJet;GenJet Eta (GenJetPt > 15)",  100, -5, 5);
  PFJetEff_Eta_Deminator = fs->make<TH1D>("PFJetEff_Eta_Deminator", "PFJet Eta;Number of GenJet;GenJet Eta (GenJetPt > 15)", 100, -5, 5);

  // Jet PU Rate
  PFJetRate_Pt_Numerator  = fs->make<TH1D>("PFJetRate_Pt_Numerator ", "PFJet Pt (1.5 < GenJetEta < 3.0);Number of GenJet;GenJet PT", 100, 0, 500);
  PFJetRate_Pt_Deminator  = fs->make<TH1D>("PFJetRate_Pt_Deminator ", "PFJet Pt (1.5 < GenJetEta < 3.0);Number of GenJet;GenJet PT", 100, 0, 500);

  PFJetRate_PtBB_Numerator  = fs->make<TH1D>("PFJetRate_PtBB_Numerator ", "PFJet Pt Barrel;Number of GenJet;GenJet PT ( 0 < GenJet Eta < 1.5)", 100, 0, 500);
  PFJetRate_PtBB_Deminator  = fs->make<TH1D>("PFJetRate_PtBB_Deminator ", "PFJet Pt Barrel;Number of GenJe;GenJet PT ( 0 < GenJet Eta < 1.5)", 100, 0, 500);

  PFJetRate_PtEC_Numerator  = fs->make<TH1D>("PFJetRate_PtEC_Numerator ", "PFJet Pt Endcap;Number of GenJet;GenJet PT ( 1.5 < GenJet Eta < 3)", 100, 0, 500);
  PFJetRate_PtEC_Deminator  = fs->make<TH1D>("PFJetRate_PtEC_Deminator ", "PFJet Pt Endcap;Number of GenJet;GenJet PT ( 1.5 < GenJet Eta < 3)", 100, 0, 500);

  PFJetRate_PtFW_Numerator  = fs->make<TH1D>("PFJetRate_PtFW_Numerator ", "PFJet Pt Forward;Number of GenJet;GenJet PT ( 3 < GenJet Eta < 5)", 100, 0, 500);
  PFJetRate_PtFW_Deminator  = fs->make<TH1D>("PFJetRate_PtFW_Deminator ", "PFJet Pt Forward;Number of GenJet;GenJet PT ( 3 < GenJet Eta < 5)", 100, 0, 500);

  PFJetRate_Eta_Numerator = fs->make<TH1D>("PFJetRate_Eta_Numerator", "PFJet Eta;Number of GenJet;GenJet Eta (GenJetPt > 15)",  100, -5, 5);
  PFJetRate_Eta_Deminator = fs->make<TH1D>("PFJetRate_Eta_Deminator", "PFJet Eta;Number of GenJet;GenJet Eta (GenJetPt > 15)", 100, -5, 5);

  return true;
}       // -----  end of function JetPerformance::BookHistogram  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::JetPTMassPerf
//  Description:  
// ===========================================================================
bool JetPerformance::JetPTMassPerf()
{

  int NPU = -99;
  for(unsigned int i=0; i < PileupHdl->size(); ++i)
  {
    if (PileupHdl->at(i).getBunchCrossing() == 0)
    {
      NPU = PileupHdl->at(i).getPU_NumInteractions();
      break;
    }  
  }

  assert(NPU != -99);

  JetEffRate();

  for(std::map<unsigned int, unsigned int>::const_iterator it=PFGenJet.begin();
    it!=PFGenJet.end(); ++it)
  {
    reco::GenJet gjet = GenJetHdl->at(it->first);
    reco::PFJet pjet = CorredJets.at(it->second);
    double ptratio = pjet.pt() / gjet.pt();
    double massratio = pjet.mass() / gjet.mass();
    JetPTPerf->Fill(gjet.pt(), ptratio );
    JetMassPerf->Fill(gjet.mass(), massratio );
    PFJetEff_Pt_Numerator->Fill(gjet.pt());
    PFJetEff_Eta_Numerator->Fill(gjet.eta());

    if (fabs(gjet.eta()) <= 1.3)
    {
      PFJetEff_PtBB_Numerator->Fill(gjet.pt());
      JetPTPerf_BB->Fill(gjet.pt(), ptratio);
      if (gjet.pt() > 30 && gjet.pt() < 150)
        JetPTPerf_NPU_LowBB->Fill(NPU, ptratio);
    }

    if (fabs(gjet.eta()) > 1.3 && fabs(gjet.eta()) <= 3.0)
    {
      PFJetEff_PtEC_Numerator->Fill(gjet.pt());
      JetPTPerf_EC->Fill(gjet.pt(), ptratio);
      if (gjet.pt() > 30 && gjet.pt() < 150)
        JetPTPerf_NPU_LowEC->Fill(NPU, ptratio);
    }

    if (fabs(gjet.eta()) > 3)
    {
      PFJetEff_PtFW_Numerator->Fill(gjet.pt());
      JetPTPerf_FW->Fill(gjet.pt(), ptratio);
      if (gjet.pt() > 30 && gjet.pt() < 150)
        JetPTPerf_NPU_LowFW->Fill(NPU, ptratio);
    }
  }

  
  return true;
}       // -----  end of function JetPerformance::JetPTMassPerf  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::GetCorrFactor
//  Description:  
// ===========================================================================
double JetPerformance::GetCorrFactor( FactorizedJetCorrector *JetCorrector, reco::PFJet &jet, double rho)
{
  JetCorrector->setJetEta(jet.eta());
  JetCorrector->setJetPt(jet.pt());
  JetCorrector->setJetA(jet.jetArea());
  JetCorrector->setRho(rho);
  return JetCorrector->getCorrection();
}       // -----  end of function JetPerformance::GetCorrFactor  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::JetEffRate
//  Description:  
// ===========================================================================
bool JetPerformance::JetEffRate()
{
  
  for(unsigned int i=0; i < GenJetHdl->size(); ++i)
  {
    reco::GenJet gjet = GenJetHdl->at(i);
    PFJetEff_Pt_Deminator->Fill(gjet.pt());
    PFJetEff_Eta_Deminator->Fill(gjet.eta());
    if (fabs(gjet.eta()) <= 1.3)     PFJetEff_PtBB_Deminator->Fill(gjet.pt());
    if (fabs(gjet.eta()) > 1.3 && fabs(gjet.eta()) <= 3.0)     
      PFJetEff_PtEC_Deminator->Fill(gjet.pt());
    if (fabs(gjet.eta()) > 3) PFJetEff_PtFW_Deminator->Fill(gjet.pt());

  }

  return true;
}       // -----  end of function JetPerformance::JetEffRate  -----

// ===  FUNCTION  ============================================================
//         Name:  JetPerformance::PlotJets
//  Description:  
// ===========================================================================
bool JetPerformance::PlotJets()
{

  for(unsigned int i=0; i < CorredJets.size(); ++i)
  {
    reco::PFJet jet = CorredJets.at(i);
    if (jet.pt() > 30)
    {
      JetEtaPT30->Fill(jet.eta());
    }
  }
  return true;
}       // -----  end of function JetPerformance::PlotJets  -----
