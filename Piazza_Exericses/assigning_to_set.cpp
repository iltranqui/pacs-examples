#include <set>
#include <algorithm>
#include <iostream>

int main() {
std::set<double> a; // create a set
a.insert(5.0);  // initialize a set 
a.insert(10.0);  // another element
auto it=std::find(a.begin(),a.end(),10.0);
//*it=20;  // it's a set ! you cannot modify the value directly 
// in order to subsittute
a.erase(it);
a.insert(20.0);
// Gives the f  ollowing error! 
// assignment of read-only location ‘it.std::_Rb_tree_const_iterator<double>::operator*()’
}


// how to create an object
//g++ -Wall -g -c Classes_ex1.cpp -o Classes_ex1.o
// how to create the executable
// g++ Classes_ex1.o -o Classes_ex1

