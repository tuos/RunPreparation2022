from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Config_pbpbLM_MiniAOD_cfg.py'
config.Data.inputDataset = '/HILowMultiplicity/HIRun2018A-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/tuos/i_ana2021/trees/PbPbLM/PbPbLM335v1_v2mptTree_Nov07'
config.Data.publication = False
config.Data.outputDatasetTag = 'PbPbLM335v1_v2mptTree_Nov07'

#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'PbPbLM335_v2mptTree_Nov07'

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
           print "Failed submitting task: %s" % (hte.headers)
      except ClientException as cle:
          print "Failed submitting task: %s" % (cle)
   
   for num in range(0,2):

       print "Submitting Data Set %d " % (num+1)

       if num == 0:
           RequestName = 'PbPbLM335v1_v2mptTree_Nov07'
           DataSetName = '/HILowMultiplicity/HIRun2018A-PromptReco-v1/AOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbLM/PbPbLM335v1_v2mptTree_Nov07'
       if num == 1:
           RequestName = 'PbPbLM335v2_v2mptTree_Nov07'
           DataSetName = '/HILowMultiplicity/HIRun2018A-PromptReco-v2/AOD'
           LumiMasks = 'Cert_326381_327564_HI_PromptReco_Collisions18_JSON.txt'
           OutDirBase = '/store/user/tuos/i_ana2021/trees/PbPbLM/PbPbLM335v2_v2mptTree_Nov07'
           
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       config.Data.lumiMask = LumiMasks
       config.Data.outLFNDirBase = OutDirBase
       submit(config)

# python crab3_multicrab_cfg.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
