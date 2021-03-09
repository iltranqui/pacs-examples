#include "metadot.hpp"
#include <iostream>
#include <complex>
int main(){
  using std::array;
  using namespace apsc::Operators;
  array<double,5> a={1.,1.,1.,1.,1.};
  array<double,5> b={1.1,2.1,3.1,4.1,5.1};
  //std::cout<<"a*b="<<metaDot<5>::apply(a,b)<<std::endl;
  // Using overloaded operator
  std::cout<<"a*b with the first implementation"<<std::endl;
  std::cout<<"a*b="<<a*b<<std::endl;
  std::cout<<"a*b with the second implementation"<<std::endl;
  std::cout<<"a*b="<<metadot17(a,b)<<std::endl;
  // the second implementation morks with arrays of different types
  array<int,5> c={1,2,3,4,5};
  std::cout<<"b*c with the second implementation"<<std::endl;
  std::cout<<"c*b="<<metadot17(c,b)<<std::endl;
  std::cout<<"Now with complex numbers"<<std::endl;
  array<std::complex<double>,3> ac={{{1.,2.3},{-1.,7.},{4.5,-9.0}}}; 
  array<std::complex<double>,3> bc={{{-1.,3.0},{-2.,7.3},{4.,10.0}}}; 
  std::cout<<"ac*bc="<<metadot17(ac,bc)<<std::endl;


}
