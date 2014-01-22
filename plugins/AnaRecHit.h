// ===========================================================================
// 
//       Filename:  AnaRecHit.h
// 
//    Description:  A class for analysising Rechit
// 
//        Version:  1.0
//        Created:  01/21/2014 12:20:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Zhenbin Wu (benwu), benwu@fnal.gov
//        Company:  Baylor University, CDF@FNAL, CMS@LPC
// 
// ===========================================================================

// ===========================================================================
//        Class:  AnaRecHit
//  Description:  
// ===========================================================================
class AnaRecHit
{
  public:

    // ====================  LIFECYCLE     ===============================
    AnaRecHit ();                             // constructor
    AnaRecHit ( const AnaRecHit &other );   // copy constructor
    ~AnaRecHit ();                            // destructor

    // ====================  ACCESSORS     ===============================

    // ====================  MUTATORS      ===============================

    // ====================  OPERATORS     ===============================

    AnaRecHit& operator = ( const AnaRecHit &other ); // assignment operator

  protected:
    // ====================  DATA MEMBERS  ===============================

  private:
    // ====================  DATA MEMBERS  ===============================

}; // -----  end of class AnaRecHit  -----

