// ===========================================================================
// 
//       Filename:  TPlot.h
// 
//    Description: 
// 
//        Version:  1.0
//        Created:  02/26/2015 14:55:15
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================

#ifndef  __TPLOT_HEADER_INC__
#define  __TPLOT_HEADER_INC__

#include "Perf2D.h"
//#include "CMS_lumi_v2.h"
//#include "tdrstyle.C"

#include <vector>
#include <set>
#include <utility>
#include <map>
#include <sstream>
#include <cassert>


#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"

#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "TKey.h"
#include "TROOT.h"
#include "TRint.h"
#include "TLine.h"
#include "TStyle.h"

struct PlotID
{
  TH1* hist;
  std::string name;
  std::string det;
  std::string algo;
  int marker;
  int color;
};

// ===========================================================================
//        Class:  TPlot
//  Description:  
// ===========================================================================
class TPlot
{
  public:

    // ====================  LIFECYCLE     ===============================
    // constructor
    TPlot ( std::map<std::string, TFile*> &detFile, std::map<std::string, std::string> &algDir);                             
    //TPlot ( const TPlot &other );   // copy constructor
    ~TPlot ();                            // destructor

    // ====================  ACCESSORS     ===============================
    bool Add(std::string det, std::string algo);
    bool SetMarkColor(std::map<std::string, int> &detMark_, std::map<std::string, int> &algColor_);
    bool Compare1D(std::string histname);
    bool AddOutputFormat(std::string format);;
    bool GetAllHist();
    bool AddEffHist(std::string Eff, std::string Num, std::string Dem);
    bool PlotAll1D();
    bool AddHist1D(std::string name);

    // ====================  MUTATORS      ===============================

    // ====================  OPERATORS     ===============================

    TPlot& operator = ( const TPlot &other ); // assignment operator

    // ====================  DATA MEMBERS  ===============================

  protected:
    // ====================  METHODS       ===============================
    TH1* GetHist1D(std::string histname, std::string det, std::string algo);
    bool SetDefaultPlotStyle( TCanvas *c1, TLegend *leg , TAxis* xaxis , TAxis* yaxis );
    bool SetPlotStyle( std::string histname, TCanvas *c1, TLegend *leg , TAxis* xaxis , TAxis* yaxis );
    bool SetTPStyle() const;
    void CMS_lumi_v2( TPad* pad, int iPeriod, int iPosX );
    TH1* GetEffHist(std::string Eff, std::string det, std::string algo);

    // ====================  DATA MEMBERS  ===============================

  private:
    // ====================  METHODS       ===============================

    // ====================  DATA MEMBERS  ===============================
    std::map<std::string, TFile*> detFile;
    std::map<std::string, std::string> algDir;
    std::map<std::string, int> detMark;
    std::map<std::string, int> algColor;


    std::vector<std::pair<std::string, std::string> > plist;
    std::set<std::string> list1D;
    std::set<std::string> list2D;
    std::set<std::string> vformat;

    std::map<std::string, std::pair<std::string, std::string> > listEff;
}; // -----  end of class TPlot  -----

#endif   // ----- #ifndef __TPLOT_HEADER_INC__  -----
