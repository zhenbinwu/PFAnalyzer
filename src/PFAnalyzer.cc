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

  PFJetRes_Pt = fs->make<TH1D>("PFJet_PT", "PF Jet_Pt " ,  100, 0, 1000);
  PFJetRes_Eta =fs->make<TH1D>("PFJet_Eta", "PF Jet Eta", 100, -5, 5);
  PFJetRes_Phi = fs->make<TH1D>("PFJet_Phi", "PF jet Phi", 100, -5, 5);

  GenJet_Pt = fs->make<TH1D>("GenJet_PT", "Gen Jet_Pt " ,  100, 0, 1000);
  GenJet_Eta =fs->make<TH1D>("GenJet_Eta", "Gen Jet Eta", 100, -5, 5);
  GenJet_Phi = fs->make<TH1D>("GenJet_Phi", "Gen jet Phi", 100, -5, 5);

  GenJetRes_Pt = fs->make<TH1D>("GenJet_PT", "Gen Jet_Pt " ,  100, 0, 1000);
  GenJetRes_Eta =fs->make<TH1D>("GenJet_Eta", "Gen Jet Eta", 100, -5, 5);
  GenJetRes_Phi = fs->make<TH1D>("GenJet_Phi", "Gen jet Phi", 100, -5, 5);

  CaloJet_Pt = fs->make<TH1D>("CaloJet_PT", "Calo Jet_Pt " ,  100, 0, 1000);
  CaloJet_Eta =fs->make<TH1D>("CaloJet_Eta", "Calo Jet Eta", 100, -5, 5);
  CaloJet_Phi = fs->make<TH1D>("CaloJet_Phi", "Calo jet Phi", 100, -5, 5);
  // Get all the input tag needed
  PFMET_Pt = fs->make<TH1D>("PFMET_PT", "PF MET_Pt " ,  100, 0, 1000);
  PFMET_Eta =fs->make<TH1D>("PFMET_Eta", "PF MET Eta", 100, -5, 5);
  PFMET_Sig = fs->make<TH1D>("PFMET_Sig", "PF MET Sig", 100, -5, 5);

  GenMET_Pt = fs->make<TH1D>("GenMET_PT", "Gen MET_Pt " ,  100, 0, 1000);
  GenMET_Eta =fs->make<TH1D>("GenMET_Eta", "Gen MET Eta", 100, -5, 5);
  GenMET_Sig = fs->make<TH1D>("GenMET_Sig", "Gen MET Sig", 100, -5, 5);

  CaloMET_Pt = fs->make<TH1D>("CaloMET_PT", "Calo MET_Pt " ,  100, 0, 1000);
  CaloMET_Eta =fs->make<TH1D>("CaloMET_Eta", "Calo MET Eta", 100, -5, 5);
  CaloMET_Sig = fs->make<TH1D>("CaloMET_Sig", "Calo MET Sig", 100, -5, 5);




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

   Handle<reco::TrackCollection> tracks;
   iEvent.getByLabel("generalTracks", tracks); 
   demohisto->Fill(tracks->size());
   //PFJetAna->SetupHandler(pfJetcollection.product());

   if (minTracks_ <= tracks->size())
   {
     LogInfo("Demo") << "number of tracks "<<tracks->size();
   }

  //for (unsigned int i = 0; i < pfJetcollection->size(); ++i)
  //{
    //reco::PFJet j = pfJetcollection->at(i);
    //std::cout << j.energy() << std::endl;
  //}


  PFJetAna();
  GenJetAna();
  CaloJetAna();
  //PFJetAna->Analyze();
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
PFAnalyzer::beginJob(const edm::Event& iEvent)
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
  return 1;
}       // -----  end of function PFAnalyzer::GetHandleByLabel  -----

// ===  FUNCTION  ============================================================
//         Name:  PFAnalyzer::RecHitAna
//  Description:  
// ===========================================================================
int PFAnalyzer::RecHitAna()
{

  //for (HBHERecHitCollection::const_iterator j=HbHeRecHitHdl->begin(); j != HbHeRecHitHdl->end(); j++) {
    //HcalDetId cell(j->id());
    //const CaloCellGeometry* cellGeometry =
      //geometry->getSubdetectorGeometry (cell)->getGeometry (cell) ;
    //double eta  = cellGeometry->getPosition().eta () ;
    //double phi  = cellGeometry->getPosition().phi () ;
    //double zc   = cellGeometry->getPosition().z ();
    //int sub     = cell.subdet();
    //int depth   = cell.depth();
    //int inteta  = cell.ieta();
    //if(inteta > 0) inteta -= 1;
    //int intphi  = cell.iphi()-1;
    //double en   = j->energy();
    //double t    = j->time();
    //int stwd    = j->flags();
    //int auxstwd = j->aux();
  //}

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


  std::vector<reco::GenJet> genjet_temp;
  for(unsigned int i=0; i < GenJetHdl->size(); i++)
  {
    reco::GenJet jet = GenJetHdl->at(i);
    genjet_temp.push_back(jet);
  }

  for(unsigned int i=0; i < PFJetHdl->size(); i++)
  {
    reco::PFJet jet = PFJetHdl->at(i);
    int found = -1;
    for(unsigned int j=0; j < genjet_temp.size(); j++)
    {
      DeltaR<reco::PFJet, reco::GenJet> deltaR;
      reco::GenJet gjet = genjet_temp.at(j);
      //if (jt.p4().DeltaR(gjet.p4()) < 0.3)
      if ( deltaR(jet, gjet) < 0.3)
      {
        PFJetRes_Pt->Fill(jet.pt());
        PFJetRes_Eta->Fill(jet.eta());
        PFJetRes_Phi->Fill(jet.phi());
        GenJetRes_Pt->Fill(gjet.pt());
        GenJetRes_Eta->Fill(gjet.eta());
        GenJetRes_Phi->Fill(gjet.phi());
        found = signed(j);
        break;
      }
    }
    if (found != -1)
    {
      genjet_temp.erase(genjet_temp.begin()+found);
    }
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
  std::cout << " size" << GenJetHdl->size() << std::endl;
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
  std::cout << " size" << CaloJetHdl->size() << std::endl;
  for(reco::CaloJetCollection::const_iterator it=CaloJetHdl->begin();
    it!=CaloJetHdl->end(); it++)
  {
    
    CaloJet_Pt->Fill(it->pt());
    CaloJet_Eta->Fill(it->eta());
    CaloJet_Phi->Fill(it->phi());
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
    PFMET_Pt->Fill(it->sumEt());
    PFMET_Eta->Fill(it->eta());
    PFMET_Sig->Fill(it->mEtSig());
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
    GenMET_Pt->Fill(MET.sumEt());
    GenMET_Eta->Fill(MET.eta());
    GenMET_Sig->Fill(MET.mEtSig());
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
    CaloMET_Pt->Fill(MET.sumEt());
    CaloMET_Eta->Fill(MET.eta());
    CaloMET_Sig->Fill(MET.mEtSig());
  }
  return 1;
}       // -----  end of function PFMETAna::CaloMETAna  -----
