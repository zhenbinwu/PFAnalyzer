from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'SLHC23p1_SHCal_140PU_MET'
config.General.workArea = 'Test1'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../METPerformance_SHCal_cfg_RECO.py'
config.JobType.allowNonProductionCMSSW = False

config.section_("Data")
config.Data.inputDataset = '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023SHCALDR-SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO'
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.publication = False
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.publishDataName = 'DYMM_SLHC23p1_PU_SHcal_MET'
config.Data.outLFN = '/store/user/benwu/JetMET_TP/MET/First/'

config.Data.ignoreLocality = False

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
