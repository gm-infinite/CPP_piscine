
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    std::cout << "\n========== EX00: POLYMORPHISM TESTS ==========\n" << std::endl;

    // ─────────────────────────────────────────────────────────────
    // TEST 1: Subject's given test - Polymorphism through Animal*
    // Key: Even though j and i are Animal*, they call Dog/Cat sounds
    // ─────────────────────────────────────────────────────────────
    std::cout << "===== TEST 1: Subject's given test =====\n" << std::endl;
    {
        const Animal* meta = new Animal();
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;

        i->makeSound(); // will output the cat sound!
        j->makeSound();
        meta->makeSound();

        delete meta;
        delete j;
        delete i;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 2: WrongAnimal - Demonstrates what happens WITHOUT virtual
    // Key: WrongCat through WrongAnimal* outputs WrongAnimal sound!
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 2: WrongAnimal (no virtual = no polymorphism) =====\n" << std::endl;
    {
        const WrongAnimal* wrongMeta = new WrongAnimal();
        const WrongAnimal* wrongCat = new WrongCat();  // WrongAnimal pointer to WrongCat!

        std::cout << "WrongAnimal type: " << wrongMeta->getType() << std::endl;
        std::cout << "WrongCat type: " << wrongCat->getType() << std::endl;

        std::cout << "\nCalling makeSound() through WrongAnimal* pointers:" << std::endl;
        wrongMeta->makeSound();
        wrongCat->makeSound();  // Outputs WrongAnimal sound, NOT WrongCat sound!
        std::cout << "--> Both output WrongAnimal sound because makeSound() is NOT virtual\n" << std::endl;

        delete wrongMeta;
        delete wrongCat;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 3: Compare - Direct WrongCat object vs through pointer
    // ─────────────────────────────────────────────────────────────
    std::cout << "===== TEST 3: Direct object vs pointer call =====\n" << std::endl;
    {
        WrongCat wrongCatObj;
        std::cout << "\nCalling makeSound() directly on WrongCat object:" << std::endl;
        wrongCatObj.makeSound();  // This DOES output WrongCat sound
        std::cout << "--> Direct call uses WrongCat::makeSound()" << std::endl;

        std::cout << "\nBut through WrongAnimal* pointer:" << std::endl;
        const WrongAnimal* ptr = &wrongCatObj;
        ptr->makeSound();  // This outputs WrongAnimal sound!
        std::cout << "--> Pointer call uses WrongAnimal::makeSound() (no virtual)" << std::endl;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 4: Orthodox Canonical Form - Copy constructor
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 4: Copy constructor =====\n" << std::endl;
    {
        Dog dog1;
        std::cout << "\nCopying dog1 to dog2 (copy constructor):" << std::endl;
        Dog dog2(dog1);
        std::cout << "dog1.getType(): " << dog1.getType() << std::endl;
        std::cout << "dog2.getType(): " << dog2.getType() << std::endl;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 5: Orthodox Canonical Form - Assignment operator
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 5: Assignment operator =====\n" << std::endl;
    {
        Cat cat1;
        Cat cat2;
        std::cout << "\nAssigning cat1 to cat2:" << std::endl;
        cat2 = cat1;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 6: Destructor order (derived before base)
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 6: Destructor order =====\n" << std::endl;
    {
        std::cout << "Creating Dog on stack:" << std::endl;
        Dog stackDog;
        std::cout << "\nDog going out of scope..." << std::endl;
    }
    std::cout << "--> Dog destructor called BEFORE Animal destructor\n" << std::endl;

    std::cout << "========== ALL EX00 TESTS COMPLETED ==========\n" << std::endl;
    return 0;
}