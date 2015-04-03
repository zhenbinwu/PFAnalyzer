// ===========================================================================
// 
//       Filename:  Perf2D.C
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/26/2015 14:55:48
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


#include "Perf2D.h"

//----------------------------------------------------------------------------
//       Class:  Perf2D
//      Method:  Perf2D
// Description:  constructor
//----------------------------------------------------------------------------
Perf2D::Perf2D (TH2D* hist_, int type_): type(type_)
{
  hist = (TH2D*)hist_->Clone();
  plotBin = false;
}  // -----  end of method Perf2D::Perf2D  (constructor)  -----

//----------------------------------------------------------------------------
//       Class:  Perf2D
//      Method:  Perf2D
// Description:  copy constructor
//----------------------------------------------------------------------------
Perf2D::Perf2D ( const Perf2D &other )
{
}  // -----  end of method Perf2D::Perf2D  (copy constructor)  -----

//----------------------------------------------------------------------------
//       Class:  Perf2D
//      Method:  ~Perf2D
// Description:  destructor
//----------------------------------------------------------------------------
Perf2D::~Perf2D ()
{
}  // -----  end of method Perf2D::-Perf2D  (destructor)  -----

//----------------------------------------------------------------------------
//       Class:  Perf2D
//      Method:  operator =
// Description:  assignment operator
//----------------------------------------------------------------------------
  Perf2D&
Perf2D::operator = ( const Perf2D &other )
{
  if ( this != &other ) {
  }
  return *this;
}  // -----  end of method Perf2D::operator =  (assignment operator)  ---




// ===  FUNCTION  ============================================================
//         Name:  Perf2D::GetPerf
//  Description:  
// ===========================================================================
TH1* Perf2D::GetPerf(std::string name)
{
  TH1D *out = NULL;
  TH1D *tempx = NULL;
  //hist->RebinY(2);

  Double_t metqt[15] = {30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 250, 300, 400, 500};
  Double_t jetpt[17] = {30,35,40,45,57,72,90,120,150,200,300,400,550,750,1000,1500,2000};

  if (false) {
  /*if ( name ==  "h2D_Parrallel_Resolution"  || name ==  "h2D_Perperndicular_Resolution" */
      /*|| name ==  "h2D_ParrallelZpt_Response" || name ==  "MET_Eff") {*/
    hist = ReBin2D(14, metqt);
    tempx = hist->ProjectionX("temppx");
    out = new TH1D(name.c_str(), tempx->GetTitle(), tempx->GetXaxis()->GetNbins(), metqt);
  }else if ( name.find("JetPTPerf") != std::string::npos) {
    hist = ReBin2D(16, jetpt);
    tempx = hist->ProjectionX("temppx");
    out = new TH1D(name.c_str(), tempx->GetTitle(), tempx->GetXaxis()->GetNbins(), jetpt);
  } else
  {
    /*hist->RebinX(10);*/
    tempx = hist->ProjectionX("temppx");
    out = new TH1D(name.c_str(), tempx->GetTitle(), tempx->GetXaxis()->GetNbins(), tempx->GetXaxis()->GetXmin(), tempx->GetXaxis()->GetXmax());
  }
  assert(out->GetXaxis()->GetNbins() == tempx->GetXaxis()->GetNbins());
  /*Double_t xAxis37[10] = {30, 40, 50, 60, 70, 80, 90, 100,  120, 150};*/
  /*hist = ReBin2D(9, xAxis37);*/

    
  for(int nb = 1; nb <= tempx->GetXaxis()->GetNbins(); nb++){
    // histogram mean and RMS
    double hmean    = -999.;
    double hmeanerr = -999.;
    double histrms  = -999.;
    double hrmserr  = -999.;
    // Fitted mean and RMS
    double mean    = -999.;
    double meanerr = -999.;
    double rms     = -999.;
    double rmserr  = -999.;
    double fitchi2 = -999.;
    // Define the output val and valerr
    double val      = -999.;
    double valerr   = -999.;


    TH1 *aux2 = hist->ProjectionY("_py", nb,nb);

     hmean = aux2->GetMean();
     hmeanerr = aux2->GetMeanError();
     histrms = aux2->GetRMS();
     hrmserr = aux2->GetRMSError();

    TF1* g2 = new TF1("g2", "gaus", hmean -1*histrms, hmean + 1*histrms);
    /*TF1* g2 = new TF1("g2", "gaus", hmean -2*histrms, hmean + 2*histrms);*/

    if (aux2->GetEntries() > 0) {

      TFitResultPtr fr2 = aux2->Fit("g2","SR");
      /*TFitResultPtr fr2 = aux2->Fit("g2","qSR");*/

/*
 *      if(0&&jetType[j] == "CHS" && b==3  && nb ==1){
 *
 *        cout << aux2->GetName()<<endl;; 
 *        aux2->Draw();
 *        cout << tempx->GetXaxis()->GetBinCenter(nb) << endl;
 *        cout << jetType[j] << " " << b << " "<<endl;
 *        return histProj;
 *      }
 */

      // Skip if fit failed
      if (fr2.Get() && !fr2->Status()){
         mean    = fr2->Parameter(1);
         meanerr = fr2->ParError(1);
         rms     = fr2->Parameter(2);
         rmserr  = fr2->ParError(2);
         fitchi2 = fr2->Chi2();
      }
    }

//----------------------------------------------------------------------------
//  Done with fitting, fill in the point
//----------------------------------------------------------------------------
   if (type == 1) /// hist MEAN (default definition for TP)
   {
     val = hmean;
     valerr = hmeanerr;
   }

   if (type == 2) /// hist RMS
   {
     val = histrms;
     valerr = hrmserr;
   }


   if (type == 3) /// fitted MEAN
   {
     val = mean;
     valerr = meanerr;
   }

   if (type == 4) /// fitted RMS
   {
     val = rms;
     valerr = rmserr;
   }


   if (type == 6) /// fitted sigma / Hist mean (default definition for TP)
   {
     val = rms / hmean ;
     valerr = val * sqrt( pow(rmserr/rms,2) + pow(hmeanerr/hmean,2));
   }

   if (plotBin && fitchi2 > 10)
   {
     PlotFineBin(name, aux2, g2, nb);
   }
   /*if (valerr / val <= 0.5) {*/
     out->SetBinContent(nb,val);
     out->SetBinError(nb,valerr);
   /*}*/
    //tempx->SetBinContent(nb,val);
    //tempx->SetBinError(nb,valerr);
    delete g2;
  }

  /*TGraphErrors tgrap(tempx);*/
  return out;
}       // -----  end of function Perf2D::GetPerf  -----

