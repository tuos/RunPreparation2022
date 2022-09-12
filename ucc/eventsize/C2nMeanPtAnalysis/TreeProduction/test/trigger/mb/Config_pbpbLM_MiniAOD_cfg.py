import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
#'/store/hidata/HIRun2018A/HIMinimumBias12/AOD/04Apr2019-v1/1310004/DE451715-3FD4-674A-801D-D238677D40D8.root'
'/store/hidata/HIRun2018A/HIMinimumBias12/AOD/04Apr2019-v1/30009/311A32E0-6F20-4148-9481-938F56BBFE60.root'
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
                                  fileName=cms.string("flow_data_PbPbMBAOD_tree.root"))

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

process.p = cms.Path(process.demo)
#process.p = cms.Path(process.NoScraping * process.centralityBin * process.demo)
#process.p = cms.Path(process.NoScraping * process.centralityBin * process.demo)
#process.p = cms.Path(process.eventSelection * process.centralityBin * process.demo)

#process.p = cms.Path(process.hltHIMinimumBias_SinglePixelTrack_Npix * process.demo)
#process.p = cms.Path(process.eventSelection * process.demo)

