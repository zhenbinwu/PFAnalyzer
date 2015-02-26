import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:./myOutputFile.root'
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("Test.root"),
      closeFileFast = cms.untracked.bool(True)
  )

from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4, src = cms.InputTag("ZMMProducer", "PFCandidatesNoMuon", "OWNPARTICLES" ) )

process.ak4PFRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag(''),
                                  #srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)


#process.JetProducer = cms.Sequence(process.genParticlesForJets * process.ak4GenJets)
process.p = cms.Path(process.ak4PFJets * process.ak4PFRaw)
