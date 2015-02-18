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
  if(! PassZCut()) return;
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
  hZPT  = fs->make<TH1D>("ZPT", "ZPT;Z PT;Number of Event", 200, 0, 200);
  hZEta  = fs->make<TH1D>("ZEta", "ZEta;Z Eta;Number of Event", 200, 0, 200);
  hZPhi  = fs->make<TH1D>("ZPhi", "ZPhi;Z Phi;Number of Event", 200, 0, 200);

  return true;
}       // -----  end of function METPerformance::BookHistogram  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::RecoEvent
//  Description:  
// ===========================================================================
bool METPerformance::RecoEvent()
{
  SumEt = 0;
  TLorentzVector lVec(0,0,0,0);
  TLorentzVector lUT(0,0,0,0);
  TLorentzVector lQT(0,0,0,0);

  for(unsigned int i=0; i < CorredJets.size(); ++i)
  {
    reco::PFJet jet = CorredJets.at(i);
    TLorentzVector jetv(jet.px(), jet.py(), jet.pz(), jet.energy());
    assert(jetv.Pt() == jet.pt());
    lVec -= jetv;
    lUT += jetv;
    SumEt += jetv.Pt();
  }

  for(unsigned int i=0; i < MuonHdl->size(); ++i)
  {
    reco::Muon muon = MuonHdl->at(i);
    TLorentzVector muonv(muon.px(), muon.py(), muon.pz(), muon.energy());
    assert(muonv.Pt() == muon.pt());
    lVec -= muonv;
    lQT += muonv;
    SumEt += muonv.Pt();
  }

  assert( lQT == RecoZ );
  Recoil = lUT;
  MET 


  iMET.fSumEt  = SumEt;
  iMET.fMet    = lVec.Pt();
  iMET.fMetPhi = lVec.Phi();
  double Dphi =  lUT.DeltaPhi(lQT);
  iMET.fU2 = lUT.Pt() * std::sin(Dphi);
  iMET.fU1 = lUT.Pt() * std::cos(Dphi);
  
  return true;
}       // -----  end of function METPerformance::RecoEvent  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::GetCorrectedJets
//  Description:  /* cursor */
// ===========================================================================
std::vector<reco::PFJet> METPerformance::GetCorrectedJets()
{
  CorredJets.clear();

  double rho = *srcRhoHdl.product();
  //  Load the JetCorrectorParameter objects into a vector, IMPORTANT: THE ORDER MATTERS HERE !!!! 
  std::vector<JetCorrectorParameters> vPar;
  if (L1JECTag_ != "")
  {
    JetCorrectorParameters L1JetPar(L1JECTag_);
    vPar.push_back(L1JetPar);
  }
  if (L2JECTag_ != "")
  {
    assert(L1JECTag_ != "");
    JetCorrectorParameters L2JetPar(L2JECTag_);
    vPar.push_back(L2JetPar);
  }
  if (L3JECTag_ != "")
  {
    assert(L1JECTag_ != "");
    assert(L2JECTag_ != "");
    JetCorrectorParameters L3JetPar(L3JECTag_);
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
//         Name:  METPerformance::BookHistogram
//  Description:  
// ===========================================================================
bool METPerformance::BookHistogram()
{
  
  return true;
}       // -----  end of function METPerformance::BookHistogram  -----
