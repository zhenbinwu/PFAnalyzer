import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
      '/store/relval/CMSSW_6_2_0_SLHC23_patch1/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTapPU140V2-v4/00000/0A2B9775-CE9F-E411-8232-002590495074.root',
        #'/store/mc/TP2023HGCALDR/QCD_Pt-15to3000_Tune4C_14TeV_pythia8/GEN-SIM-RECO/HGCALMar26_PU140BX25_PH2_1K_FB_V6-v1/10000/00D0EA4E-BCDF-E411-AD21-0025904C4F9E.root',

        #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PH2_1K_FB_V6_UPGHGCalPand-v1/00000/687D01DA-13F9-E411-B15B-0025905A6056.root',
        #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PH2_1K_FB_V6_UPGHGCalPand-v1/00000/C0D1BD0B-10F9-E411-8256-0025905A60C6.root',
        #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PH2_1K_FB_V6_UPGHGCalPand-v1/00000/E04C9DD8-13F9-E411-B204-0025905A612E.root'

       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/00675716-4BF9-E411-B487-002618943914.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/0AC753E0-56F9-E411-BDEC-002618943916.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/20320F96-4BF9-E411-B25A-00261894387A.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/2864B24E-92F9-E411-80CE-003048FFCBA4.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/2A8E3679-80F9-E411-925F-0025905938D4.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/2E854EFF-37F9-E411-82DF-0025905A60C6.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/36F92115-4BF9-E411-B756-00261894387A.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/3836392E-45F9-E411-9F52-0025905964C2.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/384029EF-75F9-E411-A9A4-0025905B85E8.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/3AA8E4AE-3BF9-E411-93CC-00261894387A.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/444A4D5B-52F9-E411-A377-002590593878.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/44F5C30D-51F9-E411-B858-0025905A60F8.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/5CB31774-4DF9-E411-ACDA-00261894387A.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/6030FA5D-37F9-E411-89C6-002618FDA207.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/6ACFE0AF-3CF9-E411-B36B-0025905A6056.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/70C668E8-32FA-E411-A16A-0025905A60A8.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/7C77EFA8-B1F9-E411-AA86-002590593878.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/7EEA6D0D-50F9-E411-885A-0025905A60F8.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/82D028AC-9DF9-E411-8DFA-0025905A6076.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/8E42D3AE-45F9-E411-852B-0025905A60C6.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/A44A915C-48F9-E411-A5C9-002618943821.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/A8ACA0F6-32FA-E411-80D8-00261894390E.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/AA6DE259-35F9-E411-A9D7-002354EF3BD0.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/B6C07E77-80F9-E411-83E1-0025905938B4.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/C032F08F-39F9-E411-BB58-00248C0BE014.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/C63F4047-4CF9-E411-A7C2-00261894387A.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/C68C28E3-48F9-E411-89CA-002618943821.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/CA8B87FE-4DF9-E411-851F-0025905A6084.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/CAC73D37-87F9-E411-AD93-003048FFD7A2.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/CE63329B-B1F9-E411-AD7A-0025905A60F8.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/D4919F90-39F9-E411-B2F8-00261894385A.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/DA2BDC33-87F9-E411-AE44-003048FFCC18.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/E8943B24-5CF9-E411-ACE1-0025905A60C6.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/ECF30F8E-51F9-E411-B932-002590593878.root',
       #'/store/relval/CMSSW_6_2_0_SLHC25_patch6/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/00000/F467AA8D-4FF9-E411-8273-002618943916.root',

        'file:/uscms_data/d3/benwu/00675716-4BF9-E411-B487-002618943914.root'

       )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("HGCal_140PU_Fix_AK4_SLHC25p6.root"),
      #fileName = cms.string("SHcal_140PU_aged_AK4_SLHC25.root"),
      closeFileFast = cms.untracked.bool(True)
  )

## GenJet
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4GenJets = ak5GenJets.clone(rParam = 0.4, jetPtMin= 0.0,
                                      doAreaFastjet=True, src = 'genParticlesForJetsNoNu')

process.load('CommonTools.RecoAlgos.TrackWithVertexRefSelector_cfi')
process.load('RecoJets.JetProducers.TracksForJets_cff')
from RecoJets.JetProducers.ak5TrackJets_cfi import ak5TrackJets
process.ak4TrackJets = ak5TrackJets.clone(rParam = 0.4, jetPtMin= 0.0)

## PFJet
from RecoJets.Configuration.RecoPFJets_cff import *
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True)

process.neuPar = cms.EDFilter("CandPtrSelector", src = cms.InputTag("particleFlow"), cut = cms.string("charge == 0"))
process.ak4NeuJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True, src = cms.InputTag('neuPar'))
process.ChaPar = cms.EDFilter("CandPtrSelector", src = cms.InputTag("particleFlow"), cut = cms.string("charge != 0"))
process.ak4ChaJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True, src = cms.InputTag('ChaPar'))

