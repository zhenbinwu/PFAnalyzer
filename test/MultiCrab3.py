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
from crab3Config import config as config

workArea = 'CrabTest/RandomTest1'
outDir =  '/store/user/benwu/JetMET_TP/NoExTracker/RandomTest1'

jobslist = {
    #'SLHC23p1_SHCal_140PU_MET' : ['../python/METPerformance_SHCal_140PU_cfg_RECO.py',  '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023SHCALDR-SHCALJan23_PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO',           3],
    #'SLHC25p1_SHCal_140PU_MET' : ['../python/METPerformance_SHCal_140PU_cfg_RECO.py',  '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023SHCALDR-SHCALMar26_PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO',           2],
    #'SLHC23p1_SHCal_0PU_MET'   : ['../python/METPerformance_SHCal_NoPU_cfg_RECO.py',   '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023SHCALDR-SHCALJan23_NoPU_PH2_1K_FB_V6-v1/GEN-SIM-RECO',                2],
    #'SLHC23p1_Aged_140PU_MET'  : ['../python/METPerformance_Phase1_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1age1kfixJan23_PU140BX25_PH1_1K_FB_V2-v1/GEN-SIM-RECO', 2],
    #'SLHC23p1_Aged_0PU_MET'    : ['../python/METPerformance_Phase1_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1age1kfixJan23_NoPU_PH1_1K_FB_V2-v1/GEN-SIM-RECO',      2],
    #'SLHC23p1_NoAged_50PU_MET' : ['../python/METPerformance_Phase1_50PU_cfg_RECO.py',  '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1NoAgedJan23_PU50BX25_DES19_62_V8-v1/GEN-SIM-RECO',     2],
    #'SLHC23p1_NoAged_0PU_MET'  : ['../python/METPerformance_Phase1_50PU_cfg_RECO.py',  '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1NoAgedJan23_NoPU_DES19_62_V8-v1/GEN-SIM-RECO',         2, 2],

    #'SLHC26_Ext_140PU_MET' : ['../python/METPerformance_HGCal_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023HGCALDR-HGCALnewsplit_PU140BX25_newsplitPU140_PH2_1K_FB_V6-v3/GEN-SIM-RECO', 2],
    #'SLHC26_NoExt_140PU_MET' : ['../python/METPerformance_HGCal_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023HGCALNoTRKExtDR-PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO', 2],
    #'SLHC25p1_Aged_140PU_MET'  : ['../python/METPerformance_Phase1_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1age1kMar26_PU140BX25_PH1_1K_FB_V2-v3/GEN-SIM-RECO', 2],
    #'SLHC25p1_NoAged_50PU_MET' : ['../python/METPerformance_Phase1_50PU_cfg_RECO.py',  '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1NoAgedMar26_PU50BX25_DES19_62_V8-v1/GEN-SIM-RECO',   2],

    #'SLHC26p2_EE28_140PU_MET' : ['../python/METPerformance_HGCal_140PU_cfg_RECO.py', '/RelValZMM_14TeV/CMSSW_6_2_0_SLHC26_patch2-PH2_1K_FB_V6_HGCalee28PU140-v1/GEN-SIM-RECO', 2],
    #'SLHC26p2_EE24_140PU_MET' : ['../python/METPerformance_HGCal_140PU_cfg_RECO.py', '/RelValZMM_14TeV/CMSSW_6_2_0_SLHC26_patch2-PH2_1K_FB_V6_HGCalee24PU140-v1/GEN-SIM-RECO', 2],
    #'SLHC26p2_EE28_140PU_MET' : ['../python/METPerformance_HGCal_140PU_cfg_RECO.py', '/RelValZMM_14TeV/CMSSW_6_2_0_SLHC26_patch2-PH2_1K_FB_V6_HGCalee18PU140-v1/GEN-SIM-RECO', 2],

    #'SLHC26_Ext_140PU_NoHFMET' : ['../python/METPerformance_HGCal_140PU_NoHF_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023HGCALDR-HGCALnewsplit_PU140BX25_newsplitPU140_PH2_1K_FB_V6-v3/GEN-SIM-RECO', 2],
    'SLHC26_NoExt_140PU_NoHFMET' : ['../python/METPerformance_NoExt_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023HGCALNoTRKExtDR-PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO', 1, 2],
    #'SLHC25p1_Aged_140PU_NoHFMET'  : ['../python/METPerformance_Phase1_140PU_NoHF_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1age1kMar26_PU140BX25_PH1_1K_FB_V2-v3/GEN-SIM-RECO', 2],
    #'SLHC25p1_NoAged_50PU_NoHFMET' : ['../python/METPerformance_Phase1_50PU_NoHF_cfg_RECO.py',  '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/GEM2019Upg14DR-Phase1NoAgedMar26_PU50BX25_DES19_62_V8-v1/GEN-SIM-RECO',   2],

    #'SLHC26p2_EE28_140PU_JET' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC26_patch2-PH2_1K_FB_V6_HGCalee28PU140-v1/GEN-SIM-RECO', 2],
    #'SLHC26p2_EE24_140PU_JET' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC26_patch2-PH2_1K_FB_V6_HGCalee24PU140-v1/GEN-SIM-RECO', 2],
    #'SLHC26p2_EE18_140PU_JET' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC26_patch2-PH2_1K_FB_V6_HGCalee18PU140-v1/GEN-SIM-RECO', 2],
    #'SLHC26_NoExt_140PU_JET' : ['../python/PFAnalyzer_Phase2_cfg.py', '/QCD_Pt-15to3000_Tune4C_14TeV_pythia8/TP2023HGCALNoTRKExtDR-PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO', 2],
    #'SLHC25p1_Ext_140PU_JET' : ['../python/PFAnalyzer_Phase2_cfg.py', '/QCD_Pt-15to3000_Tune4C_14TeV_pythia8/TP2023HGCALDR-HGCALMar26_PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO', 2],
    #'SLHC25p1_Aged_140PU_JET' : ['../python/PFAnalyzer_Phase1_cfg.py', '/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEM2019Upg14DR-Phase1age1kMar26_PU140BX25_PH1_1K_FB_V2-v1/GEN-SIM-RECO', 2],
    #'SLHC25p1_NoAged_140PU_JET' : ['../python/PFAnalyzer_Phase1_cfg.py', '/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEM2019Upg14DR-Phase1NoAgedMar26_PU50BX25_DES19_62_V8-v1/GEN-SIM-RECO', 2],

    #'SLHC23p1_HGCal_140PU_MET' : ['../METPerformance_HGCal_cfg_RECO.py', '/RelValZMM_14TeV/CMSSW_6_2_0_SLHC25_patch2-PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/GEN-SIM-RECO', 1],
    #'SLHC23p1_HGCal_0PU_MET' : ['../METPerformance_HGCal_cfg_RECO.py', '/RelValZMM_14TeV/CMSSW_6_2_0_SLHC25_patch2-PH2_1K_FB_V6_UPGHGCalPand-v1/GEN-SIM-RECO', 1],
    #'SLHC25p2_HGCal_140PU_JET' : [../python/PFAnalyzer_Phase2_cfg.py', '/QCD_Pt-15to3000_Tune4C_14TeV_pythia8/TP2023HGCALDR-HGCALMar26_PU140BX25_PH2_1K_FB_V6-v1/GEN-SIM-RECO', 3],
    #'SLHC25p2_HGCal_140PU_MET' : ['../python/METPerformance_SHCal_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023HGCALDR-HGCALMar26_PU140BX25_PH2_1K_FB_V6-v2/GEN-SIM-RECO', 2],
    #'SLHC25p4_HGCal_140PU_MET' : ['../python/METPerformance_HGCal_140PU_cfg_RECO.py', '/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/TP2023HGCALDR-HGCALnewsplit_PU140BX25_newsplitPU140_PH2_1K_FB_V6-v3/GEN-SIM-RECO', 3],

    #'SLHC25p6_HGCal_140PU_HF' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC25_patch6-PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/GEN-SIM-RECO', 1],
    #'SLHC25p4_HGCal_140PU_HF' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC25_patch4-PU_PH2_1K_FB_V6_UPGHGCalPandPU140-v1/GEN-SIM-RECO', 1],
    #'SLHC25p6_HGCal_0PU_HF' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC25_patch6-PH2_1K_FB_V6_UPGHGCalPand-v1/GEN-SIM-RECO', 2],
    #'SLHC25p4_HGCal_0PU_HF' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC25_patch4-PH2_1K_FB_V6_UPGHGCalPand-v1/GEN-SIM-RECO', 2],
    #'SLHC25_Aged_0PU_HF' : ['../python/PFAnalyzer_Phase2_cfg.py', '/RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC25-PH1_1K_FB_V2_2019GEM1k-v1/GEN-SIM-RECO', 2],


}
tasklist = {}


