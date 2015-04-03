// ===========================================================================
// 
//       Filename:  TPlot.C
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/26/2015 14:55:11
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================


#include "TPlot.h"
#include "Perf2D.h"
/*#include "CMS_lumi_v2.h"*/

//----------------------------------------------------------------------------
//       Class:  TPlot
//      Method:  TPlot
// Description:  constructor
//----------------------------------------------------------------------------
TPlot::TPlot ( std::map<std::string, TFile*> &detFile_, std::map<std::string, std::string> &algDir_):
  detFile(detFile_), algDir(algDir_)
{
  SetTPStyle();
}  // -----  end of method TPlot::TPlot  (constructor)  -----

/*//----------------------------------------------------------------------------*/
/*//       Class:  TPlot*/
/*//      Method:  TPlot*/
/*// Description:  copy constructor*/
/*//----------------------------------------------------------------------------*/
/*TPlot::TPlot ( const TPlot &other )*/
/*{*/
/*}  // -----  end of method TPlot::TPlot  (copy constructor)  -----*/

//----------------------------------------------------------------------------
//       Class:  TPlot
//      Method:  ~TPlot
// Description:  destructor
//----------------------------------------------------------------------------
TPlot::~TPlot ()
{
}  // -----  end of method TPlot::-TPlot  (destructor)  -----

//----------------------------------------------------------------------------
//       Class:  TPlot
//      Method:  operator =
// Description:  assignment operator
//----------------------------------------------------------------------------
  TPlot&
TPlot::operator = ( const TPlot &other )
{
  if ( this != &other ) {
  }
  return *this;
}  // -----  end of method TPlot::operator =  (assignment operator)  ---

