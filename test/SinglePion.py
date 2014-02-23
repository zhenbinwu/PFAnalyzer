import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load('Configuration.Geometry.GeometryExtended2019Reco_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgrade2019', '')

import os
from UserCode.PFAnalyzer.BWTool import GetList
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(os.environ['INPUTFILE'].split(','))
)


#initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
    )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )



process.load("UserCode.PFAnalyzer.PFAnalyzer_cfi")
process.PFAnalyzer.HbHeRecHitTag = cms.InputTag("hbheUpgradeReco")
process.PFAnalyzer.HfRecHitTag = cms.InputTag("hfUpgradeReco")

process.load("UserCode.PFAnalyzer.SinglePion_cfi")
process.SinglePion.HbHeRecHitTag = cms.InputTag("hbheUpgradeReco")

process.p = cms.Path(process.SinglePion)


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('file:%s' % os.environ['OUTPUTFILE']))

