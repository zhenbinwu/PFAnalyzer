#!/usr/bin/env python
# coding: utf-8

import os
import re
import shutil
import glob
import subprocess
import sys


workArea = 'tmp'
outDir =  '/store/user/benwu/JetMET_TP/MET/First_fds/'

jobslist = {
    'DYMM_Phase1_0PU_aged'    : ['../python/METPerformance_Phase1_140PU_cfg_condor.py', '/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_Phase1_0PU_aged'    , 10, 1],
    'DYMM_Phase1_0PU_noaged'  : ['../python/METPerformance_Phase1_50PU_cfg_condor.py',  '/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_Phase1_0PU_noaged'  , 8,  1],
    'DYMM_Phase1_140PU_aged'  : ['../python/METPerformance_Phase1_140PU_cfg_condor.py', '/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_Phase1_140PU_aged'  , 2,  1],
    'DYMM_Phase1_50PU_noaged' : ['../python/METPerformance_Phase1_50PU_cfg_condor.py',  '/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_Phase1_50PU_noaged' , 2,  1],
    'DYMM_SHCal_0PU_aged'     : ['../python/METPerformance_SHCal_cfg_condor.py',        '/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_SHCal_0PU_aged'     , 8,  1],
    'DYMM_SHCal_140PU_aged'   : ['../python/METPerformance_SHCal_cfg_condor.py',        '/eos/uscms/store/user/lpchgcal/benwu/TP_SLHC23/DYMM_SHCal_140PU_aged'   , 1,  1],
    }


def my_process():
    UpdateDirNames()
    curdir = os.getcwd()
    ## Create the output directory
    try:
        os.makedirs(workArea)
    except OSError:
        pass

    ## Copy files to workArea
    shutil.copy2("condor_config", workArea)
    shutil.copy2("RunCMS.csh", workArea)
    os.chdir(workArea)

    for key, value in jobslist.items():
        njobs = 0
        if len(value) == 3:
            njobs = GetFileList(key, value[1], value[2], 1)
        elif len(value) >= 4:
            njobs = GetFileList(key, value[1], value[2], value[3])

        pydir = GetPYPath(curdir, value[0])
        configName = "%s_condor" % key
        with open(configName, "w") as out:
            for line in open("condor_config", "r"):
                line = line.replace("JOBNAME", key)
                line = line.replace("PYNAME", pydir)
                line = line.replace("OUTDIR", outDir+"/"+key)
                line = line.replace("QUEUE", str(njobs))
                out.write(line)

        #subprocess.call("condor_submit %s" % configName, shell=True)


def GetFileList(name, fdir, fperjob, fraction):
    subprocess.call("rm %s*" % name, shell=True, stdout=open(os.devnull,'w'))
    flist = glob.glob("%s/*.root" % fdir)
    nfiles = len(flist)
    selfiles = nfiles/fraction
    flist = flist[:selfiles]

    for lcount in range(0, len(flist)):
        outname = name + "_" + str(lcount / fperjob)
        with open(outname, "a") as output:
            output.write("%s\n" % flist[lcount])


    subprocess.call("tar -czvf filelist.tgz %s*" % name, shell=True)
    subprocess.call("rm %s_*" % name, shell=True, stdout=open(os.devnull,'w'))
    return len(flist)/fperjob

def GetPYPath(curdir, pyconfig):
    return os.path.abspath(curdir+"/"+pyconfig)

def UpdateDirNames():
    import time
    global workArea
    global outDir

    curtime = time.strftime("%Y%m%d_%H%M%S")
    tmpname = workArea.split("/")
    if tmpname[-1] == '':
        tmpname[-2] = tmpname[-2] + "_"+ curtime
    else:
        tmpname[-1] = tmpname[-1] + "_"+ curtime
    workArea = "/".join(tmpname)

    tmpname = outDir.split("/")
    if tmpname[-1] == '':
        tmpname[-2] = tmpname[-2] + "_"+ curtime
    else:
        tmpname[-1] = tmpname[-1] + "_"+ curtime
    outDir = "/".join(tmpname)


if __name__ == "__main__":
    my_process()
    #UpdateDirNames()

