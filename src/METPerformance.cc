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
  //register your products
  /* Examples
     produces<ExampleData2>();

  //if do put with a label
  produces<ExampleData2>("label");

  //if you want to put into the Run
  produces<ExampleData2,InRun>();
  */
  //now do what ever other initialization is needed

}


METPerformance::~METPerformance()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
  void
METPerformance::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  /* This is an event example
  //Read 'ExampleData' from the Event
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);

  //Use the ExampleData to create an ExampleData2 which 
  // is put into the Event
  std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
  iEvent.put(pOut);
  */

  /* this is an EventSetup example
  //Read SetupData from the SetupRecord in the EventSetup
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
  */

}

// ------------ method called once each job just before starting event loop  ------------
  void 
METPerformance::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
METPerformance::endJob() {
}

// ------------ method called when starting to processes a run  ------------
  void 
METPerformance::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
  void 
METPerformance::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
  void 
METPerformance::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
  void 
METPerformance::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
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
//         Name:  METPerformance::ClearPerEvent
//  Description:  
// ===========================================================================
bool METPerformance::ClearPerEvent()
{
  return true;
}       // -----  end of function METPerformance::ClearPerEvent  -----

// ===  FUNCTION  ============================================================
//         Name:  METPerformance::RecoZ
//  Description:  
// ===========================================================================
TLorentzVector METPerformance::RecoZ() 
{

  

  return true;
}       // -----  end of function METPerformance::RecoZ  -----
