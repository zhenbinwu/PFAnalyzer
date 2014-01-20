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


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
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
int PFAnalyzer::GetConfigFlag() const
{
  

}       // -----  end of function PFAnalyzer::GetConfigFlag  -----
