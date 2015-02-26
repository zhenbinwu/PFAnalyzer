import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_6_2_0_SLHC23_patch2/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PH2_1K_FB_V6_UPGHGCalV5-v1/00000/B4EB6740-C3AE-E411-B7B7-0025905A610C.root',
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("Test.root"),
      closeFileFast = cms.untracked.bool(True)
  )

from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4GenJets = ak5GenJets.clone(rParam = 0.4)

process.ak4PF = cms.EDAnalyzer('JetPerformance',
                             L1JECTag = cms.string(""),
                             L2JECTag = cms.string(""),
                             L3JECTag = cms.string(""),
                             srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                             PFJetInputTag = cms.InputTag("ak4PFJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
)


process.JetProducer = cms.Sequence(process.genParticlesForJets * process.ak4GenJets)
process.p = cms.Path(process.JetProducer * process.ak4PF)
