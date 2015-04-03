#!/bin/csh -v

set EXE  = $1
set Input = $2
set outdir = $3

set file = `echo ${Input}`
#set file = `echo ${Input} | awk -F "_" '{OFS = "_"}{$NF = sprintf("%03d", $NF); printf $0}'`
date
source /cvmfs/cms.cern.ch/cmsset_default.csh
tar -xzf filelist.tgz

set CMSSW_BASE = `dirname $EXE `

cd $CMSSW_BASE
eval `scramv1 runtime -csh`
#cd ${_CONDOR_SCRATCH_DIR}
cd -

echo "cmsRun ${EXE} filelist=${file} outputFile=${file}.root "
cmsRun ${EXE} filelist=${file} outputFile=${file}.root  
xrdcp ${file}.root root://cmseos.fnal.gov:1094//${outdir}
if ($status == 0) then
  rm ${file}.root 
  rm filelist.tgz
  rm DYMM*
  echo "All jobs are done!"
endif
date
#Arguments = CMSRun filelist outdir
