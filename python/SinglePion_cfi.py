import FWCore.ParameterSet.Config as cms

SinglePion = cms.EDAnalyzer('SinglePion',
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
                            TracksTag = cms.InputTag("generalTracks"),
                            #PFJetInputTag = cms.InputTag("ak5PFJets"),
                            CaloTowerTag = cms.InputTag("towerMaker"),
                            GenJetInputTag = cms.InputTag("ak5GenJets"),
                            CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                            PFMETInputTag = cms.InputTag("pfMet"),
                            GenMETInputTag = cms.InputTag("genMetTrue"),
                            CaloMETInputTag = cms.InputTag("met"),
                            GenParticleInputTag = cms.InputTag("genParticles"),
                            PFCandidateInputTag = cms.InputTag("particleFlow"),
                            SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                            PFBlockTag = cms.InputTag("particleFlowBlock"),
                            PFTrackTag = cms.InputTag("pfTrack"),
                            #minTracks = cms.untracked.uint32(1000)

                            MatchingDeltaR = cms.untracked.double(0.3)
                           )



