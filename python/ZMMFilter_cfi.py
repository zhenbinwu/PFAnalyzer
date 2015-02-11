import FWCore.ParameterSet.Config as cms
from CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi import *

ZMMProducer = cms.EDProducer('ZMMFilter',
                                         PFCandidateInputTag = cms.InputTag("particleFlow"),
                                         VertexTag = cms.InputTag("goodOfflinePrimaryVertices"),
                                         TrackTag = cms.InputTag("generalTracks"),
                                         MuonTag = cms.InputTag("muons"),
                                         )

