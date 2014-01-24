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
#include <list>
#include <map>

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
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/Math/interface/deltaR.h"
//
#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//
// class declaration
//
//

//#include "UserCode/PFAnalyzer/plugins/AnaRecHit.h"
//#include "UserCode/PFAnalyzer/plugins/AnaPFJet.h"

class PFAnalyzer : public edm::EDAnalyzer {
   public:
      explicit PFAnalyzer(const edm::ParameterSet&);
      ~PFAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      //bool BookTH1D(std::string name, std::string title, unsigned nbins, double xlow, double xhigh);
      int RecHitAna();
      int GetInputTag(const edm::ParameterSet& iConfig);
      int GetHandleByLabel(const edm::Event& iEvent);

      // ----------member data ---------------------------
      edm::Service<TFileService> fs;


   protected:
      int PFJetAna();
      int CaloJetAna();
      int GenJetAna();
      bool HasNeutrino() const;
      int CaloMETAna();
      int GenMETAna();
      int PFMetAna();
      int PFRecHitAna();

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      bool isLeptonic;
      //----------------------------------------------------------------------------
      //  Object handler
      //----------------------------------------------------------------------------
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RecHit ~~~~~
      edm::InputTag HbHeRecHitTag_;
      edm::Handle<HBHERecHitCollection>  HbHeRecHitHdl;

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFJet ~~~~~
      edm::InputTag GenJetInputTag_;
      edm::Handle<reco::GenJetCollection> GenJetHdl;

      edm::InputTag PFJetInputTag_;
      edm::Handle<reco::PFJetCollection> PFJetHdl;

      edm::InputTag CaloJetInputTag_;
      edm::Handle<reco::CaloJetCollection> CaloJetHdl;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFMET ~~~~~
      edm::InputTag GenMETInputTag_;
      edm::Handle<reco::GenMETCollection> GenMETHdl;

      edm::InputTag PFMETInputTag_;
      edm::Handle<reco::PFMETCollection> PFMETHdl;

      edm::InputTag CaloMETInputTag_;
      edm::Handle<reco::CaloMETCollection> CaloMETHdl;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GenParticle ~~~~~
      edm::InputTag GenParticleInputTag_;
      edm::Handle<reco::GenParticleCollection> GenParticleHdl;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GenParticle ~~~~~
      edm::InputTag SimCaloHitInputTag_;
      edm::Handle<std::vector<PCaloHit> > SimCaloHitHdl;
      
      //now do what ever initialization is needed
      unsigned int minTracks_;

      //----------------------------------------------------------------------------
      //  Rechit
      //----------------------------------------------------------------------------
      TH1D* demohisto; 
      TH1D* RH_Energy;

      //----------------------------------------------------------------------------
      //  PFJet
      //----------------------------------------------------------------------------

      TH1D* PFJet_Pt;
      TH1D* PFJet_Eta;
      TH1D* PFJet_Phi;
      
      TH1D* CaloJet_Pt;
      TH1D* CaloJet_Eta;
      TH1D* CaloJet_Phi;

      TH1D* GenJet_Pt;
      TH1D* GenJet_Eta;
      TH1D* GenJet_Phi;

      std::map<unsigned int, std::list<std::pair<double, unsigned int> > > PFGenJet_deltaR;
      // GenJet -> PFJet
      std::map<unsigned int, unsigned int> PFGenJet;
      std::map<unsigned int, std::list<std::pair<double, unsigned int> > > CaloGenJet_deltaR;
      // GenJet -> CaloJet
      std::map<unsigned int, unsigned int> CaloGenJet;
      TH1D* PFJetRes_Pt;
      TH1D* PFJetRes_Eta;
      TH1D* PFJetRes_Phi;
      TH1D* GenJetRes_Pt;
      TH1D* GenJetRes_Eta;
      TH1D* GenJetRes_Phi;
      TH1D* CaloJetRes_Pt;
      TH1D* CaloJetRes_Eta;
      TH1D* CaloJetRes_Phi;


