// ===========================================================================
// 
//       Filename:  METPerformance.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/08/2015 04:26:52 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


/**\class METPerformance

Description: <+one line class summary+>

Implementation:
<+Notes on implementation+>
*/

#ifndef  __EDAnalyzer_METPERFORMANCE_INC__
#define  __EDAnalyzer_METPERFORMANCE_INC__

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <set>

// Include ROOT
#include "TH2D.h"
#include "TH1D.h"
#include "TLorentzVector.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/MuonReco/interface/Muon.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "DataFormats/Math/interface/deltaR.h"
//
// class declaration
//

class METPerformance : public edm::EDAnalyzer {
  public:
    explicit METPerformance(const edm::ParameterSet&);
    ~METPerformance();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


  private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    bool GetInputTag(const edm::ParameterSet& iConfig);
    bool GetHandleByLabel(const edm::Event& iEvent);
    bool IsDiMuon() const;
    bool BookHistogram();
    TLorentzVector GetRecoZ();

    bool SlimJet(reco::PFJet jet);
    int GetNPU() const;
    bool PassZCut() const;
    bool RecoEvent();
    std::vector<reco::PFJet> GetRawJets();
    std::vector<TLorentzVector> GetCorrectedJets();
    double GetCorrFactor( FactorizedJetCorrector *JetCorrector, reco::PFJet &jet, double rho);
    bool FillMETPerf();
    bool RecoEventGen();
    // ----------member data ---------------------------
    edm::InputTag MuonInputTag_;
    edm::Handle<std::vector<reco::Muon> > MuonHdl;

    edm::InputTag PFJetInputTag_;
    edm::Handle<reco::PFJetCollection> PFJetHdl;

    edm::InputTag GenJetInputTag_;
    edm::Handle<reco::GenJetCollection> GenJetHdl;

    edm::InputTag srcRhoInputTag_;
    edm::Handle<double> srcRhoHdl;

    edm::InputTag PileUpInfoTag_;
    edm::Handle<std::vector<PileupSummaryInfo> >  PileUpInfoHdl;

    edm::InputTag PFMETInputTag_;
    edm::Handle<reco::PFMETCollection> PFMETHdl;
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of Handler ~~~~~

    std::string L1JECTag_;
    std::string L2JECTag_;
    std::string L3JECTag_;
    double JetJECThres;
    double JetEtaThres;
    int NPU;
    bool UseGenJets;
    bool JetsMatchedGen;

    edm::Service<TFileService> fs;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Local Variable ~~~~~
    std::vector<reco::PFJet> RawJets;
    /// Jet correction factor L1L2L3 - L1
    std::vector<TLorentzVector> JetsType1;
    TLorentzVector RecoZ;
    TVector2 MET;
    TLorentzVector Recoil;
    double SumEt;
    double UnCluSumET;
    double Parrallel;
    double Perpendicular;
    double HT;
    double EC_HT;
    double BB_HT;
    double FW_HT;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Plots ~~~~~
    //Reconstructed Z
    TH1D* hZMass;
    TH1D* hZPT;
    TH1D* hZEta;
    TH1D* hZPhi;

    TH1D* hJetPT;
    TH1D* hJetEta;

    //Reconstructed MET
    TH1D* hMETPT;
    TH1D* hMETPhi;
    TH1D* hMETx;
    TH1D* hMETy;
    TH1D* h20METPT;
    TH1D* h20METPhi;
    TH1D* h20METx;
    TH1D* h20METy;


    TH1D* h40METPT;
    TH1D* h40METPhi;
    TH1D* h40METx;
    TH1D* h40METy;

    TH1D* hlogSumET;
    TH1D* hMETSig;
    TH1D* hSumET;
    TH1D* hSumET1;
    TH1D* hSumET5;
    TH1D* hSumET10;
    TH1D* hSumET30;
    TH1D* hUnCluSumET;
    TH1D* hHT;
    TH1D* hBB_HT;
    TH1D* hEC_HT;
    TH1D* hFW_HT;

    //Recoil 
    TH1D* hRecoilPT;
    TH1D* hParrallel;
    TH1D* hPerpendicular;
    TH1D* hParrallelZPT;

    TH2D* h2D_Parrallel;
    TH2D* h2D_ParrallelZpt;
    TH2D* h2D_Perperndicular;
    TH2D* h2D_SumET_Zpt;

    TH2D* h2D_JetEta_JetPT;
    TH2D* h2D_METx_SumET;
    TH2D* h2D_METy_SumET;

    TH2D* h2D_METx_BBHT;
    TH2D* h2D_METy_BBHT;
    TH2D* h2D_METx_ECHT;
    TH2D* h2D_METy_ECHT;
    TH2D* h2D_METx_FWHT;
    TH2D* h2D_METy_FWHT;

    TH2D* h2D_METx_NPU;
    TH2D* h2D_METy_NPU;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//define this as a plug-in
DEFINE_FWK_MODULE(METPerformance);
#endif   // ----- #ifndef __EDAnalyzer_METPERFORMANCE_INC__  -----