## CHSJet
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.ak4PFJetsCHS = ak5PFJetsCHS.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True)

## CHS no good vertex
process.pfPileUpJMEZW = process.pfPileUpJME.clone(Vertices = 'offlinePrimaryVertices', checkClosestZVertex = True,
                                                  verbose = cms.untracked.bool(False))
process.pfNoPileUpJMEZW = process.pfNoPileUpJME.clone(topCollection = 'pfPileUpJMEZW')
process.ak4PFJetsCHSZW = ak5PFJetsCHS.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True, src ='pfNoPileUpJMEZW')

## PuppiJet
#from Dummy.Puppi.Puppi_PhaseII_SLHC23p1_v1 import *
from Dummy.Puppi.Puppi_PhaseII_SLHC23p1_v2 import *
process.load('Dummy.Puppi.Puppi_PhaseII_SLHC23p1_v2')
process.ak4PuppiJets = ak5PFJets.clone(rParam = 0.4,  doAreaFastjet=True,
                                       jetPtMin= 0.0, src = cms.InputTag('puppi','Puppi'))

#============================================================================#
#-------------------------------     ChaJet     ----------------------------#
#============================================================================#
process.ak4Cha = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4ChaJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )
#============================================================================#
#-------------------------------     NeuJet     ----------------------------#
#============================================================================#
process.ak4Neu = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4NeuJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )

#============================================================================#
#-------------------------------     TrackJet    ----------------------------#
#============================================================================#
process.ak4Track = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4TrackJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )
#============================================================================#
#-------------------------------     PFJet     ------------------------------#
#============================================================================#
process.ak4PF = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PFJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             #VertexTag = cms.InputTag("goodOfflinePrimaryVertices"),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )

#============================================================================#
#-----------------------------     PFCHSJet     -----------------------------#
#============================================================================#
process.ak4PFchs = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFchsL1Fastjet"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                             #PFJetInputTag = cms.InputTag("ak5PFJetsCHS"),
                             #PFJetInputTag = cms.InputTag("ak5PFJets"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             #VertexTag = cms.InputTag("goodOfflinePrimaryVertices"),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )


#============================================================================#
#-----------------------------     PFCHSJet     -----------------------------#
#============================================================================#
process.ak4PFchsZW = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFchsL1Fastjet"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PFJetsCHSZW"),
                             #PFJetInputTag = cms.InputTag("ak5PFJetsCHS"),
                             #PFJetInputTag = cms.InputTag("ak5PFJets"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )



#============================================================================#
#-----------------------------     PuppiJet     -----------------------------#
#============================================================================#
process.ak4Puppi  = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )




process.ak4GenProducer = cms.Sequence(process.genParticlesForJetsNoNu  * process.ak4GenJets )
process.ak4PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PF )
#process.ak4TrackProducer = cms.Sequence( process.ak4TrackJets * process.ak4Track )
process.ak4TrackProducer = cms.Sequence(process.trackWithVertexRefSelector *process.trackRefsForJets * process.ak4TrackJets * process.ak4Track )
process.ak4PFCHSProducer = cms.Sequence( process.pfNoPileUpJMESequence * process.ak4PFJetsCHS * process.ak4PFchs)
process.ak4PFCHSProducerZW = cms.Sequence( process.pfPileUpJMEZW * process.pfNoPileUpJMEZW * process.ak4PFJetsCHSZW * process.ak4PFchsZW)
process.puppiProducer = cms.Sequence(process.puppi * process.ak4PuppiJets * process.ak4Puppi)
process.ak4NeuProducer = cms.Sequence(process.neuPar * process.ak4NeuJets * process.ak4Neu)
process.ak4ChaProducer = cms.Sequence(process.ChaPar * process.ak4ChaJets * process.ak4Cha)
#process.p = cms.Path(process.ak4GenProducer * process.ak4PFProducer )
#process.p = cms.Path(process.ak4ChaProducer *process.ak4NeuProducer *process.ak4GenProducer * process.ak4TrackProducer * process.ak4PFProducer )
                     #* process.ak4PFCHSProducer * process.puppiProducer)
process.p = cms.Path(process.ak4GenProducer * process.ak4PFProducer * process.ak4NeuProducer *  process.ak4ChaProducer
                     * process.ak4PFCHSProducer * process.puppiProducer)
#process.p = cms.Path( process.ak4PFCHSProducer * process.ak4PFProducer)
#process.p = cms.Path(process.ak4ChaProducer *process.ak4NeuProducer *process.ak4GenProducer * process.ak4TrackProducer * process.ak4PFProducer * process.ak4PFCHSProducer * process.ak4PFCHSProducerZW * process.puppiProducer)