// ===  FUNCTION  ============================================================
//         Name:  TPlot::Add
//  Description:  
// ===========================================================================
bool TPlot::Add(std::string det, std::string algo) 
{
  plist.push_back(std::make_pair(det, algo));
  return true;
}       // -----  end of function TPlot::Add  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::GetAllHist
//  Description:  
// ===========================================================================
bool TPlot::GetAllHist()
{
  assert(plist.size() > 0);
  TFile *m2File = detFile[plist.front().first];
  m2File->cd();
  std::string PATH = algDir[plist.front().second];


  gDirectory->cd(PATH.c_str());
  TIter next (gDirectory->GetListOfKeys());
  std::map<std::string, int> variable;
  std::vector<std::string> varVec;
  TKey *key;
  while ((key= (TKey*) next()))
  {
    std::string  clname = key->GetClassName() ;
    if ( clname == "TH1D" )
    {
      std::string stdname=key->GetName();
      variable.insert(std::pair<std::string, int>(stdname, 1));
    }

    if ( clname == "TH2D" )
    {
      std::string stdname=key->GetName();
      list2D.insert(stdname);
    }

  }
  for (std::map<std::string, int>::iterator it = variable.begin(); 
      it != variable.end(); ++it)
  {
    list1D.insert(it->first);
  }

  return true;
}       // -----  end of function TPlot::GetAllHist  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::SetTPStyle
//  Description:  
// ===========================================================================
bool TPlot::SetTPStyle() const
{

  /*gROOT->LoadMacro("tdrstyle.C");*/
  /*gROOT->ProcessLine("setTDRStyle()");*/
  /*gROOT->LoadMacro("CMS_lumi_v2.C");*/

  /*writeExtraText = false;       // if extra text*/
  /*extraText  = "Preliminary";  // default extra text is "Preliminary"*/
  /*lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"*/
  /*lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"*/

  /*int iPeriod = 14;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 14= PU=140,14TeV*/
  /*int iPos = 11;   // iPos=11 : top-left, left-aligned*/
  /*// iPos=33 : top-right, right-aligned*/
  /*// iPos=22 : center, centered*/
  /*int W = 800;*/
  /*int H = 600;*/
  /*int H_ref = 600; */
  /*int W_ref = 800; */
  
  /*// references for T, B, L, R*/
  /*float T = 0.08*H_ref;*/
  /*float B = 0.12*H_ref; */
  /*float L = 0.12*W_ref;*/
  /*float R = 0.04*W_ref;*/
  return true;
}       // -----  end of function TPlot::SetTPStyle  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::Compare1D
//  Description:  
// ===========================================================================
bool TPlot::Compare1D(std::string histname)
{
  std::vector<PlotID> vth1;

  for(unsigned int i=0; i < plist.size(); ++i)
  {
    PlotID temp;
    temp.name = histname;
    temp.det = plist.at(i).first;
    temp.algo = plist.at(i).second;
    temp.marker = detMark[temp.det];
    temp.color = algColor[temp.algo];
    temp.hist = GetHist1D(histname, temp.det, temp.algo);
    vth1.push_back(temp);
  }

  TCanvas *c1 = new TCanvas("Canvas", "Yes, another Canvas", 10, 10, 800, 600);
  TLegend *leg = new TLegend(0.660804,0.5776614,0.959799,0.9319372,NULL,"brNDC");

  
  TAxis* xaxis = NULL;
  TAxis* yaxis = NULL;
  double Ymax = 0;
  double ingl = 0;
  for(unsigned int i=0; i < vth1.size(); ++i)
  {
    PlotID  plot1D = vth1.at(i);
    
    // Set Marker and Color
    plot1D.hist->SetMarkerStyle(plot1D.marker);
    plot1D.hist->SetMarkerColor(plot1D.color);
    plot1D.hist->SetLineColor(plot1D.color);
    plot1D.hist->SetLineWidth(1);
    plot1D.hist->SetMarkerSize(1);

    /*if (histname.find("TauEta")  != std::string::npos)*/
    /*{*/
      /*plot1D.hist->Rebin(10);*/
    /*}*/


    //if (histname.find("Response")  == std::string::npos &&
        //histname.find("Resolution")  == std::string::npos) {
      ////plot1D.hist->Rebin(2);
      //}
    // Draw
    if (i == 0)
    {
      plot1D.hist->Draw("PE");
      xaxis = plot1D.hist->GetXaxis();
      yaxis = plot1D.hist->GetYaxis();
      ingl =  plot1D.hist->Integral();
    }
    else
    {
      if (histname.find("Response")  == std::string::npos &&
          histname.find("Resolution")  == std::string::npos) {
        /*plot1D.hist->Scale(ingl / plot1D.hist->Integral());*/
      }
      plot1D.hist->Draw("samepe");
    }

    // Add Legend
    std::stringstream ss;
    ss << plot1D.det << " " << plot1D.algo;
    leg->AddEntry(plot1D.hist, ss.str().c_str(), "lp" );

    // Get Yaxis maximun
    Ymax = plot1D.hist->GetMaximum() > Ymax ? plot1D.hist->GetMaximum() : Ymax;
    yaxis->SetRangeUser(0.0, 1.2*Ymax);
  }

  SetPlotStyle(histname, c1, leg, xaxis, yaxis);
  leg->Draw();

  for(std::set<std::string>::const_iterator it=vformat.begin();
    it!=vformat.end(); ++it)
  {
    std::stringstream ss;
    ss << histname <<"." << *it;
    c1->Update();
    c1->SaveAs(ss.str().c_str());
  }

  delete c1;
  delete leg;

  return true;
}       // -----  end of function TPlot::Compare1D  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::SetMarkColor
//  Description:  
// ===========================================================================
bool TPlot::SetMarkColor(std::map<std::string, int> &detMark_, std::map<std::string, int> &algColor_)
{
  detMark = detMark_;
  algColor = algColor_;
  return true ;
}       // -----  end of function TPlot::SetMarkColor  -----
// ===  FUNCTION  ============================================================
//         Name:  TPlot::AddOutputFormat
//  Description:  
// ===========================================================================
bool TPlot::AddOutputFormat(std::string format)
{
  vformat.insert(format);
  return true;
}       // -----  end of function TPlot::AddOutputFormat  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::SetPlotStyle
//  Description:  
// ===========================================================================
bool TPlot::SetPlotStyle( std::string histname, TCanvas *c1, TLegend *leg , TAxis* xaxis , TAxis* yaxis )
{
  SetDefaultPlotStyle(c1, leg, xaxis, yaxis);

  if (histname == "ZMass")
  {
    xaxis->SetTitle("M_{#mu #mu} [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    //yaxis->SetRangeUser(0, 300);
  }
  
  if (histname == "ZPT")
  {
    xaxis->SetTitle("q_{T} [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    yaxis->SetTitleOffset(1.5);
  }

  if (histname == "METPT")
  {
    xaxis->SetTitle("#slash{E}_{T} [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    yaxis->SetTitleOffset(1.5);
    xaxis->SetRangeUser(0, 300);
  }

  if (histname == "METPhi")
  {
    xaxis->SetTitle("#phi #slash{E}_{T} [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    //xaxis->SetRangeUser(0, 300);
  }

  if (histname == "METx")
  {
    xaxis->SetTitle("#slash{E}_{T} x [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    yaxis->SetTitleOffset(1.5);
    //xaxis->SetRangeUser(0, 300);
  }

  if (histname == "METy")
  {
    xaxis->SetTitle("#slash{E}_{T} y [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    yaxis->SetTitleOffset(1.5);
    //xaxis->SetRangeUser(0, 300);
  }
  if (histname == "SumET")
  {
    xaxis->SetTitle("#sum E_{T} [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    yaxis->SetTitleOffset(1.5);
    xaxis->SetTitleOffset(1.3);
    xaxis->SetRangeUser(0, 12000);
  }



  if (histname == "RecoilPT")
  {
    xaxis->SetTitle("u_{T} [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    //xaxis->SetRangeUser(0, 300);
  }

  if (histname == "ParrallelZPT")
  {
    xaxis->SetTitle("u_{#parallel} + q_{T} [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    yaxis->SetTitleOffset(1.5);
    //xaxis->SetRangeUser(0, 300);
  }

  if (histname == "Perpendicular")
  {
    xaxis->SetTitle("u_{#perp}  [GeV]");
    yaxis->SetTitle("Events/8 GeV");
    yaxis->SetTitleOffset(1.5);
    //xaxis->SetRangeUser(0, 300);
  }

  if (histname.find("h2D_ParrallelZpt_Response") != std::string::npos)
  {
    //xaxis->SetRangeUser(0, 150);
    yaxis->SetRangeUser(0, 1.5);
    xaxis->SetTitle("q_{T} [GeV]");
    yaxis->SetTitle("-<u_{#parallel}>/q_{T}");
    /*leg->PaintPave(0.6834171,0.2111693,0.9334171,0.5008726,NULL,"brNDC");*/
    c1->Update();
    leg->SetX1NDC(0.6834171);
    leg->SetY1NDC(0.2111693);

    leg->SetX2NDC(0.9334171);
    leg->SetY2NDC(0.5008726);
    c1->Update();
    leg->Draw();
    /*leg->SetTextColor(kRed);*/
  }

  TLatex tex;
  tex.SetNDC();
  tex.SetTextSize(0.06);

  if (histname == "PUJetRate_BR_Pt_Eff")
  {
    //xaxis->SetRangeUser(0, 150);
    c1->Update();
    c1->SetLogx(1);
    tex.DrawLatex(0.20,0.80, "0 < |#eta^{reco}| < 1.3");
    xaxis->SetTitle("P_{T}^{reco} [GeV]");
    yaxis->SetTitle("P_{T}^{reco} / P_{T}^{matched}");
    xaxis->SetMoreLogLabels();
    yaxis->SetTitleOffset(1.5);
    yaxis->SetRangeUser(0.8, 2.5);

    tex.SetTextColor(2);
    tex.DrawLatex(0.25,0.70, "NO JEC");
  }
  if (histname == "PUJetRate_EC_Pt_Eff")
  {
    //xaxis->SetRangeUser(0, 150);
    c1->Update();
    c1->SetLogx(1);
    tex.DrawLatex(0.20,0.80, "1.3 < |#eta^{reco}| < 3.0");
    xaxis->SetTitle("P_{T}^{reco} [GeV]");
    yaxis->SetTitle("P_{T}^{reco} / P_{T}^{matched}");
    xaxis->SetMoreLogLabels();
    yaxis->SetTitleOffset(1.5);
    yaxis->SetRangeUser(0.8, 2.5);
    tex.SetTextColor(2);
    tex.DrawLatex(0.25,0.70, "NO JEC");
  }
  if (histname == "PUJetRate_FW_Pt_Eff")
  {
    //xaxis->SetRangeUser(0, 150);
    c1->Update();
    c1->SetLogx(1);
    xaxis->SetMoreLogLabels();
    tex.DrawLatex(0.20,0.80, "3.0 < |#eta^{reco}| < 5.0");
    xaxis->SetTitle("P_{T}^{reco} [GeV]");
    yaxis->SetRangeUser(0.8, 3.0);
    yaxis->SetTitleOffset(1.5);
    yaxis->SetTitle("P_{T}^{reco} / P_{T}^{matched}");
    tex.SetTextColor(2);
    tex.DrawLatex(0.25,0.70, "NO JEC");
  }

  if (histname.find("h2D_Parrallel_Resolution") != std::string::npos)
  {
    //xaxis->SetRangeUser(0, 150);
    xaxis->SetTitle("q_{T} [GeV]");
    yaxis->SetTitle("#sigma(u_{#parallel})");
  }

  if (histname.find("h2D_Perperndicular_Resolution") != std::string::npos)
  {
    //xaxis->SetRangeUser(0, 150);
    xaxis->SetTitle("q_{T} [GeV]");
    yaxis->SetTitle("#sigma(u_{#perp} )");
  }

  if (histname.find("h2D_MET_Eff") != std::string::npos)
  {
    //xaxis->SetRangeUser(0, 150);
    yaxis->SetRangeUser(0, 150);
    xaxis->SetTitle("q_{T} [GeV]");
    yaxis->SetTitle("#sigma(u_{#parallel}) / ( -<u_{#parallel}>/q_{T}) ");
  }

  return true;
}       // -----  end of function TPlot::SetPlotStyle  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::SetDefaultPlotStyle
//  Description:  
// ===========================================================================
bool TPlot::SetDefaultPlotStyle( TCanvas *c1, TLegend *leg , TAxis* xaxis , TAxis* yaxis )
{
  CMS_lumi_v2(c1, 14, 11);
  return true;
}       // -----  end of function TPlot::SetDefaultPlotStyle  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::GetHist1D
//  Description:  
// ===========================================================================
TH1* TPlot::GetHist1D(std::string histname, std::string det, std::string algo)
{
   
  if (histname.find("Response") != std::string::npos )
  {
    std::stringstream ss;
    ss << algDir[algo] <<"/" << histname.substr(0, histname.find("_Response")); 
    std::cout << "fsf " << ss.str() << std::endl;
    Perf2D perf((TH2D*)detFile[det]->Get(ss.str().c_str()), 3);
    perf.DoPlotEachBin(det, algo);
    return  perf.GetPerf(histname);
  }

  if (histname.find("Resolution") != std::string::npos )
  {
    std::stringstream ss;
    ss << algDir[algo] <<"/" << histname.substr(0, histname.find("_Resolution")); 
    std::cout << "fsf " << ss.str() << std::endl;
    Perf2D perf((TH2D*)detFile[det]->Get(ss.str().c_str()), 4);
    /*perf.DoPlotEachBin(det, algo);*/
    return  perf.GetPerf(histname);
  }

  if (histname.find("_Eff") != std::string::npos )
  {
    return GetEffHist(histname, det, algo);
  }

  if (list1D.find(histname) != list1D.end())
  {
    std::stringstream ss;
    ss << algDir[algo] <<"/" << histname;
    return (TH1*)detFile[det]->Get(ss.str().c_str());
  }
  //return true;
}       // -----  end of function TPlot::GetHist1D  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::PlotAll1D
//  Description:  
// ===========================================================================
bool TPlot::PlotAll1D()
{
  //GetAllHist();

  for(std::set<std::string>::const_iterator it=list1D.begin();
    it!=list1D.end(); ++it)
  {
    std::cout << " plotting " << *it << std::endl;
    Compare1D(*it);
  }
  return true;
}       // -----  end of function TPlot::PlotAll1D  -----


// ===  FUNCTION  ============================================================
//         Name:  TPlot::CMS_lumi_v2
//  Description:  
// ===========================================================================
void TPlot::CMS_lumi_v2( TPad* pad, int iPeriod, int iPosX )
{
  //
  // Global variables
  //
  TString cmsText     = "CMS Simulation";
  float cmsTextFont   = 61;  // default is helvetic-bold

  bool writeExtraText = true;
  TString extraText   = "Preliminary";
  float extraTextFont = 52;  // default is helvetica-italics

  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  float lumiTextSize     = 0.6;
  float lumiTextOffset   = 0.2;
  float cmsTextSize      = 0.75;
  float cmsTextOffset    = 0.1;  // only used in outOfFrame version

  float relPosX    = 0.045;
  float relPosY    = 0.035;
  float relExtraDY = 1.2;

  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;

  TString lumi_13TeV = "20.1 fb^{-1}";
  TString lumi_8TeV  = "19.7 fb^{-1}";
  TString lumi_7TeV  = "5.1 fb^{-1}";
  TString lumi_14TeV = "3000 fb^{-1}, PU = 140";

  bool drawLogo      = false;

  bool outOfFrame    = false;
  if( iPosX/10==0 ) 
  {
    outOfFrame = true;
  }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
  {
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
  }
  else if ( iPeriod==2 )
  {
    lumiText += lumi_8TeV;
    lumiText += " (8 TeV)";
  }
  else if( iPeriod==3 ) 
  {
    lumiText = lumi_8TeV; 
    lumiText += " (8 TeV)";
    lumiText += " + ";
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
  }
  else if ( iPeriod==4 )
  {
    lumiText += lumi_13TeV;
    lumiText += " (13 TeV)";
  }
  else if ( iPeriod==7 )
  { 
    if( outOfFrame ) lumiText += "#scale[0.85]{";
    lumiText += lumi_13TeV; 
    lumiText += " (13 TeV)";
    lumiText += " + ";
    lumiText += lumi_8TeV; 
    lumiText += " (8 TeV)";
    lumiText += " + ";
    lumiText += lumi_7TeV;
    lumiText += " (7 TeV)";
    if( outOfFrame) lumiText += "}";
  }
  else if ( iPeriod==12 )
  {
    lumiText += "8 TeV";
  }
  else if ( iPeriod==14 )
  {
    lumiText += "14 TeV";  
    //lumiText += lumi_14TeV;
  }


  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(lumiTextSize*t);    
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
  {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
  }

  pad->cd();

  float posX_;
  if( iPosX%10<=1 )
  {
    posX_ =   l + relPosX*(1-l-r);
  }
  else if( iPosX%10==2 )
  {
    posX_ =  l + 0.5*(1-l-r);
  }
  else if( iPosX%10==3 )
  {
    posX_ =  1-r - relPosX*(1-l-r);
  }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
  {
    if( drawLogo )
    {
      posX_ =   l + 0.045*(1-l-r)*W/H;
      posY_ = 1-t - 0.045*(1-t-b);
      float xl_0 = posX_;
      float yl_0 = posY_ - 0.15;
      float xl_1 = posX_ + 0.15*H/W;
      float yl_1 = posY_;
      /*TASImage* CMS_logo = new TASImage("CMS-BW-label.png");*/
      TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
      pad_logo->Draw();
      pad_logo->cd();
      /*CMS_logo->Draw("X");*/
      pad_logo->Modified();
      pad->cd();
    }
    else
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextSize(cmsTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, cmsText);
      if( writeExtraText ) 
      {
        latex.SetTextFont(extraTextFont);
        latex.SetTextAlign(align_);
        latex.SetTextSize(extraTextSize*t);
        latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
      }
    }
  }
  else if( writeExtraText )
  {
    if( iPosX==0) 
    {
      posX_ =   l +  relPosX*(1-l-r);
      posY_ =   1-t+lumiTextOffset*t;
    }
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, extraText);      
  }

  return ;
}       // -----  end of function TPlot::CMS_lumi_v2  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::AddHist1D
//  Description:  /* cursor */
// ===========================================================================
bool TPlot::AddHist1D(std::string name)
{
  list1D.insert(name);
  return true;
}       // -----  end of function TPlot::AddHist1D  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::AddEffHist
//  Description:  Get a list of Eff
// ===========================================================================
bool TPlot::AddEffHist(std::string Eff, std::string Num, std::string Dem)
{
  AddHist1D(Eff);
  listEff[Eff] = make_pair(Num, Dem);
  return true;
}       // -----  end of function TPlot::AddEffHist  -----

// ===  FUNCTION  ============================================================
//         Name:  TPlot::GetEffHist
//  Description:  
// ===========================================================================
TH1* TPlot::GetEffHist(std::string Eff, std::string det, std::string algo)
{

  TH1* hNum = GetHist1D(listEff[Eff].first, det, algo);

  TH1* hDem = GetHist1D(listEff[Eff].second, det, algo);

  TH1* temp = (TH1*)hNum->Clone(Eff.c_str());

  assert(hNum->GetNbinsX() == hDem->GetNbinsX());
  for (int i = 0; i < hNum->GetNbinsX(); ++i)
  {
    double val = hNum->GetBinContent(i) / hDem->GetBinContent(i);
    double valerr = val * sqrt( pow(hNum->GetBinError(i)/hNum->GetBinContent(i), 2) +
        pow(hDem->GetBinError(i)/hDem->GetBinContent(i), 2) );
    if (isnan(val)) { val = 0; valerr = 0; }
    temp->SetBinContent(i, val);
    temp->SetBinError(i, valerr);
    std::cout << " bin " <<i <<" val " << val << std::endl;
  }

  //temp->Divide(hDem);
  temp->GetYaxis()->SetTitle("Efficiency");

  return temp;
}       // -----  end of function TPlot::GetEffHist  -----

