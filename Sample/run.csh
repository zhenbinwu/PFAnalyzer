#!/bin/tcsh


set step="GEN"
#set step="RAW"
#set step="Reco"
set flag="TimeCut"
#foreach pion (10)
foreach file (SingleNuE10 SinglePiE20HCAL SinglePiE50HCAL)
#foreach pion (2 5 10 25 50 100 500)
  
#============================================================================#
#----------------------------------   GEN   ---------------------------------#
#============================================================================#
  if ($step == "GEN") then
    cmsDriver.py ${file}_cfi --conditions auto:upgrade2019 -n 4000 --eventcontent FEVTDEBUG --relval 10000,100 -s GEN,SIM --datatier GEN-SIM --beamspot Gauss --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019WithGem --geometry Extended2019 --magField 38T_PostLS1 --fileout file:${file}_GEN.root --no_exec

    cp Template/GEN_crab.cfg ${file}_GEN_crab.cfg
    sed -i "s/GEN_OUT/${file}_GEN.root/g"  ${file}_GEN_crab.cfg
    sed -i "s/GEN_CRAB/${file}_cfi_GEN_SIM.py/g" ${file}_GEN_crab.cfg
    sed -i "s/GEN_DIR/${file}_GEN/g" ${file}_GEN_crab.cfg
    crab -cfg ${file}_GEN_crab.cfg -create
  endif


#============================================================================#
#--------------------------------   DIGIRAW   -------------------------------#
#============================================================================#
  if ($step == "RAW") then
    foreach PU (0 140)

      ## Get Minbias
      unset filelist
      #foreach file (`ls /pnfs/cms/WAX/11/store/user/benwu/Upgrade/CMSSW_6_2_0_SLHC6/NoPileUp/SinglePiE${pion}HCAL_GEN/*root`)
      foreach MBfile (`ls /pnfs/cms/WAX/11/store/RelVal/CMSSW_6_2_0_SLHC7/RelValMinBias_TuneZ2star_14TeV/GEN-SIM/DES19_62_V8_UPG2019-v2/00000/*root`)
        if (!($?filelist)) then
          set filelist = /`echo $MBfile | cut -d '/' -f 6-`
        else
          set filelist = /`echo $MBfile | cut -d '/' -f 6-`,$filelist
        endif
      end
      echo $filelist

      unset inputlist
      #foreach IPfile (`ls /pnfs/cms/WAX/11/store/user/benwu/Upgrade/CMSSW_6_2_0_SLHC6/GEN/SinglePiE${pion}HCAL_GEN/*root`)
      #foreach IPfile (./SinglePiE50HCALT_GEN.root)
      #if (!($?inputlist)) then
        #set inputlist = /`echo $IPfile | cut -d '/' -f 6-`
        #else
        #set inputlist = /`echo $IPfile | cut -d '/' -f 6-`,$inputlist
        #endif
        #end
        set inputlist = 'file:./SinglePiE50HCALT_GEN.root'
        echo $inputlist
        if ($PU == 0) then
          cmsDriver.py ${file} --conditions auto:upgrade2019 -n 4000 --eventcontent FEVTDEBUGHLT -s DIGI:pdigi_valid,L1,DIGI2RAW --datatier GEN-SIM-DIGI-RAW --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019 --geometry Extended2019 --magField 38T_PostLS1 --filein $inputlist --fileout file:${file}_${PU}PU_RAW.root --no_exec
          mv ${file}_DIGI_L1_DIGI2RAW.py  ${file}_DIGI_L1_DIGI2RAW_${PU}PU.py 
          #crab -cfg ${file}_${PU}_RAW_crab.cfg -create
        else
          cmsDriver.py ${file} --conditions auto:upgrade2019 -n 4000 --eventcontent FEVTDEBUGHLT -s DIGI:pdigi_valid,L1,DIGI2RAW --datatier GEN-SIM-DIGI-RAW --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019 --geometry Extended2019 --magField 38T_PostLS1 --filein $inputlist --fileout file:${file}_${PU}PU_RAW.root --pileup AVE_${PU}_BX_25ns --pileup_input $filelist --no_exec
          mv ${file}_DIGI_L1_DIGI2RAW_PU.py  ${file}_DIGI_L1_DIGI2RAW_${PU}PU.py 
        endif
        cp Template/RAW_crab.cfg ${file}_${PU}PU_RAW_crab.cfg
        sed -i "s/RAW_CRAB/${file}_DIGI_L1_DIGI2RAW_${PU}PU.py/g" ${file}_${PU}PU_RAW_crab.cfg
        sed -i "s/RAW_OUT/${file}_${PU}PU_RAW.root/g"  ${file}_${PU}PU_RAW_crab.cfg
        sed -i "s/RAW_DIR/${file}_${PU}PU_RAW/g" ${file}_${PU}PU_RAW_crab.cfg
        #cmsDriver.py ${file} --conditions auto:upgrade2019 -n 4000 --eventcontent FEVTDEBUGHLT -s DIGI:pdigi_valid,L1,DIGI2RAW --datatier GEN-SIM-DIGI-RAW --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019 --geometry Extended2019 --magField 38T_PostLS1 --filein $inputlist --fileout file:${file}_RAW.root --pileup AVE_50_BX_25ns --pileup_input $filelist --no_exec
        #cmsDriver.py ${file} --conditions auto:upgrade2019 -n 4000 --eventcontent FEVTDEBUGHLT -s DIGI:pdigi_valid,L1,DIGI2RAW --datatier GEN-SIM-DIGI-RAW --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019 --geometry Extended2019 --magField 38T_PostLS1 --filein $inputlist --fileout file:${file}_RAW.root --pileup AVE_140_BX_25ns --pileup_input $filelist --no_exec
        #cp Template/RAW_crab.cfg ${file}_RAW_crab.cfg
        #sed -i "s/RAW_CRAB/${file}_DIGI_L1_DIGI2RAW_PU.py/g" ${file}_RAW_crab.cfg
        #sed -i "s/RAW_OUT/${file}_RAW.root/g"  ${file}_RAW_crab.cfg
        #sed -i "s/RAW_DIR/${file}_RAW/g" ${file}_RAW_crab.cfg
        #crab -cfg ${file}_RAW_crab.cfg -create
      end
  endif


