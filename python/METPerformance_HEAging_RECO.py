import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
JetEta = 999

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                '/store/mc/Upg2017Summer15DR/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEN-SIM-RECO/NoAgingPU50_DES17_62_V8-v1/10000/000E1FC6-0B1A-E511-8FA5-02163E011DB7.root',
                            )
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


import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('analysis')
options.register ('HEFlag',
                  None, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "Flag for this HE aging condition")

# get and parse the command line arguments
options.parseArguments()

HEFlagMap = {
    '17Age0PU50'   : 'Upg2017Summer15DR-NoAgingPU50_DES17',
    '17Age100PU50' : 'Upg2017Summer15DR-Age100CaloPU50_U17_100FB',
    '17Age150PU50' : 'Upg2017Summer15DR-Age150CaloPU50_U17_150FB',
    '19Age0PU50'   : 'GEM2019Upg14DR-Age0CaloPU50_hcal_DES19',
    '19Age100PU50' : 'GEM2019Upg14DR-Age100CaloPU50_hcal_U19_100FB',
    '19Age150PU50' : 'GEM2019Upg14DR-Age150CaloPU50_hcal_U19_150FB',
    '19Age300PU50' : 'GEM2019Upg14DR-Age300CaloPU50_hcal_U19_300FB',
    '19Age500PU50' : 'GEM2019Upg14DR-Age500CaloPU50_hcal_U19_500FB',
    '19PlanBAge150PU50' : 'GEM2019Upg14DR-Age150CaloNoHEPU50_hcal_U19_150FB',
    '19PlanBAge300PU50' : 'GEM2019Upg14DR-Age300CaloNoHEPU50_hcal_U19_300FB',
    '19PlanBAge500PU50' : 'GEM2019Upg14DR-Age500CaloNoHEPU50_hcal_U19_500FB',
}

if options.HEFlag is None or options.HEFlag not in HEFlagMap:
    print "Missing input HEFlag"

L1PUPPIJEC = HEFlagMap[options.HEFlag] + "_MC_L1FastJet_AK4PUPPI.txt"
L2PUPPIJEC = HEFlagMap[options.HEFlag] + "_MC_L2Relative_AK4PUPPI.txt"
L3PUPPIJEC = HEFlagMap[options.HEFlag] + "_MC_L3Absolute_AK4PUPPI.txt"

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


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ AK4 PuppiJet ~~~~~
process.ak4PuppiRaw = cms.EDAnalyzer('METPerformance',
                                     L1JECTag = cms.string(""),
                                     L2JECTag = cms.string(""),
                                     L3JECTag = cms.string(""),
                                     MuonInputTag = cms.InputTag("ZMMProducer", "ZMMTightMuon"),
                                     JetEtaThresTag = cms.untracked.double(JetEta),
                                     PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                     srcRhoTag      = cms.InputTag(''),
                                     JetJECThresTag = cms.untracked.double(0),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     UseGenJets     = cms.untracked.bool(False),
                                     PileUpInfoTag  = cms.InputTag("addPileupInfo"),
                                     JetsMatchedGen =  cms.untracked.bool(False),
                                     )

process.ak4PuppiJEC = cms.EDAnalyzer('METPerformance',
                                     L1JECTag       = cms.string(L1PUPPIJEC),
                                     L2JECTag       = cms.string(L2PUPPIJEC),
                                     L3JECTag       = cms.string(L3PUPPIJEC),
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
                                     L1JECTag       = cms.string(L1PUPPIJEC),
                                     L2JECTag       = cms.string(L2PUPPIJEC),
                                     L3JECTag       = cms.string(L3PUPPIJEC),
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
                                        L1JECTag       = cms.string(L1PUPPIJEC),
                                        L2JECTag       = cms.string(L2PUPPIJEC),
                                        L3JECTag       = cms.string(L3PUPPIJEC),
                                        PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                        GenJetInputTag = cms.InputTag("ak4GenJets"),
                                        srcRhoTag      = cms.InputTag(''),
                                        PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                        )


process.GenProducer = cms.Sequence(process.genParticlesForJetsNoMuNoNu  * process.ak4GenJets )

process.PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw )

process.puppiProducer = cms.Sequence(process.puppiZMM * process.ak4PuppiJets * process.ak4PuppiRaw * process.ak4PuppiJEC * process.ak4PuppiJEC10)

process.JetPerformance = cms.Sequence(process.JETak4PFRaw * process.JETak4PuppiRaw * process.JETak4PuppiJEC )

process.p = cms.Path(process.goodOfflinePrimaryVertices * process.ZMMProducer *  process.particleFlowNoMuonTmpPtrs *
                     process.GenProducer *process.PFProducer * process.puppiProducer * process.JetPerformance)
