import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 500000

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
'/store/hidata/HIRun2018A/HIMinimumBias9/AOD/04Apr2019-v1/60000/FE030522-2862-6D45-AAFC-EAA308642521.root',
'/store/hidata/HIRun2018A/HIMinimumBias9/AOD/04Apr2019-v1/60000/FE6CAD40-3665-C046-87E3-ADADF26FCFF0.root',
'/store/hidata/HIRun2018A/HIMinimumBias9/AOD/04Apr2019-v1/60000/FE78D88F-FAD8-EF45-AF6E-4FAF4411A25C.root',
'/store/hidata/HIRun2018A/HIMinimumBias9/AOD/04Apr2019-v1/60000/FEA34B41-BD94-CE4F-A98E-1A6D59B06E8D.root',
'/store/hidata/HIRun2018A/HIMinimumBias9/AOD/04Apr2019-v1/60000/FEB09402-0F2A-E645-A313-F904B9A3AD09.root',
'/store/hidata/HIRun2018A/HIMinimumBias9/AOD/04Apr2019-v1/60000/FF066378-4E01-1F45-96A1-4CE7684FD0EA.root'
),
)


process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_v2', '')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHIMinimumBias_SinglePixelTrack_Npix = process.hltHighLevel.clone()
process.hltHIMinimumBias_SinglePixelTrack_Npix.HLTPaths = ["HLT_HIMinimumBias_SinglePixelTrack_Npix*_part*_v*"]
process.hltHIMinimumBias_SinglePixelTrack_Npix.andOr = cms.bool(True)
process.hltHIMinimumBias_SinglePixelTrack_Npix.throw = cms.bool(False)

process.MBAODprimaryVertexFilter = cms.EDFilter("VertexSelector",
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
                                  fileName=cms.string("flow_data_PbPbMBAOD_tree_withntrack.root"))

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("")

process.demo = cms.EDAnalyzer('TreeProduction',
   srcTracks = cms.InputTag("generalTracks"),
   srcVertex= cms.InputTag("offlinePrimaryVertices"),
   srcTower= cms.InputTag("towerMaker"),

#   centrality    = cms.InputTag("hiCentrality","","reRECO"),
#   centralityBin = cms.InputTag("centralityBin","HFtowers"),

   centrality    = cms.InputTag("hiCentrality"),
   centralityBin = cms.InputTag("centralityBin","HFtowers"),
   UseQuality = cms.bool(True),
   TrackQuality = cms.string('highPurity')
)

#process.eventSelection = cms.Sequence(process.hltHIMinimumBias_SinglePixelTrack_Npix * process.MBAODprimaryVertexFilter * process.NoScraping * process.hfCoincFilter * process.pileUpFilter_pPb8TeV_vtx1)
process.eventSelection = cms.Sequence(process.hltHIMinimumBias_SinglePixelTrack_Npix * process.MBAODprimaryVertexFilter * process.NoScraping * process.hfCoincFilter)

#process.p = cms.Path(process.demo)
#process.p = cms.Path(process.NoScraping * process.demo)
#process.p = cms.Path(process.NoScraping * process.centralityBin * process.demo)

#process.p = cms.Path(process.eventSelection * process.centralityBin * process.demo)
process.p = cms.Path(process.hltHIMinimumBias_SinglePixelTrack_Npix * process.MBAODprimaryVertexFilter * process.NoScraping * process.centralityBin * process.demo)

#process.p = cms.Path(process.hltHIMinimumBias_SinglePixelTrack_Npix * process.demo)
#process.p = cms.Path(process.eventSelection * process.demo)

