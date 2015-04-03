// ===========================================================================
// 
//       Filename:  Perf2D.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/26/2015 14:56:09
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================

#ifndef  __PERF2D_INC__
#define  __PERF2D_INC__

#include "TGraphErrors.h"
#include "TH2D.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPaveStats.h"

#include <sstream>
#include <algorithm>
#include <string>

// ===========================================================================
//        Class:  Perf2D
//  Description:  
// ===========================================================================
class Perf2D
{
  public:

    // ====================  LIFECYCLE     ===============================
    Perf2D (TH2D* hist, int type );                             // constructor
    Perf2D ( const Perf2D &other );   // copy constructor
    ~Perf2D ();                            // destructor

    // ====================  ACCESSORS     ===============================
    //TGraphErrors GetPerf();
    TH1* GetPerf(std::string name);
    TH2D* ReBin2D(int xsize, double xbins[]) const;
    bool DoPlotEachBin(std::string det_, std::string algo_);

    // ====================  MUTATORS      ===============================

    // ====================  OPERATORS     ===============================

    Perf2D& operator = ( const Perf2D &other ); // assignment operator

    // ====================  DATA MEMBERS  ===============================

  protected:
    // ====================  METHODS       ===============================

    // ====================  DATA MEMBERS  ===============================

  private:
    // ====================  METHODS       ===============================
    bool PlotFineBin(std::string histname, TH1* hist, TF1* fit, int idx);

    // ====================  DATA MEMBERS  ===============================
    TH2D* hist;
    /// type odd: response; even: resolution
    /// 1: mean; 2: RMS
    /// 3: Fitted peak; 4: fitted sigma
    /// 6: fitted sigma / mean ; 
    int type;

    std::string det;
    std::string algo;
    bool plotBin;

}; // -----  end of class Perf2D  -----

#endif   // ----- #ifndef __PERF2D_INC__  -----
