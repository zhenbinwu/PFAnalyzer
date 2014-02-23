// ===========================================================================
// 
//       Filename:  SinglePion.hh
// 
//    Description:  A class for study single pion samples
// 
//        Version:  1.0
//        Created:  02/03/2014 01:51:58 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


/**\class SinglePion

Description: <+one line class summary+>

Implementation:
<+Notes on implementation+>
*/

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/ParticleFlowReco/interface/CalibrationResultWrapper.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "UserCode/PFAnalyzer/interface/HistTool.h"
#include "TH1.h"
#include "TH2.h"
//
// class declaration
//

#ifndef  __EDAnalyzer_SINGLEPION_INC__
#define  __EDAnalyzer_SINGLEPION_INC__

class SinglePion : public edm::EDAnalyzer {
  public:
    explicit SinglePion(const edm::ParameterSet&);
    ~SinglePion();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    bool HCalTiming(std::vector<unsigned int> CanIdx);
    bool GetHitMap(std::vector<unsigned int> CanIdx);
    bool PFClusterRef(reco::PFClusterRef CRef);
    // ----------member data ---------------------------
    edm::Service<TFileService> fs;


  private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    // ----------member data ---------------------------
    std::map<unsigned int, std::list<std::pair<double, unsigned int> > > GenPion_deltaR;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GenParticle ~~~~~
    edm::InputTag GenParticleInputTag_;
    edm::Handle<reco::GenParticleCollection> GenParticleHdl;

    edm::InputTag PFCandidateInputTag_;
    edm::Handle<std::vector<reco::PFCandidate> >  PFCandidateHdl;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RecHit ~~~~~
    edm::InputTag HbHeRecHitTag_;
    edm::Handle<HBHERecHitCollection>  HbHeRecHitHdl;

    edm::InputTag CaloTowerTag_;
    edm::Handle<edm::SortedCollection<CaloTower,edm::StrictWeakOrdering<CaloTower>  > >  CaloTowerHdl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RecHit ~~~~~
    edm::ESHandle<CaloGeometry> calo;
    std::map<DetId, edm::SortedCollection<CaloTower>::const_iterator> CaloTowerMap;
    std::map<DetId, HBHERecHitCollection::const_iterator> RecHitMap;

    HistTool* hs;

    TH1D* HcalTrk;
    //TH1D* HcalTrk_GenPt;
    TH1D* PionEcal;
    TH1D* PionHcal;
    TH1D* PionTrkPt;
    TH1D* PionTrkP;
    TH1D* PionTrkEta;
    TH1D* PionTrkPhi;
    TH1D* PionGen_Pt;
    TH1D* PionGen_Eta;
    TH1D* PionGen_Phi;
    TH1D* PionGenCan_Pt;
    TH1D* PionGenCan_Eta;
    TH1D* PionGenCan_Phi;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//define this as a plug-in
DEFINE_FWK_MODULE(SinglePion);
#endif   // ----- #ifndef __EDAnalyzer_SINGLEPION_INC__  -----

