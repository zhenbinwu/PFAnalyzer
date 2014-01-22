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
  BookTH1D("HbheRechit", "Number of HbHeRechit", 1000, 0, 3000);

  // Get all the input tag needed
  GetInputTag(iConfig);

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
   using namespace edm;

   GetHandleByLabel(iEvent);
   Handle<reco::TrackCollection> tracks;
   iEvent.getByLabel("generalTracks", tracks); 
   iEvent.getByLabel("ak8PFJets", pfJetcollection); 
   demohisto->Fill(tracks->size());

   if (minTracks_ <= tracks->size())
   {
     LogInfo("Demo") << "number of tracks "<<tracks->size();
   }

  for (unsigned int i = 0; i < pfJetcollection->size(); ++i)
  {
    reco::PFJet j = pfJetcollection->at(i);
    std::cout << j.energy() << std::endl;
  }
  std::cout<<"Run to \033[0;31m"<<__func__<<"\033[0m at \033[1;36m"<< __FILE__<<"\033[0m, line \033[0;34m"<< __LINE__<<"\033[0m"<< std::endl; 
  for(unsigned int i=0; i < HcalPFRecHitHdl->size(); i++)
  {
    reco::PFRecHit HcalPFRH = HcalPFRecHitHdl->at(i);
    std::cout << HcalPFRH.energy() << std::endl;
  }


}


// ------------ method called once each job just before starting event loop  ------------
void 
PFAnalyzer::beginJob()
{
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
//         Name:  PFAnalyzer::BookTH1D
//  Description:  
// ===========================================================================
bool PFAnalyzer::BookTH1D(std::string name, std::string title, unsigned nbins, double xlow, double xhigh)
{
  Hist1D[name] = fs->make<TH1D>(name.c_str(), title.c_str(), nbins , xlow, xhigh);
  return true;
}       // -----  end of function PFAnalyzer::BookTH1D  -----

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
  return 1;
}       // -----  end of function PFAnalyzer::GetHandleByLabel  -----
