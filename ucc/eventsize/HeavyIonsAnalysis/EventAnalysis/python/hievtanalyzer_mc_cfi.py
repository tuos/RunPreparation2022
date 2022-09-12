import FWCore.ParameterSet.Config as cms

hiEvtAnalyzer = cms.EDAnalyzer('HiEvtAnalyzer',
   CentralitySrc    = cms.InputTag("hiCentrality"),
   CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
   EvtPlane         = cms.InputTag("hiEvtPlane"),
   EvtPlaneFlat     = cms.InputTag("hiEvtPlaneFlat",""),
   HiMC             = cms.InputTag("heavyIon"),
   Vertex           = cms.InputTag("offlineSlimmedPrimaryVerticesRecovery"),
   HFfilters = cms.InputTag("hiHFfilters","hiHFfilters","DQM"),
   doCentrality     = cms.bool(True),
   doEvtPlane       = cms.bool(True),
   doEvtPlaneFlat   = cms.bool(True),
   doVertex         = cms.bool(True),
   doMC             = cms.bool(True),
   doHiMC           = cms.bool(True),
   useHepMC         = cms.bool(False),
   evtPlaneLevel    = cms.int32(0)
)

#from HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi import *

#hiEvtAnalyzer.HFfilters = cms.InputTag("hiHFfilters","hiHFfilters","DQM"),

#hiEvtAnalyzer.doMC   = True
#hiEvtAnalyzer.doHiMC = True
