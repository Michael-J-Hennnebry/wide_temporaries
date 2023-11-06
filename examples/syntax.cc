// copyright Michael J. Hennebry

#include <iostream>
using std::cout, std::cin;

#include "wide_temporaries.hh"

using mjh::wide_temporaries ;

typedef wide_temporaries<long double> greg_t ;
// typedef mjh::wide_temporaries fred_t ;
// g++ cannot seem to decide whether fred_t is valid
typedef mjh::wide_temporaries<> hank_t ;

// an individual wide_temporaries can be initializd like a floating point
greg_t x={ 1 };
greg_t y{ 2 } ;
greg_t z=3;

// an array of wide_temporaries can be initialized
// like an array of floating point
greg_t w[]={ 1, 2, 3, 3.3L } ;  // no complaint about 3.3L being too wide


int main(void)
{
    char endl[]= " .\n";
    x=1./7.;
    long double ld=x;
    cout <<"ld=" <<ld <<endl;
    cout <<"x=" <<x <<"=" <<x.get_narrow() <<endl;
    cout <<"Type new value for x\n";
    cin >>x;
    cout<<"x=" <<x <<endl;
    cout<<"x=" <<x.get_narrow() <<endl;
}  // dummy

