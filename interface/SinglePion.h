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

Description: 

Implementation:
<+Notes on implementation+>
*/

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <sstream>

// CMSSW include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"

// CMSSW DataFormats Headers
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/CalibrationResultWrapper.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecTrack.h"
#include "DataFormats/ParticleFlowReco/interface/PFTrajectoryPoint.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElementCluster.h"
#include "DataFormats/Common/interface/Ref.h"

// UserCode Includes
#include "UserCode/PFAnalyzer/interface/HistTool.h"
#include "UserCode/PFAnalyzer/interface/TDCTimeCorr.h"

// ROOT Headers
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

    // ----------member data ---------------------------
    edm::Service<TFileService> fs;


  private:
//----------------------------------------------------------------------------
//  Default functions
//----------------------------------------------------------------------------
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

//----------------------------------------------------------------------------
//  Member data
//----------------------------------------------------------------------------
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Begin Handler ~~~~~
    edm::InputTag GenParticleInputTag_;
    edm::Handle<reco::GenParticleCollection> GenParticleHdl;

    edm::InputTag PFCandidateInputTag_;
    edm::Handle<std::vector<reco::PFCandidate> >  PFCandidateHdl;

    edm::InputTag HbHeRecHitTag_;
    edm::Handle<HBHERecHitCollection>  HbHeRecHitHdl;

    edm::InputTag CaloTowerTag_;
    edm::Handle<edm::SortedCollection<CaloTower,edm::StrictWeakOrdering<CaloTower> > >  CaloTowerHdl;

    edm::InputTag EBRecHitTag_;
    edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > >  EBRecHitHdl;
    edm::InputTag EERecHitTag_;
    edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > >  EERecHitHdl;

    edm::InputTag TracksTag_;
    edm::Handle<std::vector<reco::Track> >  TracksHdl;

    edm::InputTag HcalPFClusterTag_;
    edm::Handle<std::vector<reco::PFCluster> >  HcalPFClusterHdl;
    edm::InputTag EcalPFClusterTag_;
    edm::Handle<std::vector<reco::PFCluster> >  EcalPFClusterHdl;
    
    edm::InputTag PFBlockTag_;
    edm::Handle<std::vector<reco::PFBlock> >  PFBlockHdl;

    edm::InputTag PFTrackTag_;
    edm::Handle<std::vector<reco::PFRecTrack> >  PFTrackHdl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of Handler ~~~~~

    HistTool* hs;
    edm::ESHandle<CaloGeometry> calo;
    double MatchingdR;

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Local members ~~~~~
    // A struct for containing
    struct PionAso {
      reco::GenParticleCollection::const_iterator GenPion;
      std::vector<std::vector<reco::Track>::const_iterator> vTracks;
      std::vector<std::vector<reco::PFCluster>::const_iterator> vHcalPFCluster;
      std::vector<std::vector<reco::PFCluster>::const_iterator> vEcalPFCluster;
      std::vector<edm::SortedCollection<CaloTower>::const_iterator> vCaloTower;
      std::vector<HBHERecHitCollection::const_iterator> vRecHit;
      std::vector<edm::SortedCollection<EcalRecHit>::const_iterator> vEcalRecHit;
      //std::vector<edm::SortedCollection<EcalRecHit>::const_iterator> vEERecHit;

    };				// ----------  end of struct PionAso  ----------

    std::map<unsigned int, PionAso> PionMap;


    std::map<unsigned int, std::list<std::pair<double, unsigned int> > > GenPion_deltaR;
    std::map<unsigned int, std::list<std::pair<double, unsigned int> > > GenPionPFTrack;
    std::map<DetId, edm::SortedCollection<CaloTower>::const_iterator> CaloTowerMap;
    std::map<DetId, HBHERecHitCollection::const_iterator> RecHitMap;
    std::map<unsigned int, unsigned int > PFTrackMap;
    std::vector<std::pair<double, double> > PFTrack2DMap;
    std::vector<double> HCalLCluster;


//----------------------------------------------------------------------------
//  Member Functions
//----------------------------------------------------------------------------
    /// General function to get the input tag from iConfig
    bool GetInputTag(const edm::ParameterSet& iConfig);
    /// General function to get the handler from iEvent
    bool GetHandler(const edm::Event& iEvent);
    /// General function for booking histograms
    bool BookHistogram();
    
    /// Get the Corrected TDC Time from Anton's method
    double GetCorTDCTime(HBHERecHitCollection::const_iterator& recHit, bool timecut=false) const;

    bool HCalTiming(std::vector<unsigned int> CanIdx);
    bool GetHitMapCan(std::vector<unsigned int> CanIdx);
    bool GetHitMapGen( std::vector<unsigned int> GenIdx );
    bool PFClusterRef(reco::PFClusterRef CRef);
    std::vector<unsigned int> FilterPUPion();
    std::map<std::string, double> HcalNoTimeHit(HBHERecHitCollection::const_iterator hcalhit);
    bool GeneralTracks( std::vector<unsigned int> GenIdx );
    bool HcalPFCluster( std::vector<unsigned int> GenIdx );
    bool EcalPFCluster( std::vector<unsigned int> GenIdx );
    std::vector<unsigned int> FilterTurePion(std::vector<unsigned int> GenIdx);
    bool HcalLocalCluster(double cone);
    bool PFTracks( std::vector<unsigned int> GenIdx );

    bool HcalNoTimeHit();
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

