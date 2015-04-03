import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0093AA51-9CCA-E411-9865-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0246399C-9FCA-E411-A6D5-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/02A88BB0-9ACA-E411-B2A0-0025905B8598.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0415F615-98CA-E411-BD4E-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0C6763C0-99CA-E411-ABB3-0025905A48C0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/10E5186F-9ACA-E411-A4D6-0025905A60BC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/1A68DB2C-9CCA-E411-92CF-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/1ED9AC2C-9CCA-E411-A8A6-0025905A48F0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/22235F62-98CA-E411-824D-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/22A29C0C-96CA-E411-AE42-0025905A60F2.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/247D226E-9ACA-E411-A84F-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/24D974C0-99CA-E411-863D-0025905A6076.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/24E3D92D-9ACA-E411-86C8-0025905B8598.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/2847D7C6-9BCA-E411-9684-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/287FC963-98CA-E411-8C9D-0025905A48C0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/2AD67F24-9BCA-E411-B48E-0025905A48F0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/34017B8D-9DCA-E411-9219-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/36C8FEB7-94CA-E411-8FAB-0026189438C0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/3C3F66BF-99CA-E411-8195-0025905A48C0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/44B22652-9ECA-E411-8817-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/461533B2-9ACA-E411-BD79-0025905A48C0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/488A32E4-97CA-E411-9CC1-0025905A48F0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/4A01FBE3-97CA-E411-AF21-0025905A48FC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/4E1CDFC8-9BCA-E411-9763-0025905A48F0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/4EB3B8EE-96CA-E411-8678-0025905A6070.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/5299C200-96CA-E411-8494-0025905A6084.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/52CC1BD3-96CA-E411-B48B-0025905B8582.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/52E00326-98CA-E411-A385-0025905A60BC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/54DBFCDC-9ACA-E411-87F2-0025905A6076.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/562B8E33-9DCA-E411-8BA9-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/565D5E4E-99CA-E411-91BD-0025905A60BC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/569DA1E9-98CA-E411-9590-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/5846AB4D-99CA-E411-AB57-0025905A610C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/58A9B665-9ACA-E411-A03F-0025905A48C0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/5E265CB0-9ACA-E411-A7AE-0025905A48F0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/5EB78C0A-A2CA-E411-8E7C-0025905A60BE.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/62535EB2-A1CA-E411-9667-003048FF86CA.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/6258134B-95CA-E411-8386-0025905B8610.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/6C4555FE-94CA-E411-973C-0025905A6084.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/74807763-98CA-E411-A880-0025905A6088.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/760F8862-98CA-E411-97DC-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/7653C3D1-95CA-E411-9276-0025905B85B2.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/786A35C8-9BCA-E411-802C-0025905B8598.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/7A3554E5-97CA-E411-9997-0025905B855E.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/7AF1195F-9CCA-E411-AC14-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/821A77E3-98CA-E411-AEAE-0025905A6088.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/823C1BE9-9ACA-E411-BA97-0025905A60D6.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/84D4B624-93CA-E411-A88E-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/865AD9E3-97CA-E411-AED9-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/8C334D72-93CA-E411-8F8C-0025905B8582.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/8E30394F-99CA-E411-953D-0025905A48F0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/90D331B0-9ACA-E411-8280-0025905A60BC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/90D55A8B-99CA-E411-BA62-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9680DB21-9ACA-E411-829A-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/96C6F152-99CA-E411-B15C-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/96D9C6FD-9CCA-E411-AC9A-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9811BBE5-9ACA-E411-A63D-0026189438D9.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9A253FAB-9ACA-E411-B0C7-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9AA16F8C-99CA-E411-92DF-0025905A60BC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9C55184B-95CA-E411-BDFB-0025905A60F4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9C7C7F47-97CA-E411-BE2A-0025905B85AE.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/A460F1BA-98CA-E411-954B-0025905A60BC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/A6A81A25-98CA-E411-8ED3-0025905A60B2.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/ACFEEAD1-96CA-E411-B97A-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/B6295E79-97CA-E411-B01A-0025905A60BC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/BC11ECBE-99CA-E411-8D24-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/BC170ED1-96CA-E411-A99E-0025905B85EE.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/BC3C5578-97CA-E411-BB36-0025905B855C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C28543E0-97CA-E411-A868-0025905A60F2.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C49453C5-9BCA-E411-968A-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C642FB6E-9ACA-E411-830F-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C8677B11-97CA-E411-B94E-0025905B855E.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/CA5BE047-97CA-E411-B8DD-0025905B860E.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/CEB397BE-99CA-E411-9BCC-0025905A48F0.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/CEF272D8-97CA-E411-A7F9-0025905A613C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D07FD4D0-95CA-E411-ACFC-0025905B860E.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D43243D2-96CA-E411-8A1B-0025905B85E8.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D4428A11-97CA-E411-917C-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D65D6A2D-9CCA-E411-B9BE-0025905B8598.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D8490699-9CCA-E411-9267-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/E2CDF8B7-98CA-E411-A085-0025905A48FC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/E40838E4-9ACA-E411-AD46-0025905A6118.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/E490162C-9CCA-E411-80EF-0025905A6066.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/EC2B6AF4-96CA-E411-B1C9-0025905B855C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/EC2EF17D-97CA-E411-B8E3-0025905A610C.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/EE0C370E-96CA-E411-925C-0025905A48FC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/EE9FAEBE-99CA-E411-B8B8-0025905A48FC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/EEB52D21-9DCA-E411-9127-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/F0A28A88-99CA-E411-8EE7-0025905A48FC.root',
       '/store/relval/CMSSW_6_2_0_SLHC25/RelValQCDForPF_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/FE140E63-98CA-E411-954B-0025905A48C0.root'
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("SHCAL_140PU_SLHC25.root"),
      closeFileFast = cms.untracked.bool(True)
  )

