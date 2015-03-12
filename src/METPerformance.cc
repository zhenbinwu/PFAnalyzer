// ===========================================================================
// 
//       Filename:  METPerformance.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/08/2015 04:25:25 PM
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


#include "UserCode/PFAnalyzer/interface/METPerformance.h"


//
// constructors and destructor
//
METPerformance::METPerformance(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  GetInputTag(iConfig);
  BookHistogram();

}

METPerformance::~METPerformance()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
  void
METPerformance::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  GetHandleByLabel(iEvent);


#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif

  if (! IsDiMuon ()) return;

  GetRecoZ();

  RecoEvent();
  FillMETPerf();
}


// ------------ method called once each job just before starting event loop  ------------
  void 
METPerformance::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
  void 
METPerformance::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
  void 
METPerformance::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
  void 
METPerformance::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
  void 
METPerformance::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
  void 
METPerformance::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
  void
METPerformance::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::IsDiMuon
//  Description:  
// ===========================================================================
bool METPerformance::IsDiMuon() const
{
  //std::cout << " size? " << MuonHdl->size() << std::endl;
  return MuonHdl->size() == 2;
}       // -----  end of function METPerformance::IsDiMuon  -----
// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetRecoZ
//  Description:  
// ===========================================================================
TLorentzVector METPerformance::GetRecoZ()
{
  RecoZ.SetXYZT(0.0, 0.0, 0.0, 0.0);
  for(unsigned int i=0; i < MuonHdl->size(); ++i)
  {
    reco::Muon muon = MuonHdl->at(i);
    TLorentzVector tempmuon(muon.px(), muon.py(), muon.pz(), muon.energy() );
    RecoZ += tempmuon;
  }

  return RecoZ;
}       // -----  end of function METPerformance::GetRecoZ  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::PassZCut
//  Description:  
// ===========================================================================
bool METPerformance::PassZCut() const
{
  if (RecoZ.M() < 80 || RecoZ.M() > 200) return false;
  return true;
}       // -----  end of function METPerformance::PassZCut  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::BookHistogram
//  Description:  
// ===========================================================================
bool METPerformance::BookHistogram()
{
  
  hZMass  = fs->make<TH1D>("ZMass", "ZMass;Z mass;Number of Event", 200, 0, 200);
  hZPT  = fs->make<TH1D>("ZPT", "ZPT;Z PT;Number of Event", 150, 0, 150);
  hZEta  = fs->make<TH1D>("ZEta", "ZEta;Z Eta;Number of Event", 40, -5, 5);
  hZPhi  = fs->make<TH1D>("ZPhi", "ZPhi;Z Phi;Number of Event", 28, -7, 7);

  hMETPT  = fs->make<TH1D>("METPT",  "MET PT; MET PT; Number of Event", 100, 0 , 500);
  hMETPhi  = fs->make<TH1D>("METPhi",  "MET Phi; MET Phi; Number of Event", 28, 0, 7);
  hMETx  = fs->make<TH1D>("METx",  "MET x; MET x; Number of Event", 100, -200, 200);
  hMETy  = fs->make<TH1D>("METy",  "MET y; MET y; Number of Event", 100, -200, 200);
  hSumET  = fs->make<TH1D>("SumET",  "MET PT; SumET; Number of Event", 500, 0, 10000);
  hlogSumET  = fs->make<TH1D>("logSumET",  "MET PT; logSumET; Number of Event", 200, 0, log10(10000));
  hMETSig  = fs->make<TH1D>("METSig",  "MET PT; MET PT; Number of Event", 50, 0, 1);

  hRecoilPT = fs->make<TH1D>("RecoilPT",  "Recoil PT; MET PT; Number of Event", 200, 0 , 200);
  hParrallel = fs->make<TH1D>("Parrallel ",  "Recoil PT; MET PT; Number of Event", 80, -200 , 200);
  hParrallelZPT = fs->make<TH1D>("ParrallelZPT ",  "Recoil PT; MET PT; Number of Event", 80, -200 , 200);
  hPerpendicular = fs->make<TH1D>("Perpendicular ",  "Recoil PT; MET PT; Number of Event", 80, -200, 200);

  h2D_Parrallel = fs->make<TH2D>("h2D_Parrallel",  "Recoil PT; MET PT; Number of Event", 150, 0, 150, 100, -200, 200);
  h2D_ParrallelZpt = fs->make<TH2D>("h2D_ParrallelZpt",  "Recoil PT; MET PT; Number of Event", 150, 0, 150, 100, -20, 20);
  h2D_Perperndicular= fs->make<TH2D>("h2D_Perperndicular",  "Recoil PT; MET PT; Number of Event", 150, 0, 150, 100, -200, 200);

  h2D_METx_SumET= fs->make<TH2D>("h2D_METx_SumET",  "h2D_METx_SumET PT; MET PT; Number of Event", 500, 0, 10000, 100, -200, 200);
  h2D_METy_SumET= fs->make<TH2D>("h2D_METy_SumET",  "h2D_METy_SumET PT; MET PT; Number of Event", 500, 0, 10000, 100, -200, 200);

  return true;
}       // -----  end of function METPerformance::BookHistogram  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::RecoEvent
//  Description:  
// ===========================================================================
bool METPerformance::RecoEvent()
{
  // Clear up event default 
  GetCorrectedJets();
  RecoZ.SetXYZT(0.0, 0.0, 0.0, 0.0);
  MET.SetMagPhi(0.0, 0.0);
  Recoil.SetXYZT(0.0, 0.0, 0.0, 0.0);
  SumEt = 0;
  Parrallel = 0;
  Perpendicular = 0;


  // Local temp variable.
  TLorentzVector lVec(0,0,0,0);
  TLorentzVector lUT(0,0,0,0);
  TLorentzVector lQT(0,0,0,0);

  for(unsigned int i=0; i < CorredJets.size(); ++i)
  {
    reco::PFJet jet = CorredJets.at(i);
    TLorentzVector jetv(jet.px(), jet.py(), jet.pz(), jet.energy());
    assert(fabs(jetv.Pt() - jet.pt() ) < 0.01);
    lVec -= jetv;
    lUT += jetv;
    SumEt += jetv.Pt();
  }

  for(unsigned int i=0; i < MuonHdl->size(); ++i)
  {
    reco::Muon muon = MuonHdl->at(i);
    TLorentzVector muonv(muon.px(), muon.py(), muon.pz(), muon.energy());
    //assert(muonv.Pt() == muon.pt());
    assert(fabs(muonv.Pt() - muon.pt() ) < 0.01);
    lVec -= muonv;
    lQT += muonv;
    SumEt += muonv.Pt();
  }

  RecoZ = lQT;
  assert( lQT == RecoZ );
  Recoil = lUT;
  MET.SetMagPhi(lVec.Pt(), lVec.Phi());

  double Dphi =  lUT.DeltaPhi(lQT);
  Perpendicular = lUT.Pt() * std::sin(Dphi);
  Parrallel = lUT.Pt() * std::cos(Dphi);

  return true;
}       // -----  end of function METPerformance::RecoEvent  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetCorrectedJets
//  Description:  /* cursor */
// ===========================================================================
std::vector<reco::PFJet> METPerformance::GetCorrectedJets()
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
    ss << CMSPath <<"/src/UserCode/PFAnalyzer/JEC/"<< L1JECTag_;
    JetCorrectorParameters L1JetPar(ss.str());
    vPar.push_back(L1JetPar);
  }
  if (L2JECTag_ != "")
  {
    assert(L1JECTag_ != "");
    std::stringstream ss;
    ss << CMSPath <<"/src/UserCode/PFAnalyzer/JEC/"<< L2JECTag_;
    JetCorrectorParameters L2JetPar(ss.str());
    vPar.push_back(L2JetPar);
  }
  if (L3JECTag_ != "")
  {
    assert(L1JECTag_ != "");
    assert(L2JECTag_ != "");
    std::stringstream ss;
    ss << CMSPath <<"/src/UserCode/PFAnalyzer/JEC/"<< L3JECTag_;
    JetCorrectorParameters L3JetPar(ss.str());
    vPar.push_back(L3JetPar);
  }

  FactorizedJetCorrector *JetCorrector = new FactorizedJetCorrector(vPar);

  for(reco::PFJetCollection::const_iterator it=PFJetHdl->begin();
      it!=PFJetHdl->end(); it++)
  {

    reco::PFJet rawJet = *it;
    reco::PFJet correctedJet = rawJet;

    double jec  = 1.0;
    if (vPar.size() != 0)
    {
      jec = GetCorrFactor(JetCorrector, correctedJet, rho);
    }
    correctedJet.scaleEnergy(jec);

    //----------------------------------------------------------------------------
    //  Type1 MET in CMS has corrected jet PT > 10GeV
    //  We keep this as we don't really trust the JEC for jets below 10GeV
    //----------------------------------------------------------------------------
    if (correctedJet.pt() > 10)
      CorredJets.push_back(correctedJet);
    else
      CorredJets.push_back(rawJet);

  }

  return CorredJets;
}       // -----  end of function METPerformance::GetCorrectedJets  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetCorrFactor
//  Description:  
// ===========================================================================
double METPerformance::GetCorrFactor( FactorizedJetCorrector *JetCorrector, reco::PFJet &jet, double rho)
{
  JetCorrector->setJetEta(jet.eta());
  JetCorrector->setJetPt(jet.pt());
  JetCorrector->setJetA(jet.jetArea());
  JetCorrector->setRho(rho);
  return JetCorrector->getCorrection();
}       // -----  end of function METPerformance::GetCorrFactor  -----


