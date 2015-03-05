// ===========================================================================
// 
//       Filename:  JetPerformance.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/08/2015 04:22:20 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


/**\class JetPerformance

Description: <+one line class summary+>

Implementation:
<+Notes on implementation+>
*/

#ifndef  __EDAnalyzer_JETPERFORMANCE_INC__
#define  __EDAnalyzer_JETPERFORMANCE_INC__

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>

// Root include files
#include "TH2D.h"
#include "TH1D.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
//
// class declaration
//

class JetPerformance : public edm::EDAnalyzer {
  public:
    explicit JetPerformance(const edm::ParameterSet&);
    ~JetPerformance();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


  private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    bool GetHandleByLabel(const edm::Event& iEvent);
    bool GetInputTag(const edm::ParameterSet& iConfig);
    bool JetMatching();
    std::vector<reco::PFJet> GetCorrectedJets();
    bool CleanPerEvent();
    bool BookHistogram();
    bool JetPTMassPerf();
    double GetCorrFactor( FactorizedJetCorrector *JetCorrector, reco::PFJet &jet, double rho);
    bool JetEffRate();
    // ----------member data ---------------------------
    edm::InputTag GenJetInputTag_;
    edm::Handle<reco::GenJetCollection> GenJetHdl;

    edm::InputTag PFJetInputTag_;
    edm::Handle<reco::PFJetCollection> PFJetHdl;

    edm::InputTag PileupInputTag_;
    edm::Handle<std::vector<PileupSummaryInfo> > PileupHdl;

    edm::InputTag srcRhoInputTag_;
    edm::Handle<double> srcRhoHdl;

    std::string L1JECTag_;
    std::string L2JECTag_;
    std::string L3JECTag_;

    edm::Service<TFileService> fs;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Local Variables ~~~~~
    std::vector<reco::PFJet> CorredJets;
    DeltaR<reco::PFJet, reco::GenJet> deltaR;
    std::map<unsigned int, std::list<std::pair<double, unsigned int> > > PFGenJet_deltaR;
    // GenJet -> PFJet
    std::map<unsigned int, unsigned int> PFGenJet;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Plots ~~~~~
    // Jet response and resolution
    TH2D* JetPTPerf;
    TH2D* JetPTPerf_BB;
    TH2D* JetPTPerf_EC;
    TH2D* JetPTPerf_FW;
    TH2D* JetPTPerf_NPU_LowBB;
    TH2D* JetPTPerf_NPU_LowEC;
    TH2D* JetPTPerf_NPU_LowFW;
    TH2D* JetMassPerf;
    TH2D* JetMassPerf_BB;
    TH2D* JetMassPerf_EC;
    TH2D* JetMassPerf_FW;


    // Jet Efficiency 
    TH1D* PFJetEff_Pt_Numerator ;
    TH1D* PFJetEff_Pt_Deminator ;
    TH1D* PFJetEff_PtBB_Numerator ;
    TH1D* PFJetEff_PtBB_Deminator ;
    TH1D* PFJetEff_PtEC_Numerator ;
    TH1D* PFJetEff_PtEC_Deminator ;
    TH1D* PFJetEff_PtFW_Numerator ;
    TH1D* PFJetEff_PtFW_Deminator ;
    TH1D* PFJetEff_Eta_Numerator;
    TH1D* PFJetEff_Eta_Deminator;

    // Jet PU Rate
    TH1D* PFJetRate_Pt_Numerator ;
    TH1D* PFJetRate_Pt_Deminator ;
    TH1D* PFJetRate_PtBB_Numerator ;
    TH1D* PFJetRate_PtBB_Deminator ;
    TH1D* PFJetRate_PtEC_Numerator ;
    TH1D* PFJetRate_PtEC_Deminator ;
    TH1D* PFJetRate_PtFW_Numerator ;
    TH1D* PFJetRate_PtFW_Deminator ;
    TH1D* PFJetRate_Eta_Numerator;
    TH1D* PFJetRate_Eta_Deminator;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//define this as a plug-in
DEFINE_FWK_MODULE(JetPerformance);
#endif   // ----- #ifndef __EDAnalyzer_JETPERFORMANCE_INC__  -----

