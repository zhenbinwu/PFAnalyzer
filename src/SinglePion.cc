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

#include <bitset>
#include "UserCode/PFAnalyzer/interface/SinglePion.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElementCluster.h"
#include "DataFormats/Common/interface/Ref.h"
//
// constructors and destructor
//
SinglePion::SinglePion(const edm::ParameterSet& iConfig)
{
  hs = new HistTool("fdf");

  GenParticleInputTag_= iConfig.getParameter<edm::InputTag>("GenParticleInputTag");
  PFCandidateInputTag_= iConfig.getParameter<edm::InputTag>("PFCandidateInputTag");
  HbHeRecHitTag_ = iConfig.getParameter<edm::InputTag>("HbHeRecHitTag");
  CaloTowerTag_ = iConfig.getParameter<edm::InputTag>("CaloTowerTag");
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
  hs->AddTH1("NEvents", "Number of Events", 2, 0, 2);
  hs->AddTH1("Rechittime", "Rechittimgng", 400, -100, 100);
  hs->AddTH2("RHTimeEnergy", "Rechit Time vs. Energy", "Energy", "Time", 400, 0, 100, 400, -100, 100);
}

SinglePion::~SinglePion()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
  void
SinglePion::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  iEvent.getByLabel(GenParticleInputTag_, GenParticleHdl); 
  iEvent.getByLabel(PFCandidateInputTag_, PFCandidateHdl); 
  iEvent.getByLabel(HbHeRecHitTag_, HbHeRecHitHdl); 
  iEvent.getByLabel(CaloTowerTag_, CaloTowerHdl); 

  iSetup.get<CaloGeometryRecord>().get(calo);
  
  hs->FillTH1("NEvents", 1);


 
  std::vector<unsigned int> GenIdx;

  double GenE = 0;
  for(unsigned int i=0; i < GenParticleHdl->size(); i++)
  {
    reco::GenParticle gen = GenParticleHdl->at(i);
    if (fabs(gen.pdgId()) == 211  || fabs(gen.pdgId()) == 12)
    {
      GenIdx.push_back(i);
      GenE = gen.p4().E();
      PionGen_Pt->Fill(gen.p4().pt());
      PionGen_Eta->Fill(gen.p4().Eta());
      PionGen_Phi->Fill(gen.p4().Phi());
    }
  }

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
  

  assert(GenE != 0);

  //std::cout << " how many 211? " << GenIdx.size() << std::endl;

  std::vector<unsigned int> CanIdx;
  RecHitMap.clear();

  if (IsPion)
    CanIdx = FilterTurePion(GenIdx);
  else
    CanIdx = FilterPUPion();


  HCalTiming(CanIdx);
  

#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif


}


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
 
  GetHitMap(CanIdx);

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

          //std::cout << ele->type() << std::endl;

          PFClusterRef(ele->clusterRef());
        }
        
      }

      //std::vector<reco::PFBlock> PFBlockV = blkRef.product();

      //for(std::vector<reco::PFBlock>::iterator bit=PFBlockV.begin();
        //bit!=PFBlockV.end(); bit++)
      //{
        
        //std::cout << bit << std::endl;
      //}
      
    }

  }

  return true;
}       // -----  end of function SinglePion::HCalTiming  -----


// ===  FUNCTION  ============================================================
//         Name:  SinglePion::GetHitMap
//  Description:  
// ===========================================================================
bool SinglePion::GetHitMap(std::vector<unsigned int> CanIdx)
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
}       // -----  end of function SinglePion::GetHitMap  -----

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
       //Fuck it reference to CaloTower??
      //for (HBHERecHitCollection::const_iterator j=HbHeRecHitHdl->begin(); j != HbHeRecHitHdl->end(); j++) {
        //std::cout << "Det ID from Cluster " << std::bitset<32>(hit->first.rawId()) <<"  Rechit " << std::bitset<32>(j->detid().rawId() )<< std::endl;
        //if (hit->first == j->detid())
        //{
          //std::cout << "=============================================" << j->time() << std::endl;
        //}
      //}


      //for (edm::SortedCollection<CaloTower>::const_iterator j=CaloTowerHdl->begin(); j != CaloTowerHdl->end(); j++) {
        ////std::cout << "Det ID from Cluster " << std::bitset<32>(hit->first.rawId()) <<"  Rechit " << std::bitset<32>(j->id().rawId() )<< std::endl;
        //if (hit->first == j->id())
        //{
          ////std::cout << "=============================================" << j->hcalTime() << std::endl;
          //const std::vector<DetId>& CHitID =  j->constituents();

          //for(std::vector<DetId>::const_iterator dit=CHitID.begin();
            //dit!=CHitID.end(); dit++)
          //{

            ////std::cout << " Detid from the tower? " <<  std::bitset<32>(dit->rawId()) << std::endl;
            //for (HBHERecHitCollection::const_iterator k=HbHeRecHitHdl->begin(); k != HbHeRecHitHdl->end(); k++) {
              ////std::cout << "Det ID from Cluster " << std::bitset<32>(dit->rawId()) <<"  Rechit " << std::bitset<32>(k->detid().rawId() )<< std::endl;
              //if (*dit == k->detid())
              //{
                ////std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << k->time() << std::endl;
                //hs->FillTH1("Rechittimgng", k->time());
              //}
            //}

          //}

        //}

      //}
//----------------------------------------------------------------------------
//  Not so fuck version
//----------------------------------------------------------------------------
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
            }
          }
      }

    }

      //std::cout << *it << std::endl;
    //const std::vector< reco::PFRecHitFraction >& recHitFractions() const 
      //k
    //std::cout << it-> << std::endl;
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
    //if (can.trackRef()->outerP() < 0.8*GenE || can.trackRef()->outerP() > 1.2*GenE ) continue;
    
    for(unsigned int j=0; j < GenIdx.size(); j++)
    {
      reco::GenParticle gen = PFCandidateHdl->at(GenIdx.at(j));
      double delR = deltaR(can, gen);
      if (delR< 0.3)
      {
        GenPion_deltaR[j].push_front(std::make_pair(delR, i));
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
double SinglePion::GetCorTDCTime(HBHERecHitCollection::const_iterator& recHit) const
{
  
  DetId detId = recHit->detid();
  double tTime = -999.;


  if (detId.det()==DetId::Hcal) {
      HcalSubdetector tHcalSubDet = HcalDetId(detId).subdet();
      tTime = recHit->time();
      if ( (tHcalSubDet==HcalEndcap || tHcalSubDet==HcalBarrel) && tTime > -200 ) {
        if (tHcalSubDet==HcalEndcap) 
          tTime = TDCTimeCorr::tdcCorrHE(tTime, recHit->energy(), HcalDetId(detId).depth());
        else if (tHcalSubDet==HcalBarrel) 
          tTime = TDCTimeCorr::tdcCorrHB(tTime, recHit->energy(), HcalDetId(detId).depth());
        if (tTime > 12 || tTime< -13) 
          return -999;  // this is the cut for all depths for th first try
    }
  }
  return tTime;
}       // -----  end of function SinglePion::GetCorTDCTime  -----
