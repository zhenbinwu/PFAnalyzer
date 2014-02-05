import FWCore.ParameterSet.Config as cms

from JetMETCorrections.Configuration.DefaultJEC_cff import *
ak5PFchsL1Fastjet  = ak5PFL1Fastjet.clone ( algorithm = cms.string('AK5PFchs') )

PFAnalyzer = cms.EDAnalyzer('PFAnalyzer',
                            minTracks = cms.untracked.uint32(1000),
                            #HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                            HbHeRecHitTag = cms.InputTag("hbhereco"),
                            HfRecHitTag = cms.InputTag("hfreco"),
                            #HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                            HoRecHitTag = cms.InputTag("horeco"),
                            EcalPFRecHitTag = cms.InputTag("particleFlowRecHitECAL"),
                            HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHCAL", "Cleaned"),
                            HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO"),
                            PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                            EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                            HcalPFClusterTag = cms.InputTag("particleFlowClusterHCAL"),
                            HOPFClusterTag = cms.InputTag("particleFlowClusterHO"),
                            PSPFClusterTag = cms.InputTag("particleFlowClusterPS"),
                            PFJetInputTag = cms.InputTag("ak5PFJetsCHS"),
                            #PFJetInputTag = cms.InputTag("ak5PFJets"),
                            GenJetInputTag = cms.InputTag("ak5GenJets"),
                            CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                            PFMETInputTag = cms.InputTag("pfMet"),
                            GenMETInputTag = cms.InputTag("genMetTrue"),
                            CaloMETInputTag = cms.InputTag("met"),
                            GenParticleInputTag = cms.InputTag("genParticles"),
                            SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ), 
                            #minTracks = cms.untracked.uint32(1000)
                           )



