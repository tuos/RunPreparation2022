import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
'/store/hidata/HIRun2018A/HILowMultiplicity/AOD/PromptReco-v1/000/326/886/00000/1297EA31-7BD8-8848-A727-9C0A2C06AC58.root'
#'/store/hidata/HIRun2018A/HILowMultiplicity/AOD/PromptReco-v2/000/326/887/00000/493E0169-0956-F446-AFA0-E455E5716DA3.root'
),
)


process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_v3', '')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHIFullTracksLowMultiplicity = process.hltHighLevel.clone()
process.hltHIFullTracksLowMultiplicity.HLTPaths = ["HLT_HIFullTracks_Multiplicity335_HF1OR_v*"]
process.hltHIFullTracksLowMultiplicity.andOr = cms.bool(True)
process.hltHIFullTracksLowMultiplicity.throw = cms.bool(False)

process.LMprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True), # otherwise it won't filter the events
)
process.NoScraping = cms.EDFilter("FilterOutScraping",
 applyfilter = cms.untracked.bool(True),
 debugOn = cms.untracked.bool(False),
 numtrack = cms.untracked.uint32(10),
 thresh = cms.untracked.double(0.25)
)
process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")

#process.load("HeavyIonsAnalysis.VertexAnalysis.pileUpFilter_cff")

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("flow_data_LMPbPb_tree.root"))

process.demo = cms.EDAnalyzer('TreeProduction',
   srcTracks = cms.InputTag("generalTracks"),
   srcVertex= cms.InputTag("offlinePrimaryVertices"),
   srcTower= cms.InputTag("towerMaker"),
   UseQuality = cms.bool(True),
   TrackQuality = cms.string('highPurity')
)

#process.eventSelection = cms.Sequence(process.hltHIFullTracksLowMultiplicity * process.LMprimaryVertexFilter * process.NoScraping * process.hfCoincFilter * process.pileUpFilter_pPb8TeV_vtx1)
process.eventSelection = cms.Sequence(process.hltHIFullTracksLowMultiplicity * process.LMprimaryVertexFilter * process.NoScraping * process.hfCoincFilter)

#process.p = cms.Path(process.demo)
#process.p = cms.Path(process.hltHIFullTracksLowMultiplicity * process.demo)
process.p = cms.Path(process.eventSelection * process.demo)

