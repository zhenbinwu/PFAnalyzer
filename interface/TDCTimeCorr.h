#ifndef RecoLocalCalo_HcalRecAlgos_TDCTimeCorr_h_
#define RecoLocalCalo_HcalRecAlgos_TDCTimeCorr_h_

#include <cmath>

// Move the corrections once it is decided where and how it is applied
// The corrections can be expanded to include time from pulse shape
//
// Anton

/// Linearize the HBHE TDC time on depth-by-depth basis from the measured time
/// Temporary implementation for testing of PF modifications for Phase 2 upgrades.


class TDCTimeCorr {

  public:

  /// return corrected TDC time for HB
  static float tdcCorrHB(float rawTime, float rhE, int detDepth );

  /// return corrected TDC time for HE
  static float tdcCorrHE(float rawTime, float rhE, int detDepth );

// other corretions
};

#endif
