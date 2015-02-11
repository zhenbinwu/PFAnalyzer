// ===========================================================================
// 
//       Filename:  ZMMFilter.cc
// 
//    Description:  Removing Z->MM from the PFcandidate list
// 
//        Version:  1.0
//        Created:  02/08/2015 04:24:13 PM
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


#include "UserCode/PFAnalyzer/interface/ZMMFilter.h"

//
// constructors and destructor
//
ZMMFilter::ZMMFilter(const edm::ParameterSet& iConfig)
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
  produces<std::vector<reco::PFCandidate> >("PFCandidatesNoMuon").setBranchAlias("PFCadidatesNoMuon");
  produces<std::vector<reco::Muon> >("ZMMTightMuon").setBranchAlias("ZMMTightMuon");
  PFCandidateInputTag_ =iConfig.getParameter<edm::InputTag>("PFCandidateInputTag");
  MuonInputTag_ = iConfig.getParameter<edm::InputTag>("MuonTag");
  VertexTag_ = iConfig.getParameter<edm::InputTag>("VertexTag");
  TrackTag_ = iConfig.getParameter<edm::InputTag>("TrackTag");
}


ZMMFilter::~ZMMFilter()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
  void
ZMMFilter::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
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

   iEvent.getByLabel(PFCandidateInputTag_, PFCandidateHdl); 
   assert(PFCandidateHdl.isValid());

   iEvent.getByLabel(MuonInputTag_, MuonHdl); 
   assert(MuonHdl.isValid());

   iEvent.getByLabel(VertexTag_, VertexHdl); 
   assert(VertexHdl.isValid());

   iEvent.getByLabel(TrackTag_, TrackHdl); 
   assert(TrackHdl.isValid());
   
   std::auto_ptr<std::vector<reco::Muon> > ZMMTightMuon(new std::vector<reco::Muon>);
   std::vector<reco::Muon> tempMuon = GetTightMuons();
   *ZMMTightMuon.get() = tempMuon;
   iEvent.put(ZMMTightMuon, "ZMMTightMuon");

   std::auto_ptr<std::vector<reco::PFCandidate> > PFCandidatesNoMuon(new std::vector<reco::PFCandidate>);
   *PFCandidatesNoMuon.get() = GetPFCandidatesNoMuon(tempMuon);
   iEvent.put(PFCandidatesNoMuon, "PFCandidatesNoMuon");
}

// ------------ method called once each job just before starting event loop  ------------
  void 
ZMMFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ZMMFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
  void 
ZMMFilter::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
  void 
ZMMFilter::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
  void 
ZMMFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
  void 
ZMMFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
  void
ZMMFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ===  FUNCTION  ============================================================
//         Name:  ZMMFilter::passTightMuon
//  Description:  Tight Muon definition from Bacon
// ===========================================================================
bool ZMMFilter::passTightMuon(reco::Muon &muon) const
{
  //if(!(iMuon->typeBits & kGlobal))  return false;
  if(! muon.isGlobalMuon())  return false;
  //if(!(iMuon->typeBits & kPFMuon))  return false;
  if(! muon.isPFMuon()) return false;
  if(! muon.innerTrack().isNonnull()) return false;

  //if(iMuon->muNchi2        > 10)    return false;
  if(muon.globalTrack()->normalizedChi2() > 10)    return false;
  //if(iMuon->nValidHits     < 1)     return false;
  if (muon.globalTrack()->hitPattern().numberOfValidMuonHits()   < 1)  return false;
  //if(iMuon->nMatchStn      < 2)     return false;
  if (muon.numberOfMatchedStations() < 2) return false;
  //if(iMuon->nPixHits       < 1)     return false;
  if (muon.innerTrack()->hitPattern().numberOfValidPixelHits() <1 ) return false;
  //if(iMuon->nTkLayers      < 6)     return false;
  if (muon.innerTrack()->hitPattern().trackerLayersWithMeasurement()  < 6) return false;

  std::map<std::string, double> pvMap = CheckMuonPV(muon);
  if(fabs(pvMap["dz"])  > 0.2)        return false;
  if(fabs(pvMap["d0"])  > 0.045)      return false;

  // Isolation: checking with Muon POG: DeltaBeta Isolation
  double totalIso =  ComputeMuonIsolation(muon);
  if(totalIso/muon.pt() > 0.20) return false; //tight cut 0.12, loost cut 0.20 
  return true;

}       // -----  end of function ZMMFilter::passTightMuon  -----

