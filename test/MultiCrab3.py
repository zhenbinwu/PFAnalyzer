#!/usr/bin/env python
# encoding: utf-8

# File        : MultiCrab3.py
# Author      : Ben Wu
# Contact     : benwu@fnal.gov
# Date        : 2015 Apr 01
#
# Description :


import copy, os, time

from CRABAPI.RawCommand import crabCommand
from SHCal_DYMM_crab3Config import config as config

workArea = 'CrabTest'
outDir =  '/store/user/benwu/JetMET_TP/MET/First/'

jobslist = {
    'SLHC23p1_SHCal_140PU_MET' : ['../METPerformance_SHCal_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023SHCALDR-SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO', 3],
    'SLHC23p1_SHCal_0PU_MET' : ['../METPerformance_SHCal_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023SHCALDR-SHCALJan23_NoPU_PH2_1K_FB_V6-v1/GEN-SIM-RECO', 3],

    'SLHC23p1_Aged_140PU_MET' : ['../METPerformance_Phase1_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1age1kfixJan23_PU140BX25_PH1_1K_FB_V2-v1/GEN-SIM-RECO', 3],
    'SLHC23p1_Aged_0PU_MET' : ['../METPerformance_Phase1_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1age1kfixJan23_NoPU_PH1_1K_FB_V2-v1/GEN-SIM-RECO', 3],

    'SLHC23p1_NoAged_50PU_MET' : ['../METPerformance_Phase1_50PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1NoAgedJan23_PU50BX25_DES19_62_V8-v1/GEN-SIM-RECO', 3],
    'SLHC23p1_NoAged_0PU_MET' : ['../METPerformance_Phase1_50PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1NoAgedJan23_NoPU_DES19_62_V8-v1/GEN-SIM-RECO', 3],

    'SLHC23p1_HGCal_140PU_MET' : ['../METPerformance_HGCal_cfg_RECO.py', '/RelValZMM_14TeV/CMSSW_6_2_0_SLHC25_patch2-PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/GEN-SIM-RECO', 1],
    'SLHC23p1_HGCal_0PU_MET' : ['../METPerformance_HGCal_cfg_RECO.py', '/RelValZMM_14TeV/CMSSW_6_2_0_SLHC25_patch2-PH2_1K_FB_V6_UPGHGCalPand-v1/GEN-SIM-RECO', 1],

}
tasklist = {}


for key, value in jobslist.items():
    tempconfig = copy.deepcopy(config)
    tempconfig.General.requestName = key
    tempconfig.General.workArea = workArea
    tempconfig.Data.publishDataName = key
    tempconfig.Data.outLFN = outDir
    if len(value) > 0:
        tempconfig.JobType.psetName = value[0]
    if len(value) > 1:
        tempconfig.Data.inputDataset = value[1]
    if len(value) > 2:
        tempconfig.Data.unitsPerJob = value[2]
    if len(value) > 3:
        tempconfig.Data.totalUnits = value[3]
    results = crabCommand('submit', config = tempconfig)
    tasklist[results['uniquerequestname']] = key
    del tempconfig

while True:
    for request, name in tasklist.items():
        dirname = './%s/crab_%s' % (workArea, name)
        fulldir = os.path.abspath(dirname)
        try:
            results = crabCommand('status', dir=fulldir)
            print "For task", request, "the job states are", results['jobsPerStatus']
        except:
            pass
        time.sleep(20)




