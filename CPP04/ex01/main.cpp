
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    std::cout << "\n========== EX01: BRAIN & DEEP COPY TESTS ==========\n" << std::endl;

    // ─────────────────────────────────────────────────────────────
    // TEST 1: Subject's given test - Virtual destructor needed
    // Deleting Dog/Cat through Animal* must call proper destructors
    // ─────────────────────────────────────────────────────────────
    std::cout << "===== TEST 1: Subject's given test =====\n" << std::endl;
    {
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        std::cout << "\nDeleting through Animal* (should not leak):" << std::endl;
        delete j;  // Must call Dog destructor, then Animal destructor
        delete i;  // Must call Cat destructor, then Animal destructor
    }
    std::cout << "--> Both Brain destructors called (no memory leak)\n" << std::endl;

    // ─────────────────────────────────────────────────────────────
    // TEST 2: Animal array - Half Dogs, Half Cats
    // ─────────────────────────────────────────────────────────────
    std::cout << "===== TEST 2: Array of Animals =====\n" << std::endl;
    {
        const int size = 10;
        const Animal* animals[size];

        std::cout << "Creating " << size/2 << " Dogs:" << std::endl;
        for (int i = 0; i < size/2; ++i)
            animals[i] = new Dog();

        std::cout << "\nCreating " << size/2 << " Cats:" << std::endl;
        for (int i = size/2; i < size; ++i)
            animals[i] = new Cat();

        std::cout << "\nPolymorphic makeSound() calls:" << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << "animals[" << i << "] (" << animals[i]->getType() << "): ";
            animals[i]->makeSound();
        }

        std::cout << "\nDeleting all animals as Animal*:" << std::endl;
        for (int i = 0; i < size; ++i)
            delete animals[i];
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 3: Cat Deep Copy - Copy Constructor
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 3: Cat deep copy (copy constructor) =====\n" << std::endl;
    {
        Cat original;
        original.setBrainIdea(0, "Chase the laser");
        original.setBrainIdea(1, "Sleep on keyboard");

        std::cout << "\nCopying original to copy:" << std::endl;
        Cat copy(original);

        std::cout << "\nBrain addresses (must be DIFFERENT for deep copy):" << std::endl;
        std::cout << "Original Brain: " << original.getBrain() << std::endl;
        std::cout << "Copy Brain:     " << copy.getBrain() << std::endl;

        if (original.getBrain() != copy.getBrain())
            std::cout << "[OK] Different addresses - deep copy confirmed\n" << std::endl;
        else
            std::cout << "[FAIL] Same address - shallow copy!\n" << std::endl;

        std::cout << "Modifying copy's idea[0] to 'MODIFIED'..." << std::endl;
        copy.setBrainIdea(0, "MODIFIED");

        std::cout << "Original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy idea[0]:     " << copy.getBrain()->getIdea(0) << std::endl;

        if (original.getBrain()->getIdea(0) != copy.getBrain()->getIdea(0))
            std::cout << "[OK] Original unchanged - true deep copy" << std::endl;
        else
            std::cout << "[FAIL] Original changed - shallow copy!" << std::endl;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 4: Dog Deep Copy - Copy Constructor
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 4: Dog deep copy (copy constructor) =====\n" << std::endl;
    {
        Dog original;
        original.setBrainIdea(0, "Fetch the ball");

        std::cout << "\nCopying original to copy:" << std::endl;
        Dog copy(original);

        std::cout << "\nBrain addresses:" << std::endl;
        std::cout << "Original Brain: " << original.getBrain() << std::endl;
        std::cout << "Copy Brain:     " << copy.getBrain() << std::endl;

        copy.setBrainIdea(0, "MODIFIED DOG IDEA");

        std::cout << "\nAfter modifying copy:" << std::endl;
        std::cout << "Original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy idea[0]:     " << copy.getBrain()->getIdea(0) << std::endl;

        if (original.getBrain()->getIdea(0) != copy.getBrain()->getIdea(0))
            std::cout << "[OK] Deep copy works for Dog" << std::endl;
        else
            std::cout << "[FAIL] Shallow copy!" << std::endl;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 5: Assignment Operator Deep Copy
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 5: Assignment operator deep copy =====\n" << std::endl;
    {
        Cat cat1;
        cat1.setBrainIdea(0, "Cat1 original idea");

        Cat cat2;
        cat2.setBrainIdea(0, "Cat2 original idea");

        std::cout << "Before assignment:" << std::endl;
        std::cout << "cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
        std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

        std::cout << "\nAssigning cat1 to cat2 (cat2 = cat1):" << std::endl;
        cat2 = cat1;

        std::cout << "\nAfter assignment:" << std::endl;
        std::cout << "cat1 Brain: " << cat1.getBrain() << std::endl;
        std::cout << "cat2 Brain: " << cat2.getBrain() << std::endl;
        std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

        cat2.setBrainIdea(0, "MODIFIED after assignment");

        std::cout << "\nAfter modifying cat2:" << std::endl;
        std::cout << "cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
        std::cout << "cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

        if (cat1.getBrain() != cat2.getBrain() && 
            cat1.getBrain()->getIdea(0) != cat2.getBrain()->getIdea(0))
            std::cout << "[OK] Assignment operator performs deep copy" << std::endl;
        else
            std::cout << "[FAIL] Assignment operator is shallow!" << std::endl;
    }

    std::cout << "\n========== ALL EX01 TESTS COMPLETED ==========\n" << std::endl;
    return 0;
}