import FWCore.ParameterSet.Config as cms

process = cms.Process("OWNPARTICLES")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #"file:/Users/benwu/Data/Dataset/SLHC/SLHC23p1/DYMM_SHCAL_PU140_SLHC23p1.root"
        '/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_NoPU_PH2_1K_FB_V6-v1/10000/04E051DD-30C6-E411-9959-0025905A60B6.root',
    )

)


from RecoParticleFlow.PFProducer.particleFlowTmpPtrs_cfi import particleFlowTmpPtrs
process.ZMMProducer = cms.EDProducer('ZMMFilter',
                                         PFCandidateInputTag = cms.InputTag("particleFlow"),
                                         VertexTag = cms.InputTag("goodOfflinePrimaryVertices"),
                                         TrackTag = cms.InputTag("generalTracks"),
                                         MuonTag = cms.InputTag("muons"),
                                         )

process.particleFlowNoMuonTmpPtrs = particleFlowTmpPtrs.clone(
                                     src = cms.InputTag('ZMMProducer', 'PFCandidatesNoMuon')
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('DYMM_SHCAL_140PU.root'),
    outputCommands = cms.untracked.vstring('drop *',
                                           "keep *_addPileupInfo_*_*", # PU
                                           "keep *_offlinePrimaryVertices_*_*", #Vertex
                                           "keep *_genParticles_*_*",
                                           "keep *_kt6PFJets_rho_*",
                                           "keep *_generalTracks_*_*",
                                           #"keep *_particleFlow__*",
                                           "keep *_ZMMProducer_*_*",
                                           "keep *_particleFlowNoMuonTmpPtrs_*_*",
                                           "keep *_electronGsfTracks_*_*",
                                           )

)

process.p = cms.Path(process.goodOfflinePrimaryVertices * process.ZMMProducer * process.particleFlowNoMuonTmpPtrs )

process.e = cms.EndPath(process.out)
