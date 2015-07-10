// ===========================================================================
// 
//       Filename:  SinglePion.cc
// 
//    Description:  A class for Single pion study
// 
//        Version:  1.0
//        Created:  02/03/2014 01:49:47 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================

#include "UserCode/PFAnalyzer/interface/SinglePion.h"
//
// constructors and destructor
//
SinglePion::SinglePion(const edm::ParameterSet& iConfig)
{
  hs = new HistTool("fdf");

  // Get all the input tags from iConfig
  GetInputTag(iConfig);

  // Book Histogram
  BookHistogram();
}


SinglePion::~SinglePion()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::GetInputTag
//  Description:  Get all the input tag from iConfig
// ===========================================================================
bool SinglePion::GetInputTag(const edm::ParameterSet& iConfig)
{
  PFTrackTag_ = iConfig.getParameter<edm::InputTag>("PFTrackTag");
  GenParticleInputTag_= iConfig.getParameter<edm::InputTag>("GenParticleInputTag");
  PFCandidateInputTag_= iConfig.getParameter<edm::InputTag>("PFCandidateInputTag");
  HbHeRecHitTag_ = iConfig.getParameter<edm::InputTag>("HbHeRecHitTag");
  CaloTowerTag_ = iConfig.getParameter<edm::InputTag>("CaloTowerTag");
  TracksTag_ = iConfig.getParameter<edm::InputTag>("TracksTag");
  HcalPFClusterTag_ = iConfig.getParameter<edm::InputTag>("HcalPFClusterTag");
  EcalPFClusterTag_ = iConfig.getParameter<edm::InputTag>("EcalPFClusterTag");
  PFBlockTag_ = iConfig.getParameter<edm::InputTag>("PFBlockTag");

  EBRecHitTag_ = iConfig.getParameter<edm::InputTag>("EBRecHitTag");
  EERecHitTag_ = iConfig.getParameter<edm::InputTag>("EERecHitTag");

  MatchingdR = iConfig.getUntrackedParameter<double>("MatchingDeltaR");

  return true;
}       // -----  end of function SinglePion::GetInputTag  -----


