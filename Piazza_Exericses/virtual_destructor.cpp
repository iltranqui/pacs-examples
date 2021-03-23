#include <iostream>

using namespace std;

// This class as a destructor that tells when an object is destroyed
class Foo
{
public:
  ~Foo(){cout<<"Destroying a Foo object\n";}  // default deconstructor ? 
  // shouldn't i put a constructor as well ? 
};

class Base1
{
public:
    Base1(){
        cout << "Base1 Constructor Called\n";
    }
  // here I forgot virtual!
    ~Base1(){
        cout << "Base1 Destructor called\n";
    }
};

class Derived1: public Base1
{
public:
    Derived1(){
        cout << "Derived1 constructor called\n";
    }
    ~Derived1(){
        cout << "Derived1 destructor called\n";
    }
private:
  Foo foo;
};

class Base2
{
public:
    Base2(){
        cout << "Base2 Constructor Called\n";
    }
    virtual ~Base2(){
        cout << "Base2 Destructor called\n";
    }
};

class Derived2: public Base2
{
public:
    Derived2(){
        cout << "Derived2 constructor called\n";
    }
    ~Derived2(){
        cout << "Derived2 destructor called\n";
    }
private:
  Foo foo;
};



int main()
{
  // Without virtual
    Base1 *b1 = new Derived1();
    delete b1;
    // When you delete the pointer b1  only the destructor of Base1 is called, so possible additional data members of Derived1 are not destroyed!
    // You call before hand Base, rather than Derived1
    cout<<std::endl;
// With virtual
    Base2 *b2 = new Derived2();
    delete b2;
}

/*
Base1 Constructor Called
Derived1 constructor called
Base1 Destructor called

Base2 Constructor Called
Derived2 constructor called
Derived2 destructor called
Destroying a Foo object
Base2 Destructor called
+/