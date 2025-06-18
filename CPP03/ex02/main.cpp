#include "FragTrap.hpp"

int main()
{
    std::cout << "\n##### FragTrap tests #####\n";
    {
        FragTrap default_fragtrap;
        FragTrap kuzyilma("kuzyilma");
        FragTrap copy_kuzyilma(kuzyilma);
        FragTrap test("test");

        std::cout << "\n---- assignment (operator=) and beRepaired function test -----\n";

        test = default_fragtrap;
        test.beRepaired(10);

        std::cout << "\n---- highFivesGuys function test -----\n";

        kuzyilma.highFivesGuys();

        std::cout << "\n---- attack and takeDamage function test -----\n";

        test.SetAttackdamage(5);
        test.Attack("kuzyilma");
        kuzyilma.TakeDamage(test.GetAttackdamage());

        std::cout << "\n---- zero hit points test -----\n";

        copy_kuzyilma.SetAttackdamage(999);
        copy_kuzyilma.Attack("test");
        test.TakeDamage(999);
        test.beRepaired(100);
        test.Attack("hello");
        test.TakeDamage(999);

        std::cout << "\n---- zero energy points test -----\n";

        kuzyilma.SetEnergypoints(3);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.Attack("test");
        kuzyilma.TakeDamage(1);

        std::cout << '\n';
    }
}