// ===  FUNCTION  ============================================================
//         Name:  SinglePion::BookHistogram
//  Description:  
// ===========================================================================
bool SinglePion::BookHistogram()
{
  HcalTrk =fs->make<TH1D>("HcalTrk", "Hcal/TrkP", 600, 0, 1.5);
  PionEcal =fs->make<TH1D>("PionEcal", "PionECal", 100, 0, 100);
  PionHcal =fs->make<TH1D>("PionHcal", "PionHCal", 100, 0, 100);
  PionTrkPt =fs->make<TH1D>("PionTrkPt", "PionTrkPt", 500, 0, 100);
  PionTrkP =fs->make<TH1D>("PionTrkP", "PionTrkP", 500, 0, 100);
  PionTrkEta =fs->make<TH1D>("PionTrkEta", "PionTrkEta", 100, -5, 5);
  PionTrkPhi =fs->make<TH1D>("PionTrkPhi", "PionTrkPhi", 140, -7, 7);
  PionGen_Pt = fs->make<TH1D>("PionGen_Pt", "PionGen_Pt", 100, 0, 100);
  PionGen_Eta = fs->make<TH1D>("PionGen_Eta", "PionGen_Eta", 100, -5, 5);
  PionGen_Phi = fs->make<TH1D>("PionGen_Phi", "PionGen_Phi", 140, -7, 7);
  PionGenCan_Pt = fs->make<TH1D>("PionGenCan_Pt", "PionGenCan_Pt", 100, 0, 100);
  PionGenCan_Eta = fs->make<TH1D>("PionGenCan_Eta", "PionGenCan_Eta", 100, -5, 5);
  PionGenCan_Phi = fs->make<TH1D>("PionGenCan_Phi", "PionGenCan_Phi", 140, -7, 7);

  hs->AddTH1("PionTrkP2", "PionTrk P for all PFCandidates", 500, 0, 100);
  hs->AddTH1("NEvents", "Number of Events", 2, 0, 2);
  hs->AddTH1("Rechittime", "Rechit Time from PFCandidate associated with GenPion", "Time", "No. of RecHit", 400, -100, 100);
  hs->AddTH2("RHTimeEnergy", "Rechit Time vs. Energy", "Energy", "Time", 400, 0, 100, 400, -100, 100);
  hs->AddTH1("RechittimeD1", "Rechit time for Detph1", 400, -100, 100);
  hs->AddTH1("RechittimeD2", "Rechit time for Detph2", 400, -100, 100);
  hs->AddTH1("RechittimeD3", "Rechit time for Detph3", 400, -100, 100);
  hs->AddTH1("RechittimeD4", "Rechit time for Detph4", 400, -100, 100);

  hs->AddTH1("HBRechittime", "HB Rechit time", "Time", "No. of HB Rechit", 400, -100, 100);
  hs->AddTH1("HBRechittimeE3", "HB Rechit time(Rechit < 3GeV)","Time", "No. of HB Rechit", 400, -100, 100);
  hs->AddTH1("HBRechittimeE310", "HB Rechit time (3 < Rechit < 10GeV)","Time", "No. of HB Rechit", 400, -100, 100);
  hs->AddTH1("HBRechittimeE10", "HB Rechit time (Rechit > 10GeV)","Time", "No. of HB Rechit", 400, -100, 100);

  hs->AddTH1("HERechittime", "HE Rechit time","Time", "No. of HE Rechit", 400, -100, 100);
  hs->AddTH1("HERechittimeE3", "HE Rechit time (Rechit < 3GeV)","Time", "No. of HE Rechit", 400, -100, 100);
  hs->AddTH1("HERechittimeE310", "HE Rechit time (3 < Rechit < 10GeV)","Time", "No. of HE Rechit", 400, -100, 100);
  hs->AddTH1("HERechittimeE10", "HE Rechit time (Rechit > 10GeV)","Time", "No. of HE Rechit", 400, -100, 100);

  hs->AddTH1("LocalClusterRechittime", "Time of Rechit associated to the Local Cluster", "Time", "No. of Rechit", 400, -100, 100);
  hs->AddTH1("LocalClusterHBRechittime", "Time of HB Rechit associated to the Local Cluster", "Time", "No. of HB Rechit", 400, -100, 100);
  hs->AddTH1("LocalClusterHERechittime", "Time of HE Rechit associated to the Local Cluster", "Time", "No. of HE Rechit", 400, -100, 100);
  hs->AddTH1("NT1LocalClusterRechittime", "ADC Time of noTime Rechit associated to the Local Cluster", "Time", "No. of Rechit", 400, -100, 100);
  hs->AddTH1("NT2LocalClusterRechittime", "ECal Time of noTime Rechit associated to the Local Cluster", "Time", "No. of Rechit", 400, -100, 100);
  hs->AddTH1("NT3LocalClusterRechittime", "HCal Time of noTime Rechit associated to the Local Cluster", "Time", "No. of Rechit", 400, -100, 100);

  hs->AddTH1("TCLocalClusterRechittime", "Time of Rechit associated to the Local Cluster with Timing Cut", "Time", "No. of Rechit", 400, -100, 100);
  hs->AddTH1("TCLocalClusterHBRechittime", "Time of HB Rechit associated to the Local Cluster with Timing Cut", "Time", "No. of HB Rechit", 400, -100, 100);
  hs->AddTH1("TCLocalClusterHERechittime", "Time of HE Rechit associated to the Local Cluster with Timing Cut", "Time", "No. of HE Rechit", 400, -100, 100);

  hs->AddTH2("RHTimeEnergyD1", "Rechit Time vs. Energy Depth1", "Energy", "Time", 400, 0, 100, 400, -100, 100);
  hs->AddTH2("RHTimeEnergyD2", "Rechit Time vs. Energy Depth2", "Energy", "Time", 400, 0, 100, 400, -100, 100);
  hs->AddTH2("RHTimeEnergyD3", "Rechit Time vs. Energy Depth3", "Energy", "Time", 400, 0, 100, 400, -100, 100);
  hs->AddTH2("RHTimeEnergyD4", "Rechit Time vs. Energy Depth4", "Energy", "Time", 400, 0, 100, 400, -100, 100);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ General Tracks ~~~~~
  hs->AddTH1("TracksP", "TracksP", 400, 0, 100);
  hs->AddTH1("TracksPAroundGen", "Tracks Mometum within 0.3 around GenPion", 400, 0, 100);
  hs->AddTH1("HBTracksP", "HB TracksP", 400, 0, 100);
  hs->AddTH1("HBTracksPAroundGen", "HB Tracks Mometum within 0.3 around GenPion", 400, 0, 100);
  hs->AddTH1("HETracksP", "HE TracksP", 400, 0, 100);
  hs->AddTH1("HETracksPAroundGen", "HE Tracks Mometum within 0.3 around GenPion", 400, 0, 100);
  hs->AddTH1("TracksEta", "TracksEta", 140, -7, 7);
  hs->AddTH1("HcalClusterE", "HcalClusterE", 400, 0, 200);
  hs->AddTH1("HcalClusterEAroundGen", "HcalCluster Energy within 0.3 around GenPion", 400, 0, 200);
  hs->AddTH1("EcalClusterE", "EcalClusterE", 400, 0, 200);
  hs->AddTH1("EcalClusterEAroundGen", "EcalCluster Energy within 0.3 around GenPion", 400, 0, 200);
  hs->AddTH1("CaloClusterEAroundGen", "Sum of CaloCluster Energy within 0.3 around GenPion", 400, 0, 200);
  hs->AddTH1("SumRecHitEAroundGen", "Sum of Rechit Energy within 0.3 around GenPion", 400, 0, 200);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PFTrack ~~~~~
  hs->AddTH1("PFTracksP", "PFTracksP", 400, 0, 100);
  hs->AddTH1("PFTracksZ", "PFTracksZ", 400, -20, 20);
  hs->AddTH1("PFTracksPAroundGen", "PFTracks Mometum within 0.3 around GenPion", 400, 0, 100);
  hs->AddTH1("PFTracksZAroundGen", "Z of PFTracks  within 0.3 around GenPion", 400, -20, 20);
  hs->AddTH1("HBPFTracksP", "HB PFTracksP", 400, 0, 100);
  hs->AddTH1("HBPFTracksPAroundGen", "HB PFTracks Mometum within 0.3 around GenPion", 400, 0, 100);
  hs->AddTH1("HEPFTracksP", "HE PFTracksP", 400, 0, 100);
  hs->AddTH1("HEPFTracksPAroundGen", "HE PFTracks Mometum within 0.3 around GenPion", 400, 0, 100);

  hs->AddTH1("HCalLocalCluster2", "HCalLocalCluster cone 0.2", 400, 0, 100);
  hs->AddTH1("HCalLocalClusterHP2", "HCalLocalCluster Hcal/P cone 0.2", 400, 0, 2);
  hs->AddTH1("TCHCalLocalCluster2", "HCalLocalCluster cone 0.2 with Time Cut", 400, 0, 100);
  hs->AddTH1("TCHCalLocalClusterHP2", "HCalLocalCluster Hcal/P cone 0.2 with Time Cut", 400, 0, 2);
  hs->AddTH1("NTHCalLocalCluster2", "HCalLocalCluster cone 0.2 without noTime Rechit", 400, 0, 100);
  hs->AddTH1("NTHCalLocalClusterHP2", "HCalLocalCluster Hcal/P cone 0.2 without noTime Rechit", 400, 0, 2);
  hs->AddTH1("HCalLocalCluster3", "HCalLocalCluster cone 0.3", 400, 0, 100);
  hs->AddTH1("HCalLocalCluster4", "HCalLocalCluster cone 0.4", 400, 0, 100);
  hs->AddTH1("HCalLocalCluster5", "HCalLocalCluster cone 0.5", 400, 0, 100);
  hs->AddTH1("HCalLocalCluster6", "HCalLocalCluster cone 0.6", 400, 0, 100);
  hs->AddTH1("HCalLocalCluster7", "HCalLocalCluster cone 0.7", 400, 0, 100);
  

  // No time rechit studies
  hs->AddTH1("NT1HCalLocalCluster2", "HCalLocalCluster cone 0.2 with noTime Rechit of ADC time", 400, 0, 100);
  hs->AddTH1("NT1HCalLocalClusterHP2", "HCalLocalCluster Hcal/P cone 0.2 with noTime Rechit of ADC time", 400, 0, 2);
  hs->AddTH1("NT2HCalLocalCluster2", "HCalLocalCluster cone 0.2 with noTime Rechit of ECAl hittime", 400, 0, 100);
  hs->AddTH1("NT2HCalLocalClusterHP2", "HCalLocalCluster Hcal/P cone 0.2 with noTime Rechit of ECAl hittime", 400, 0, 2);
  hs->AddTH1("NT3HCalLocalCluster2", "HCalLocalCluster cone 0.2 with noTime Rechit of HCAl hittime", 400, 0, 100);
  hs->AddTH1("NT3HCalLocalClusterHP2", "HCalLocalCluster Hcal/P cone 0.2 with noTime Rechit of HCAl hittime", 400, 0, 2);


  hs->AddTH1("ADCRechittime", "Time of noTime Rechit associated to the Local Cluster with ADC Time", "Time", "No. of Rechit", 400, -100, 100);
  hs->AddTH1("EcalRechittime", "Time of noTime Rechit associated to the Local Cluster with ECAl Time", "Time", "No. of Rechit", 400, -100, 100);
  hs->AddTH1("HcalRechittime", "Time of noTime Rechit associated to the Local Cluster with HCAl Time", "Time", "No. of Rechit", 400, -100, 100);

  return true;
}       // -----  end of function SinglePion::BookHistogram  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::GetHandler
//  Description:  
// ===========================================================================
bool SinglePion::GetHandler(const edm::Event& iEvent)
{
  iEvent.getByLabel(GenParticleInputTag_, GenParticleHdl); 
  iEvent.getByLabel(PFCandidateInputTag_, PFCandidateHdl); 
  iEvent.getByLabel(HbHeRecHitTag_, HbHeRecHitHdl); 
  iEvent.getByLabel(CaloTowerTag_, CaloTowerHdl); 
  iEvent.getByLabel(TracksTag_, TracksHdl); 
  iEvent.getByLabel(HcalPFClusterTag_, HcalPFClusterHdl); 
  iEvent.getByLabel(EcalPFClusterTag_, EcalPFClusterHdl); 
  iEvent.getByLabel(PFBlockTag_, PFBlockHdl); 
  iEvent.getByLabel(PFTrackTag_, PFTrackHdl); 
  iEvent.getByLabel(EBRecHitTag_, EBRecHitHdl); 
  iEvent.getByLabel(EERecHitTag_, EERecHitHdl); 

  return true;
}       // -----  end of function SinglePion::GetHandler  -----


