
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    std::cout << "\n##### given test #####\n\n";
    {
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        delete j;//should not create a leak
        delete i;
    }
    std::cout << "\n##### shallow-deep copy test #####\n\n";
    {
        std::cout << "Creating original cat...\n";
        Cat original;
        original.setBrainIdea(0, "Chase the laser");

        std::cout << "Copying cat using copy constructor...\n";
        Cat copy = original;

        std::cout << "Original Cat Brain Address: " << original.getBrain() << std::endl;
        std::cout << "Copy Cat Brain Address:     " << copy.getBrain() << std::endl;

        std::cout << "Original Brain Idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy Brain Idea[0]:     " << copy.getBrain()->getIdea(0) << std::endl;

        if (original.getBrain() == copy.getBrain()) {
            std::cout << "\n❌ Shallow copy confirmed: both Cats share the same Brain.\n";
        } else {
            std::cout << "\n✅ Deep copy detected (or shallow copy failed).\n";
        }

    }
    std::cout << "\n##### 10 animal array test #####\n\n";
    {
        const Animal* animals[10];

        // Fill first half with Dogs
        for (int i = 0; i < 5; ++i) {
            animals[i] = new Dog();
        }

        // Fill second half with Cats
        for (int i = 5; i < 10; ++i) {
            animals[i] = new Cat();
        }

        // Delete all animals through base pointer
        for (int i = 0; i < 10; ++i) {
            delete animals[i];
        }
    }
}