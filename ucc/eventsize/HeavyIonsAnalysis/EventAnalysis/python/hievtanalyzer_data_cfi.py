import FWCore.ParameterSet.Config as cms

hiEvtAnalyzer = cms.EDAnalyzer('HiEvtAnalyzer',
   CentralitySrc    = cms.InputTag("hiCentrality"),
   CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
   EvtPlane         = cms.InputTag("hiEvtPlane"),
   EvtPlaneFlat     = cms.InputTag("hiEvtPlaneFlat",""),   
   HiMC             = cms.InputTag("heavyIon"),                            
   Vertex           = cms.InputTag("offlineSlimmedPrimaryVerticesRecovery"),
   HFfilters = cms.InputTag("hiHFfilters","hiHFfilters","PAT"),
   doCentrality     = cms.bool(True),
   doEvtPlane       = cms.bool(True),
   doEvtPlaneFlat   = cms.bool(True),                               
   doVertex         = cms.bool(True),
   doMC             = cms.bool(False),
   doHiMC           = cms.bool(False),
   useHepMC         = cms.bool(False),
   evtPlaneLevel    = cms.int32(0)
)
