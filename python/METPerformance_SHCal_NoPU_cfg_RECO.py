import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                '/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_NoPU_PH2_1K_FB_V6-v1/10000/04E051DD-30C6-E411-9959-0025905A60B6.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/003E69A0-89A7-E411-82FC-0025905B8606.root'
                            )
                                #'file:/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_SHCal_140PU_aged/DYMM_SHCAL_140PU_aged_106_1_HpL.root')
                            #fileNames = cms.untracked.vstring(filelist)
                            #fileNames = cms.untracked.vstring( ['file:%s' % x.strip() for x in open(options.filelist, 'r').readlines()])
                            #fileNames = cms.untracked.vstring('file:%s' % x for x in glob.glob("/eos/uscms/store/user/lpcjme/benwu/TP_SLHC23/DYMM_Phase1_140PU_aged/DYMM_Phase1_140PU_age*.root"))
)

process.TFileService = cms.Service("TFileService",
      #fileName = cms.string(options.outputFile),
      fileName = cms.string("SHCal_ZMM_0PU.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.load("CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi")
process.ZMMProducer = cms.EDProducer('ZMMFilter',
                                         PFCandidateInputTag = cms.InputTag("particleFlow"),
                                         VertexTag = cms.InputTag("goodOfflinePrimaryVertices"),
                                         TrackTag = cms.InputTag("generalTracks"),
                                         MuonTag = cms.InputTag("muons"),
                                         )

from RecoParticleFlow.PFProducer.particleFlowTmpPtrs_cfi import particleFlowTmpPtrs
process.particleFlowNoMuonTmpPtrs = particleFlowTmpPtrs.clone(
                                     src = cms.InputTag('ZMMProducer', 'PFCandidatesNoMuon')
)

## GenJet
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4GenJets = ak5GenJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True,
                                      src = 'genParticlesForJetsNoMuNoNu')

## AK4 PFJet
from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True,
                                    src = cms.InputTag("ZMMProducer", "PFCandidatesNoMuon") )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PFJet ~~~~~
process.ak4PFRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  JetJECThresTag = cms.untracked.double(0),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  UseGenJets     = cms.untracked.bool(False),
                                  JetsMatchedGen =  cms.untracked.bool(False),
)

process.ak4PFGenRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  JetJECThresTag = cms.untracked.double(0),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  UseGenJets     = cms.untracked.bool(False),
                                  JetsMatchedGen =  cms.untracked.bool(True),
)

process.ak4PFGenJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  JetJECThresTag = cms.untracked.double(10),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  UseGenJets     = cms.untracked.bool(False),
                                  JetsMatchedGen =  cms.untracked.bool(True),
)

process.ak4_10_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.untracked.double(10),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  UseGenJets     = cms.untracked.bool(False),
                                  JetsMatchedGen =  cms.untracked.bool(False),
)

process.ak4_15_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.untracked.double(15),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  UseGenJets     = cms.untracked.bool(False),
                                  JetsMatchedGen =  cms.untracked.bool(False),
)


process.ak4_20_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.untracked.double(20),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  UseGenJets     = cms.untracked.bool(False),
                                  JetsMatchedGen =  cms.untracked.bool(False),
)


process.ak4_30_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.untracked.double(30),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  UseGenJets     = cms.untracked.bool(False),
                                  JetsMatchedGen =  cms.untracked.bool(False),
)


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PuppiJet ~~~~~
process.ak4GenRaw = cms.EDAnalyzer('METPerformance',
                                   L1JECTag       = cms.string(""),
                                   L2JECTag       = cms.string(""),
                                   L3JECTag       = cms.string(""),
                                   MuonInputTag   = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                   PFJetInputTag  = cms.InputTag("ak5PFJets"),
                                   GenJetInputTag = cms.InputTag("ak4GenJets"),
                                   UseGenJets     = cms.untracked.bool(True),
                                   srcRhoTag      = cms.InputTag(''),
                                   JetJECThresTag = cms.untracked.double(0),
                                   PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                   JetsMatchedGen =  cms.untracked.bool(False),
)

#============================================================================#
#-------------------------------     PFJet     ------------------------------#
#============================================================================#
process.JETak4PFRaw = cms.EDAnalyzer('JetPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  )


process.JETak4PFJECL1 = cms.EDAnalyzer('JetPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  )

process.JETak4PFJEC = cms.EDAnalyzer('JetPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_ShashliknoPU_V1_L3Absolute_AK4PF.txt"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  )




process.GenProducer = cms.Sequence(process.genParticlesForJetsNoMuNoNu  * process.ak4GenJets * process.ak4GenRaw )
process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4_10_PFJEC *  process.ak4PFGenRaw * process.ak4PFGenJEC *
                                  process.ak4_15_PFJEC * process.ak4_20_PFJEC *process.ak4_30_PFJEC )

#process.p = cms.Path(
process.p = cms.Path(process.goodOfflinePrimaryVertices * process.ZMMProducer *  process.particleFlowNoMuonTmpPtrs *
                     process.GenProducer * process.PFProducer* process.JETak4PFRaw * process.JETak4PFJECL1 * process.JETak4PFJEC)
                     #process.GenProducer * process.PFProducer * process.PFCHSProducer * process.puppiProducer)
