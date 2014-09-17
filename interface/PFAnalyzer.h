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

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
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
#include "TProfile.h"
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

#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CommonTools/ParticleFlow/interface/PFPileUpAlgo.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
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
    int PCaloHitAna() const;

    // ----------member data ---------------------------
    edm::Service<TFileService> fs;


  protected:
    //int PFJetAna();
    int PFJetAna(const edm::Event& iEvent, const edm::EventSetup& iSetup);
    int CaloJetAna();
    int GenJetAna();
    bool HasNeutrino() const;
    int CaloMETAna();
    int GenMETAna();
    int PFMetAna();
    int PFRecHitAna();
    int PFClusterAna();

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
    edm::InputTag PFJetTag_;
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
    edm::InputTag PFCandidateInputTag_;
    edm::Handle<std::vector<reco::PFCandidate> > PFCandidateHdl;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Begin Handler ~~~~~
    edm::InputTag VertexTag_;
    edm::Handle<std::vector<reco::Vertex> >  VertexHdl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of Handler ~~~~~

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

    PFPileUpAlgo PFPUAlgo;
    bool PFCandidateAna();

    TH1D* Rho_His;
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
    TH1D* PFJetRaw_Pt;
    TH1D* PFJetRaw_Eta;
    TH1D* PFJetRaw_Phi;


    TH1D* CaloJet_Pt;
    TH1D* CaloJet_Eta;
    TH1D* CaloJet_Phi;

    TH1D* GenJet_Pt;
    TH1D* GenJet_Eta;
    TH1D* GenJet_Phi;

    TH1D* GenJet10_Eta;
    TH1D* GenJet20_Eta;
    TH1D* GenJet30_Eta;
    TH1D* GenJet40_Eta;
    TH1D* GenJet50_Eta;

    TH1D* PFJet10_Eta;
    TH1D* PFJet20_Eta;
    TH1D* PFJet30_Eta;
    TH1D* PFJet40_Eta;
    TH1D* PFJet50_Eta;
    TH1D* PFJet80_Eta;
    TH1D* PFJet100_Eta;

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


    TH1D* PFJet_Gen10_20_Pt;
    TH1D* PFJet_Gen20_30_Pt;
    TH1D* PFJet_Gen30_40_Pt;
    TH1D* PFJet_Gen40_50_Pt;
    TH1D* PFJet_Gen50_60_Pt;
    TH1D* PFJet_Gen60_70_Pt;
    TH1D* PFJet_Gen70_80_Pt;
    TH1D* PFJet_Gen80_100_Pt;
    TH1D* PFJet_Gen100_120_Pt;
    TH1D* PFJet_Gen120_150_Pt;
    TH1D* PFJet_Gen150_200_Pt;
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
    //TH1D* N_SimCalo;
    //TH1D* SimCalo_Eta;
    //TH1D* SimCalo_Energy;
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


    TH1D*  N_SimCalo       ;
    TH1D*  SimCalo_iEta    ;
    TH1D*  SimCalo_iPhi    ;
    TH1D*  SimCalo_Energy  ;
    TH1D*  SimCalo_SumE_iEta;
    TH1D*  SimCalo_SumE_iPhi;

    //----------------------------------------------------------------------------
    //  HbHe PFCluster
    //----------------------------------------------------------------------------
    TH1D* HcalPFCL_Size;
    TH1D* HcalPFCL_N;
    //TH1D* HcalPFCL_Nhits;
    TH1D* HcalPFCL_Eta;
    TH1D* HcalPFCL_Phi;
    TH2D* HcalPFCL_EtaPhi_N;
    TH2D* HcalPFCL_EtaPhi_Energy;
    TH2D* HcalPFCL_EtaPhi_Pt;
    TH1D* HcalPFCL_Energy;
    TH1D* HcalPFCL_Pt;
    TH1D* HcalPFCL_SumE_Eta;
    TH1D* HcalPFCL_SumE_Phi;
    TH1D* HcalPFCL_SumPt_Eta;
    TH1D* HcalPFCL_SumPt_Phi;




    TH1D* PFJetG_Eta_M5_M4;
    TH1D* PFJetG_Eta_M4_M3;
    TH1D* PFJetG_Eta_M3_M2;
    TH1D* PFJetG_Eta_M2_M1;
    TH1D* PFJetG_Eta_M1_M0;
    TH1D* PFJetG_Eta_P5_P4;
    TH1D* PFJetG_Eta_P4_P3;
    TH1D* PFJetG_Eta_P3_P2;
    TH1D* PFJetG_Eta_P2_P1;
    TH1D* PFJetG_Eta_P1_P0;















    TH1D* GenJetRes0_Pt;
    TH1D* GenJetRes0_Eta;
    TH1D* GenJetRes0_Phi;
    TH1D* GenJetRes1_Pt;
    TH1D* GenJetRes1_Eta;
    TH1D* GenJetRes1_Phi;
    TH1D* GenJetRes2_Pt;
    TH1D* GenJetRes2_Eta;
    TH1D* GenJetRes2_Phi;
    TH1D* GenJetRes3_Pt;
    TH1D* GenJetRes3_Eta;
    TH1D* GenJetRes3_Phi;
    TH1D* CaloJet_Gen10_20_Pt;
    TH1D* CaloJet_Gen20_30_Pt;
    TH1D* CaloJet_Gen30_40_Pt;
    TH1D* CaloJet_Gen40_50_Pt;
    TH1D* CaloJet_Gen50_60_Pt;
    TH1D* CaloJet_Gen60_70_Pt;
    TH1D* CaloJet_Gen70_80_Pt;
    TH1D* CaloJet_Gen80_100_Pt;
    TH1D* CaloJet_Gen100_120_Pt;
    TH1D* CaloJet_Gen120_150_Pt;
    TH1D* CaloJet_Gen150_200_Pt;
    TH1D* PFJetG_Gen10_20_Pt;
    TH1D* PFJetG_Gen20_30_Pt;
    TH1D* PFJetG_Gen30_40_Pt;
    TH1D* PFJetG_Gen40_50_Pt;
    TH1D* PFJetG_Gen50_60_Pt;
    TH1D* PFJetG_Gen60_70_Pt;
    TH1D* PFJetG_Gen70_80_Pt;
    TH1D* PFJetG_Gen80_100_Pt;
    TH1D* PFJetG_Gen100_120_Pt;
    TH1D* PFJetG_Gen120_150_Pt;
    TH1D* PFJetG_Gen150_200_Pt;
    TH1D* PFJetG_Gen200_500_Pt;
    TH1D* PFJetG_Gen500_1000_Pt;
    TH1D* CaloJetG_Gen10_20_Pt;
    TH1D* CaloJetG_Gen20_30_Pt;
    TH1D* CaloJetG_Gen30_40_Pt;
    TH1D* CaloJetG_Gen40_50_Pt;
    TH1D* CaloJetG_Gen50_60_Pt;
    TH1D* CaloJetG_Gen60_70_Pt;
    TH1D* CaloJetG_Gen70_80_Pt;
    TH1D* CaloJetG_Gen80_100_Pt;
    TH1D* CaloJetG_Gen100_120_Pt;
    TH1D* CaloJetG_Gen120_150_Pt;
    TH1D* CaloJetG_Gen150_200_Pt;
    TH1D* CaloJetG_Gen200_500_Pt;
    TH1D* CaloJetG_Gen500_1000_Pt;
    TH2D* HcalRH_iEtaiPhi;

    TH1D* PFJetG1_Gen10_20_Pt;
    TH1D* PFJetG1_Gen20_30_Pt;
    TH1D* PFJetG1_Gen30_40_Pt;
    TH1D* PFJetG1_Gen40_50_Pt;
    TH1D* PFJetG1_Gen50_60_Pt;
    TH1D* PFJetG1_Gen60_70_Pt;
    TH1D* PFJetG1_Gen70_80_Pt;
    TH1D* PFJetG1_Gen80_100_Pt;
    TH1D* PFJetG1_Gen100_120_Pt;
    TH1D* PFJetG1_Gen120_150_Pt;
    TH1D* PFJetG1_Gen150_200_Pt;
    TH1D* PFJetG1_Gen200_500_Pt;
    TH1D* PFJetG1_Gen500_1000_Pt;

    TH1D* PFJetG2_Gen10_20_Pt;
    TH1D* PFJetG2_Gen20_30_Pt;
    TH1D* PFJetG2_Gen30_40_Pt;
    TH1D* PFJetG2_Gen40_50_Pt;
    TH1D* PFJetG2_Gen50_60_Pt;
    TH1D* PFJetG2_Gen60_70_Pt;
    TH1D* PFJetG2_Gen70_80_Pt;
    TH1D* PFJetG2_Gen80_100_Pt;
    TH1D* PFJetG2_Gen100_120_Pt;
    TH1D* PFJetG2_Gen120_150_Pt;
    TH1D* PFJetG2_Gen150_200_Pt;
    TH1D* PFJetG2_Gen200_500_Pt;
    TH1D* PFJetG2_Gen500_1000_Pt;

    TH1D* PFJetG3_Gen10_20_Pt;
    TH1D* PFJetG3_Gen20_30_Pt;
    TH1D* PFJetG3_Gen30_40_Pt;
    TH1D* PFJetG3_Gen40_50_Pt;
    TH1D* PFJetG3_Gen50_60_Pt;
    TH1D* PFJetG3_Gen60_70_Pt;
    TH1D* PFJetG3_Gen70_80_Pt;
    TH1D* PFJetG3_Gen80_100_Pt;
    TH1D* PFJetG3_Gen100_120_Pt;
    TH1D* PFJetG3_Gen120_150_Pt;
    TH1D* PFJetG3_Gen150_200_Pt;
    TH1D* PFJetG3_Gen200_500_Pt;
    TH1D* PFJetG3_Gen500_1000_Pt;

    TProfile* PFJet_PUCh;
    TProfile* PFJet_LVCh;
    TProfile* PFJet_Ch;
    TProfile* PFJet_Nh;
    TProfile* PFJet_Ele;
    TProfile* PFJet_Muon;
    TProfile* PFJet_Photon;
    TProfile* PFJet_HFEM;
    TProfile* PFJet_HFHad;





    TH1D* PFJetEff_Pt_Numerator ;
    TH1D* PFJetEff_Pt_Deminator ;
    TH1D* PFJetEff_Pt           ;
    TH1D* PFJetEff_Eta_Numerator;
    TH1D* PFJetEff_Eta_Deminator;
    TH1D* PFJetEff_Eta          ;


    TH2D* PFCH_EtaVsNPV;


};

//define this as a plug-in
DEFINE_FWK_MODULE(PFAnalyzer);



