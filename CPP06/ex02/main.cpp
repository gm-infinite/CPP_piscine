#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>

// Function declarations
Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main()
{
    std::srand(std::time(0));
    
    std::cout << "=== Generating random objects ===" << std::endl;
    for (int i = 0; i < 10; i++) {
        Base* obj = generate();
        
        std::cout << "Object " << i + 1 << ": ";
        std::cout << "Pointer identify: ";
        identify(obj);
        
        std::cout << "         Reference identify: ";
        identify(*obj);
        
        delete obj;
    }
    
    std::cout << "\n=== Testing known types ===" << std::endl;
    Base* a = new A();
    Base* b = new B();
    Base* c = new C();
    
    std::cout << "A object: ";
    identify(a);
    std::cout << "B object: ";
    identify(b);
    std::cout << "C object: ";
    identify(c);
    
    delete a;
    delete b;
    delete c;
    
    return 0;
}


Base* generate(void)
{
	int random = rand()%3;

	switch (random)
	{
		case(0):
			return new A();
		case(1):
			return new B();
		case(2):
			return new C();
	}
	return NULL;
}
void identify(Base* p)
{
	std::cout << (dynamic_cast<A*>(p) ? "A" : (dynamic_cast<B*>(p) ? "B" : (dynamic_cast<C*>(p) ? "C" : "How did you reach here???"))) << std::endl;
}
void identify(Base& p)
{
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	}
	catch (std::exception& e) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
	}
	catch (std::exception& e) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	}
	catch (std::exception& e) {}
}