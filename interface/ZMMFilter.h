// ===========================================================================
// 
//       Filename:  ZMMFilter.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/08/2015 04:24:55 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================

/**\class ZMMFilter

Description: <+one line class summary+>

Implementation:
<+Notes on implementation+>
*/

#ifndef  __EDProducer_ZMMFILTER_INC__
#define  __EDProducer_ZMMFILTER_INC__

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/Math/interface/deltaR.h"
//
// class declaration
//

class ZMMFilter : public edm::EDProducer {
  public:
    explicit ZMMFilter(const edm::ParameterSet&);
    ~ZMMFilter();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
    virtual void beginJob() ;
    virtual void produce(edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;

    virtual void beginRun(edm::Run&, edm::EventSetup const&);
    virtual void endRun(edm::Run&, edm::EventSetup const&);
    virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
    virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

    bool passTightMuon(reco::Muon &muon) const;
    double ComputeMuonIsolation(reco::Muon &mu) const;
    std::map<std::string, double> CheckMuonPV(reco::Muon &muon) const;

    std::vector<reco::Muon> GetTightMuons() const;
    std::vector<reco::PFCandidate> GetPFCandidatesNoMuon(const std::vector<reco::Muon> &ZMMTightMuon) const;
    // ----------member data ---------------------------
    edm::InputTag PFCandidateInputTag_;
    edm::Handle<std::vector<reco::PFCandidate> > PFCandidateHdl;

    edm::InputTag MuonInputTag_;
    edm::Handle<std::vector<reco::Muon> > MuonHdl;

    edm::InputTag VertexTag_;
    edm::Handle<std::vector<reco::Vertex> >  VertexHdl;

    edm::InputTag TrackTag_;
    edm::Handle<std::vector<reco::Track> >  TrackHdl;

    DeltaR<reco::PFCandidate, reco::Muon> deltaR;

};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//define this as a plug-in
DEFINE_FWK_MODULE(ZMMFilter);
#endif   // ----- #ifndef __EDProducer_ZMMFILTER_INC__  -----