// ===  FUNCTION  ============================================================
//         Name:  ZMMFilter::ComputeMuonIsolation
//  Description:  Using deltaBeta isolation as suggested by Muon POG
// Muon PF isolation with delta-beta PU correction:
// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation
// Code is taken from : // https://github.com/cms-sw/cmssw/blob/2773aeba7f5bd5522d831d2b84fa36b0bc6c8216/PhysicsTools/Heppy/python/analyzers/objects/LeptonAnalyzer.py 
// ===========================================================================
double ZMMFilter::ComputeMuonIsolation(reco::Muon &mu) const
{
  double isolation = -1;
  // rhoArea (Not yet full defined IMO )
  //isolation = (mu.pfIsolationR04().sumChargedHadronPt + max( mu.pfIsolationR04().sumNeutralHadronEt + mu.pfIsolationR04().sumPhotonEt - mu.rho * mu.EffectiveArea04,0.0))

  isolation = (mu.pfIsolationR04().sumChargedHadronPt + std::max( mu.pfIsolationR04().sumNeutralHadronEt + mu.pfIsolationR04().sumPhotonEt - mu.pfIsolationR04().sumPUPt/2, float(0.0)));
  return isolation;
}       // -----  end of function ZMMFilter::ComputeMuonIsolation  -----

// ===  FUNCTION  ============================================================
//         Name:  ZMMFilter::CheckMuonPV
//  Description:  
// =========================================================================== 
std::map<std::string, double> ZMMFilter::CheckMuonPV(reco::Muon &muon) const
{
  // Use tracker track if available, otherwise use STA track
  const reco::TrackRef muTrack = muon.innerTrack().isNonnull() ? muon.innerTrack() : muon.standAloneMuon();
  const reco::Vertex pv = VertexHdl->at(0);
  //
  // Impact Parameter
  //==============================
  double d0 = -muTrack->dxy(pv.position());  // note: d0 = -dxy
  double dz =  muTrack->dz(pv.position());
  std::map<std::string, double> reMap;

  reMap["d0"] = d0;
  reMap["dz"] = dz;
  return reMap;
}       // -----  end of function ZMMFilter::CheckMuonPV  -----

// ===  FUNCTION  ============================================================
//         Name:  ZMMFilter::GetTightMuons
//  Description:  
// ===========================================================================
std::vector<reco::Muon> ZMMFilter::GetTightMuons() const
{
  std::vector<reco::Muon> temp;
  for(unsigned int i=0; i < MuonHdl->size(); ++i)
  {
    reco::Muon muon = MuonHdl->at(i);
    if (passTightMuon(muon))
      temp.push_back(muon);
  }

  return temp;
}       // -----  end of function ZMMFilter::GetTightMuons  -----

// ===  FUNCTION  ============================================================
//         Name:  ZMMFilter::GetPFCandidatesNoMuon
//  Description:  
// ===========================================================================
std::vector<reco::PFCandidate> ZMMFilter::GetPFCandidatesNoMuon(const std::vector<reco::Muon> &ZMMTightMuon) const
{
  std::vector<reco::PFCandidate> temp;
  unsigned int matchcount = 0;
  for(unsigned int i=0; i < PFCandidateHdl->size(); ++i)
  {
    reco::PFCandidate can = PFCandidateHdl->at(i);

    bool lMatch = false;
    for(unsigned int j=0; j < ZMMTightMuon.size(); ++j)
    {
      reco::Muon muon = ZMMTightMuon.at(j);
      double delR = deltaR(can, muon);
      if (delR > 0.05 ) continue;
      if (fabs(can.pt() - muon.pt()) > 0.1) continue;
      lMatch= true;
      matchcount ++ ;
    }
    if (!lMatch)
    {
      temp.push_back(can);
    }
  }
  assert(matchcount == ZMMTightMuon.size());
  assert( PFCandidateHdl->size() - temp.size() == matchcount);

  return temp;
}       // -----  end of function ZMMFilter::GetPFCandidatesNoMuon  -----


