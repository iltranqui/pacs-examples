class Base
{
 public:
 Base()=default; // this inserts a default constructor
 Base(double y):x{y}{};
 virtual double compute()const {return x*x;};
 // virtual: it can be overriden
 virtual ~Base()=default;
 // also a good thing is to add a destructor since we added a default contructor
 protected:
 double x=0.
};

class Derived : public Base
{
 public:
 using Base::Base;
 double compute() const override {return x*x*x;};
 // cannot get x because it comes from a private class, even though it comes from a public passage
 // we are carrying into Derived all constructors of Base (without the ; ), so it is sufficient to add Base()=default; in Base
};

int main()
{
Base * p = new Derived;
auto y = p->compute();   //  this results unused
delete p;
}

// how to create an object
//g++ -Wall -g -c Classes_ex1.cpp -o Classes_ex1.o
// how to create the executable
// g++ Classes_ex1.o -o Classes_ex1

