// copyright Michael J. Hennebry

#include <iostream>
using std::cout ;
#include <iomanip>
using std::setprecision ;
#include <cmath>
using std::sin ;
using std::tan ;
using std::cos ;
using std::pow ;

#include "wide_temporaries.hh"

enum { COUNT=100*1000 } ;
float xf[COUNT], yf[COUNT];
mjh::wide_temporaries<double, float> xw[COUNT], yw[COUNT];

int main(void)
{
for(int j=0; j< COUNT; ++j) {
    xf[j]=tan(j+1./3.) ;
    yf[j]=pow(2, 20*sin(j));
}  // j

for(int j=0; j< COUNT; ++j) {
    xw[j]=xf[j];
    yw[j]=yf[j];
}  // j

double dotf=0;
double dotw=0;
long double dotkh=0, dotkl=0;  // for Kahan summation

for(int j=0; j< COUNT; ++j) {
    dotf+=xf[j]*yf[j];
    dotw+=xw[j]*yw[j];                 //with IEEE, the multiplication is exact
    dotkl+=xf[j]*(long double)(yf[j]); //with IEEE, the multiplication is exact
    long double dotkh0=dotkh;
    dotkh+=dotkl;
    dotkl+=dotkh0-dotkh;
}  // j

cout <<"dotf =" <<setprecision(13) <<dotf <<'\n' ;
cout <<"dotw =" <<setprecision(13) <<dotw <<'\n' ;
cout <<"dotkh=" <<setprecision(13) <<dotkh <<'\n' ;
cout <<"dotf-dotkh=" <<(dotf-dotkh) <<'\n';
cout <<"dotw-dotkh=" <<(dotw-dotkh) <<'\n';

}  // main
