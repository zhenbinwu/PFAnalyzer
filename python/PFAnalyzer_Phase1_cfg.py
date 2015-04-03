import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       '/store/relval/CMSSW_6_2_0_SLHC23_patch1/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH1_1K_FB_V3_2019GEMPU-v5/00000/24362D1B-35A1-E411-B2CB-0025905A60D2.root',
       )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("Phase1_140PU_aged_AK4_SLHC23p1.root"),
      closeFileFast = cms.untracked.bool(True)
  )

## GenJet
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4GenJets = ak5GenJets.clone(rParam = 0.4, jetPtMin= 0.0,
                                      doAreaFastjet=True, src = 'genParticlesForJetsNoNu')

## PFJet
from RecoJets.Configuration.RecoPFJets_cff import *
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True)

## CHSJet
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.ak4PFJetsCHS = ak5PFJetsCHS.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True)

## PuppiJet
from Dummy.Puppi.Puppi_PhaseI_SLHC23p1_v2 import *
process.load('Dummy.Puppi.Puppi_PhaseI_SLHC23p1_v2')
process.ak4PuppiJets = ak5PFJets.clone(rParam = 0.4,  doAreaFastjet=True,
                                       jetPtMin= 0.0, src = cms.InputTag('puppi','Puppi'))


#============================================================================#
#-------------------------------     PFJet     ------------------------------#
#============================================================================#
process.ak4PF = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
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

#============================================================================#
#-----------------------------     PFCHSJet     -----------------------------#
#============================================================================#
process.ak4PFchs = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFchsL1Fastjet"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
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



#============================================================================#
#-----------------------------     PuppiJet     -----------------------------#
#============================================================================#
process.ak4Puppi  = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PuppiJets"),
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




process.ak4GenProducer = cms.Sequence(process.genParticlesForJetsNoNu  * process.ak4GenJets )
process.ak4PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PF )
process.ak4PFCHSProducer = cms.Sequence( process.pfNoPileUpJMESequence * process.ak4PFJetsCHS * process.ak4PFchs)
process.puppiProducer = cms.Sequence(process.puppi * process.ak4PuppiJets * process.ak4Puppi)
process.p = cms.Path(process.ak4GenProducer * process.ak4PFProducer * process.ak4PFCHSProducer * process.puppiProducer)

