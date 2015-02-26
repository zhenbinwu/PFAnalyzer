import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("UserCode.PFAnalyzer.PFAnalyzer_cfi")
process.load("Dummy/Puppi/Puppi_PhaseII_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(

       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/04BE1DAA-209C-E411-A948-0026189438B4.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/061031B6-349C-E411-B9D0-00248C0BE005.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0A1895AA-209C-E411-9725-0026189438CF.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0C5203DC-3A9C-E411-A841-002618943826.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0CB749CC-2B9C-E411-81FC-0025905A48BA.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/0E2DB31A-299C-E411-8E55-0025905938A4.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/103212FE-349C-E411-A687-002618943865.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/123240FB-209C-E411-ABF0-00248C0BE018.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/149048B1-209C-E411-94FD-003048FFD7D4.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/16C83B18-289C-E411-8D71-0025905A612C.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/1877D4FC-309C-E411-802F-00261894395F.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/1EE1AC65-209C-E411-982D-002618943940.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/223F3EB8-349C-E411-B94E-002618943910.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/2619E5A4-279C-E411-9CA3-003048FFD728.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/26A57F46-289C-E411-BE0F-0025905964CC.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/26EE43B4-209C-E411-B352-003048FFD744.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/2A8D63B5-209C-E411-8E88-003048FF86CA.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/30C23CAB-209C-E411-B07F-00248C55CC9D.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/30D59FA8-209C-E411-A908-002618943870.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/3468478B-369C-E411-9FA5-002618943985.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/34C99805-2D9C-E411-84D4-002618943930.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/36443CB0-209C-E411-AD12-003048D25BA6.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/3679D8CC-289C-E411-A30B-002618943916.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/38E6680A-289C-E411-9129-002618943832.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/3C25F2E9-219C-E411-AF75-002590593872.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/3C580C97-279C-E411-8738-00248C55CC9D.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/3E0FFAD1-2C9C-E411-B36A-002618943982.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/404A566D-209C-E411-AF0B-0025905A48FC.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/4C838908-219C-E411-BAE1-002590593876.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/4CBBDC29-389C-E411-9012-0026189438A2.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/4EB2374C-219C-E411-8F67-002590596484.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/543985AE-209C-E411-8317-0025905A60B4.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/56DE2A4D-219C-E411-B36D-002590593878.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/5A6F5030-2E9C-E411-8B01-002618943866.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/5AFDF950-359C-E411-8C53-002618943948.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/60431D0B-3E9C-E411-85B0-0025905964A2.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/667E23FF-349C-E411-B443-002618943807.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/66B2F826-229C-E411-9627-002590596484.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/683F72B6-209C-E411-9801-0025905938A4.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/6AA65C2C-209C-E411-A12F-00248C0BE018.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/6E0A338D-219C-E411-9408-002618943985.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/70126A0F-3B9C-E411-A89B-0026189437F9.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/70548B97-279C-E411-99F4-00248C55CC3C.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/70584B39-219C-E411-8A43-00248C0BE018.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/70D248FE-349C-E411-AD9B-00261894394A.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/745DE698-279C-E411-ABD4-002618943934.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/74B47244-2F9C-E411-8524-00261894397F.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/76A78D55-279C-E411-9A74-00248C0BE018.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/76CD3573-229C-E411-97B8-0025905A605E.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/7A80840B-2F9C-E411-AD09-0026189438DF.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/82AEE868-239C-E411-A164-00261894395F.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/847A8EB4-319C-E411-93C7-002618943981.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/848ED68C-349C-E411-BD17-0025905A605E.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/84B1D541-309C-E411-8666-003048FFCB9E.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/8893175A-319C-E411-819C-002618943972.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/8A212A76-2C9C-E411-A9C0-002618943868.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/8E026B88-219C-E411-87A4-00261894390A.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/8E3AC1AF-209C-E411-A6F6-0025905A611E.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/96D5FD70-209C-E411-923B-0025905B8576.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9CBF18B6-349C-E411-BEA3-002618943856.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/9E441A79-349C-E411-A8B8-002618943900.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/A8AF5A33-389C-E411-91F5-0025905A609E.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/B6406ECC-289C-E411-A5F1-002354EF3BE0.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/B83F85A8-209C-E411-A7D8-0025905A60B0.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/B8A84FE2-359C-E411-B481-002618943947.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/BA626093-219C-E411-85DA-002618943980.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C052BA76-349C-E411-9686-00261894397A.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C2EFE3F7-309C-E411-97E4-002618943854.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C2F9D79D-2D9C-E411-B280-002618FDA287.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C816344F-2F9C-E411-B91D-002618943947.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C88AF4B5-209C-E411-A821-003048FFD75C.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/C8D9198C-219C-E411-A658-002618FDA216.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/CC456697-279C-E411-A590-0025905A48E4.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/CCCFB40A-319C-E411-83BC-002590593872.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D0E50435-389C-E411-B312-002618FDA210.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D2337C32-289C-E411-93BD-002618943934.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D2EC7637-249C-E411-9EB3-0025905A6132.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/D4533AE9-319C-E411-A229-00259059642E.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/DA4F713E-219C-E411-B8C2-002354EF3BE2.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/DED5D749-2F9C-E411-BE3D-00261894388A.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/E0DABC97-279C-E411-9C07-0025905A6122.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/E43DED8D-219C-E411-97F3-00261894397A.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/EA8F7F2D-2E9C-E411-B88D-00261894386F.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/EE6682B5-319C-E411-AD1B-0025905A610C.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/F09084C4-2B9C-E411-B9AC-002618943800.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/F2057C61-209C-E411-A355-002618943910.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/F68E7BE9-339C-E411-9AEA-0026189438B8.root',
       '/store/relval/CMSSW_6_2_0_SLHC23/RelValQCD_Pt_80_120_14TeV/GEN-SIM-RECO/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/FCE08F4E-359C-E411-81DA-00248C0BE005.root'
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/02BBEBC6-A00E-E411-91CD-002618943866.root'

      ###  Calo
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/4A96278E-840E-E411-B53E-00261894397A.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/00AB1998-860E-E411-911B-0026189438F9.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/02BBEBC6-A00E-E411-91CD-002618943866.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/10B0AB58-880E-E411-84C9-002618943856.root'
      ## 3D
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/008EFFA6-E50E-E411-88AF-003048FFD732.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/08062A32-970E-E411-AB5F-0026189438B8.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/0CBC12D7-7C0E-E411-8E22-0025905A60B0.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/20010B66-970E-E411-B815-002618943865.root',
      #'/store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/test3dclus_phase1_PU140bx25_DES19_62_V8-v2/00000/280C269F-670E-E411-A1AD-0025905B858E.root'

       ### SLHC16 Phase2

      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/28523C0F-F518-E411-ACA3-0025905A60B4.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/386A660F-D518-E411-967D-0025905A612E.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/3ADC9932-3219-E411-B1CF-0025905B8582.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/66B4D9DB-FE18-E411-A60F-003048FFCB96.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/886717F5-EB18-E411-9B0D-00248C55CC40.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/A40A18BC-E218-E411-B767-0025905A60C6.root',
      #'/store/relval/CMSSW_6_2_0_SLHC16/RelValTTbar_14TeV/GEN-SIM-RECO/DES23_62_V1_UPG2023SHNoTaper-v1/00000/DA6AE2CD-E818-E411-A6BF-0025905A60E4.root'

     ### SLHC16 Phase I 50PU NoAge-1

        #'file:/data/nbay04/c/benwu/JetMET_TP/SLHC17/QCD_SHCAL_age1k_140PU.root'
       )

     #fileNames = cms.untracked.vstring('root://xrootd.unl.edu//store/mc/GEM2019Upg14DR/QCD_Pt-15to3000_Tune4C_Flat_14TeV_pythia8/GEN-SIM-RECO/testcalotow_phase1_PU140bx25_DES19_62_V8-v2/00000/02BBEBC6-A00E-E411-91CD-002618943866.root')
                            ,
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("Shaslik_140PU_aged_AK4_100.root"),
      closeFileFast = cms.untracked.bool(True)
  )
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'PH2_1K_FB_V4::All'