// ------------ method called for each event  ------------
  void
SinglePion::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

//----------------------------------------------------------------------------
//  Global Setup 
//----------------------------------------------------------------------------
  GetHandler(iEvent);
  iSetup.get<CaloGeometryRecord>().get(calo);

  hs->FillTH1("NEvents", 1);
//----------------------------------------------------------------------------
//  Start the analyzer
//----------------------------------------------------------------------------

  PionMap.clear();
  std::vector<unsigned int> GenIdx;

  for(unsigned int i=0; i < GenParticleHdl->size(); i++)
  {
    reco::GenParticle gen = GenParticleHdl->at(i);
    if (fabs(gen.pdgId()) == 211 )
    {
      GenIdx.push_back(i);
      PionMap[i] = PionAso();
      PionMap[i].GenPion = GenParticleHdl->begin() + i;
      PionGen_Pt->Fill(gen.p4().pt());
      PionGen_Eta->Fill(gen.p4().Eta());
      PionGen_Phi->Fill(gen.p4().Phi());
    }
  }

  GeneralTracks(GenIdx);
  HcalPFCluster(GenIdx);
  EcalPFCluster(GenIdx);
  GetHitMapGen(GenIdx);
  PFTracks(GenIdx);
  HcalLocalCluster(0.2); // 3 by 3 cluster
  //HcalLocalCluster(0.3); // 5 by 5 cluster
  //HcalLocalCluster(0.4); // 5 by 5 cluster
  //HcalLocalCluster(0.5); // 5 by 5 cluster
  //HcalLocalCluster(0.6); // 5 by 5 cluster
  //HcalLocalCluster(0.7); // 5 by 5 cluster


  bool IsPion=false;
  for(unsigned int i=0; i < GenIdx.size(); i++)
  {
    reco::GenParticle gen = GenParticleHdl->at(GenIdx.at(i));
    if (fabs(gen.pdgId()) == 211)
    {
      IsPion = true;
      break;
    }
  }
  


  std::vector<unsigned int> CanIdx;

  if (IsPion)
    CanIdx = FilterTurePion(GenIdx);
  // Don't do PUPion for Nv 
  //else
    //CanIdx = FilterPUPion();


  HCalTiming(CanIdx);
  
} // End of Analyzer


// ------------ method called once each job just before starting event loop  ------------
  void 
SinglePion::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
  void 
SinglePion::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
  void 
SinglePion::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
  void 
SinglePion::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
  void 
SinglePion::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
  void 
SinglePion::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SinglePion::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::HCalTiming
//  Description:  
// ===========================================================================
bool SinglePion::HCalTiming(std::vector<unsigned int> CanIdx)
{

  //GetHitMapCan(CanIdx);

  for (unsigned int i = 0; i < CanIdx.size(); ++i)
  {
    reco::PFCandidate can = PFCandidateHdl->at(CanIdx.at(i));

    // Now getting the bloc
    reco::PFCandidate::ElementsInBlocks block = can.elementsInBlocks();

    for(std::vector<reco::PFCandidate::ElementInBlock>::iterator it=block.begin();
        it!=block.end(); it++)
    {
      reco::PFBlockRef blockRef = it->first;

      for(std::vector<reco::PFBlock>::const_iterator bit=blockRef.product()->begin();
          bit!=blockRef.product()->end(); bit++)
      {
        const edm::OwnVector< reco::PFBlockElement >&  elements  = bit->elements();

        for(edm::OwnVector<reco::PFBlockElement>::const_iterator ele=elements.begin();
            ele!=elements.end(); ele++)
        {
          //Get the damn HCAL cluster finally
          if (ele->type() != reco::PFBlockElement::HCAL) continue;

          PFClusterRef(ele->clusterRef());
        }

      }

    }

  }

  return true;
}       // -----  end of function SinglePion::HCalTiming  -----