// ===  FUNCTION  ============================================================
//         Name:  METPerformance::FillMETPerf
//  Description:  
// ===========================================================================
bool METPerformance::FillMETPerf()
{
  
  if(! PassZCut()) return false;

  // Reco Z
  //std::cout << " Reco Z " << RecoZ.M() << " pt " << RecoZ.Pt() << std::endl;
  hZMass->Fill(RecoZ.M());
  hZPT->Fill(RecoZ.Pt());
  hZEta->Fill(RecoZ.Eta());
  hZPhi->Fill(RecoZ.Phi());

  // MET
  hMETPT->Fill(MET.Mod());
  hMETPhi->Fill(MET.Phi());
  hMETx->Fill(MET.Px());
  hMETy->Fill(MET.Py());
  hSumET->Fill(SumEt);
  hMETSig->Fill(MET.Mod()/SumEt);

  // Recoil
  hRecoilPT->Fill(Recoil.Pt());
  hParrallel->Fill(Parrallel);
  hParrallelZPT->Fill(Parrallel + RecoZ.Pt());
  hPerpendicular->Fill(Perpendicular);

  // 2D Performance
  h2D_Parrallel ->Fill(RecoZ.Pt(), Parrallel + RecoZ.Pt());
  h2D_ParrallelZpt ->Fill(RecoZ.Pt(), -1 * Parrallel / RecoZ.Pt());
  h2D_Perperndicular ->Fill(RecoZ.Pt(), Perpendicular);

  h2D_METx_SumET->Fill(SumEt, MET.Px());
  h2D_METy_SumET->Fill(SumEt, MET.Py());

  return true;
}       // -----  end of function METPerformance::FillMETPerf  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetInputTag
//  Description:  
// ===========================================================================
bool METPerformance::GetInputTag(const edm::ParameterSet& iConfig)
{
  MuonInputTag_   = iConfig.getParameter<edm::InputTag>("MuonInputTag");
  PFJetInputTag_  = iConfig.getParameter<edm::InputTag>("PFJetInputTag");
  srcRhoInputTag_ = iConfig.getParameter<edm::InputTag>("srcRhoTag");
  PileUpInfoTag_  = iConfig.getParameter<edm::InputTag>("PileUpInfoTag");

  L1JECTag_ = iConfig.getParameter<std::string>("L1JECTag");
  L2JECTag_ = iConfig.getParameter<std::string>("L2JECTag");
  L3JECTag_ = iConfig.getParameter<std::string>("L3JECTag");

  return true;
}       // -----  end of function METPerformance::GetInputTag  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetHandleByLabel
//  Description:  
// ===========================================================================
bool METPerformance::GetHandleByLabel(const edm::Event& iEvent)
{
  iEvent.getByLabel(MuonInputTag_, MuonHdl); 
  iEvent.getByLabel(PFJetInputTag_, PFJetHdl); 
  iEvent.getByLabel(srcRhoInputTag_, srcRhoHdl); 
  //iEvent.getByLabel(PileUpInfoTag_, PileUpInfoHdl); 
  return true;
}       // -----  end of function METPerformance::GetHandleByLabel  -----
