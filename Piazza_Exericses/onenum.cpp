// What's wrong with this function

double oneNorm(std::vector<double> & x)
{
  double res{0.0};
  for (std::size_t i=0;i<x.size();++i) res+=std::abs(x[i]);
  return res;
}

// I think we're missing a const qualifier for the input parameter of the function
//double oneNorm(std::vector & x)  -> const oneNorm(std::vector & x) since it doesn't change vector x. Not necessary, but just to be sure
// since it doesn't modify the vector x

// std::size_t is the unsigned integer type of the result of the sizeof operator as well as the sizeof... operator and the alignof operator (since C++11).

// With that function would this code compile?

bool compare1Norm (const std::vector<double> & x, const std::vector<double> & y)
{
  return oneNorm(x) < oneNorm(y);
}

// A method and const methods with the same name are two different functions (although they share the name)
//  To avoid stupid errors use the override specification when you override.  Use -Wsuggest-override as a warning (it works with g++ and clang++)

double oneNorm2(std::vector<double> & x)
{
  double res{0.0};
  for (std::size_t i=0;i<x.size();++i) res+=std::abs(x[i]);
  return res;
}

bool compare1Norm2 (const std::vector<double> & x, const std::vector<double> & y)
{
  return oneNorm2(x) < oneNorm2(y);
}

// Where override ??? then