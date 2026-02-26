#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    std::cout << "\n========== EX01: DEEP COPY ==========\n" << std::endl;

    // TEST 1: Subject's required test - delete through base pointer
    std::cout << "--- TEST 1: Delete through Animal* ---\n" << std::endl;
    {
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        std::cout << "\nDeleting j (Dog):" << std::endl;
        delete j;
        std::cout << "\nDeleting i (Cat):" << std::endl;
        delete i;
    }

    // TEST 2: Array of Animals (half Dogs, half Cats)
    std::cout << "\n--- TEST 2: Array of Animals ---\n" << std::endl;
    {
        const int SIZE = 4;
        const Animal* animals[SIZE];

        std::cout << "Creating 2 Dogs:" << std::endl;
        for (int i = 0; i < SIZE / 2; i++)
            animals[i] = new Dog();
        
        std::cout << "\nCreating 2 Cats:" << std::endl;
        for (int i = SIZE / 2; i < SIZE; i++)
            animals[i] = new Cat();

        std::cout << "\nmakeSound() on each:" << std::endl;
        for (int i = 0; i < SIZE; i++)
        {
            std::cout << "animals[" << i << "] (" << animals[i]->getType() << "): ";
            animals[i]->makeSound();
        }

        std::cout << "\nDeleting all:" << std::endl;
        for (int i = 0; i < SIZE; i++)
            delete animals[i];
    }

    // TEST 3: Deep copy proof - Copy Constructor
    std::cout << "\n--- TEST 3: Copy Constructor Deep Copy ---\n" << std::endl;
    {
        Cat original;
        original.setBrainIdea(0, "I love fish");

        std::cout << "\nOriginal Brain: " << original.getBrain() << std::endl;
        std::cout << "Original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;

        std::cout << "\nCat copy(original):" << std::endl;
        Cat copy(original);

        std::cout << "\nOriginal Brain: " << original.getBrain() << std::endl;
        std::cout << "Copy Brain:     " << copy.getBrain() << std::endl;
        std::cout << "Copy idea[0]:   " << copy.getBrain()->getIdea(0) << std::endl;

        std::cout << "\nModifying copy idea[0] to \"MODIFIED\"" << std::endl;
        copy.setBrainIdea(0, "MODIFIED");

        std::cout << "\nOriginal idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy idea[0]:     " << copy.getBrain()->getIdea(0) << std::endl;
    }

    // TEST 4: Deep copy proof - Assignment Operator
    std::cout << "\n--- TEST 4: Assignment Operator Deep Copy ---\n" << std::endl;
    {
        Dog dog1;
        dog1.setBrainIdea(0, "Fetch ball");

        Dog dog2;
        dog2.setBrainIdea(0, "Bark");

        std::cout << "\nBefore assignment:" << std::endl;
        std::cout << "dog1 Brain: " << dog1.getBrain() << ", idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
        std::cout << "dog2 Brain: " << dog2.getBrain() << ", idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;

        std::cout << "\ndog2 = dog1:" << std::endl;
        dog2 = dog1;

        std::cout << "\nAfter assignment:" << std::endl;
        std::cout << "dog1 Brain: " << dog1.getBrain() << ", idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
        std::cout << "dog2 Brain: " << dog2.getBrain() << ", idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;

        std::cout << "\nModifying dog2 idea[0] to \"MODIFIED\"" << std::endl;
        dog2.setBrainIdea(0, "MODIFIED");

        std::cout << "\ndog1 idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
        std::cout << "dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;
    }

    std::cout << "\n========== END EX01 ==========\n" << std::endl;
    return 0;
}