// ===  FUNCTION  ============================================================
//         Name:  SinglePion::GetHitMapCan
//  Description:  
// ===========================================================================
bool SinglePion::GetHitMapCan(std::vector<unsigned int> CanIdx)
{
  CaloTowerMap.clear();
  
  DeltaR<reco::PFCandidate, CaloTower> CalodeltaR;
  for (edm::SortedCollection<CaloTower>::const_iterator j=CaloTowerHdl->begin(); 
      j != CaloTowerHdl->end(); j++) {
    for (unsigned int i = 0; i < CanIdx.size(); ++i)
    {
      reco::PFCandidate can = PFCandidateHdl->at(CanIdx.at(i));
      if (CalodeltaR(can, *j) < 1.0)
      {
        CaloTowerMap[j->id()] = j;
      }
    }
  } 

  const CaloGeometry *geom = (const CaloGeometry*)calo.product();

  for (HBHERecHitCollection::const_iterator k=HbHeRecHitHdl->begin(); 
      k != HbHeRecHitHdl->end(); k++) {
    const CaloCellGeometry *cell = geom->getGeometry( k->detid());

    for (unsigned int i = 0; i < CanIdx.size(); ++i)
    {
      reco::PFCandidate can = PFCandidateHdl->at(CanIdx.at(i));
      if (reco::deltaR(can.eta(), can.phi(), cell->getPosition().eta(), cell->getPosition().phi() < 1.0))
      {
        RecHitMap[k->detid()] = k;
      }
    }
  }

  //std::cout << " Tower size " << CaloTowerMap.size() <<" RECHit size " << RecHitMap.size() << std::endl;
  return true;
}       // -----  end of function SinglePion::GetHitMapCan  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::PFClusterRef
//  Description:  
// ===========================================================================
bool SinglePion::PFClusterRef(reco::PFClusterRef CRef)
{

  for(std::vector<reco::PFCluster>::const_iterator it=CRef.product()->begin();
      it!=CRef.product()->end(); it++)
  {
    // From PFCluster get the hits? PFRechit or Rechit?
    // recHitFractions return PFRechit
    // hitsAndFractions_ from CaloCluster return hits by detId (Rechit??)
    //
    const std::vector< std::pair<DetId, float> > & hits = it->hitsAndFractions();
    for(std::vector<std::pair<DetId, float> >::const_iterator hit=hits.begin();
        hit!=hits.end(); hit++)
    {
      if (CaloTowerMap.find(hit->first) != CaloTowerMap.end())
      {
        const std::vector<DetId>& CHitID =  CaloTowerMap[hit->first]->constituents();
        for(std::vector<DetId>::const_iterator dit=CHitID.begin();
            dit!=CHitID.end(); dit++)
        {
          if (RecHitMap.find(dit->rawId()) != RecHitMap.end())
          {
            HBHERecHitCollection::const_iterator rhit = RecHitMap[dit->rawId()];
            double RHTime = GetCorTDCTime(rhit);
            hs->FillTH1("Rechittime", RHTime);
            hs->FillTH2("RHTimeEnergy", rhit->energy(), RHTime);
            if (HcalDetId(rhit->detid()).depth() == 1) 
            {
              hs->FillTH1("RechittimeD1", RHTime);
              hs->FillTH2("RHTimeEnergyD1", rhit->energy(), RHTime);

            }
            if (HcalDetId(rhit->detid()).depth() == 2) 
            {
              hs->FillTH1("RechittimeD2", RHTime);
              hs->FillTH2("RHTimeEnergyD2", rhit->energy(), RHTime);
            }
            if (HcalDetId(rhit->detid()).depth() == 3) 
            {
              hs->FillTH1("RechittimeD3", RHTime);
              hs->FillTH2("RHTimeEnergyD3", rhit->energy(), RHTime);
            }
            if (HcalDetId(rhit->detid()).depth() == 4) 
            {
              hs->FillTH1("RechittimeD4", RHTime);
              hs->FillTH2("RHTimeEnergyD4", rhit->energy(), RHTime);
            }
          }
        }
      }

    }

  }


  return true;
}       // -----  end of function SinglePion::PFClusterRef  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::FilterTurePion
//  Description:  
// ===========================================================================
std::vector<unsigned int> SinglePion::FilterTurePion(std::vector<unsigned int> GenIdx)
{
  GenPion_deltaR.clear();
  std::vector<unsigned int> CanIdx;

  DeltaR<reco::PFCandidate, reco::GenParticle> deltaR;

  for(unsigned int i=0; i < PFCandidateHdl->size(); i++)
  {
    reco::PFCandidate can = PFCandidateHdl->at(i);
    if (can.particleId() != 1) continue;
    
    for(unsigned int j=0; j < GenIdx.size(); j++)
    {
      reco::GenParticle gen = GenParticleHdl->at(GenIdx.at(j));
      double delR = deltaR(can, gen);
      double Ediff = fabs(can.trackRef()->outerP()/gen.energy() -1);
      if (delR< 0.5)
      {
        hs->FillTH1("PionTrkP2", can.trackRef()->outerP());
        if (can.trackRef()->outerP() < 0.8*gen.p4().E() 
            || can.trackRef()->outerP() > 1.2*gen.p4().E()) 
          continue;
        GenPion_deltaR[j].push_front(std::make_pair(Ediff, i));
      }
    }
  }

  for(std::map<unsigned int, std::list<std::pair<double, unsigned int> > >::iterator it=GenPion_deltaR.begin();
    it!=GenPion_deltaR.end(); it++)
  {
    reco::GenParticle  gen = GenParticleHdl->at(it->first);
    it->second.sort();
    
    reco::PFCandidate can = PFCandidateHdl->at(it->second.front().second);
    PionEcal->Fill(can.ecalEnergy());
    //if (can.ecalEnergy() < 2)
    if (can.ecalEnergy() < 2)
    {
      PionHcal->Fill(can.hcalEnergy());
      CanIdx.push_back(it->second.front().second);
      reco::TrackRef trk = can.trackRef();
      if (trk.isNonnull())
      {
        PionTrkPt->Fill(trk->outerPt());
        PionTrkP->Fill(trk->outerP());
        PionTrkEta->Fill(trk->outerEta());
        PionTrkPhi->Fill(trk->outerPhi());
        HcalTrk->Fill(can.hcalEnergy()/ trk->outerP() );
        PionGenCan_Pt->Fill(gen.p4().pt());
        PionGenCan_Eta->Fill(gen.p4().Eta());
        PionGenCan_Phi->Fill(gen.p4().Phi());
      }

    }
  }

  return CanIdx;
}       // -----  end of function SinglePion::FilterTurePion  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::FilterPUPion
//  Description:  
// ===========================================================================
std::vector<unsigned int> SinglePion::FilterPUPion()
{
  std::vector<unsigned int> CanIdx;
  for(unsigned int i=0; i < PFCandidateHdl->size(); i++)
  {
    reco::PFCandidate can = PFCandidateHdl->at(i);
    if (can.particleId() != 1) continue;
    CanIdx.push_back(i);
    PionEcal->Fill(can.ecalEnergy());
    PionHcal->Fill(can.hcalEnergy());
    reco::TrackRef trk = can.trackRef();
    PionTrkPt->Fill(trk->outerPt());
    PionTrkP->Fill(trk->outerP());
    PionTrkEta->Fill(trk->outerEta());
    PionTrkPhi->Fill(trk->outerPhi());
    HcalTrk->Fill(can.hcalEnergy()/ trk->outerP() );
  }

  return CanIdx;
}       // -----  end of function SinglePion::FilterPUPion  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::GetCorTDCTime
//  Description:  
// ===========================================================================
double SinglePion::GetCorTDCTime(HBHERecHitCollection::const_iterator& recHit, bool timecut) const
{
  
  DetId detId = recHit->detid();
  double tTime = recHit->time();
  if (detId.det()==DetId::Hcal) {
      HcalSubdetector tHcalSubDet = HcalDetId(detId).subdet();
      if ( (tHcalSubDet==HcalEndcap || tHcalSubDet==HcalBarrel) && tTime > -200 ) {
        if (tHcalSubDet==HcalEndcap) 
          tTime = TDCTimeCorr::tdcCorrHE(tTime, recHit->energy(), HcalDetId(detId).depth());
        else if (tHcalSubDet==HcalBarrel) 
          tTime = TDCTimeCorr::tdcCorrHB(tTime, recHit->energy(), HcalDetId(detId).depth());
        if (timecut)
        {
          if (tTime > 12 || tTime< -13) 
            return -999;  // this is the cut for all depths for th first try
        }
    }
  }
  return tTime;
}       // -----  end of function SinglePion::GetCorTDCTime  -----


