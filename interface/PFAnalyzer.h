// ===========================================================================
// 
//       Filename:  PFAnalyzer.h
// 
//    Description:  A EDAnalyzer aim for the particle flow study
// 
//        Version:  1.0
//        Created:  01/16/2014 09:50:43 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CMS@FNAL
// 
// ===========================================================================

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/SortedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHit.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFSuperCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
//
// class declaration
//

class PFAnalyzer : public edm::EDAnalyzer {
   public:
      explicit PFAnalyzer(const edm::ParameterSet&);
      ~PFAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      bool BookTH1D(std::string name, std::string title, unsigned nbins, double xlow, double xhigh);
      int GetInputTag(const edm::ParameterSet& iConfig);
      int GetHandleByLabel(const edm::Event& iEvent);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      //----------------------------------------------------------------------------
      //  Object handler
      //----------------------------------------------------------------------------
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RecHit ~~~~~
      edm::InputTag HbHeRecHitTag_;
      edm::Handle<edm::SortedCollection<HBHERecHit,edm::StrictWeakOrdering<HBHERecHit> > >  HbHeRecHitHdl;

      edm::InputTag HfRecHitTag_;
      edm::Handle<edm::SortedCollection<HFRecHit,edm::StrictWeakOrdering<HFRecHit> > >  HfRecHitHdl;

      edm::InputTag HoRecHitTag_;
      edm::Handle<edm::SortedCollection<HORecHit,edm::StrictWeakOrdering<HORecHit> > >  HoRecHitHdl;


      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFRecHit ~~~~~
      edm::InputTag EcalPFRecHitTag_;
      edm::Handle<std::vector<reco::PFRecHit> >  EcalPFRecHitHdl;

      edm::InputTag HcalPFRecHitTag_;
      edm::Handle<std::vector<reco::PFRecHit> >  HcalPFRecHitHdl;

      edm::InputTag HOPFRecHitTag_;
      edm::Handle<std::vector<reco::PFRecHit> >  HOPFRecHitHdl;

      edm::InputTag PSPFRecHitTag_;
      edm::Handle<std::vector<reco::PFRecHit> >  PSPFRecHitHdl;
      
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFCluster ~~~~~
      edm::InputTag EcalPFClusterTag_;
      edm::Handle<std::vector<reco::PFCluster> >  EcalPFClusterHdl;

      edm::InputTag HcalPFClusterTag_;
      edm::Handle<std::vector<reco::PFCluster> >  HcalPFClusterHdl;

      edm::InputTag HOPFClusterTag_;
      edm::Handle<std::vector<reco::PFCluster> >  HOPFClusterHdl;

      edm::InputTag PSPFClusterTag_;
      edm::Handle<std::vector<reco::PFCluster> >  PSPFClusterHdl;

      edm::InputTag pfJetInputTag_;
      edm::Handle<reco::PFJetCollection> pfJetcollection;
      
      //now do what ever initialization is needed
      edm::Service<TFileService> fs;
      unsigned int minTracks_;
      std::map<std::string, TH1*> Hist1D;
      TH1D* demohisto; 
};

//define this as a plug-in
DEFINE_FWK_MODULE(PFAnalyzer);
