import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('/store/user/lpcjme/benwu/TP_SLHC23/DYMM_Phase1_50PU_noaged/DYMM_Phase1_50PU_noaged_192_1_VUT.root')
                            #fileNames = cms.untracked.vstring(filelist)
                            #fileNames = cms.untracked.vstring( ['file:%s' % x.strip() for x in open(options.filelist, 'r').readlines()])
                            #fileNames = cms.untracked.vstring('file:%s' % x for x in glob.glob("/eos/uscms/store/user/lpcjme/benwu/TP_SLHC23/DYMM_Phase1_50PU_aged/DYMM_Phase1_50PU_age*.root"))
)

process.TFileService = cms.Service("TFileService",
      #fileName = cms.string(options.outputFile),
      fileName = cms.string("Phase1_ZMM_50PU.root"),
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

from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
## AK4 PFJet
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True,
                                    src = cms.InputTag("ZMMProducer", "PFCandidatesNoMuon") )
## AK4 CHSJet
from CommonTools.ParticleFlow.pfNoPileUpJME_cff import *
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.PFPileUpZMM = pfPileUp.clone( PFCandidates='particleFlowNoMuonTmpPtrs', Vertices = 'goodOfflinePrimaryVertices')
process.PFNoPileUpZMM = pfNoPileUp.clone(topCollection = 'PFPileUpZMM', bottomCollection = 'particleFlowNoMuonTmpPtrs' )
process.ak4PFJetsCHS = ak5PFJets.clone(rParam = 0.4, doAreaFastjet=True,
                                       jetPtMin = 0.0, src = cms.InputTag("PFNoPileUpZMM"))

## AK4 PuppiJet
from Dummy.Puppi.Puppi_PhaseI_SLHC23p1_v2 import *
process.puppiZMM = puppi.clone( PFcandName = cms.InputTag("ZMMProducer", "PFCandidatesNoMuon"))
process.ak4PuppiJets = ak5PFJets.clone(rParam = 0.4,  doAreaFastjet=True,
                                       jetPtMin= 0.0, src = cms.InputTag('puppiZMM','Puppi'))

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PFJet ~~~~~
process.ak4PFRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  JetJECThresTag = cms.double(0),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4_10_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  JetJECThresTag = cms.double(10),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4_15_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.double(15),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4_20_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.double(20),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4_30_PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.double(30),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 CHSJet ~~~~~
process.ak4PFCHSRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                  srcRhoTag      = cms.InputTag(''),
                                  JetJECThresTag = cms.double(0),
                                  #srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4_10_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PFchs.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PFchs.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PFchs.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.double(10),
                                  PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4_15_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PFchs.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PFchs.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PFchs.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.double(15),
                                  PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4_20_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PFchs.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PFchs.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PFchs.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.double(20),
                                  PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)


process.ak4_30_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L1FastJet_AK4PFchs.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L2Relative_AK4PFchs.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseI_50PU_V2_L3Absolute_AK4PFchs.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  JetJECThresTag = cms.double(30),
                                  PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PuppiJet ~~~~~
process.ak4PuppiRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                  PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                  srcRhoTag      = cms.InputTag(''),
                                  JetJECThresTag = cms.double(0),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

#process.ak4PuppiJEC = cms.EDAnalyzer('METPerformance',
                                  #L1JECTag = cms.string("PhaseII_Shashlik50PU_L1FastJet_AK4Puppi.txt"),
                                  #L2JECTag = cms.string("PhaseII_Shashlik50PU_L2Relative_AK4Puppi.txt"),
                                  #L3JECTag = cms.string("PhaseII_Shashlik50PU_L3Absolute_AK4Puppi.txt"),
                                  #MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  #PuppiJetInputTag = cms.InputTag("ak4PuppiJets"),
                                  ##srcRhoTag      = cms.InputTag(''),
                                  #srcRhoTag      = cms.InputTag('kt6PuppiJets','rho'),
                                  #PileUpInfoTag = cms.InputTag("addPileupInfo"),
#)


process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4_10_PFJEC * process.ak4_15_PFJEC * process.ak4_20_PFJEC *process.ak4_30_PFJEC )

process.PFCHSProducer = cms.Sequence(process.goodOfflinePrimaryVertices * process.PFPileUpZMM  * process.PFNoPileUpZMM *
                                     process.ak4PFJetsCHS * process.ak4PFCHSRaw * process.ak4_10_PFCHSJEC * process.ak4_15_PFCHSJEC *
                                     process.ak4_20_PFCHSJEC * process.ak4_30_PFCHSJEC )


process.puppiProducer = cms.Sequence(process.puppiZMM * process.ak4PuppiJets * process.ak4PuppiRaw)


#process.p = cms.Path(
process.p = cms.Path( process.goodOfflinePrimaryVertices * process.ZMMProducer *  process.particleFlowNoMuonTmpPtrs *
                     process.PFProducer * process.PFCHSProducer * process.puppiProducer)
