
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    std::cout << "\n========== EX02: ABSTRACT CLASS TESTS ==========\n" << std::endl;

    // ─────────────────────────────────────────────────────────────
    // TEST 1: Animal is now ABSTRACT - Cannot be instantiated
    // This is what CHANGED from ex01 - uncomment to see compiler error
    // ─────────────────────────────────────────────────────────────
    std::cout << "===== TEST 1: Animal is abstract =====\n" << std::endl;
    {
        std::cout << "The following lines would cause compiler errors:" << std::endl;
        std::cout << "  // Animal a;              // Error!" << std::endl;
        std::cout << "  // Animal* a = new Animal(); // Error!" << std::endl;
        std::cout << "\n(Uncomment lines below to verify - will not compile)\n" << std::endl;
        
        // UNCOMMENT THESE TO VERIFY ANIMAL CANNOT BE INSTANTIATED:
        // Animal a;                    // Error: cannot instantiate abstract class
        // Animal* a = new Animal();    // Error: cannot instantiate abstract class
        
        std::cout << "[OK] Animal is abstract and cannot be instantiated" << std::endl;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 2: But Dog and Cat CAN still be instantiated
    // Everything else works exactly as in ex01
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 2: Dog and Cat work normally =====\n" << std::endl;
    {
        const Animal* dog = new Dog();
        const Animal* cat = new Cat();

        std::cout << "\nPolymorphism still works:" << std::endl;
        std::cout << "dog->getType(): " << dog->getType() << std::endl;
        std::cout << "cat->getType(): " << cat->getType() << std::endl;
        
        std::cout << "\nmakeSound() through Animal*:" << std::endl;
        dog->makeSound();
        cat->makeSound();

        delete dog;
        delete cat;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 3: Array of Animals still works
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 3: Array of Animals =====\n" << std::endl;
    {
        const Animal* animals[4];

        animals[0] = new Dog();
        animals[1] = new Dog();
        animals[2] = new Cat();
        animals[3] = new Cat();

        std::cout << "\nCalling makeSound() on each:" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << animals[i]->getType() << ": ";
            animals[i]->makeSound();
        }

        std::cout << "\nDeleting through Animal*:" << std::endl;
        for (int i = 0; i < 4; ++i)
            delete animals[i];
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 4: Deep copy still works
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== TEST 4: Deep copy still works =====\n" << std::endl;
    {
        Cat original;
        original.setBrainIdea(0, "Original idea");

        Cat copy(original);

        std::cout << "Brain addresses:" << std::endl;
        std::cout << "Original: " << original.getBrain() << std::endl;
        std::cout << "Copy:     " << copy.getBrain() << std::endl;

        copy.setBrainIdea(0, "MODIFIED");

        std::cout << "\nAfter modifying copy:" << std::endl;
        std::cout << "Original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy idea[0]:     " << copy.getBrain()->getIdea(0) << std::endl;

        if (original.getBrain()->getIdea(0) != copy.getBrain()->getIdea(0))
            std::cout << "[OK] Deep copy works" << std::endl;
        else
            std::cout << "[FAIL] Shallow copy!" << std::endl;
    }

    // ─────────────────────────────────────────────────────────────
    // TEST 5: Compare with ex01 - what changed
    // ─────────────────────────────────────────────────────────────
    std::cout << "\n===== SUMMARY: What changed from ex01 =====\n" << std::endl;
    std::cout << "BEFORE (ex01): Animal could be instantiated" << std::endl;
    std::cout << "  const Animal* meta = new Animal(); // Worked" << std::endl;
    std::cout << "  meta->makeSound(); // Printed '*Animal noises*'" << std::endl;
    std::cout << "\nAFTER (ex02): Animal is ABSTRACT" << std::endl;
    std::cout << "  const Animal* meta = new Animal(); // COMPILE ERROR!" << std::endl;
    std::cout << "  makeSound() = 0; // Pure virtual function" << std::endl;
    std::cout << "\nReason: 'Creating Animal objects doesn't make sense'" << std::endl;
    std::cout << "        'It's true, they make no sound!'" << std::endl;

    std::cout << "\n========== ALL EX02 TESTS COMPLETED ==========\n" << std::endl;
    return 0;
}
