import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

from UserCode.PFAnalyzer.BWTool import GetList
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:TTBar_14TeV.root'
      GetList('/data/nbay04/a/benwu/Fresh/CMSSW_6_2_0_SLHC6/src/SinglePion/SinglePiE50HCAL_RECO.root')
      #GetList('/pnfs/cms/WAX/11/store/relval/CMSSW_6_2_0_SLHC3/RelValTTbar_14TeV/ ')
    )
)


#initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
    )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )



process.load("UserCode.PFAnalyzer.PFAnalyzer_cfi")
process.PFAnalyzer.HbHeRecHitTag = cms.InputTag("hbheUpgradeReco")
process.PFAnalyzer.HfRecHitTag = cms.InputTag("hfUpgradeReco")

process.load("UserCode.PFAnalyzer.SinglePion_cfi")
process.SinglePion.HbHeRecHitTag = cms.InputTag("hbheUpgradeReco")

#process.demo = cms.EDAnalyzer('PFAnalyzer',
                      #minTracks = cms.untracked.uint32(1000),
                      #HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                      #HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                      #HoRecHitTag = cms.InputTag("horeco"),
                      #EcalPFRecHitTag = cms.InputTag("particleFlowRecHitECAL"),
                      #HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHCAL"),
                      #HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO"),
                      #PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                      #EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                      #HcalPFClusterTag = cms.InputTag("particleFlowClusterHCAL"),
                      #HOPFClusterTag = cms.InputTag("particleFlowClusterHO"),
                      #PSPFClusterTag = cms.InputTag("particleFlowClusterPS"),
                      #PFJetInputTag = cms.InputTag("ak5PFJets"),
                      #GenJetInputTag = cms.InputTag("ak5GenJets"),
                      #CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                      #PFMETInputTag = cms.InputTag("pfMet"),
                      #GenMETInputTag = cms.InputTag("genMetTrue"),
                      #CaloMETInputTag = cms.InputTag("met"),
                      #GenParticleInputTag = cms.InputTag("genParticles"),
                      #SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ), 
                              ##minTracks = cms.untracked.uint32(1000)

#)

process.p = cms.Path(process.SinglePion)
#process.Tracer = cms.Service("Tracer")


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('SinglePi_0PU_E50.root')
                                  )

