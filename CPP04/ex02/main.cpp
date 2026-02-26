#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    std::cout << "\n========== EX02: ABSTRACT CLASS ==========\n" << std::endl;

    // TEST 1: Animal cannot be instantiated (uncomment to see compile error)
    std::cout << "--- TEST 1: Animal is abstract ---\n" << std::endl;
    {
        // Uncomment these lines to see compile errors:
        // Animal a;
        // Animal* a = new Animal();
        
        std::cout << "Animal cannot be instantiated (compile error if uncommented)" << std::endl;
    }

    // TEST 2: Dog and Cat work normally
    std::cout << "\n--- TEST 2: Dog and Cat through Animal* ---\n" << std::endl;
    {
        const Animal* dog = new Dog();
        const Animal* cat = new Cat();

        std::cout << "\ndog->getType(): " << dog->getType() << std::endl;
        std::cout << "cat->getType(): " << cat->getType() << std::endl;

        std::cout << "\ndog->makeSound(): "; dog->makeSound();
        std::cout << "cat->makeSound(): "; cat->makeSound();

        std::cout << "\nDeleting:" << std::endl;
        delete dog;
        delete cat;
    }

    // TEST 3: Array of Animals
    std::cout << "\n--- TEST 3: Array of Animals ---\n" << std::endl;
    {
        const Animal* animals[4];
        animals[0] = new Dog();
        animals[1] = new Dog();
        animals[2] = new Cat();
        animals[3] = new Cat();

        std::cout << "\nmakeSound() on each:" << std::endl;
        for (int i = 0; i < 4; i++)
        {
            std::cout << "animals[" << i << "] (" << animals[i]->getType() << "): ";
            animals[i]->makeSound();
        }

        std::cout << "\nDeleting all:" << std::endl;
        for (int i = 0; i < 4; i++)
            delete animals[i];
    }

    // TEST 4: Deep copy still works
    std::cout << "\n--- TEST 4: Deep Copy ---\n" << std::endl;
    {
        Cat original;
        original.setBrainIdea(0, "Original idea");

        std::cout << "\nOriginal Brain: " << original.getBrain() << std::endl;
        std::cout << "Original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;

        std::cout << "\nCat copy(original):" << std::endl;
        Cat copy(original);

        std::cout << "\nOriginal Brain: " << original.getBrain() << std::endl;
        std::cout << "Copy Brain:     " << copy.getBrain() << std::endl;

        std::cout << "\nModifying copy idea[0] to \"MODIFIED\"" << std::endl;
        copy.setBrainIdea(0, "MODIFIED");

        std::cout << "\nOriginal idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy idea[0]:     " << copy.getBrain()->getIdea(0) << std::endl;
    }

    std::cout << "\n========== END EX02 ==========\n" << std::endl;
    return 0;
}