      TH1D* PFJet_Gen0_50_Pt;
      TH1D* PFJet_Gen50_80_Pt;
      TH1D* PFJet_Gen80_120_Pt;
      TH1D* PFJet_Gen120_200_Pt;
      TH1D* PFJet_Gen200_500_Pt;
      TH1D* PFJet_Gen500_1000_Pt;

      TH1D* CaloJet_Gen0_50_Pt;
      TH1D* CaloJet_Gen50_80_Pt;
      TH1D* CaloJet_Gen80_120_Pt;
      TH1D* CaloJet_Gen120_200_Pt;
      TH1D* CaloJet_Gen200_500_Pt;
      TH1D* CaloJet_Gen500_1000_Pt;



      //----------------------------------------------------------------------------
      //  MET
      //----------------------------------------------------------------------------

      TH1D* PFMET_Pt;
      TH1D* PFMET_Phi;
      TH1D* PFMET_SumEt;
      TH1D* PFMET_Px;
      TH1D* PFMET_Py;
      
      TH1D* CaloMET_Pt;
      TH1D* CaloMET_Phi;
      TH1D* CaloMET_SumEt;
      TH1D* CaloMET_Px;
      TH1D* CaloMET_Py;

      TH1D* GenMET_Pt;
      TH1D* GenMET_Phi;
      TH1D* GenMET_SumEt;
      TH1D* GenMET_Px;
      TH1D* GenMET_Py;

      TH1D* Lep_PFMET_Pt;
      TH1D* Lep_PFMET_Phi;
      TH1D* Lep_PFMET_SumEt;
      TH1D* Lep_PFMET_Px;
      TH1D* Lep_PFMET_Py;
      
      TH1D* Lep_CaloMET_Pt;
      TH1D* Lep_CaloMET_Phi;
      TH1D* Lep_CaloMET_SumEt;
      TH1D* Lep_CaloMET_Px;
      TH1D* Lep_CaloMET_Py;

      TH1D* Lep_GenMET_Pt;
      TH1D* Lep_GenMET_Phi;
      TH1D* Lep_GenMET_SumEt;
      TH1D* Lep_GenMET_Px;
      TH1D* Lep_GenMET_Py;


      TH1D* Had_PFMET_Pt;
      TH1D* Had_PFMET_Phi;
      TH1D* Had_PFMET_SumEt;
      TH1D* Had_PFMET_Px;
      TH1D* Had_PFMET_Py;
      
      TH1D* Had_CaloMET_Pt;
      TH1D* Had_CaloMET_Phi;
      TH1D* Had_CaloMET_SumEt;
      TH1D* Had_CaloMET_Px;
      TH1D* Had_CaloMET_Py;

      TH1D* Had_GenMET_Pt;
      TH1D* Had_GenMET_Phi;
      TH1D* Had_GenMET_SumEt;
      TH1D* Had_GenMET_Px;
      TH1D* Had_GenMET_Py;


//----------------------------------------------------------------------------
//  Sim Calo Hit
//----------------------------------------------------------------------------
      TH1D* N_SimCalo;
      TH1D* SimCalo_Eta;
      TH1D* SimCalo_Energy;
      //AnaRecHit *RecHitAna;
      //AnaPFJet *PFJetAna;
//----------------------------------------------------------------------------
//  HbHe Rechit
//----------------------------------------------------------------------------
      TH1D* HcalRH_N;
      TH1D* HcalRH_iEta;
      TH1D* HcalRH_iPhi;
      TH2D* HcalRH_iEtaPhi;
      TH1D* HcalRH_Energy;
      TH1D* HcalRH_SumE_Eta;
      TH1D* HcalRH_SumE_Phi;

//----------------------------------------------------------------------------
//  HbHe PFRechit
//----------------------------------------------------------------------------
      TH1D* HcalPFRH_N;
      TH1D* HcalPFRH_iEta;
      TH1D* HcalPFRH_iPhi;
      TH2D* HcalPFRH_iEtaPhi;
      TH1D* HcalPFRH_Energy;
      TH1D* HcalPFRH_SumE_Eta;
      TH1D* HcalPFRH_SumE_Phi;

};

//define this as a plug-in
DEFINE_FWK_MODULE(PFAnalyzer);
