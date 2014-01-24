//
// Package:    PFAnalyzer
// Class:      PFAnalyzer
// 
/**\class PFAnalyzer PFAnalyzer.cc UserCode/PFAnalyzer/plugins/PFAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  zhenbin wu
//         Created:  Fri, 17 Jan 2014 02:44:28 GMT
// $Id$
//
#include "UserCode/PFAnalyzer/interface/PFAnalyzer.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "DataFormats/HcalDetId/interface/HcalElectronicsId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"

//
// constants, enums and typedefs
//
//
// static data member definitions
//

//
// constructors and destructor
//
PFAnalyzer::PFAnalyzer(const edm::ParameterSet& iConfig):
minTracks_(iConfig.getUntrackedParameter<unsigned int>("minTracks",0))
{
   //now do what ever initialization is needed
  demohisto = fs->make<TH1D>("tracks" , "Tracks" , 100 , 0 , 5000 );
  RH_Energy = fs->make<TH1D>("Rechit_energy" , "Rechit_Energy" , 100 , 0 , 5000 );

  PFJet_Pt = fs->make<TH1D>("PFJet_PT", "PF Jet_Pt " ,  100, 0, 1000);
  PFJet_Eta =fs->make<TH1D>("PFJet_Eta", "PF Jet Eta", 100, -5, 5);
  PFJet_Phi = fs->make<TH1D>("PFJet_Phi", "PF jet Phi", 100, -5, 5);

  PFJetRes_Pt = fs->make<TH1D>("PFJetRes_PT", "PF Jet_Pt " ,  100, 0, 1000);
  PFJetRes_Eta =fs->make<TH1D>("PFJetRes_Eta", "PF Jet Eta", 100, -5, 5);
  PFJetRes_Phi = fs->make<TH1D>("PFJetRes_Phi", "PF jet Phi", 100, -5, 5);

  GenJet_Pt = fs->make<TH1D>("GenJet_PT", "Gen Jet_Pt " ,  100, 0, 1000);
  GenJet_Eta =fs->make<TH1D>("GenJet_Eta", "Gen Jet Eta", 100, -5, 5);
  GenJet_Phi = fs->make<TH1D>("GenJet_Phi", "Gen jet Phi", 100, -5, 5);

  GenJetRes_Pt = fs->make<TH1D>("GenJetRes_PT", "Gen Jet_Pt " ,  100, 0, 1000);
  GenJetRes_Eta =fs->make<TH1D>("GenJetRes_Eta", "Gen Jet Eta", 100, -5, 5);
  GenJetRes_Phi = fs->make<TH1D>("GenJetRes_Phi", "Gen jet Phi", 100, -5, 5);

  CaloJet_Pt = fs->make<TH1D>("CaloJet_PT", "Calo Jet_Pt " ,  100, 0, 1000);
  CaloJet_Eta =fs->make<TH1D>("CaloJet_Eta", "Calo Jet Eta", 100, -5, 5);
  CaloJet_Phi = fs->make<TH1D>("CaloJet_Phi", "Calo jet Phi", 100, -5, 5);
  CaloJetRes_Pt = fs->make<TH1D>("CaloJetRes_PT", "Calo Jet_Pt " ,  100, 0, 1000);
  CaloJetRes_Eta =fs->make<TH1D>("CaloJetRes_Eta", "Calo Jet Eta", 100, -5, 5);
  CaloJetRes_Phi = fs->make<TH1D>("CaloJetRes_Phi", "Calo jet Phi", 100, -5, 5);

  PFJet_Gen0_50_Pt = fs->make<TH1D>("PFJet_Gen0_50_Pt", "PFJet (GenJet 0~50) Pt " ,  100, 0, 1000);
  PFJet_Gen50_80_Pt = fs->make<TH1D>("PFJet_Gen50_80_Pt", "PFJet (GenJet 50~80) Pt " ,  100, 0, 1000);
  PFJet_Gen80_120_Pt = fs->make<TH1D>("PFJet_Gen80_120_Pt", "PFJet (GenJet 80~120) Pt " ,  100, 0, 1000);
  PFJet_Gen120_200_Pt = fs->make<TH1D>("PFJet_Gen120_200_Pt", "PFJet (GenJet 120~200) Pt " ,  100, 0, 1000);
  PFJet_Gen200_500_Pt = fs->make<TH1D>("PFJet_Gen200_500_Pt", "PFJet (GenJet 200~500) Pt " ,  100, 0, 1000);
  PFJet_Gen500_1000_Pt = fs->make<TH1D>("PFJet_Gen500_1000_Pt", "PFJet (GenJet 500~1000) Pt " ,  100, 0, 1000);

  CaloJet_Gen0_50_Pt = fs->make<TH1D>("CaloJet_Gen0_50_Pt", "CaloJet (GenJet 0~50) Pt " ,  100, 0, 1000);
  CaloJet_Gen50_80_Pt = fs->make<TH1D>("CaloJet_Gen50_80_Pt", "CaloJet (GenJet 50~80) Pt " ,  100, 0, 1000);
  CaloJet_Gen80_120_Pt = fs->make<TH1D>("CaloJet_Gen80_120_Pt", "CaloJet (GenJet 80~120) Pt " ,  100, 0, 1000);
  CaloJet_Gen120_200_Pt = fs->make<TH1D>("CaloJet_Gen120_200_Pt", "CaloJet (GenJet 120~200) Pt " ,  100, 0, 1000);
  CaloJet_Gen200_500_Pt = fs->make<TH1D>("CaloJet_Gen200_500_Pt", "CaloJet (GenJet 200~500) Pt " ,  100, 0, 1000);
  CaloJet_Gen500_1000_Pt = fs->make<TH1D>("CaloJet_Gen500_1000_Pt", "CaloJet (GenJet 500~1000) Pt " ,  100, 0, 1000);

  // Get all the input tag needed
  PFMET_Pt = fs->make<TH1D>("PFMET_PT", "PF MET_Pt " ,  200, 0, 800);
  PFMET_Phi =fs->make<TH1D>("PFMET_Phi", "PF MET Phi", 100, -5, 5);
  PFMET_SumEt = fs->make<TH1D>("PFMET_SumEt", "PF MET SumEt", 100, 0, 1000);
  PFMET_Px = fs->make<TH1D>("PFMET_Px", "PF MET_Px " ,  200, -400, 400);
  PFMET_Py = fs->make<TH1D>("PFMET_Py", "PF MET_Py " ,  200, -400, 400);

  GenMET_Pt = fs->make<TH1D>("GenMET_PT", "Gen MET_Pt " ,  200, 0, 800);
  GenMET_Phi =fs->make<TH1D>("GenMET_Phi", "Gen MET Phi", 100, -5, 5);
  GenMET_SumEt = fs->make<TH1D>("GenMET_SumEt", "Gen MET SumEt", 100, 0, 1000);
  GenMET_Px = fs->make<TH1D>("GenMET_Px", "Gen MET_Px " ,  200, -400, 400);
  GenMET_Py = fs->make<TH1D>("GenMET_Py", "Gen MET_Py " ,  200, -400, 400);

  CaloMET_Pt = fs->make<TH1D>("CaloMET_PT", "Calo MET_Pt " ,  200, 0, 800);
  CaloMET_Phi =fs->make<TH1D>("CaloMET_Phi", "Calo MET Phi", 100, -5, 5);
  CaloMET_SumEt = fs->make<TH1D>("CaloMET_SumEt", "Calo MET SumEt", 100, 0, 1000);
  CaloMET_Px = fs->make<TH1D>("CaloMET_Px", "Calo MET_Px " ,  200, -400, 400);
  CaloMET_Py = fs->make<TH1D>("CaloMET_Py", "Calo MET_Py " ,  200, -400, 400);

  Lep_PFMET_Pt = fs->make<TH1D>("Lep_PFMET_PT", "Lep_PF MET_Pt " ,  200, 0, 800);
  Lep_PFMET_Phi =fs->make<TH1D>("Lep_PFMET_Phi", "Lep_PF MET Phi", 100, -5, 5);
  Lep_PFMET_SumEt = fs->make<TH1D>("Lep_PFMET_SumEt", "Lep_PF MET SumEt", 100, 0, 1000);
  Lep_PFMET_Px = fs->make<TH1D>("Lep_PFMET_Px", "Lep_PF MET_Px " ,  200, -400, 400);
  Lep_PFMET_Py = fs->make<TH1D>("Lep_PFMET_Py", "Lep_PF MET_Py " ,  200, -400, 400);

  Lep_GenMET_Pt = fs->make<TH1D>("Lep_GenMET_PT", "Lep_Gen MET_Pt " ,  200, 0, 800);
  Lep_GenMET_Phi =fs->make<TH1D>("Lep_GenMET_Phi", "Lep_Gen MET Phi", 100, -5, 5);
  Lep_GenMET_SumEt = fs->make<TH1D>("Lep_GenMET_SumEt", "Lep_Gen MET SumEt", 100, 0, 1000);
  Lep_GenMET_Px = fs->make<TH1D>("Lep_GenMET_Px", "Lep_Gen MET_Px " ,  200, -400, 400);
  Lep_GenMET_Py = fs->make<TH1D>("Lep_GenMET_Py", "Lep_Gen MET_Py " ,  200, -400, 400);

  Lep_CaloMET_Pt = fs->make<TH1D>("Lep_CaloMET_PT", "Lep_Calo MET_Pt " ,  200, 0, 800);
  Lep_CaloMET_Phi =fs->make<TH1D>("Lep_CaloMET_Phi", "Lep_Calo MET Phi", 100, -5, 5);
  Lep_CaloMET_SumEt = fs->make<TH1D>("Lep_CaloMET_SumEt", "Lep_Calo MET SumEt", 100, 0, 1000);
  Lep_CaloMET_Px = fs->make<TH1D>("Lep_CaloMET_Px", "Lep_Calo MET_Px " ,  200, -400, 400);
  Lep_CaloMET_Py = fs->make<TH1D>("Lep_CaloMET_Py", "Lep_Calo MET_Py " ,  200, -400, 400);

  Had_PFMET_Pt = fs->make<TH1D>("Had_PFMET_PT", "Had_PF MET_Pt " ,  200, 0, 800);
  Had_PFMET_Phi =fs->make<TH1D>("Had_PFMET_Phi", "Had_PF MET Phi", 100, -5, 5);
  Had_PFMET_SumEt = fs->make<TH1D>("Had_PFMET_SumEt", "Had_PF MET SumEt", 100, 0, 1000);
  Had_PFMET_Px = fs->make<TH1D>("Had_PFMET_Px", "Had_PF MET_Px " ,  200, -400, 400);
  Had_PFMET_Py = fs->make<TH1D>("Had_PFMET_Py", "Had_PF MET_Py " ,  200, -400, 400);

  Had_GenMET_Pt = fs->make<TH1D>("Had_GenMET_PT", "Had_Gen MET_Pt " ,  200, 0, 800);
  Had_GenMET_Phi =fs->make<TH1D>("Had_GenMET_Phi", "Had_Gen MET Phi", 100, -5, 5);
  Had_GenMET_SumEt = fs->make<TH1D>("Had_GenMET_SumEt", "Had_Gen MET SumEt", 100, 0, 1000);
  Had_GenMET_Px = fs->make<TH1D>("Had_GenMET_Px", "Had_Gen MET_Px " ,  200, -400, 400);
  Had_GenMET_Py = fs->make<TH1D>("Had_GenMET_Py", "Had_Gen MET_Py " ,  200, -400, 400);

  Had_CaloMET_Pt = fs->make<TH1D>("Had_CaloMET_PT", "Had_Calo MET_Pt " ,  200, 0, 800);
  Had_CaloMET_Phi =fs->make<TH1D>("Had_CaloMET_Phi", "Had_Calo MET Phi", 100, -5, 5);
  Had_CaloMET_SumEt = fs->make<TH1D>("Had_CaloMET_SumEt", "Had_Calo MET SumEt", 100, 0, 1000);
  Had_CaloMET_Px = fs->make<TH1D>("Had_CaloMET_Px", "Had_Calo MET_Px " ,  200, -400, 400);
  Had_CaloMET_Py = fs->make<TH1D>("Had_CaloMET_Py", "Had_Calo MET_Py " ,  200, -400, 400);


  // RecHit
  HcalRH_N = fs->make<TH1D>("HcalRH_N" , "Number of Hbhe RecHit",  300, 0, 3000);
  HcalRH_iEta = fs->make<TH1D>("HcalRH_iEta" , "iEta of Hbhe RecHit",  80, -40, 40);
  HcalRH_iPhi = fs->make<TH1D>("HcalRH_iPhi" , "iPhi of Hbhe RecHit",  100, 0, 100);
  HcalRH_Energy = fs->make<TH1D>("HcalRH_Energy" , "Hcal RecHit Energy",  200, 0, 1000);
  HcalRH_SumE_Eta = fs->make<TH1D>("HcalRH_SumE_iEta" , "Hcal RecHit SumE Vs. iEta",  80, -40, 40);
  HcalRH_SumE_Phi = fs->make<TH1D>("HcalRH_SumE_iPhi" , "Hcal RecHit SumE Vs iphi",  100, 0, 100);

  // PFRecHit
  HcalPFRH_N = fs->make<TH1D>("HcalPFRH_N" , "Number of Hbhe PFRecHit",  300, 0, 3000);
  HcalPFRH_iEta = fs->make<TH1D>("HcalPFRH_iEta" , "iEta of Hbhe PFRecHit",  80, -40, 40);
  HcalPFRH_iPhi = fs->make<TH1D>("HcalPFRH_iPhi" , "iPhi of Hbhe PFRecHit",  100, 0, 100);
  HcalPFRH_Energy = fs->make<TH1D>("HcalPFRH_Energy" , "Hcal PFRecHit Energy",  200, 0, 1000);
  HcalPFRH_SumE_Eta = fs->make<TH1D>("HcalPFRH_SumE_iEta" , "Hcal PFRecHit SumE Vs. iEta",  80, -40, 40);
  HcalPFRH_SumE_Phi = fs->make<TH1D>("HcalPFRH_SumE_iPhi" , "Hcal PFRecHit SumE Vs iphi",  100, 0, 100);
  //HcalRH_iEtaPhi = fs->make<TH1D>("N_SimCalo" , "Number of Sim Calo Hit",  200, 0, 1000);

  N_SimCalo = fs->make<TH1D>("N_SimCalo" , "Number of Sim Calo Hit",  200, 0, 1000);
  SimCalo_Eta = fs->make<TH1D>("SimCalo_Eta" , "Sim Calo Hit_Eta",  200, -5, 5);
  SimCalo_Energy = fs->make<TH1D>("SimCalo_Energy" , "Sim Calo Hit_Energy",  200, 0, 1000);

  GetInputTag(iConfig);
  //PFJetAna->Test();
  //RecHitAna->SetupHandler(HbHeRecHitHdl, HfRecHitHdl, HoRecHitHdl);
}


PFAnalyzer::~PFAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
PFAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   GetHandleByLabel(iEvent);
   using namespace edm;

   //Handle<reco::TrackCollection> tracks;
   //iEvent.getByLabel("generalTracks", tracks); 
   //demohisto->Fill(tracks->size());
   ////PFJetAna->SetupHandler(pfJetcollection.product());

   //if (minTracks_ <= tracks->size())
   //{
     //LogInfo("Demo") << "number of tracks "<<tracks->size();
   //}

  //for (unsigned int i = 0; i < pfJetcollection->size(); ++i)
  //{
    //reco::PFJet j = pfJetcollection->at(i);
    //std::cout << j.energy() << std::endl;
  //}

   RecHitAna();
   PFRecHitAna();
   PFJetAna();
   GenJetAna();
   CaloJetAna();
  //PFJetAna->Analyze();
  isLeptonic = false;
  isLeptonic = HasNeutrino();
  PFMetAna();
  GenMETAna();
  CaloMETAna();
  //RecHitAna->Analyze();
  //for(unsigned int i=0; i < HcalPFRecHitHdl->size(); i++)
  //{
    //reco::PFRecHit HcalPFRH = HcalPFRecHitHdl->at(i);
    //std::cout << HcalPFRH.energy() << std::endl;
  //}




    //std::cout << HcalPFRH.energy() << std::endl;
  //}


}


// ------------ method called once each job just before starting event loop  ------------
void 
PFAnalyzer::beginJob()
{
   //RecHitAna.AnaRecHit(HbHeRecHitHdl, HfRecHitHdl, HoRecHitHdl);

   //RecHitAna->BookHistogram(fs);
   //PFJetAna->BookHist(fs);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PFAnalyzer::endJob() 
{
}


// ------------ method called when starting to processes a run  ------------
/*
void 
PFAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
PFAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
PFAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
PFAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PFAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::GetConfigFlag
//  Description:  
// ===========================================================================
int PFAnalyzer::GetInputTag(const edm::ParameterSet& iConfig)
{
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RecHit ~~~~~
  HbHeRecHitTag_ = iConfig.getParameter<edm::InputTag>("HbHeRecHitTag");
  HfRecHitTag_ = iConfig.getParameter<edm::InputTag>("HfRecHitTag");
  HoRecHitTag_ = iConfig.getParameter<edm::InputTag>("HoRecHitTag");

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFRecHit ~~~~~
  EcalPFRecHitTag_ = iConfig.getParameter<edm::InputTag>("EcalPFRecHitTag");
  HcalPFRecHitTag_ = iConfig.getParameter<edm::InputTag>("HcalPFRecHitTag");
  HOPFRecHitTag_ = iConfig.getParameter<edm::InputTag>("HOPFRecHitTag");
  PSPFRecHitTag_ = iConfig.getParameter<edm::InputTag>("PSPFRecHitTag");

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFCluster ~~~~~
  EcalPFClusterTag_ = iConfig.getParameter<edm::InputTag>("EcalPFClusterTag");
  HcalPFClusterTag_ = iConfig.getParameter<edm::InputTag>("HcalPFClusterTag");
  HOPFClusterTag_ = iConfig.getParameter<edm::InputTag>("HOPFClusterTag");
  PSPFClusterTag_ = iConfig.getParameter<edm::InputTag>("PSPFClusterTag");

  GenJetInputTag_ = iConfig.getParameter<edm::InputTag>("GenJetInputTag");
  CaloJetInputTag_ = iConfig.getParameter<edm::InputTag>("CaloJetInputTag");
  PFJetInputTag_ = iConfig.getParameter<edm::InputTag>("PFJetInputTag");

  GenMETInputTag_ = iConfig.getParameter<edm::InputTag>("GenMETInputTag");
  CaloMETInputTag_ = iConfig.getParameter<edm::InputTag>("CaloMETInputTag");
  PFMETInputTag_ = iConfig.getParameter<edm::InputTag>("PFMETInputTag");

  GenParticleInputTag_= iConfig.getParameter<edm::InputTag>("GenParticleInputTag");
  SimCaloHitInputTag_ = iConfig.getParameter<edm::InputTag>("SimCaloHitInputTag");
  //caloJetInputTag_ = iConfig.getParameter<edm::InputTag>("caloJetInputTag");

  return 1;
}       // -----  end of function PFAnalyzer::GetConfigFlag  -----

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::GetHandleByLabel
//  Description:  
// ===========================================================================
int PFAnalyzer::GetHandleByLabel(const edm::Event& iEvent)
{

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RecHit ~~~~~
   iEvent.getByLabel(HbHeRecHitTag_, HbHeRecHitHdl); 
   iEvent.getByLabel(HfRecHitTag_, HfRecHitHdl); 
   iEvent.getByLabel(HoRecHitTag_, HoRecHitHdl); 

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFRecHit ~~~~~
   iEvent.getByLabel(EcalPFRecHitTag_, EcalPFRecHitHdl); 
   iEvent.getByLabel(HcalPFRecHitTag_, HcalPFRecHitHdl); 
   iEvent.getByLabel(HOPFRecHitTag_, HOPFRecHitHdl); 
   iEvent.getByLabel(PSPFRecHitTag_, PSPFRecHitHdl); 

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFCluster ~~~~~
   iEvent.getByLabel(EcalPFClusterTag_, EcalPFClusterHdl); 
   iEvent.getByLabel(HcalPFClusterTag_, HcalPFClusterHdl); 
   iEvent.getByLabel(HOPFClusterTag_, HOPFClusterHdl); 
   iEvent.getByLabel(PSPFClusterTag_, PSPFClusterHdl); 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFJet ~~~~~
   iEvent.getByLabel(GenJetInputTag_, GenJetHdl); 
   iEvent.getByLabel(PFJetInputTag_, PFJetHdl); 
   iEvent.getByLabel(CaloJetInputTag_, CaloJetHdl); 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFMET ~~~~~
   iEvent.getByLabel(GenMETInputTag_, GenMETHdl); 
   iEvent.getByLabel(PFMETInputTag_, PFMETHdl); 
   iEvent.getByLabel(CaloMETInputTag_, CaloMETHdl); 

   iEvent.getByLabel(GenParticleInputTag_, GenParticleHdl); 
   iEvent.getByLabel(SimCaloHitInputTag_, SimCaloHitHdl); 
  return 1;
}       // -----  end of function PFAnalyzer::GetHandleByLabel  -----

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::RecHitAna
//  Description:  
// ===========================================================================
int PFAnalyzer::RecHitAna()
{
  HcalRH_N->Fill(HbHeRecHitHdl->size());

  for (HBHERecHitCollection::const_iterator j=HbHeRecHitHdl->begin(); j != HbHeRecHitHdl->end(); j++) {
    HcalDetId cell(j->id());

    HcalRH_iEta->Fill(cell.ieta());
    HcalRH_iPhi->Fill(cell.iphi());
    HcalRH_Energy->Fill(j->energy());
    HcalRH_SumE_Eta->Fill(cell.ieta(), j->energy());
    HcalRH_SumE_Phi->Fill(cell.iphi(), j->energy());
    //int sub     = cell.subdet();
    //int depth   = cell.depth();
    //int inteta  = cell.ieta();
    //if(inteta > 0) inteta -= 1;
    //int intphi  = cell.iphi()-1;
    //double en   = j->energy();
    //double t    = j->time();
    //int stwd    = j->flags();
    //int auxstwd = j->aux();
  }

  return 1;
}       // -----  end of function PFAnalyzer::RecHitAna  -----

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::PFJetAna
//  Description:  
// ===========================================================================
int PFAnalyzer::PFJetAna()
{
  if (!PFJetHdl.isValid())
  {
    return 0;
  }
  std::cout << " size" << PFJetHdl->size() << std::endl;
  for(reco::PFJetCollection::const_iterator it=PFJetHdl->begin();
    it!=PFJetHdl->end(); it++)
  {
    
    PFJet_Pt->Fill(it->pt());
    PFJet_Eta->Fill(it->eta());
    PFJet_Phi->Fill(it->phi());
  }

  //Gen PF Jet matching

  PFGenJet_deltaR.clear();
  DeltaR<reco::PFJet, reco::GenJet> deltaR;

  for(unsigned int i=0; i < PFJetHdl->size(); i++)
  {
    reco::PFJet jet = PFJetHdl->at(i);
    for(unsigned int j=0; j < GenJetHdl->size(); j++)
    {
      reco::GenJet gjet = GenJetHdl->at(j);
      //if (jt.p4().DeltaR(gjet.p4()) < 0.3)
      double delR = deltaR(jet, gjet);
      if ( deltaR(jet, gjet) < 0.3)
      {
        PFGenJet_deltaR[j].push_front(std::make_pair(delR, i));
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
    reco::PFJet jet = PFJetHdl->at(it->second.front().second);
    PFGenJet[it->first] = it->second.front().second;
    PFJetRes_Pt->Fill(jet.pt());
    PFJetRes_Eta->Fill(jet.eta());
    PFJetRes_Phi->Fill(jet.phi());
    GenJetRes_Pt->Fill(gjet.pt());
    GenJetRes_Eta->Fill(gjet.eta());
    GenJetRes_Phi->Fill(gjet.phi());
  }


  for(std::map<unsigned int, unsigned int>::iterator it=PFGenJet.begin();
    it!=PFGenJet.end(); it++)
  {
    reco::GenJet gjet = GenJetHdl->at(it->first);
    reco::PFJet jet = PFJetHdl->at(it->second);
    if (gjet.pt() >= 0 && gjet.pt() < 50) PFJet_Gen0_50_Pt->Fill(jet.pt());
    if (gjet.pt() >= 50 && gjet.pt() < 80) PFJet_Gen50_80_Pt->Fill(jet.pt());
    if (gjet.pt() >= 80 && gjet.pt() < 120) PFJet_Gen80_120_Pt->Fill(jet.pt());
    if (gjet.pt() >= 120 && gjet.pt() < 200) PFJet_Gen120_200_Pt->Fill(jet.pt());
    if (gjet.pt() >= 200 && gjet.pt() < 500) PFJet_Gen200_500_Pt->Fill(jet.pt());
    if (gjet.pt() >= 500 && gjet.pt() < 1000) PFJet_Gen500_1000_Pt->Fill(jet.pt());
  }

  return 1;
}       // -----  end of function PFAnalyzer::PFJetAna  -----

// ===  FUNCTION  ============================================================
//         Name:  PFJetAna::GenJetAna
//  Description:  
// ===========================================================================
int PFAnalyzer::GenJetAna()
{
  if (!GenJetHdl.isValid())
  {
    return 0;
  }
  for(reco::GenJetCollection::const_iterator it=GenJetHdl->begin();
    it!=GenJetHdl->end(); it++)
  {
    
    GenJet_Pt->Fill(it->pt());
    GenJet_Eta->Fill(it->eta());
    GenJet_Phi->Fill(it->phi());
  }
  return 1;
}       // -----  end of function PFJetAna::GenJetAna  -----

// ===  FUNCTION  ============================================================
//         Name:  PFJetAna::CaloJetAna
//  Description:  
// ===========================================================================
int PFAnalyzer::CaloJetAna()
{
  if (!CaloJetHdl.isValid())
  {
    return 0;
  }
  for(reco::CaloJetCollection::const_iterator it=CaloJetHdl->begin();
    it!=CaloJetHdl->end(); it++)
  {
    
    CaloJet_Pt->Fill(it->pt());
    CaloJet_Eta->Fill(it->eta());
    CaloJet_Phi->Fill(it->phi());
  }


  //Gen Calo Jet matching

  CaloGenJet_deltaR.clear();
  DeltaR<reco::CaloJet, reco::GenJet> deltaR;

  for(unsigned int i=0; i < CaloJetHdl->size(); i++)
  {
    reco::CaloJet jet = CaloJetHdl->at(i);
    for(unsigned int j=0; j < GenJetHdl->size(); j++)
    {
      reco::GenJet gjet = GenJetHdl->at(j);
      //if (jt.p4().DeltaR(gjet.p4()) < 0.3)
      double delR = deltaR(jet, gjet);
      if ( deltaR(jet, gjet) < 0.3)
      {
        CaloGenJet_deltaR[j].push_front(std::make_pair(delR, i));
      }
    }
  }

  CaloGenJet.clear();
  //Get the index ;of the cloest jet to the GenJet
  for(std::map<unsigned int, std::list<std::pair<double, unsigned int> > >::iterator it=CaloGenJet_deltaR.begin();
    it!=CaloGenJet_deltaR.end(); it++)
  {
    reco::GenJet gjet = GenJetHdl->at(it->first);
    it->second.sort();
    reco::CaloJet jet = CaloJetHdl->at(it->second.front().second);
    CaloGenJet[it->first] = it->second.front().second;
    CaloJetRes_Pt->Fill(jet.pt());
    CaloJetRes_Eta->Fill(jet.eta());
    CaloJetRes_Phi->Fill(jet.phi());
    GenJetRes_Pt->Fill(gjet.pt());
    GenJetRes_Eta->Fill(gjet.eta());
    GenJetRes_Phi->Fill(gjet.phi());
  }


  for(std::map<unsigned int, unsigned int>::iterator it=CaloGenJet.begin();
    it!=CaloGenJet.end(); it++)
  {
    reco::GenJet gjet = GenJetHdl->at(it->first);
    reco::CaloJet jet = CaloJetHdl->at(it->second);
    if (gjet.pt() >= 0 && gjet.pt() < 50) CaloJet_Gen0_50_Pt->Fill(jet.pt());
    if (gjet.pt() >= 50 && gjet.pt() < 80) CaloJet_Gen50_80_Pt->Fill(jet.pt());
    if (gjet.pt() >= 80 && gjet.pt() < 120) CaloJet_Gen80_120_Pt->Fill(jet.pt());
    if (gjet.pt() >= 120 && gjet.pt() < 200) CaloJet_Gen120_200_Pt->Fill(jet.pt());
    if (gjet.pt() >= 200 && gjet.pt() < 500) CaloJet_Gen200_500_Pt->Fill(jet.pt());
    if (gjet.pt() >= 500 && gjet.pt() < 1000) CaloJet_Gen500_1000_Pt->Fill(jet.pt());
  }

  return 1;
}       // -----  end of function PFJetAna::CaloJetAna  -----

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::HasNeutrino
//  Description:  
// ===========================================================================
bool PFAnalyzer::HasNeutrino() const
{
  for(std::vector<reco::GenParticle>::const_iterator it=GenParticleHdl->begin();
    it!=GenParticleHdl->end(); it++)
  {
    if (fabs(it->pdgId()) ==  12  || fabs(it->pdgId()) ==  14  || fabs(it->pdgId()) ==  16)
    {
      if (fabs(it->mother()->pdgId()) == 24)
      {
        return true;
      }
    }
  }
  return false;
}       // -----  end of function PFAnalyzer::HasNeutrino  -----

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::PFMetAna
//  Description:  
// ===========================================================================
int PFAnalyzer::PFMetAna()
{
  for(reco::PFMETCollection::const_iterator it=PFMETHdl->begin();
    it!=PFMETHdl->end(); it++)
  {
    PFMET_Pt->Fill(it->pt());
    PFMET_Px->Fill(it->px());
    PFMET_Py->Fill(it->py());
    PFMET_Phi->Fill(it->phi());
    PFMET_SumEt->Fill(it->sumEt());

    if (isLeptonic)
    {
      Lep_PFMET_Pt->Fill(it->pt());
      Lep_PFMET_Px->Fill(it->px());
      Lep_PFMET_Py->Fill(it->py());
      Lep_PFMET_Phi->Fill(it->phi());
      Lep_PFMET_SumEt->Fill(it->sumEt());
    }
    else
    {
      Had_PFMET_Pt->Fill(it->pt());
      Had_PFMET_Px->Fill(it->px());
      Had_PFMET_Py->Fill(it->py());
      Had_PFMET_Phi->Fill(it->phi());
      Had_PFMET_SumEt->Fill(it->sumEt());
    }

  }

  return 1;
}       // -----  end of function PFAnalyzer::PFMetAna  -----

// ===  FUNCTION  ============================================================
//         Name:  PFMETAna::GenMETAna
//  Description:  
// ===========================================================================
int PFAnalyzer::GenMETAna()
{
  for(unsigned int i=0; i < GenMETHdl->size(); i++)
  {
    reco::GenMET MET = GenMETHdl->at(i);
    GenMET_Pt->Fill(MET.pt());
    GenMET_Px->Fill(MET.px());
    GenMET_Py->Fill(MET.py());
    GenMET_Phi->Fill(MET.phi());
    GenMET_SumEt->Fill(MET.sumEt());
    if (isLeptonic)
    {
      Lep_GenMET_Pt->Fill(MET.pt());
      Lep_GenMET_Px->Fill(MET.px());
      Lep_GenMET_Py->Fill(MET.py());
      Lep_GenMET_Phi->Fill(MET.phi());
      Lep_GenMET_SumEt->Fill(MET.sumEt());
    }
    else
    {
      Had_GenMET_Pt->Fill(MET.pt());
      Had_GenMET_Px->Fill(MET.px());
      Had_GenMET_Py->Fill(MET.py());
      Had_GenMET_Phi->Fill(MET.phi());
      Had_GenMET_SumEt->Fill(MET.sumEt());
    }
  }
  return 1;
}       // -----  end of function PFMETAna::GenMETAna  -----

// ===  FUNCTION  ============================================================
//         Name:  PFMETAna::CaloMETAna
//  Description:  
// ===========================================================================
int PFAnalyzer::CaloMETAna()
{
  for(unsigned int i=0; i < CaloMETHdl->size(); i++)
  {
    reco::CaloMET MET = CaloMETHdl->at(i);
    CaloMET_Pt->Fill(MET.pt());
    CaloMET_Px->Fill(MET.px());
    CaloMET_Py->Fill(MET.py());
    CaloMET_Phi->Fill(MET.phi());
    CaloMET_SumEt->Fill(MET.sumEt());
    if (isLeptonic)
    {
      Lep_CaloMET_Pt->Fill(MET.pt());
      Lep_CaloMET_Px->Fill(MET.px());
      Lep_CaloMET_Py->Fill(MET.py());
      Lep_CaloMET_Phi->Fill(MET.phi());
      Lep_CaloMET_SumEt->Fill(MET.sumEt());
    }
    else
    {
      Had_CaloMET_Pt->Fill(MET.pt());
      Had_CaloMET_Px->Fill(MET.px());
      Had_CaloMET_Py->Fill(MET.py());
      Had_CaloMET_Phi->Fill(MET.phi());
      Had_CaloMET_SumEt->Fill(MET.sumEt());
    }
  }
  return 1;
}       // -----  end of function PFMETAna::CaloMETAna  -----

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::PCaloHitAna
//  Description:  
// ===========================================================================
//int PFAnalyzer::PCaloHitAna() const
//{
  //N_SimCalo->Fill(SimCaloHitHjdl->size());
  //for(unsigned int i=0; i < SimCaloHitHdl->size(); i++)
  //{
    //PCaloHit hit = SimCaloHitHdl->at(i);
    //SimCalo_Eta->Fill(hit.id())
  //}
  //return 1;
//}       // -----  end of function PFAnalyzer::PCaloHitAna  -----

//// ===  FUNCTION  ============================================================
////         Name:  PFAnalyzer::RecHitAna
////  Description:  
//// ===========================================================================
//int PFAnalyzer::RecHitAna() const
//{

  //return 1;
//}       // -----  end of function PFAnalyzer::RecHitAna  -----
//

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::PFRecHitAna
//  Description:  
// ===========================================================================
int PFAnalyzer::PFRecHitAna()
{
  HcalPFRH_N->Fill(HcalPFRecHitHdl->size());

  for(unsigned int i=0; i < HcalPFRecHitHdl->size(); i++)
  {
    reco::PFRecHit pfhit = HcalPFRecHitHdl->at(i);
    HcalDetId cell(pfhit.detId());

    HcalPFRH_iEta->Fill(cell.ieta());
    HcalPFRH_iPhi->Fill(cell.iphi());
    HcalPFRH_Energy->Fill(pfhit.energy());
    HcalPFRH_SumE_Eta->Fill(cell.ieta(), pfhit.energy());
    HcalPFRH_SumE_Phi->Fill(cell.iphi(), pfhit.energy());
    
  }

  return 1;
}       // -----  end of function PFAnalyzer::PFRecHitAna  -----
