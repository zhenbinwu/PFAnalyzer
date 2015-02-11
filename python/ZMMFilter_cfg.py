import FWCore.ParameterSet.Config as cms

process = cms.Process("OWNPARTICLES")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi")
process.load("Dummy/Puppi/Puppi_PhaseII_cff")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/003E69A0-89A7-E411-82FC-0025905B8606.root',
    )
)

process.ZMMProducer = cms.EDProducer('ZMMFilter',
                                         PFCandidateInputTag = cms.InputTag("particleFlow"),
                                         VertexTag = cms.InputTag("goodOfflinePrimaryVertices"),
                                         TrackTag = cms.InputTag("generalTracks"),
                                         MuonTag = cms.InputTag("muons"),
                                         )


process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root'),
    outputCommands = cms.untracked.vstring('drop *',
                                           "keep *_ZMMProducer_*_*",
                                           )

)
#from JetMETCorrections.Configuration.DefaultJEC_cff import *
#from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
#from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
#from RecoJets.Configuration.RecoPFJets_cff import *
#process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
#process.load('RecoJets.Configuration.GenJetParticles_cff')
#process.ak4GenJets = ak5GenJets.clone(rParam = 0.4)
#process.Newak4PFJets = ak5PFJets.clone(rParam = 0.4, src = cms.InputTag('ZMMProducer', 'PFCandidatesNoMuon'))

#process.Newak4PFJetsCHS = ak5PFJets.clone(rParam = 0.4, src = cms.InputTag('ZMMProducer', 'PFCandidatesNoMuon'))
##process.Newak4PFJetsCHS = ak5PFJetsCHS.clone(rParam = 0.4, doFastJetNonUniform = cms.bool(True),
                                          ##puCenters = cms.vdouble(5,-4,-3,-2,-1,0,1,2,3,4,5), puWidth = cms.double(.8), nExclude = cms.uint32(2))
#process.Newpuppi = process.puppi.clone( candName = cms.untracked.string('ZMMProducer', 'PFCandidatesNoMuon'))
#process.Newak4PuppiJets = ak5PFJets.clone(rParam = 0.4, src = cms.InputTag('Newpuppi','Puppi'))


#process.Jet4Producer = cms.Sequence(process.genParticlesForJets * process.Newak4PFJets * process.Newak4PFJetsCHS * process.Newak4GenJets)
#process.PuppiProducer = cms.Sequence(process.Newpuppi * process.Newak4PuppiJets )

#process.p = cms.Path(process.goodOfflinePrimaryVertices * process.ZMMProducer *process.Jet4Producer * process.PuppiProducer)
process.p = cms.Path(process.goodOfflinePrimaryVertices * process.ZMMProducer )

process.e = cms.EndPath(process.out)
