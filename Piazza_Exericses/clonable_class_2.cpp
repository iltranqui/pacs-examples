#include "CloningUtilities.hpp"
#include <iostream>
#include <memory>

class Base; //forward declaration!
using ptr_type=std::unique_ptr<Base>;
class Base
{
public:
  virtual ~Base()=default;
  Base()=default;
  Base(Base const &){std::cout<<"Constructing a Base object\n";}
  virtual ptr_type clone()const
    {
      std::cout<<" I am cloning myself: a Base object\n";
      return std::make_unique<Base>(*this);
    }
};

class Derived: public Base
{
public:
  Derived()=default;
  Derived(Derived const &){std::cout<<"Constructing a Derived object\n";}
  ptr_type clone()const
    {
      std::cout<<" I am cloning myself: a Derived object\n";
      return std::make_unique<Derived>(*this);
    }
};

class Composer
{
public:
  Composer()=default;
  Composer(ptr_type c):component{std::move(c)}
    {std::cout<<"creating a class composed polymorphically with a Base\n";}
  // all the implicit constructor/operators are fine!
private:
  apsc::PointerWrapper<Base> component;
};

int main()
{
  Composer composer(std::make_unique<Derived>());
  // copying it
  auto composer2=composer;
  Composer composer3;
  composer3 = composer2;
}