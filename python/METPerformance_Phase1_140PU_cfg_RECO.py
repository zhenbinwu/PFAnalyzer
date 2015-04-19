import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring('/store/user/lpcjme/benwu/TP_SLHC23/DYMM_Phase1_50PU_noaged/DYMM_Phase1_50PU_noaged_192_1_VUT.root')
                            fileNames = cms.untracked.vstring(
                                '/store/mc/GEM2019Upg14DR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kfixJan23_PU140BX25_PH1_1K_FB_V2-v1/00000/04A2E804-E1BD-E411-9040-008CFA0518D4.root',
                                '/store/mc/GEM2019Upg14DR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kfixJan23_PU140BX25_PH1_1K_FB_V2-v1/00000/04F6572C-0FBE-E411-BB5B-00266CFFCCC8.root',
                                '/store/mc/GEM2019Upg14DR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kfixJan23_PU140BX25_PH1_1K_FB_V2-v1/00000/0858D297-46BD-E411-B52C-00266CFF0840.root',
                                '/store/mc/GEM2019Upg14DR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/Phase1age1kfixJan23_PU140BX25_PH1_1K_FB_V2-v1/00000/08A33DAC-DABD-E411-BE9D-00266CFEFDC4.root',
                            )

                            #fileNames = cms.untracked.vstring(filelist)
                            #fileNames = cms.untracked.vstring( ['file:%s' % x.strip() for x in open(options.filelist, 'r').readlines()])
                            #fileNames = cms.untracked.vstring('file:%s' % x for x in glob.glob("/eos/uscms/store/user/lpcjme/benwu/TP_SLHC23/DYMM_Phase1_140PU_aged/DYMM_Phase1_140PU_age*.root"))
                            )

process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string(options.outputFile),
                                   fileName = cms.string("Phase1_ZMM_140PU.root"),
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
                                     L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PF.txt"),
                                     L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PF.txt"),
                                     L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PF.txt"),
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
                                      L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PF.txt"),
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
                                      L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PF.txt"),
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
                                      L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PF.txt"),
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
                                      L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PF.txt"),
                                      MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                      JetJECThresTag = cms.untracked.double(30),
                                      PFJetInputTag = cms.InputTag("ak4PFJets"),
                                      srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                      PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                      GenJetInputTag = cms.InputTag("ak4GenJets"),
                                      UseGenJets     = cms.untracked.bool(False),
                                      JetsMatchedGen =  cms.untracked.bool(False),
                                      )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 CHSJet ~~~~~
process.ak4PFCHSRaw = cms.EDAnalyzer('METPerformance',
                                     L1JECTag = cms.string(""),
                                     L2JECTag = cms.string(""),
                                     L3JECTag = cms.string(""),
                                     MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetJECThresTag = cms.untracked.double(0),
                                     #srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                     PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     JetsMatchedGen =  cms.untracked.bool(False),
                                     )

process.ak4_10_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                         L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PFchs.txt"),
                                         MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                         JetJECThresTag = cms.untracked.double(10),
                                         PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                         srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                         PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                         GenJetInputTag = cms.InputTag("ak4GenJets"),
                                         UseGenJets     = cms.untracked.bool(False),
                                         JetsMatchedGen =  cms.untracked.bool(False),
                                         )

process.ak4_15_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                         L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PFchs.txt"),
                                         MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                         JetJECThresTag = cms.untracked.double(15),
                                         PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                         srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                         PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                         GenJetInputTag = cms.InputTag("ak4GenJets"),
                                         UseGenJets     = cms.untracked.bool(False),
                                         JetsMatchedGen =  cms.untracked.bool(False),
                                         )

process.ak4_20_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                         L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PFchs.txt"),
                                         MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                         JetJECThresTag = cms.untracked.double(20),
                                         PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                         srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                         PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                         GenJetInputTag = cms.InputTag("ak4GenJets"),
                                         UseGenJets     = cms.untracked.bool(False),
                                         JetsMatchedGen =  cms.untracked.bool(False),
                                         )

process.ak4_30_PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                         L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PFchs.txt"),
                                         MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                         JetJECThresTag = cms.untracked.double(30),
                                         PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                         srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                         PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                         GenJetInputTag = cms.InputTag("ak4GenJets"),
                                         UseGenJets     = cms.untracked.bool(False),
                                         JetsMatchedGen =  cms.untracked.bool(False),
                                         )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PuppiJet ~~~~~
process.ak4PuppiRaw = cms.EDAnalyzer('METPerformance',
                                     L1JECTag = cms.string(""),
                                     L2JECTag = cms.string(""),
                                     L3JECTag = cms.string(""),
                                     MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetJECThresTag = cms.untracked.double(0),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                     JetsMatchedGen =  cms.untracked.bool(False),
                                     )