// ===  FUNCTION  ============================================================
//         Name:  Perf2D::ReBin2D
//  Description:  
// ===========================================================================
TH2D* Perf2D::ReBin2D(int xsize, double xbins[]) const
{

  //create a new TH2 with your bin arrays spec
  //double xbins[4]={0,70,130,400};
  //double ybins[4]={0,50,100,400};

  std::stringstream ss;
  TString detname(det);
  detname.ReplaceAll(" ", "_");
  ss << detname<<"_" << algo <<"_" << hist->GetName();
  TH2D *h = new TH2D(ss.str().c_str(), hist->GetTitle(), xsize,xbins, hist->GetYaxis()->GetNbins(), hist->GetYaxis()->GetXmin(), hist->GetYaxis()->GetXmax());
  TAxis *xaxis = h->GetXaxis();
  TAxis *yaxis = h->GetYaxis();
  for (int j=1;j<=yaxis->GetNbins();j++) {
    for (int i=1;i<=xaxis->GetNbins();i++) {
      h->Fill(xaxis->GetBinCenter(i),yaxis->GetBinCenter(j),hist->GetBinContent(i,j));
    }
  }
  return h;
}       // -----  end of function Perf2D::ReBin2D  -----

// ===  FUNCTION  ============================================================
//         Name:  Perf2D::DoPlotEachBin
//  Description:  
// ===========================================================================
bool Perf2D::DoPlotEachBin(std::string det_, std::string algo_) 
{
  det = det_;
  algo = algo_;
  plotBin = true;
  return plotBin;
}       // -----  end of function Perf2D::DoPlotEachBin  -----

// ===  FUNCTION  ============================================================
//         Name:  Perf2D::PlotFineBin
//  Description:  
// ===========================================================================
bool Perf2D::PlotFineBin(std::string histname, TH1* hist, TF1* fit, int idx)
{
  TCanvas *c1 = new TCanvas("fdf", "fdf", 600, 500);
  std::stringstream ss;
  TString detname(det);
  detname.ReplaceAll(" ", "_");
  //std::replace(det.begin(), det.end(), " ", "_");
  //std::replace(algo.begin(), algo.end(), " ", "_") ;
  ss <<detname << "_" <<  algo<< "_" << histname << "_" << idx <<".root";
  /*ss <<detname << "_" <<  algo<< "_" << histname << "_" << idx <<".png";*/
  hist->Draw();

  //collect stat of the first histogram (h1) 
  //TPaveStats *tps1 = (TPaveStats*) c1->GetPrimitive("stats");
  //TPaveStats *tps1 = (TPaveStats*) hist->FindObject("stats");
  //tps1->SetName("Histogram");
  //double X1 = tps1->GetX1NDC();
  //double Y1 = tps1->GetY1NDC();
  //double X2 = tps1->GetX2NDC();
  //double Y2 = tps1->GetY2NDC();

  fit->Draw("same");
  c1->Update(); //IMPORTANT

  //[> collect stat of the second histogram (h2) <]
  //TPaveStats *tps2 = (TPaveStats*) fit->FindObject("stats");
  //tps2->SetName("FitResult");
  //tps2->SetTextColor(kRed);
  //tps2->SetLineColor(kRed);
  //tps2->SetX1NDC(X1);
  //tps2->SetX2NDC(X2);
  //tps2->SetY1NDC(Y1-(Y2-Y1));
  //tps2->SetY2NDC(Y1);
  c1->SaveAs(ss.str().c_str());
  delete c1;
  return true;
}       // -----  end of function Perf2D::PlotFineBin  -----