// ===  FUNCTION  ============================================================
//         Name:  SinglePion::GeneralTracks
//  Description:  Search the general tracks matching to Gen Pion
// ===========================================================================
bool SinglePion::GeneralTracks( std::vector<unsigned int> GenIdx )
{
  for(unsigned int i=0; i < TracksHdl->size(); i++)
  {
    reco::Track trk = TracksHdl->at(i);
    hs->FillTH1("TracksP", trk.outerP());
    if (fabs(trk.outerEta()) < 1.4) hs->FillTH1("HBTracksP", trk.outerP());
    if (fabs(trk.outerEta()) >  1.6 && fabs(trk.outerEta()) < 3.0) hs->FillTH1("HETracksP", trk.outerP());

    for(unsigned int j=0; j < GenIdx.size(); j++)
    {
      reco::GenParticle gen = GenParticleHdl->at(GenIdx.at(j));
      if (deltaR(gen.eta(), gen.phi(), trk.outerEta(), trk.outerPhi()) < MatchingdR)
      {
        hs->FillTH1("TracksPAroundGen", trk.outerP());
        PionMap[GenIdx.at(j)].vTracks.push_back(TracksHdl->begin()+i);

        if (fabs(trk.outerEta()) < 1.4) 
          hs->FillTH1("HBTracksPAroundGen", trk.outerP());
        if (fabs(trk.outerEta()) >  1.6 && fabs(trk.outerEta()) < 3.0) 
          hs->FillTH1("HETracksPAroundGen", trk.outerP());

      }
    }

  }

  return true;
}       // -----  end of function SinglePion::GeneralTracks  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::HcalPFCluster
//  Description:  
// ===========================================================================
bool SinglePion::HcalPFCluster( std::vector<unsigned int> GenIdx )
{
  for(unsigned int i=0; i < HcalPFClusterHdl->size(); i++)
  {
    reco::PFCluster cluster = HcalPFClusterHdl->at(i);
    hs->FillTH1("HcalClusterE", cluster.energy());

    for(unsigned int j=0; j < GenIdx.size(); j++)
    {
      reco::GenParticle gen = GenParticleHdl->at(GenIdx.at(j));

      if (deltaR(gen.eta(), gen.phi(), cluster.eta(), cluster.phi()) < MatchingdR)
      {
        PionMap[GenIdx.at(j)].vHcalPFCluster.push_back(HcalPFClusterHdl->begin()+i);
        hs->FillTH1("HcalClusterEAroundGen", cluster.energy());
      }

    }
  }
  return true;
}       // -----  end of function SinglePion::HcalPFCluster  -----


