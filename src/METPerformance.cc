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

  if (PFJetHdl->size() == 0) return;

#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif

  if (!UseGenJets)
  {
    GetCorrectedJets();
    RecoEvent();
  }
  else
  {
    RecoEventGen();
  }


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
  if (! IsDiMuon ()) return false;
  if (RecoZ.M() < 80 || RecoZ.M() > 200) return false;
  //if (fabs(RecoZ.Eta()) > 3.0) return false;

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

  h20METPT  = fs->make<TH1D>("METPT_20",  "MET PT; MET PT (qt > 20GeV); Number of Event", 100, 0 , 500);
  h20METPhi  = fs->make<TH1D>("METPhi_20",  "MET Phi; MET Phi (qt > 20GeV); Number of Event", 28, 0, 7);
  h20METx  = fs->make<TH1D>("METx_20",  "MET x; MET x (qt > 20GeV); Number of Event", 100, -200, 200);
  h20METy  = fs->make<TH1D>("METy_20",  "MET y; MET y (qt > 20GeV); Number of Event", 100, -200, 200);
  
  h40METPT  = fs->make<TH1D>("METPT_40",  "MET PT; MET PT (qt > 40GeV); Number of Event", 100, 0 , 500);
  h40METPhi  = fs->make<TH1D>("METPhi_40",  "MET Phi; MET Phi (qt > 40GeV); Number of Event", 28, 0, 7);
  h40METx  = fs->make<TH1D>("METx_40",  "MET x; MET x (qt > 40GeV); Number of Event", 100, -200, 200);
  h40METy  = fs->make<TH1D>("METy_40",  "MET y; MET y (qt > 40GeV); Number of Event", 100, -200, 200);

  hSumET  = fs->make<TH1D>("SumET",  "MET PT; SumET; Number of Event", 500, 0, 10000);
  hSumET1  = fs->make<TH1D>("SumET1",  "MET PT; SumET (PT>1); Number of Event", 100, 0, 5000);
  hSumET5  = fs->make<TH1D>("SumET5",  "MET PT; SumET (PT>5); Number of Event", 100, 0, 5000);
  hSumET10  = fs->make<TH1D>("SumET10",  "MET PT; SumET (PT>10); Number of Event", 100, 0, 5000);
  hSumET30  = fs->make<TH1D>("SumET30",  "MET PT; SumET (PT>30); Number of Event", 100, 0, 5000);
  hlogSumET  = fs->make<TH1D>("logSumET",  "MET PT; logSumET; Number of Event", 200, 0, log10(10000));
  hMETSig  = fs->make<TH1D>("METSig",  "MET PT; MET PT; Number of Event", 50, 0, 1);
  hUnCluSumET  = fs->make<TH1D>("UnCluSumET",  "MET PT; Unclustered Jet SumET; Number of Event", 100, 0, 5000);
  hBB_HT  = fs->make<TH1D>("BB_HT",  "BB_HT; BB_HT; Number of Event", 100, 0, 5000);
  hEC_HT  = fs->make<TH1D>("EC_HT",  "EC_HT; EC_HT; Number of Event", 100, 0, 5000);
  hFW_HT  = fs->make<TH1D>("FW_HT",  "FW_HT; FW_HT; Number of Event", 100, 0, 5000);

  hJetPT  = fs->make<TH1D>("JetPT",  "Jet PT; Jet PT; Number of Event", 100, 0 , 500);
  hJetEta  = fs->make<TH1D>("JetEta", "JetEta;Jet Eta;Number of Event", 50, -5, 5);
  h2D_JetEta_JetPT = fs->make<TH2D>("h2D_JetEta_JetPT",  "Jet Eta ;Jet PT; Number of Event", 100, -5, 5, 100, 0, 100);

  hRecoilPT = fs->make<TH1D>("RecoilPT",  "Recoil PT; MET PT; Number of Event", 200, 0 , 200);
  hParrallel = fs->make<TH1D>("Parrallel ",  "Recoil PT; MET PT; Number of Event", 80, -200 , 200);
  hParrallelZPT = fs->make<TH1D>("ParrallelZPT ",  "Recoil PT; MET PT; Number of Event", 80, -200 , 200);
  hPerpendicular = fs->make<TH1D>("Perpendicular ",  "Recoil PT; MET PT; Number of Event", 80, -200, 200);

  h2D_Parrallel = fs->make<TH2D>("h2D_Parrallel",  "Recoil PT; MET PT; Number of Event", 500, 0, 500, 4000, -200, 200);
  h2D_ParrallelZpt = fs->make<TH2D>("h2D_ParrallelZpt",  "Recoil PT; MET PT; Number of Event", 500, 0, 500, 4000, -20, 20);
  h2D_Perperndicular= fs->make<TH2D>("h2D_Perperndicular",  "Recoil PT; MET PT; Number of Event", 500, 0, 500, 4000, -200, 200);

  h2D_METx_SumET= fs->make<TH2D>("h2D_METx_SumET",  "h2D_METx_SumET PT; MET PT; Number of Event", 500, 0, 10000, 100, -200, 200);
  h2D_METy_SumET= fs->make<TH2D>("h2D_METy_SumET",  "h2D_METy_SumET PT; MET PT; Number of Event", 500, 0, 10000, 100, -200, 200);
  h2D_SumET_Zpt = fs->make<TH2D>("h2D_SumET_Zpt",  "Recoil PT; SumET; Number of Event", 500, 0, 500, 5000, 0, 10000);

  h2D_METx_BBHT= fs->make<TH2D>("h2D_METx_BBHT",  "h2D_METx_BBHT PT; HT(BB) / HT; Number of Event", 500, 0, 1, 100, -200, 200);
  h2D_METy_BBHT= fs->make<TH2D>("h2D_METy_BBHT",  "h2D_METy_BBHT PT; HT(BB) / HT; Number of Event", 500, 0, 1, 100, -200, 200);
  h2D_METx_ECHT= fs->make<TH2D>("h2D_METx_ECHT",  "h2D_METx_ECHT PT; HT(EC) / HT; Number of Event", 500, 0, 1, 100, -200, 200);
  h2D_METy_ECHT= fs->make<TH2D>("h2D_METy_ECHT",  "h2D_METy_ECHT PT; HT(EC) / HT; Number of Event", 500, 0, 1, 100, -200, 200);
  h2D_METx_FWHT= fs->make<TH2D>("h2D_METx_FWHT",  "h2D_METx_FWHT PT; HT(FW) / HT; Number of Event", 500, 0, 1, 100, -200, 200);
  h2D_METy_FWHT= fs->make<TH2D>("h2D_METy_FWHT",  "h2D_METy_FWHT PT; HT(FW) / HT; Number of Event", 500, 0, 1, 100, -200, 200);

  h2D_METx_NPU= fs->make<TH2D>("h2D_METx_NPU",  "h2D_METx_NPU PT; NPU; Number of Event", 250, 0, 250, 100, -200, 200);
  h2D_METy_NPU= fs->make<TH2D>("h2D_METy_NPU",  "h2D_METy_NPU PT; NPU; Number of Event", 250, 0, 250, 100, -200, 200);

  return true;
}       // -----  end of function METPerformance::BookHistogram  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::RecoEvent
//  Description:  
// ===========================================================================
bool METPerformance::RecoEvent()
{
  // Clear up event default 
  RecoZ.SetXYZT(0.0, 0.0, 0.0, 0.0);
  MET.SetMagPhi(0.0, 0.0);
  Recoil.SetXYZT(0.0, 0.0, 0.0, 0.0);
  SumEt = 0;
  Parrallel = 0;
  Perpendicular = 0;
  BB_HT = 0.0;
  EC_HT = 0.0;
  FW_HT = 0.0;
  NPU = GetNPU();


  double SumEt1 = 0;
  double SumEt5 = 0;
  double SumEt10 = 0;
  double SumEt30 = 0;

  // Local temp variable.
  TLorentzVector lVec(0,0,0,0);
  TLorentzVector lUT(0,0,0,0);
  TLorentzVector lQT(0,0,0,0);

  // Raw MET = - Sum(PFJets)
  for(unsigned int i=0; i < RawJets.size(); ++i)
  {
    reco::PFJet jet = RawJets.at(i);
    TLorentzVector jetv(jet.px(), jet.py(), jet.pz(), jet.energy());
    assert(fabs(jetv.Pt() - jet.pt() ) < 0.01);
    lVec -= jetv;
    lUT += jetv;
    SumEt += jetv.Pt();

    if (jet.pt() > 1) SumEt1 += jet.pt();
    if (jet.pt() > 5) SumEt5 += jet.pt();
    if (jet.pt() > 10) SumEt10 += jet.pt();
    if (jet.pt() > 30) SumEt30 += jet.pt();

    hJetPT->Fill(jet.pt());
    hJetEta->Fill(jet.eta());
    h2D_JetEta_JetPT->Fill(jet.eta(), jet.pt());

    HT += jet.pt();
    if (fabs(jet.eta()) <= 1.3) BB_HT += jet.pt();
    if (fabs(jet.eta()) > 1.3 && fabs(jet.eta()) < 3.0) EC_HT += jet.pt();
    if (fabs(jet.eta()) >= 3.0) FW_HT += jet.pt();
  }


  // Apply type 1 Correction, empty if now JEC are applied
  for(unsigned int i=0; i < JetsType1.size(); ++i)
  {
    TLorentzVector jetv(JetsType1.at(i));
    lVec -= jetv;
    lUT += jetv;
    SumEt += jetv.Pt();

    HT += jetv.Pt();
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

  hUnCluSumET->Fill(UnCluSumET);
  hSumET1->Fill(SumEt1);
  hSumET5->Fill(SumEt5);
  hSumET10->Fill(SumEt10);
  hSumET30->Fill(SumEt30);


  return true;
}       // -----  end of function METPerformance::RecoEvent  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetCorrectedJets
//  Description:  /* cursor */
// ===========================================================================
std::vector<TLorentzVector> METPerformance::GetCorrectedJets()
{
  GetRawJets();
  JetsType1.clear();

  if (L1JECTag_ == "" && L2JECTag_ == "" && L3JECTag_ == "")
    return JetsType1;

  double rho = 0.0;
  if (srcRhoHdl.isValid())
  {
    rho = *srcRhoHdl.product();
  }

  //  Load the JetCorrectorParameter objects into a vector, IMPORTANT: THE ORDER MATTERS HERE !!!! 
  std::vector<JetCorrectorParameters> vParL1;
  std::vector<JetCorrectorParameters> vPar;
  char* CMSPath = getenv("CMSSW_BASE");
  if (L1JECTag_ != "")
  {
    std::stringstream ss;
    ss << CMSPath <<"/src/UserCode/PFAnalyzer/data/"<< L1JECTag_;
    JetCorrectorParameters L1JetPar(ss.str());

    //std::cout << " L1 " << ss.str() << std::endl;
    vPar.push_back(L1JetPar);
    vParL1.push_back(L1JetPar);
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

  FactorizedJetCorrector *JetCorrectorL1 = new FactorizedJetCorrector(vParL1);
  FactorizedJetCorrector *JetCorrector = new FactorizedJetCorrector(vPar);

  for(unsigned int i=0; i < RawJets.size(); ++i)
  {
    reco::PFJet rawJet = RawJets.at(i);
    reco::PFJet L1Jet = rawJet;
    reco::PFJet correctedJet = rawJet;

    // L1 Jets
    double jec  = 0.0;
    if (L1JECTag_ != "")
    {
      jec = GetCorrFactor(JetCorrectorL1, L1Jet, rho);
      //std::cout << "L! JEC " << jec << std::endl;
    }
    L1Jet.scaleEnergy(jec);

    // L1L2L3 Jets
    jec  = 0.0;
    if (L1JECTag_ != "" && L2JECTag_ != "" && L3JECTag_ != "")
    {
      jec = GetCorrFactor(JetCorrector, correctedJet, rho);
      //std::cout << "L123 JEC " << jec << std::endl;
    }
    correctedJet.scaleEnergy(jec);

    //std::cout << " JEC " << jec <<" rawPT " << rawJet.pt() <<" correctedJet PT " << correctedJet.pt() << std::endl;
    //----------------------------------------------------------------------------
    //  Type1 MET in CMS has corrected jet PT > 10GeV
    //  We keep this as we don't really trust the JEC for jets below 10GeV
    //  Taking the 4vector difference L1L2L3 - L1
    //----------------------------------------------------------------------------
    if (correctedJet.pt() > JetJECThres)
    {
      TLorentzVector corTLV(correctedJet.px(), correctedJet.py(), correctedJet.pz(), correctedJet.energy());
      TLorentzVector L1TLV(L1Jet.px(), L1Jet.py(), L1Jet.pz(), L1Jet.energy());
      //std::cout << " CorTLV " << corTLV.Pt() <<" L1TLV "<<L1TLV.Pt() <<" diff " << (corTLV-L1TLV).Pt()<< std::endl;
      JetsType1.push_back(corTLV - L1TLV);
    }

  }

  delete JetCorrector;
  delete JetCorrectorL1;

  return JetsType1;
}       // -----  end of function METPerformance::GetCorrectedJets  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetCorrFactor
//  Description:  
// ===========================================================================
double METPerformance::GetCorrFactor( FactorizedJetCorrector *JetCorrector, reco::PFJet &jet, double rho)
{
  //std::cout << " eta " << jet.eta() << " pt " << jet.pt()  <<" area " << jet.jetArea() <<" rho " << rho <<" consti " << jet.getPFConstituents().size()<< std::endl;
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
  
  //if(! PassZCut()) return false;


  // MET
  hMETPT->Fill(MET.Mod());
  hMETPhi->Fill(MET.Phi());
  hMETx->Fill(MET.Px());
  hMETy->Fill(MET.Py());
  hSumET->Fill(SumEt);
  hMETSig->Fill(MET.Mod()/SumEt);
  
  hBB_HT->Fill(BB_HT);
  hEC_HT->Fill(EC_HT);
  hFW_HT->Fill(FW_HT);


  h2D_METx_SumET->Fill(SumEt, MET.Px());
  h2D_METy_SumET->Fill(SumEt, MET.Py());

  h2D_METx_BBHT->Fill(BB_HT/SumEt, MET.Px());
  h2D_METy_BBHT->Fill(BB_HT/SumEt, MET.Py());
  h2D_METx_ECHT->Fill(EC_HT/SumEt, MET.Px());
  h2D_METy_ECHT->Fill(EC_HT/SumEt, MET.Py());
  h2D_METx_FWHT->Fill(FW_HT/SumEt, MET.Px());
  h2D_METy_FWHT->Fill(FW_HT/SumEt, MET.Py());
  h2D_METx_NPU->Fill(NPU, MET.Px());
  h2D_METy_NPU->Fill(NPU, MET.Py());

  if(! PassZCut()) return false;

  // Reco Z
  //std::cout << " Reco Z " << RecoZ.M() << " pt " << RecoZ.Pt() << std::endl;
  hZMass->Fill(RecoZ.M());
  hZPT->Fill(RecoZ.Pt());
  hZEta->Fill(RecoZ.Eta());
  hZPhi->Fill(RecoZ.Phi());

  // Recoil
  hRecoilPT->Fill(Recoil.Pt());
  hParrallel->Fill(Parrallel);
  hParrallelZPT->Fill(Parrallel + RecoZ.Pt());
  hPerpendicular->Fill(Perpendicular);

  //if (RecoZ.Pt() > 20 && fabs(RecoZ.Eta()) < 3.0)
  if (RecoZ.Pt() > 20 )
  {
    h20METPT->Fill(MET.Mod());
    h20METPhi->Fill(MET.Phi());
    h20METx->Fill(MET.Px());
    h20METy->Fill(MET.Py());
  }
  //if (RecoZ.Pt() > 40 && fabs(RecoZ.Eta()) < 3.0)
  if (RecoZ.Pt() > 40)
  {
    h40METPT->Fill(MET.Mod());
    h40METPhi->Fill(MET.Phi());
    h40METx->Fill(MET.Px());
    h40METy->Fill(MET.Py());
  }
 

  // 2D Performance
  h2D_Parrallel ->Fill(RecoZ.Pt(), Parrallel + RecoZ.Pt());
  h2D_ParrallelZpt ->Fill(RecoZ.Pt(), -1 * Parrallel / RecoZ.Pt());
  h2D_Perperndicular ->Fill(RecoZ.Pt(), Perpendicular);
  h2D_SumET_Zpt->Fill(RecoZ.Pt(), SumEt);

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
  GenJetInputTag_ = iConfig.getParameter<edm::InputTag>("GenJetInputTag");
  srcRhoInputTag_ = iConfig.getParameter<edm::InputTag>("srcRhoTag");
  PileUpInfoTag_  = iConfig.getParameter<edm::InputTag>("PileUpInfoTag");

  L1JECTag_ = iConfig.getParameter<std::string>("L1JECTag");
  L2JECTag_ = iConfig.getParameter<std::string>("L2JECTag");
  L3JECTag_ = iConfig.getParameter<std::string>("L3JECTag");
  
  JetJECThres= iConfig.getUntrackedParameter<double>("JetJECThresTag", 0);
  UseGenJets =  iConfig.getUntrackedParameter<bool>("UseGenJets", false);
  JetsMatchedGen =  iConfig.getUntrackedParameter<bool>("JetsMatchedGen", false);
  JetEtaThres= iConfig.getUntrackedParameter<double>("JetEtaThresTag", 999);

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
  iEvent.getByLabel(PileUpInfoTag_, PileUpInfoHdl); 
  iEvent.getByLabel(GenJetInputTag_, GenJetHdl); 
  return true;
}       // -----  end of function METPerformance::GetHandleByLabel  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetRawJets
//  Description:  
// ===========================================================================
std::vector<reco::PFJet> METPerformance::GetRawJets() 
{
  RawJets.clear();

  // Set doesn't work with reco::PFJet, changed to iterator
  std::set<reco::PFJetCollection::const_iterator> setJet;

  for(reco::PFJetCollection::const_iterator it=PFJetHdl->begin();
      it!=PFJetHdl->end(); it++)
  {
    reco::PFJet rawJet = *it;
    if (JetEtaThres != 999)
    {
      if (fabs(rawJet.eta()) > JetEtaThres) continue;
    }

    if (!JetsMatchedGen)
    {
      //SlimJet(rawJet);
      RawJets.push_back(rawJet);
    } else{
      DeltaR<reco::PFJet, reco::GenJet> deltaR;

      // Using only jets that are matched to genjets
      // If a single genjet pointing at random direction, look for the exact
      // oposited for the pileup jet

      TLorentzVector optJet;
      TLorentzVector rawJetTLV;
      for(unsigned int i=0; i < GenJetHdl->size(); ++i)
      {
        reco::GenJet gjet = GenJetHdl->at(i);
        if (deltaR(rawJet, gjet) <= 0.2)
          setJet.insert(it);
        optJet.SetPtEtaPhiE(gjet.pt(), -1 * gjet.eta(), -1* gjet.phi(), gjet.energy());
        rawJetTLV.SetPtEtaPhiE(rawJet.pt(), rawJet.eta(), rawJet.phi(), rawJet.energy());
        if (optJet.DeltaR(rawJetTLV) <= 0.2)
          setJet.insert(it);
      }

    }
  }

  if (JetsMatchedGen && setJet.size() != 0)
  {
    for(std::set<reco::PFJetCollection::const_iterator>::const_iterator it=setJet.begin();
      it!=setJet.end(); ++it)
    {
      RawJets.push_back(*(*it));
    }
  }
  
  return RawJets;
}       // -----  end of function METPerformance::GetRawJets  -----


// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetNPU
//  Description:  
// ===========================================================================
int METPerformance::GetNPU() const
{
  for(unsigned int i=0; i < PileUpInfoHdl->size(); ++i)
  {
    PileupSummaryInfo pu = PileUpInfoHdl->at(i);
    if (pu.getBunchCrossing() == 0)
      return pu.getPU_NumInteractions();
  }
  return -1;
}       // -----  end of function METPerformance::GetNPU  -----


// ===  FUNCTION  ============================================================
//         Name:  METPerformance::RecoEventGen
//  Description:  
// ===========================================================================
bool METPerformance::RecoEventGen()
{
  // Clear up event default 
  RecoZ.SetXYZT(0.0, 0.0, 0.0, 0.0);
  MET.SetMagPhi(0.0, 0.0);
  Recoil.SetXYZT(0.0, 0.0, 0.0, 0.0);
  SumEt = 0;
  Parrallel = 0;
  Perpendicular = 0;
  BB_HT = 0.0;
  EC_HT = 0.0;
  FW_HT = 0.0;
  NPU = GetNPU();


  double SumEt1 = 0;
  double SumEt5 = 0;
  double SumEt10 = 0;
  double SumEt30 = 0;

  // Local temp variable.
  TLorentzVector lVec(0,0,0,0);
  TLorentzVector lUT(0,0,0,0);
  TLorentzVector lQT(0,0,0,0);

  // Raw MET = - Sum(PFJets)
  for(unsigned int i=0; i < GenJetHdl->size(); ++i)
  {
    reco::GenJet jet = GenJetHdl->at(i);
    TLorentzVector jetv(jet.px(), jet.py(), jet.pz(), jet.energy());
    assert(fabs(jetv.Pt() - jet.pt() ) < 0.01);
    lVec -= jetv;
    lUT += jetv;
    SumEt += jetv.Pt();

    if (jet.pt() > 1) SumEt1 += jet.pt();
    if (jet.pt() > 5) SumEt5 += jet.pt();
    if (jet.pt() > 10) SumEt10 += jet.pt();
    if (jet.pt() > 30) SumEt30 += jet.pt();

    hJetPT->Fill(jet.pt());
    hJetEta->Fill(jet.eta());
    h2D_JetEta_JetPT->Fill(jet.eta(), jet.pt());

    HT += jet.pt();
    if (fabs(jet.eta()) <= 1.3) BB_HT += jet.pt();
    if (fabs(jet.eta()) > 1.3 && fabs(jet.eta()) < 3.0) EC_HT += jet.pt();
    if (fabs(jet.eta()) >= 3.0) FW_HT += jet.pt();
  }

  for(unsigned int i=0; i < MuonHdl->size(); ++i)
  {
    reco::Muon muon = MuonHdl->at(i);
    TLorentzVector muonv(muon.px(), muon.py(), muon.pz(), muon.energy());
    //assert(muonv.Pt() == muon.pt());
    assert(fabs(muonv.Pt() - muon.pt() ) < 0.01);
    //lVec -= muonv;
    //SumEt += muonv.Pt();
    lQT += muonv;
    //lUT -= muonv; //Since GenJet has Muons, removing them here 
  }

  RecoZ = lQT;
  assert( lQT == RecoZ );
  Recoil = lUT;
  MET.SetMagPhi(lVec.Pt(), lVec.Phi());

  double Dphi =  lUT.DeltaPhi(lQT);
  Perpendicular = lUT.Pt() * std::sin(Dphi);
  Parrallel = lUT.Pt() * std::cos(Dphi);

  hUnCluSumET->Fill(UnCluSumET);
  hSumET1->Fill(SumEt1);
  hSumET5->Fill(SumEt5);
  hSumET10->Fill(SumEt10);
  hSumET30->Fill(SumEt30);

  return true;
}       // -----  end of function METPerformance::RecoEventGen  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::SlimJet
//  Description:  /* cursor */
// ===========================================================================
bool METPerformance::SlimJet(reco::PFJet jet)
{

  //std::cout << "orignial jet pt " << jet.pt() << std::endl;
  std::vector<const reco::Candidate*> jetconst = jet.getJetConstituentsQuick();
  TLorentzVector  newJet(0, 0, 0, 0);
  for(unsigned int i=0; i < jetconst.size(); ++i)
  {
    if (jetconst.at(i)->charge() != 0)
    {
      TLorentzVector temp(jetconst.at(i)->px(), jetconst.at(i)->py(), jetconst.at(i)->pz(), jetconst.at(i)->energy());
      newJet += temp;
    }
  }
  jet.setP4(reco::Candidate::LorentzVector(newJet.Px(), newJet.Py(), newJet.Pz(), newJet.E()));
  
  //std::cout << "new jet pt " << jet.pt() << std::endl;
  return true;
}       // -----  end of function METPerformance::SlimJet  -----