## GenJet
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4GenJets = ak5GenJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True,
                                      src = 'genParticlesForJetsNoNu')

## PFJet
from RecoJets.Configuration.RecoPFJets_cff import *
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True)

## CHSJet
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.ak4PFJetsCHS = ak5PFJetsCHS.clone(rParam = 0.4, jetPtMin= 0.0, doAreaFastjet=True)

## PuppiJet
from Dummy.Puppi.Puppi_PhaseII_SLHC23p1_v2 import *
process.load('Dummy.Puppi.Puppi_PhaseII_SLHC23p1_v2')
process.ak4PuppiJets = ak5PFJets.clone(rParam = 0.4,  doAreaFastjet=True,
                                       jetPtMin= 0.0, src = cms.InputTag('puppi','Puppi'))

#============================================================================#
#-------------------------------     PFJet     ------------------------------#
#============================================================================#
process.ak4PFRaw = cms.EDAnalyzer('JetPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  )

process.ak4PFJEC = cms.EDAnalyzer('JetPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L2Relative_AK4PF.txt"),
                                  L3JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L3Absolute_AK4PF.txt"),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  )

process.ak4PFJECL1 = cms.EDAnalyzer('JetPerformance',
                                  L1JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L1FastJet_AK4PF.txt"),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                  PFJetInputTag = cms.InputTag("ak4PFJets"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                  )



#============================================================================#
#-----------------------------     PFCHSJet     -----------------------------#
#============================================================================#
process.ak4PFCHSRaw = cms.EDAnalyzer('JetPerformance',
                                     L1JECTag = cms.string(""),
                                     L2JECTag = cms.string(""),
                                     L3JECTag = cms.string(""),
                                     PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                     PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                     )

process.ak4PFCHSJEC = cms.EDAnalyzer('JetPerformance',
                                     L1JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L1FastJet_AK4PFchs.txt"),
                                     L2JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L2Relative_AK4PFchs.txt"),
                                     L3JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L3Absolute_AK4PFchs.txt"),
                                     PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                     GenJetInputTag = cms.InputTag("ak4GenJets"),
                                     srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                     PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                     )

process.ak4PFCHSJECL1 = cms.EDAnalyzer('JetPerformance',
                                       L1JECTag = cms.string("SLHC23p1_PhaseII_Shashlik140PU_L1FastJet_AK4PFchs.txt"),
                                       L2JECTag = cms.string(""),
                                       L3JECTag = cms.string(""),
                                       PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                                       GenJetInputTag = cms.InputTag("ak4GenJets"),
                                       srcRhoTag      = cms.InputTag('kt6PFJets','rho'),
                                       PileUpInfoTag = cms.InputTag("addPileupInfo"),
                                       )


#============================================================================#
#-----------------------------     PuppiJet     -----------------------------#
#============================================================================#
process.ak4PuppiRaw = cms.EDAnalyzer('JetPerformance',
                                  L1JECTag = cms.string(""),
                                  L2JECTag = cms.string(""),
                                  L3JECTag = cms.string(""),
                                  PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                                  GenJetInputTag = cms.InputTag("ak4GenJets"),
                                  srcRhoTag      = cms.InputTag(''),
                                  PileUpInfoTag = cms.InputTag("addPileupInfo"),
)

process.ak4GenProducer = cms.Sequence(process.genParticlesForJetsNoNu  * process.ak4GenJets )

process.ak4PFProducer = cms.Sequence(process.ak4PFJets * process.ak4PFRaw * process.ak4PFJEC * process.ak4PFJECL1 )
process.ak4PFCHSProducer = cms.Sequence( process.pfNoPileUpJMESequence * process.ak4PFJetsCHS *
                                        process.ak4PFCHSRaw * process.ak4PFCHSJEC *process.ak4PFCHSJECL1 )
process.puppiProducer = cms.Sequence(process.puppi * process.ak4PuppiJets * process.ak4PuppiRaw)
process.p = cms.Path(process.ak4GenProducer * process.ak4PFProducer * process.ak4PFCHSProducer * process.puppiProducer)

