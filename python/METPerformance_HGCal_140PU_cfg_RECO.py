import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
JetEta = 3

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                #'/store/mc/TP2023HGCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/HGCALnewsplit_PU140BX25_newsplitPU140_PH2_1K_FB_V6-v3/00000/001F40A8-0AF8-E411-8A29-0025905A48FC.root',
                                '/store/mc/TP2023HGCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/HGCALnewsplit_PU140BX25_newsplitPU140_PH2_1K_FB_V6-v3/80000/FCE04190-E4F8-E411-B49D-0025905B860C.root'
                                #'file:./HGCAl.root'


                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/0069789B-A9A7-E411-A95B-0025905A6094.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/009E9C8A-6BA7-E411-A166-003048FFCB84.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/00C53674-D4A7-E411-BA17-0025905B8598.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/00E39594-B9A7-E411-A1F9-003048FF9AC6.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/02450C60-E0A8-E411-8859-0025905A60A8.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/0296D02E-B2A7-E411-ADDE-0025905A60B8.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/02B32EDA-B3A7-E411-988B-003048FFD7D4.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/02FB1826-B7A8-E411-95A5-0025905A605E.root',
                                #'/store/mc/TP2023SHCALDR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/00000/0443F985-B5A7-E411-B89F-0025905A6066.root',
                            ),
                            #'file:/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_SHCal_140PU_aged/DYMM_SHCAL_140PU_aged_106_1_HpL.root')
                            #fileNames = cms.untracked.vstring(filelist)
                            #fileNames = cms.untracked.vstring( ['file:%s' % x.strip() for x in open(options.filelist, 'r').readlines()])
                            #firstRun = cms.untracked.uint32(1),
                            #firstEvent = cms.untracked.uint32(417137),
                            #fileNames = cms.untracked.vstring('file:%s' % x for x in glob.glob("/eos/uscms/store/user/lpcjme/benwu/TP_SLHC23/DYMM_Phase1_140PU_aged/DYMM_Phase1_140PU_age*.root"))
                            )

#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )
process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string(options.outputFile),
                                   fileName = cms.string("HGCal_ZMM_140PU.root"),
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
from Dummy.Puppi.Puppi_PhaseII_SLHC23p1_v2 import *
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
                                  JetEtaThresTag = cms.untracked.double(JetEta),
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
                                     L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PF.txt"),
                                     L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PF.txt"),
                                     L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PF.txt"),
                                     MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                     PFJetInputTag = cms.InputTag("ak4PFJets"),
                                     srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                     JetJECThresTag = cms.untracked.double(10),
                                     PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     JetsMatchedGen =  cms.untracked.bool(True),
                                     )

process.ak4_10_PFJEC = cms.EDAnalyzer('METPerformance',
                                      L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PF.txt"),
                                      MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                      JetJECThresTag = cms.untracked.double(10),
                                      JetEtaThresTag = cms.untracked.double(JetEta),
                                      PFJetInputTag = cms.InputTag("ak4PFJets"),
                                      srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                      PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                      GenJetInputTag = cms.InputTag("ak4GenJets"),
                                      UseGenJets     = cms.untracked.bool(False),
                                      JetsMatchedGen =  cms.untracked.bool(False),
                                      )

process.ak4_15_PFJEC = cms.EDAnalyzer('METPerformance',
                                      L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PF.txt"),
                                      MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                      JetJECThresTag = cms.untracked.double(15),
                                      PFJetInputTag = cms.InputTag("ak4PFJets"),
                                      srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                      PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                      GenJetInputTag = cms.InputTag("ak4GenJets"),
                                      UseGenJets     = cms.untracked.bool(False),
                                      JetsMatchedGen =  cms.untracked.bool(False),
                                      )

process.ak4_20_PFJEC = cms.EDAnalyzer('METPerformance',
                                      L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PF.txt"),
                                      MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                      JetEtaThresTag = cms.untracked.double(JetEta),
                                      JetJECThresTag = cms.untracked.double(20),
                                      PFJetInputTag = cms.InputTag("ak4PFJets"),
                                      srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                      PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                      GenJetInputTag = cms.InputTag("ak4GenJets"),
                                      UseGenJets     = cms.untracked.bool(False),
                                      JetsMatchedGen =  cms.untracked.bool(False),
                                      )

process.ak4_30_PFJEC = cms.EDAnalyzer('METPerformance',
                                      L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PF.txt"),
                                      L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PF.txt"),
                                      L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PF.txt"),
                                      MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                      JetEtaThresTag = cms.untracked.double(JetEta),
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
                                         L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PFchs.txt"),
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
                                         L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PFchs.txt"),
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
                                         L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L3Absolute_AK4PFchs.txt"),
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
                                         L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PFchs.txt"),
                                         L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PFchs.txt"),
                                         L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PFchs.txt"),
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
                                     L1JECTag       = cms.string(""),
                                     L2JECTag       = cms.string(""),
                                     L3JECTag       = cms.string(""),
                                     MuonInputTag   = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                     PFJetInputTag  = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetJECThresTag = cms.untracked.double(0),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                     JetsMatchedGen =  cms.untracked.bool(False),
                                     )

