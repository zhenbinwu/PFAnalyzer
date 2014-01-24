import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('PFAnalyzer',
                      minTracks = cms.untracked.uint32(1000),
                      HbHeRecHitTag = cms.string("hbheUpgradeReco"),
                      HfRecHitTag = cms.string("hbheUpgradeReco"),
                      HoRecHitTag = cms.string("horeco"),
                      EcalPFRecHitTag = cms.string("particleFlowRecHitECAL"),
                      HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHCAL", "Clean"),
                      HOPFRecHitTag = cms.string("particleFlowRecHitHO"),
                      PSPFRecHitTag = cms.string("particleFlowRecHitPS"),
                      EcalPFClusterTag = cms.string("particleFlowClusterECAL"),
                      HcalPFClusterTag = cms.string("particleFlowClusterHCAL"),
                      HOPFClusterTag = cms.string("particleFlowClusterHO"),
                      PSPFClusterTag = cms.string("particleFlowClusterPS"),

                      )
