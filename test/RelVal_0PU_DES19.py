import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(600) )
process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'DES19_62_V8::All'


#from JetMETCorrections.Configuration.DefaultJEC_cff import *
#ak5PFchsL1Fastjet  = ak5PFL1Fastjet.clone ( algorithm = cms.string('AK5PFchs') )


from UserCode.PFAnalyzer.BWTool import GetList
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:TTBar_14TeV.root'
      GetList('/data/nbay04/c/benwu/PFSample/CMSSW_6_2_0_SLHC3/RelValTTbar_14TeV_DES19.root')
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

process.p = cms.Path(process.PFAnalyzer)
#process.Tracer = cms.Service("Tracer")


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('RV0PU_DES19.root')
                                  )