// ===  FUNCTION  ============================================================
//         Name:  SinglePion::EcalPFCluster
//  Description:  
// ===========================================================================
bool SinglePion::EcalPFCluster( std::vector<unsigned int> GenIdx )
{
  for(unsigned int i=0; i < EcalPFClusterHdl->size(); i++)
  {
    reco::PFCluster cluster = EcalPFClusterHdl->at(i);
    hs->FillTH1("EcalClusterE", cluster.energy());


    for(unsigned int j=0; j < GenIdx.size(); j++)
    {
      reco::GenParticle gen = GenParticleHdl->at(GenIdx.at(j));
      if (deltaR(gen.eta(), gen.phi(), cluster.eta(), cluster.phi()) < MatchingdR)
      {
        PionMap[GenIdx.at(j)].vEcalPFCluster.push_back(EcalPFClusterHdl->begin()+i);
        hs->FillTH1("EcalClusterEAroundGen", cluster.energy());
      }
    }
  }
  return true;
}       // -----  end of function SinglePion::EcalPFCluster  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::GetHitMapGen
//  Description:  
// ===========================================================================
bool SinglePion::GetHitMapGen( std::vector<unsigned int> GenIdx )
{

  std::vector<double> CaloSum;
  std::vector<double> RecHitSum;
  CaloTowerMap.clear();
  RecHitMap.clear();

  for(unsigned int i=0; i < GenIdx.size(); i++)
  {
    CaloSum.push_back(0);
    RecHitSum.push_back(0);
  }

  
  DeltaR<reco::GenParticle, CaloTower> CalodeltaR;
  for (edm::SortedCollection<CaloTower>::const_iterator j=CaloTowerHdl->begin(); 
      j != CaloTowerHdl->end(); j++) {
    for (unsigned int i = 0; i < GenIdx.size(); ++i)
    {
      reco::GenParticle gen= GenParticleHdl->at(GenIdx.at(i));
      if (CalodeltaR(gen, *j) < 1.0)
      {
        CaloTowerMap[j->id()] = j;
        PionMap[GenIdx.at(i)].vCaloTower.push_back(j);
        CaloSum.at(i) += j->energy();
      }
    }
  } 

  const CaloGeometry *geom = (const CaloGeometry*)calo.product();

  for (HBHERecHitCollection::const_iterator k=HbHeRecHitHdl->begin(); 
      k != HbHeRecHitHdl->end(); k++) {
    const CaloCellGeometry *cell = geom->getGeometry( k->detid());

    if(fabs(cell->getPosition().eta())  < 1.4 )
    {

      hs->FillTH1("HBRechittime", GetCorTDCTime(k));
      if (k->energy() < 3) hs->FillTH1("HBRechittimeE3", GetCorTDCTime(k));
      else if (k->energy() < 10) hs->FillTH1("HBRechittimeE310", GetCorTDCTime(k));
      else  hs->FillTH1("HBRechittimeE10", GetCorTDCTime(k));
    }

    if(fabs(cell->getPosition().eta())  > 1.6 && fabs(cell->getPosition().eta())  < 2.5)
    {

      hs->FillTH1("HERechittime", GetCorTDCTime(k));
      if (k->energy() < 3) hs->FillTH1("HERechittimeE3", GetCorTDCTime(k));
      else if (k->energy() < 10) hs->FillTH1("HERechittimeE310", GetCorTDCTime(k));
      else  hs->FillTH1("HERechittimeE10", GetCorTDCTime(k));
    }


    for (unsigned int i = 0; i < GenIdx.size(); ++i)
    {
      reco::GenParticle gen= GenParticleHdl->at(GenIdx.at(i));
      if (reco::deltaR(gen.eta(), gen.phi(), cell->getPosition().eta(), cell->getPosition().phi() < 0.5))
      {
        RecHitSum.at(i) += k->energy();
        RecHitMap[k->detid()] = k;
        PionMap[GenIdx.at(i)].vRecHit.push_back(k);
      }
    }
  }
  

  for(unsigned int i=0; i < GenIdx.size(); i++)
  {
    hs->FillTH1("CaloClusterEAroundGen", CaloSum.at(i));
    hs->FillTH1("SumRecHitEAroundGen", RecHitSum.at(i));
  }


//----------------------------------------------------------------------------
//  To get the EE and EB Rechit 
//  Anton: his idea is to use the CaloTower constituent for the HCal and Ecal
//  rechit. However, the constituent of the CaloTower are just the detId. So
//  it is not that useful for our purpose. Still use the same idea as the
//  eta/phi around the gen pion for the ecal rechit that we are interested.
//----------------------------------------------------------------------------
  

  for (edm::SortedCollection<EcalRecHit>::const_iterator ecalhit=EBRecHitHdl->begin(); 
      ecalhit != EBRecHitHdl->end(); ecalhit++) {
    const CaloCellGeometry *cell = geom->getGeometry( ecalhit->detid());

    for (unsigned int i = 0; i < GenIdx.size(); ++i)
    {
      reco::GenParticle gen= GenParticleHdl->at(GenIdx.at(i));
      if (reco::deltaR(gen.eta(), gen.phi(), cell->getPosition().eta(), cell->getPosition().phi() < 0.5))
      {
        PionMap[GenIdx.at(i)].vEcalRecHit.push_back(ecalhit);
      }
    }
  }
  for (edm::SortedCollection<EcalRecHit>::const_iterator ecalhit=EERecHitHdl->begin(); 
      ecalhit != EERecHitHdl->end(); ecalhit++) {
    const CaloCellGeometry *cell = geom->getGeometry( ecalhit->detid());

    for (unsigned int i = 0; i < GenIdx.size(); ++i)
    {
      reco::GenParticle gen= GenParticleHdl->at(GenIdx.at(i));
      if (reco::deltaR(gen.eta(), gen.phi(), cell->getPosition().eta(), cell->getPosition().phi() < 0.5))
      {
        PionMap[GenIdx.at(i)].vEcalRecHit.push_back(ecalhit);
      }
    }
  }

  return true;
}       // -----  end of function SinglePion::GetHitMapGen  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::PFTracks
//  Description:  
// ===========================================================================
bool SinglePion::PFTracks( std::vector<unsigned int> GenIdx )
{

  GenPionPFTrack.clear();
  PFTrackMap.clear();
  PFTrack2DMap.clear();

  for(unsigned int i=0; i < PFTrackHdl->size(); i++)
  {
    reco::PFRecTrack rtrk = PFTrackHdl->at(i);

    ////Inner trajet 
    //const reco::PFTrajectoryPoint& closestApproach = 
      //rtrk.trajectoryPoint(reco::PFTrajectoryPoint::ClosestApproach);
    // extra polate
    const reco::PFTrajectoryPoint& atHCAL = 
      rtrk.extrapolatedPoint(reco::PFTrajectoryPoint::HCALEntrance);
    hs->FillTH1("PFTracksP", rtrk.trackRef()->innerMomentum().Mag2());
    hs->FillTH1("PFTracksZ", rtrk.trackRef()->innerPosition().z());

    if (fabs(atHCAL.momentum().eta()) < 1.4) 
      hs->FillTH1("HBPFTracksP", atHCAL.momentum().P());
    if (fabs(atHCAL.momentum().eta()) >  1.6 && fabs(atHCAL.momentum().eta()) < 3.0) 
      hs->FillTH1("HEPFTracksP", atHCAL.momentum().P());

    for(unsigned int j=0; j < GenIdx.size(); j++)
    {
      reco::GenParticle gen = GenParticleHdl->at(GenIdx.at(j));
      // Use the extrapolatedPoint for matching? or should I use the
      // closestApproach for matching?
      //if (deltaR(gen.eta(), gen.phi(), atHCAL.momentum().eta(), atHCAL.momentum().phi()) < 0.5)
      if (deltaR(gen.eta(), gen.phi(), rtrk.trackRef()->innerMomentum().Eta(), 
            rtrk.trackRef()->innerMomentum().Phi()) < 0.3)
      {
        //std::cout << " ---------------------------------" << rtrk.trackRef()->innerPosition().z() << std::endl;
        hs->FillTH1("PFTracksZAroundGen", rtrk.trackRef()->innerPosition().z());
        hs->FillTH1("PFTracksPAroundGen", atHCAL.momentum().P());

        if (fabs(atHCAL.momentum().eta()) < 1.4) 
          hs->FillTH1("HBPFTracksPAroundGen", atHCAL.momentum().P());
        if (fabs(atHCAL.momentum().eta()) >  1.6 && fabs(atHCAL.momentum().eta()) < 3.0) 
          hs->FillTH1("HEPFTracksPAroundGen", atHCAL.momentum().P());

        double Ediff = fabs(atHCAL.momentum().P()/gen.energy() -1);

        GenPionPFTrack[j].push_front(std::make_pair(Ediff, i));
      }
    }
  }

  int matchcount=0;
  //Get the PFTrack assocaite with the GenPion
  for(std::map<unsigned int, std::list<std::pair<double, unsigned int> > >::iterator it=GenPionPFTrack.begin();
    it!=GenPionPFTrack.end(); it++)
  {
    reco::GenParticle gen = GenParticleHdl->at(it->first);
    it->second.sort();

    reco::PFRecTrack rtrk = PFTrackHdl->at(it->second.front().second);
    //std::cout << rtrk.trackId() << std::endl;
    // extra polate
    const reco::PFTrajectoryPoint& atHCAL = 
      rtrk.extrapolatedPoint(reco::PFTrajectoryPoint::HCALEntrance);


    //std::cout << atHCAL.isValid() << " "<< atHCAL.detId() << " " << atHCAL.layer() << std::endl;
    //std::cout << atHCAL.positionREP().eta() << " " << atHCAL.positionREP().phi() <<" g: " << gen.eta() << "  " << gen.phi() << std::endl;
    if (atHCAL.isValid())
    {
      //std::cout << atHCAL.detId() << std::endl;
      //std::cout << " find one " <<  HcalDetId(atHCAL.detId()).ieta() << "      " << HcalDetId(atHCAL.detId()).iphi() << std::endl;
      PFTrackMap[matchcount++] = it->second.front().second;
      PFTrack2DMap.push_back(std::make_pair(atHCAL.positionREP().eta(), atHCAL.positionREP().phi()));
    }
  }

  return true;
}       // -----  end of function SinglePion::PFTracks  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::HcalLocalCluster
//  Description:  
// ===========================================================================
bool SinglePion::HcalLocalCluster(double cone)
{

  HCalLCluster.clear();
  std::vector<double> HCalLClusterTC;
  std::vector<double> HCalLClusterNT;
  std::vector<double> HCalLClusterNT1;
  std::vector<double> HCalLClusterNT2;
  std::vector<double> HCalLClusterNT3;


  assert(PFTrack2DMap.size() == PFTrackMap.size());
  if (PFTrack2DMap.size() == 0) return false;

  std::vector<std::vector<HBHERecHitCollection::const_iterator> > RHCollection;
  for(unsigned int i=0; i < PFTrack2DMap.size(); i++)
  {
    HCalLCluster.push_back(0);
    HCalLClusterTC.push_back(0);
    HCalLClusterNT.push_back(0);
    HCalLClusterNT1.push_back(0);
    HCalLClusterNT2.push_back(0);
    HCalLClusterNT3.push_back(0);

    std::vector<HBHERecHitCollection::const_iterator> temp;
    RHCollection.push_back(temp);
  }

  const CaloGeometry *geom = (const CaloGeometry*)calo.product();
  for(std::map<DetId, HBHERecHitCollection::const_iterator>::const_iterator rhit=RecHitMap.begin();
      rhit!=RecHitMap.end(); rhit++)
  {
    const CaloCellGeometry *cell = geom->getGeometry(rhit->second->detid());
    double RHeta = cell->getPosition().eta();
    double RHphi = cell->getPosition().phi();

    //std::cout << " RH 2D " << RHieta <<"  " <<RHiphi << std::endl;
    for(unsigned int i=0; i < PFTrack2DMap.size(); i++)
    {
      double PFeta =  PFTrack2DMap.at(i).first;
      double PFphi =  PFTrack2DMap.at(i).second;

      //std::cout << " PF 2D " << PFieta <<"  " <<PFiphi << std::endl;
      //if ( abs(RHieta - PFieta) < bsize && abs(RHiphi - PFiphi) < bsize)
      if ( reco::deltaR(PFeta, PFphi, RHeta, RHphi ) < cone)
      {
        HCalLCluster.at(i) += rhit->second->energy();
        RHCollection.at(i).push_back(rhit->second);

        HBHERecHitCollection::const_iterator localhit = rhit->second;
        if (GetCorTDCTime(localhit, true) != -999.)
          HCalLClusterTC.at(i) += rhit->second->energy();
        if (GetCorTDCTime(localhit, false) != -999.) //No time cut, but remove notime 
          HCalLClusterNT.at(i) += rhit->second->energy();

        // no time study
        if (GetCorTDCTime(localhit, false) != -999.) //No time cut, but remove notime 
        {
          HCalLClusterNT1.at(i) += rhit->second->energy();
          HCalLClusterNT2.at(i) += rhit->second->energy();
          HCalLClusterNT3.at(i) += rhit->second->energy();
        }
        else
        {
          std::map<std::string, double> newTime = HcalNoTimeHit(rhit->second);
#ifdef  TIMEADC
         if ( newTime["ADC"] != -999.)
         {
           HCalLClusterNT1.at(i) += rhit->second->energy();
           hs->FillTH1("ADCRechittime", newTime["ADC"]);
         } 
#endif     // -----  not TIMEADC  -----

         if ( newTime["ECAL"] != -999.)
         {
           HCalLClusterNT2.at(i) += rhit->second->energy();
           hs->FillTH1("EcalRechittime", newTime["ECAL"]);
         }
         if ( newTime["HCAL"] != -999.)
         {
           HCalLClusterNT3.at(i) += rhit->second->energy();
           hs->FillTH1("HcalRechittime", newTime["HCAL"]);
         }

        }

      }
    }
  }
  

  // Check the PFEcalcluster
  
  // Remove the PFEcal > 2 GeV for full hadronize pion
  std::map<unsigned int, bool> PassECal;
  std::map<unsigned int, double> TrkMometum;
  for(unsigned int i=0; i < PFTrackMap.size(); i++)
  {
    PassECal[i]=false;
    reco::PFRecTrack rtrk = PFTrackHdl->at(PFTrackMap[i]);
    TrkMometum[i]=rtrk.trackRef()->outerP();

    const reco::PFTrajectoryPoint& atECAL = 
      rtrk.extrapolatedPoint(reco::PFTrajectoryPoint::ECALEntrance);

    if (atECAL.isValid())
    {
      for(unsigned int j=0; j < EcalPFClusterHdl->size(); j++)
      {
        reco::PFCluster ecal = EcalPFClusterHdl->at(j);
        if ( reco::deltaR(atECAL.positionREP().eta(), atECAL.positionREP().phi(), ecal.eta(), ecal.phi() ) < 0.05)
        {
          if (ecal.energy() > 2)  PassECal[i]=false;
          else PassECal[i]=true;
          break;
        }
      }
    }
  }
  
  assert(PassECal.size() == HCalLCluster.size());

  std::stringstream  ss;
  ss << "HCalLocalCluster" << cone*10;
  for(unsigned int i=0; i < HCalLCluster.size(); i++)
  {
    if (PassECal[i]) 
    {
      hs->FillTH1(ss.str(), HCalLCluster.at(i));
      hs->FillTH1("TCHCalLocalCluster2", HCalLClusterTC.at(i));
      hs->FillTH1("NTHCalLocalCluster2", HCalLClusterNT.at(i));
      hs->FillTH1("NT1HCalLocalCluster2", HCalLClusterNT1.at(i));
      hs->FillTH1("NT2HCalLocalCluster2", HCalLClusterNT2.at(i));
      hs->FillTH1("NT3HCalLocalCluster2", HCalLClusterNT3.at(i));
      hs->FillTH1("HCalLocalClusterHP2", HCalLCluster.at(i)/ TrkMometum.at(i) );
      hs->FillTH1("TCHCalLocalClusterHP2", HCalLClusterTC.at(i)/ TrkMometum.at(i) );
      hs->FillTH1("NTHCalLocalClusterHP2", HCalLClusterNT.at(i)/ TrkMometum.at(i) );
      hs->FillTH1("NT1HCalLocalClusterHP2", HCalLClusterNT1.at(i)/ TrkMometum.at(i) );
      hs->FillTH1("NT2HCalLocalClusterHP2", HCalLClusterNT2.at(i)/ TrkMometum.at(i) );
      hs->FillTH1("NT3HCalLocalClusterHP2", HCalLClusterNT3.at(i)/ TrkMometum.at(i) );

      const CaloGeometry *geom = (const CaloGeometry*)calo.product();
      for(unsigned int j=0; j < RHCollection.at(i).size(); j++)
      {
        double RHtime =GetCorTDCTime(RHCollection.at(i).at(j));
        double TCRHtime =GetCorTDCTime(RHCollection.at(i).at(j), true);
        hs->FillTH1("LocalClusterRechittime", RHtime);
        hs->FillTH1("TCLocalClusterRechittime", TCRHtime);
        const CaloCellGeometry *cell = geom->getGeometry(RHCollection.at(i).at(j)->detid());
        if(fabs(cell->getPosition().eta())  < 1.4 )
        {
          hs->FillTH1("LocalClusterHBRechittime", RHtime );
          hs->FillTH1("TCLocalClusterHBRechittime", TCRHtime );
        }
        if(fabs(cell->getPosition().eta())  > 1.6 && fabs(cell->getPosition().eta())  < 2.5)
        {
          hs->FillTH1("LocalClusterHERechittime", RHtime );
          hs->FillTH1("TCLocalClusterHERechittime", TCRHtime );
        }
      }
    }
  }
  return true;
}       // -----  end of function SinglePion::HcalLocalCluster  -----