from JetMETCorrections.Configuration.DefaultJEC_cff import *
from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
from RecoJets.Configuration.RecoPFJets_cff import *
process.load('CommonTools.ParticleFlow.pfNoPileUpJME_cff')
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.ak4PFJets = ak5PFJets.clone(rParam = 0.4 )
process.ak4GenJets = ak5GenJets.clone(rParam = 0.4)
process.ak4PFJetsCHS = ak5PFJetsCHS.clone(rParam = 0.4)
process.ak4PuppiJets = ak5PFJets.clone(rParam = 0.4, src = cms.InputTag('puppi','Puppi'))

process.ak4PFchs = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFchsL1Fastjet"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PFJetsCHS"),
                             #PFJetInputTag = cms.InputTag("ak5PFJetsCHS"),
                             #PFJetInputTag = cms.InputTag("ak5PFJets"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )

process.ak4PF = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PFJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )

process.ak4Puppi  = cms.EDAnalyzer('PFAnalyzer',
                             minTracks = cms.untracked.uint32(1000),
                             PFJetTag = cms.InputTag("ak5PFL1FastL2L3"),
                             HbHeRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             #HbHeRecHitTag = cms.InputTag("hbhereco"),
                             #HfRecHitTag = cms.InputTag("hfreco"),
                             HfRecHitTag = cms.InputTag("hbheUpgradeReco"),
                             HoRecHitTag = cms.InputTag("horeco"),
                             EcalPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             HcalPFRecHitTag = cms.InputTag("particleFlowRecHitHBHE", "Cleaned"),
                             HOPFRecHitTag = cms.InputTag("particleFlowRecHitHO", "Cleaned"),
                             PSPFRecHitTag = cms.InputTag("particleFlowRecHitPS"),
                             EcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFCandidateInputTag = cms.InputTag("particleFlow"),
                             HcalPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             HOPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PSPFClusterTag = cms.InputTag("particleFlowClusterECAL"),
                             PFJetInputTag = cms.InputTag("ak4PuppiJets"),
                             GenJetInputTag = cms.InputTag("ak4GenJets"),
                             CaloJetInputTag = cms.InputTag("ak5CaloJets"),
                             PFMETInputTag = cms.InputTag("pfMet"),
                             GenMETInputTag = cms.InputTag("genMetTrue"),
                             CaloMETInputTag = cms.InputTag("met"),
                             GenParticleInputTag = cms.InputTag("genParticles"),
                             SimCaloHitInputTag = cms.InputTag("g4SimHits", "HcalHits",  "SIM" ),
                             VertexTag = cms.InputTag("offlinePrimaryVertices"),
                             #minTracks = cms.untracked.uint32(1000)
                            )




#process.ak5PFL1Fastjet = process.ak5PFchsL1.clone( PFJetTag = cms.InputTag("ak5PFJetsL1Fast") )

process.Jet4Producer = cms.Sequence(process.pfNoPileUpJMESequence * process.genParticlesForJets * process.ak4PFJets * process.ak4PFJetsCHS *process.ak4GenJets)
process.PuppiProducer = cms.Sequence(process.puppi * process.ak4PuppiJets * process.ak4Puppi)
process.p = cms.Path(process.Jet4Producer * process.ak4PF * process.ak4PFchs * process.PuppiProducer )
#process.p = cms.Path(process.ak5PFchsL1 * process.ak5PFL1 )
##process.p = cms.Path(process.ak5PFchsL1 *process.ak5PFL1Fastjet)

