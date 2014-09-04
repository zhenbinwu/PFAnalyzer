import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("UserCode.PFAnalyzer.PFAnalyzer_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/02BBEBC6-A00E-E411-91CD-002618943866.root'

      ###  Calo
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/4A96278E-840E-E411-B53E-00261894397A.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/00AB1998-860E-E411-911B-0026189438F9.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/02BBEBC6-A00E-E411-91CD-002618943866.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/10B0AB58-880E-E411-84C9-002618943856.root'
      ## 3D
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/008EFFA6-E50E-E411-88AF-003048FFD732.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/08062A32-970E-E411-AB5F-0026189438B8.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/0CBC12D7-7C0E-E411-8E22-0025905A60B0.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/20010B66-970E-E411-B815-002618943865.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/280C269F-670E-E411-A1AD-0025905B858E.root'

       ### SLHC16 Phase2

      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/28523C0F-F518-E411-ACA3-0025905A60B4.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/386A660F-D518-E411-967D-0025905A612E.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/3ADC9932-3219-E411-B1CF-0025905B8582.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/66B4D9DB-FE18-E411-A60F-003048FFCB96.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/886717F5-EB18-E411-9B0D-00248C55CC40.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/A40A18BC-E218-E411-B767-0025905A60C6.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/DA6AE2CD-E818-E411-A6BF-0025905A60E4.root'

     ### SLHC16 Phase I 50PU NoAge

        'file:/data/nbay04/c/benwu/JetMET_TP/SLHC17/QCD_SHCAL_age1k_140PU.root'
       )

     #fileNames = cms.untracked.vstring('root://xrootd.unl.edu//store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/02BBEBC6-A00E-E411-91CD-002618943866.root')
                            ,
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("Shaslik_140PU_aged_AK4.root"),
      closeFileFast = cms.untracked.bool(True)
  )
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'PH2_1K_FB_V4::All'

from JetMETCorrections.Configuration.DefaultJEC_cff import *
from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
from RecoJets.Configuration.RecoPFJets_cff import *
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4 )
process.ak4GenJets = ak5GenJets.clone(rParam = 0.4)
process.ak4PFJetsCHS = ak5PFJetsCHS.clone(rParam = 0.4)

process.ak5PFchsL1 = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFchsL1Fastjet"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHCAL", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                             #PFJetInputTag = cms.InputTag("ak5PFJetsCHS"),
                             #PFJetInputTag = cms.InputTag("ak5PFJets"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )

process.ak5PFL1 = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHCAL", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PFJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )

#process.ak5PFL1Fastjet = process.ak5PFchsL1.clone( PFJetTag = cms.InputTag("ak5PFJetsL1Fast") )

process.Jet4Producer = cms.Sequence(process.pfNoPileUpJMESequence * process.genParticlesForJets * process.ak4PFJets * process.ak4PFJetsCHS *process.ak4GenJets)
process.p = cms.Path(process.Jet4Producer * process.ak5PFL1 * process.ak5PFchsL1 )
#process.p = cms.Path(process.ak5PFchsL1 * process.ak5PFL1 )
##process.p = cms.Path(process.ak5PFchsL1 *process.ak5PFL1Fastjet)