// ===  FUNCTION  ============================================================
//         Name:  SinglePion::HcalNoTimeHit
//  Description:  
// ===========================================================================
std::map<std::string, double> SinglePion::HcalNoTimeHit(HBHERecHitCollection::const_iterator hcalhit)
{
  assert(hcalhit->time() == -999.);

  std::map<std::string, double> newTime; 

  // Special ADC time from Anton's patch
#ifdef  TIMEADC
  newTime["ADC"] = hcalhit->timeADC();
#endif     // -----  not TIMEADC  -----

  // Get a local small collection of hcal and ecal rechit
  // around this rechit
  std::map<HBHERecHitCollection::const_iterator, int> vHcalRecHit;
  std::map<edm::SortedCollection<EcalRecHit>::const_iterator, double> vEcalRecHit;

  const CaloGeometry *geom = (const CaloGeometry*)calo.product();

  for(std::map<unsigned int, PionAso>::const_iterator pit=PionMap.begin();
    pit!=PionMap.end(); pit++)
  {
    //Get Hcal rechit
    for(std::vector<HBHERecHitCollection::const_iterator>::const_iterator 
        hit=pit->second.vRecHit.begin(); hit!=pit->second.vRecHit.end(); hit++)
    {
      if (fabs(HcalDetId((*hit)->detid()).ieta() - HcalDetId(hcalhit->detid()).ieta())< 3
          && fabs(HcalDetId((*hit)->detid()).iphi() - HcalDetId(hcalhit->detid()).iphi())< 3)
        vHcalRecHit[*hit] =  (HcalDetId((*hit)->detid()).ieta() - HcalDetId(hcalhit->detid()).ieta()) + 
          (HcalDetId((*hit)->detid()).iphi() - HcalDetId(hcalhit->detid()).iphi());
    }

    //Get Ecal rechit
    const CaloCellGeometry *hcalcell = geom->getGeometry( hcalhit->detid());

    for(std::vector<edm::SortedCollection<EcalRecHit>::const_iterator>::const_iterator 
        eit=pit->second.vEcalRecHit.begin(); eit!=pit->second.vEcalRecHit.end(); eit++)
    {

      const CaloCellGeometry *ecalcell = geom->getGeometry((*eit)->detid());

      double deltaR = reco::deltaR(hcalcell->getPosition().eta(), 
          hcalcell->getPosition().phi(), ecalcell->getPosition().eta(), 
          ecalcell->getPosition().phi());
      if (deltaR < 0.2)
        vEcalRecHit[*eit] = deltaR;
    }
  }
  

  //From neiboring hcal hits
  int imin=9;
  HBHERecHitCollection::const_iterator cloesthit = hcalhit;
  for(std::map<HBHERecHitCollection::const_iterator, int>::const_iterator mpit=vHcalRecHit.begin();
    mpit!=vHcalRecHit.end(); mpit++)
  {
    if (mpit->first->time() == -999.) continue;
    if (mpit->second <= imin) 
    {
      imin = mpit->second;
      cloesthit = mpit->first;
    }
  }
  newTime["HCAL"] = GetCorTDCTime(cloesthit, false);

  //For the cloest ecal hit
  
  double getEcalhit = false;
  double deltaR = 1.0;
  edm::SortedCollection<EcalRecHit>::const_iterator cloestecalhit(0);
  for(std::map<edm::SortedCollection<EcalRecHit>::const_iterator, double>::const_iterator ehit=vEcalRecHit.begin();
    ehit!=vEcalRecHit.end(); ehit++)
  {
    if (ehit->first->time() == -999.) continue;
    if (ehit->second <= deltaR)
    {
      deltaR = ehit->second;
      cloestecalhit = ehit->first;
      getEcalhit = true;
    }
  }
  if (getEcalhit)
    newTime["ECAL"] = cloestecalhit->time();
  else
    newTime["ECAL"] = -999.;

  return newTime;
}       // -----  end of function SinglePion::HcalNoTimeHit  -----


