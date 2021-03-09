#include <dlfcn.h>

#include <cmath>
#include <functional>
#include <iostream>

double
integrand(double x)
{
  return (std::pow(std::sin(std::pow(x, 2)), 2));
}

int
main(int argc, char **argv)
{
  void *handle = dlopen("adaptive_quadrature.so", RTLD_LAZY);
  if (!handle)
    {
      std::cerr << "Cannot load object!" << std::endl;
      std::cerr << dlerror() << std::endl;

      return 1;
    }

  void *sym = dlsym(handle, "integrate");
  if (!sym)
    {
      std::cerr << "Cannot load symbol!" << std::endl;
      std::cerr << dlerror() << std::endl;

      return 1;
    }

  double (*integrate)(std::function<double(double)>, double, double);
  integrate = reinterpret_cast<decltype(integrate)>(sym);

  double res = integrate(integrand, 0, M_PI);

  std::cout << "res = " << res << std::endl;

  return 0;
}
