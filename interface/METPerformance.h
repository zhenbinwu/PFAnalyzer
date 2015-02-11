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

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

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

    // ----------member data ---------------------------
    edm::InputTag MuonInputTag_;
    edm::Handle<std::vector<reco::Muon> > MuonHdl;

    edm::InputTag PFJetInputTag_;
    edm::Handle<reco::PFJetCollection> PFJetHdl;

    edm::InputTag srcRhoInputTag_;
    edm::Handle<double> srcRhoHdl;

    std::string L1JECTag_;
    std::string L2JECTag_;
    std::string L3JECTag_;

    edm::Service<TFileService> fs;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Local Variable ~~~~~
    TLorentzVector RecoZ;
    TLorentzVector MET;
    TLorentzVector Recoil;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Plots ~~~~~
    //Reconstructed Z
    TH1D ZMass;
    TH1D ZPT;
    TH1D ZEta;
    TH1D ZPhi;

    //Reconstructed MET
    TH1D MET;
    TH1D METPhi;
    TH1D METx;
    TH1D METy;
    TH1D SumET;
    TH1D SumHT;
    TH1D METSig;

    //Recoil 
    TH1D RecoilPT;
    TH1D Parrallel;



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