for key, value in jobslist.items():
    tempconfig = copy.deepcopy(config)
    tempconfig.General.requestName = key
    tempconfig.General.workArea = workArea
    tempconfig.Data.publishDataName = key
    tempconfig.Data.outLFNDirBase = outDir
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

haddcmd = """#!/usr/bin/env python
# encoding: utf-8

# File        : hadd.py
# Author      : Ben Wu
# Contact     : benwu@fnal.gov
# Date        : 2015 Jul 10
#
# Description :
import glob
import subprocess

if __name__ == "__main__":
    g = glob.glob("*/*")
    nfile = 100
    for gdir in g:
        name = gdir.split('/')[-1]
        files = glob.glob("%s/*/*/*root" % gdir)
        fiter  = len(files) / nfile
        if len(files) % nfile != 0:
            fiter += 1
        Plist = []
        for it in range(0, fiter):
            cms = "hadd -f "
            cms += "%s_%d.root " % (name, it)
            if it == 0:
                cms += " ".join(files[:nfile*(it+1)])
            elif it == fiter:
                cms += " ".join(files[nfile*it:])
            else:
                cms += " ".join(files[nfile*it:nfile*(it+1)])
            #print cms
            Plist.append(subprocess.Popen(cms, shell=True))

        exitcode = [p.wait() for p in Plist]

        cms = "hadd -f "
        cms += "%s.root " % name
        rm = "rm "
        for it in range(0, fiter):
            filename =  "%s_%d.root" % (name, it)
            cms += " %s" % filename
            rm += " %s" % filename

        #print cms
        #print rm
        subprocess.call(cms, shell=True)
        subprocess.call(rm, shell=True)
"""
PFNoutDir = "/eos/uscms/%s/" % outDir
try:
    os.makedirs(PFNoutDir)
    file = open("/eos/uscms/%s/hadd.py" % outDir, 'w')
    file.write(haddcmd)
    file.close()
except OSError:
    pass


while True:
    for request, name in tasklist.items():
        dirname = './%s/crab_%s' % (workArea, name)
        fulldir = os.path.abspath(dirname)
        try:
            results = crabCommand('status', dir=fulldir)
            print "For task", request, "the job states are", results['jobsPerStatus']
        except:
            pass
        time.sleep(120)