#============================================================================#
#---------------------------------   Reco   ---------------------------------#
#============================================================================#
  if ($step == "Reco") then
    set outputlist = "OUTPUT_FILE"
    set inputlist = "INPUT_FILE"

    unset minlist
    foreach MBfile (`ls /pnfs/cms/WAX/11/store/RelVal/CMSSW_6_2_0_SLHC7/RelValMinBias_TuneZ2star_14TeV/GEN-SIM/DES19_62_V8_UPG2019-v2/00000/*root`)
      if (!($?minlist)) then
        set minlist = /`echo $MBfile | cut -d '/' -f 6-`
      else
        set minlist = /`echo $MBfile | cut -d '/' -f 6-`,$minlist
      endif
    end



    foreach PU (0PU 50PU 140PU 50PUOOT 140PUOOT)
    #foreach PU (140PUOOT)
      set pNu = `echo $PU | grep -oE "[[:digit:]]{1,}" `
    if ($PU == 0PU) then
      cmsDriver.py ${file} --conditions auto:upgrade2019 -n -1 --eventcontent FEVTDEBUGHLT -s RAW2DIGI,L1Reco,RECO --datatier GEN-SIM-RECO --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019 --geometry Extended2019 --magField 38T_PostLS1 --filein $inputlist --fileout $outputlist --no_exec
      mv ${file}_RAW2DIGI_L1Reco_RECO.py  ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
    else
      cmsDriver.py ${file} --conditions auto:upgrade2019 -n -1 --eventcontent FEVTDEBUGHLT -s RAW2DIGI,L1Reco,RECO --datatier GEN-SIM-RECO --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019 --geometry Extended2019 --magField 38T_PostLS1 --filein $inputlist --fileout $outputlist --pileup AVE_${pNu}_BX_25ns --pileup_input $minlist --no_exec
      mv ${file}_RAW2DIGI_L1Reco_RECO_PU.py  ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
    endif
      sed -i "s/'INPUT_FILE'/os.environ['INPUTFILE'].split(',')/g"  ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
      sed -i "s/'OUTPUT_FILE'/'file:%s'\ %\ os.environ['OUTPUTFILE']/g"  ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
      sed -i '/#\ Output\ definition/r output.txt'  ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
      sed -i "s/outputCommands\ =\ process.FEVTDEBUGHLTEventContent.outputCommands,/outputCommands\ =\ myOutputCommands,/g"  ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
      sed -i "8 iimport\ os" ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 

      if ($PU =~ *OOT) then
        sed -i "s/process.mix.input.nbPileupEvents.averageNumber\ =\ cms.double(${pNu}.000000)/process.mix.input.nbPileupEvents.averageNumber\ =\ cms.double(0.0001)/g" ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
        sed -i '/process.mix.maxBunch\ =\ cms.int32(3)/r OOT.txt' ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
        sed -i "s/process.mix.input.intFixed_OOT\ =\ cms.untracked.int32(50)/process.mix.input.intFixed_OOT\ =\ cms.untracked.int32(${pNu})/g" ${file}_RAW2DIGI_L1Reco_RECO_${PU}_${flag}.py 
      endif


      #${file}_DIGI_L1_DIGI2RECO_${PU}PU.py/g" ${file}_${PU}PU_RECO_crab.cfg
        #crab -cfg ${file}_${PU}_RAW_crab.cfg -create
      #cp Template/RECO_crab.cfg ${file}_${PU}PU_RECO_crab.cfg
      #sed -i "s/RECO_CRAB/${file}_DIGI_L1_DIGI2RECO_${PU}PU.py/g" ${file}_${PU}PU_RECO_crab.cfg
      #sed -i "s/RECO_OUT/${file}_${PU}PU_RECO.root/g"  ${file}_${PU}PU_RECO_crab.cfg
      #sed -i "s/RECO_DIR/${file}_${PU}PU_RECO/g" ${file}_${PU}PU_RECO_crab.cfg

      echo "------------------------------"

      ./Condor.csh  ${file}  ${PU}_RAW RECO_${PU}_${flag}

      #### Submit jobs
      
    endif
  end
end