process.ak4PuppiJEC = cms.EDAnalyzer('METPerformance',
                                     L1JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PUPPI.txt"),
                                     L2JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PUPPI.txt"),
                                     L3JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PUPPI.txt"),
                                     MuonInputTag   = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     PFJetInputTag  = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                     JetJECThresTag = cms.untracked.double(0),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                     JetsMatchedGen =  cms.untracked.bool(False),
                                     )

process.ak4PuppiJEC10 = cms.EDAnalyzer('METPerformance',
                                     L1JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PUPPI.txt"),
                                     L2JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PUPPI.txt"),
                                     L3JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PUPPI.txt"),
                                     MuonInputTag   = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     PFJetInputTag  = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                     JetJECThresTag = cms.untracked.double(10),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                     JetsMatchedGen =  cms.untracked.bool(False),
                                     )
process.ak4PuppiJEC20 = cms.EDAnalyzer('METPerformance',
                                     L1JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PUPPI.txt"),
                                     L2JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PUPPI.txt"),
                                     L3JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PUPPI.txt"),
                                     MuonInputTag   = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     PFJetInputTag  = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                     JetJECThresTag = cms.untracked.double(20),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                     JetsMatchedGen =  cms.untracked.bool(False),
                                     )

process.ak4PuppiJEC30 = cms.EDAnalyzer('METPerformance',
                                     L1JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PUPPI.txt"),
                                     L2JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PUPPI.txt"),
                                     L3JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PUPPI.txt"),
                                     MuonInputTag   = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     PFJetInputTag  = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                     JetJECThresTag = cms.untracked.double(30),
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
                                       L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PF.txt"),
                                       L2JECTag = cms.string(""),
                                       L3JECTag = cms.string(""),
                                       srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                       PFJetInputTag = cms.InputTag("ak4PFJets"),
                                       GenJetInputTag = cms.InputTag("ak4GenJets"),
                                       PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                       )

process.JETak4PFJEC = cms.EDAnalyzer('JetPerformance',
                                     L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PF.txt"),
                                     L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PF.txt"),
                                     L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PF.txt"),
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
                                          L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PFchs.txt"),
                                          L2JECTag = cms.string(""),
                                          L3JECTag = cms.string(""),
                                          PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                          GenJetInputTag = cms.InputTag("ak4GenJets"),
                                          srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                          PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                          )

process.JETak4PFCHSJEC = cms.EDAnalyzer('JetPerformance',
                                        L1JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PFchs.txt"),
                                        L2JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PFchs.txt"),
                                        L3JECTag = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PFchs.txt"),
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
                                        L1JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L1FastJet_AK4PUPPI.txt"),
                                        L2JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L2Relative_AK4PUPPI.txt"),
                                        L3JECTag       = cms.string("SLHC25p4_PhaseII_HGCal140PU_L3Absolute_AK4PUPPI.txt"),
                                        PFJetInputTag  = cms.InputTag("ak4PuppiJets"),
                                        GenJetInputTag = cms.InputTag("ak4GenJets"),
                                        srcRhoTag      = cms.InputTag(''),
                                        PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                        )


process.GenProducer = cms.Sequence(process.genParticlesForJetsNoMuNoNu  * process.ak4GenJets )
#process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4_10_PFJEC *  process.ak4PFGenRaw * process.ak4PFGenJEC *
                                  #process.ak4_15_PFJEC * process.ak4_20_PFJEC *process.ak4_30_PFJEC )

process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4PFGenRaw * process.ak4PFGenJEC * process.ak4_10_PFJEC )
#process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4_10_PFJEC )
#process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4PFGenRaw * process.ak4PFGenJEC * process.ak4_10_PFJEC )
process.PFCHSProducer = cms.Sequence(process.goodOfflinePrimaryVertices * process.PFPileUpZMM  * process.PFNoPileUpZMM *
                                     process.ak4PFJetsCHS * process.ak4PFCHSRaw * process.ak4_10_PFCHSJEC * process.ak4_15_PFCHSJEC *
                                     process.ak4_20_PFCHSJEC * process.ak4_30_PFCHSJEC )


process.puppiProducer = cms.Sequence(process.puppiZMM * process.ak4PuppiJets * process.ak4PuppiRaw * process.ak4PuppiJEC
                                     * process.ak4PuppiJEC10 * process.ak4PuppiJEC20 * process.ak4PuppiJEC30)
#process.puppiProducer = cms.Sequence(process.puppiZMM * process.ak4PuppiJets * process.ak4PuppiRaw * process.ak4PuppiJEC)
process.JetPerformance = cms.Sequence( process.JETak4PFJEC * process.JETak4PuppiJEC )
#process.JetPerformance = cms.Sequence( process.JETak4PFRaw * process.JETak4PFJEC * process.JETak4PuppiRaw* process.JETak4PuppiJEC )
#process.JetPerformance = cms.Sequence( process.JETak4PFRaw * process.JETak4PFJECL1 * process.JETak4PFJEC* process.JETak4PFCHSRaw *
                                      #process.JETak4PFCHSJECL1 * process.JETak4PFCHSJEC* process.JETak4PuppiRaw* process.JETak4PuppiJEC )
process.p = cms.Path(process.goodOfflinePrimaryVertices * process.ZMMProducer *  process.particleFlowNoMuonTmpPtrs *
                     process.GenProducer *process.PFProducer * process.puppiProducer)
                     #process.GenProducer * process.PFProducer * process.PFCHSProducer * process.puppiProducer * process.JetPerformance)
