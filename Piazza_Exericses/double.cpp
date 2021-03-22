#include <vector>
#include <iostream>

std::vector<double>a={3,4,5,6};
std::vector<double>b;

auto f=[&b](double c){b.emplace_back(c/2.0);};
auto d=[](double c){std::cout<<c<<"_";};

for (auto i: a)f(i); // fills b
for (auto i: b)d(i);  /w/ prints b
// b contains a/2