process.ak4PuppiJEC = cms.EDAnalyzer('METPerformance',
                                     L1JECTag       = cms.string("SLHC23p1_PhaseI_140PU_V3_L1FastJet_AK4PUPPI.txt"),
                                     L2JECTag       = cms.string("SLHC23p1_PhaseI_140PU_V3_L2Relative_AK4PUPPI.txt"),
                                     L3JECTag       = cms.string("SLHC23p1_PhaseI_140PU_V3_L3Absolute_AK4PUPPI.txt"),
                                     MuonInputTag   = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     PFJetInputTag  = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetJECThresTag = cms.untracked.double(0),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     PileUpInfoTag  = cms.InputTag("addPileupInfo"),
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
                                       L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PF.txt"),
                                       L2JECTag = cms.string(""),
                                       L3JECTag = cms.string(""),
                                       srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                       PFJetInputTag = cms.InputTag("ak4PFJets"),
                                       GenJetInputTag = cms.InputTag("ak4GenJets"),
                                       PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                       )

process.JETak4PFJEC = cms.EDAnalyzer('JetPerformance',
                                     L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PF.txt"),
                                     L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PF.txt"),
                                     L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PF.txt"),
                                     srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                     PFJetInputTag = cms.InputTag("ak4PFJets"),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                     )


#============================================================================#
#-----------------------------     PFCHSJet     -----------------------------#
#============================================================================#
process.JETak4PFCHSRaw = cms.EDAnalyzer('JetPerformance',
                                        L1JECTag = cms.string(""),
                                        L2JECTag = cms.string(""),
                                        L3JECTag = cms.string(""),
                                        PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                        GenJetInputTag = cms.InputTag("ak4GenJets"),
                                        srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                        PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                        )

process.JETak4PFCHSJECL1 = cms.EDAnalyzer('JetPerformance',
                                          L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PFchs.txt"),
                                          L2JECTag = cms.string(""),
                                          L3JECTag = cms.string(""),
                                          PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                          GenJetInputTag = cms.InputTag("ak4GenJets"),
                                          srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                          PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                          )

process.JETak4PFCHSJEC = cms.EDAnalyzer('JetPerformance',
                                        L1JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L1FastJet_AK4PFchs.txt"),
                                        L2JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L2Relative_AK4PFchs.txt"),
                                        L3JECTag = cms.string("SLHC23p1_PhaseI_140PU_V2_L3Absolute_AK4PFchs.txt"),
                                        PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                        GenJetInputTag = cms.InputTag("ak4GenJets"),
                                        srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                        PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                        )



#============================================================================#
#-----------------------------     PuppiJet     -----------------------------#
#============================================================================#
process.JETak4PuppiRaw = cms.EDAnalyzer('JetPerformance',
                                        L1JECTag = cms.string(""),
                                        L2JECTag = cms.string(""),
                                        L3JECTag = cms.string(""),
                                        PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                        GenJetInputTag = cms.InputTag("ak4GenJets"),
                                        srcRhoTag      = cms.InputTag(''),
                                        PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                        )
process.JETak4PuppiJEC = cms.EDAnalyzer('JetPerformance',
                                        L1JECTag       = cms.string("SLHC23p1_PhaseI_140PU_V3_L1FastJet_AK4PUPPI.txt"),
                                        L2JECTag       = cms.string("SLHC23p1_PhaseI_140PU_V3_L2Relative_AK4PUPPI.txt"),
                                        L3JECTag       = cms.string("SLHC23p1_PhaseI_140PU_V3_L3Absolute_AK4PUPPI.txt"),
                                        PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                        GenJetInputTag = cms.InputTag("ak4GenJets"),
                                        srcRhoTag      = cms.InputTag(''),
                                        PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                        )


process.GenProducer = cms.Sequence(process.genParticlesForJetsNoMuNoNu  * process.ak4GenJets * process.ak4GenRaw )
process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4_10_PFJEC *  process.ak4PFGenRaw * process.ak4PFGenJEC *
                                  process.ak4_15_PFJEC * process.ak4_20_PFJEC *process.ak4_30_PFJEC )

process.PFCHSProducer = cms.Sequence(process.goodOfflinePrimaryVertices * process.PFPileUpZMM  * process.PFNoPileUpZMM *
                                     process.ak4PFJetsCHS * process.ak4PFCHSRaw * process.ak4_10_PFCHSJEC * process.ak4_15_PFCHSJEC *
                                     process.ak4_20_PFCHSJEC * process.ak4_30_PFCHSJEC )


process.puppiProducer = cms.Sequence(process.puppiZMM * process.ak4PuppiJets * process.ak4PuppiRaw * process.ak4PuppiJEC)
process.JetPerformance = cms.Sequence( process.JETak4PFRaw * process.JETak4PFJECL1 * process.JETak4PFJEC* process.JETak4PFCHSRaw *
                                      process.JETak4PFCHSJECL1 * process.JETak4PFCHSJEC* process.JETak4PuppiRaw* process.JETak4PuppiJEC )
process.p = cms.Path(process.goodOfflinePrimaryVertices * process.ZMMProducer *  process.particleFlowNoMuonTmpPtrs *
                     process.GenProducer * process.PFProducer * process.PFCHSProducer * process.puppiProducer * process.JetPerformance)
