import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

#The line below always has to be included to make VarParsing work
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.register ('filelist',
                  '',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "filelist to process")
options.parseArguments()

#import glob
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( ['file:%s' % x.strip() for x in open(options.filelist, 'r').readlines()])
                            #fileNames = cms.untracked.vstring('file:%s' % x for x in glob.glob("/eos/uscms/store/user/lpcjme/benwu/TP_SLHC23/DYMM_Phase1_140PU_aged/DYMM_Phase1_140PU_age*.root"))
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string(options.outputFile),
      #fileName = cms.string("Phase1_ZMM_140PU.root"),
      closeFileFast = cms.untracked.bool(True)
  )

from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
## AK4 PFJet
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0,
                                    src = cms.InputTag("ZMMProducer", "PFCandidatesNoMuon", "OWNPARTICLES" ) )
## AK4 CHSJet
from CommonTools.ParticleFlow.pfNoPileUpJME_cff import *
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.PFPileUpZMM = pfPileUp.clone( PFCandidates='particleFlowNoMuonTmpPtrs', Vertices = 'goodOfflinePrimaryVertices')
process.PFNoPileUpZMM = pfNoPileUp.clone(topCollection = 'PFPileUpZMM', bottomCollection = 'particleFlowNoMuonTmpPtrs' )
process.ak4PFJetsCHS = ak5PFJets.clone(rParam = 0.4,  jetPtMin = 0.0, src = cms.InputTag("PFNoPileUpZMM"))

## AK4 PuppiJet
from Dummy.Puppi.Puppi_SHCal_SLHC23p1_v1 import *
process.puppiZMM = puppi.clone( PFcandName = cms.InputTag("ZMMProducer", "PFCandidatesNoMuon", "OWNPARTICLES" ))
process.ak4PuppiJets = ak5PFJets.clone(rParam = 0.4,  jetPtMin= 0.0, src = cms.InputTag('puppiZMM','Puppi'))

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PFJet ~~~~~
process.ak4PFRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag(''),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4PFJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L3Absolute_AK4PF.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 CHSJet ~~~~~
process.ak4PFCHSRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                  srcRhoTag      = cms.InputTag(''),
                                  #srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4PFCHSJEC = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L1FastJet_AK4PFchs.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L2Relative_AK4PFchs.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L3Absolute_AK4PFchs.txt"),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PuppiJet ~~~~~
process.ak4PuppiRaw = cms.EDAnalyzer('METPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                  srcRhoTag      = cms.InputTag(''),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

#process.ak4PuppiJEC = cms.EDAnalyzer('METPerformance',
                                  #L1JECTag = cms.string("PhaseII_Shashlik140PU_L1FastJet_AK4Puppi.txt"),
                                  #L2JECTag = cms.string("PhaseII_Shashlik140PU_L2Relative_AK4Puppi.txt"),
                                  #L3JECTag = cms.string("PhaseII_Shashlik140PU_L3Absolute_AK4Puppi.txt"),
                                  #MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon", "OWNPARTICLES"),
                                  #PuppiJetInputTag = cms.InputTag("ak4PuppiJets"),
                                  ##srcRhoTag      = cms.InputTag(''),
                                  #srcRhoTag      = cms.InputTag('kt6PuppiJets','rho'),
                                  #PileUpInfoTag = cms.InputTag("addPileupInfo"),
#)


process.ak4PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4PFJEC )
process.ak4PFCHSProducer = cms.Sequence(process.goodOfflinePrimaryVertices * process.PFPileUpZMM  * process.PFNoPileUpZMM *
                                        process.ak4PFJetsCHS * process.ak4PFCHSRaw * process.ak4PFCHSJEC )
process.puppiProducer = cms.Sequence(process.puppiZMM * process.ak4PuppiJets * process.ak4PuppiRaw)
process.p = cms.Path(process.ak4PFProducer * process.ak4PFCHSProducer * process.puppiProducer)
