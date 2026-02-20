#include "FragTrap.hpp"

void printTrapStats(const FragTrap& dt, const std::string& label) {
    std::cout << "---- " << label << " ----\n";
    std::cout << "FragTrap Name: " << dt.GetName() << '\n';
    std::cout << "Hitpoints: " << dt.GetHitpoints() << '\n';
    std::cout << "Energypoints: " << dt.GetEnergypoints() << '\n';
    std::cout << "Attackdamage: " << dt.GetAttackdamage() << '\n';
    std::cout << "--------------------------\n\n";
}

int main ()
{
        std::cout << "\n##### FragTrap tests #####\n";
    {
        FragTrap default_Fragtrap;
        FragTrap kuzyilma("kuzyilma");
        FragTrap copy_kuzyilma(kuzyilma);
        FragTrap test("test");


        std::cout << "Name:" << kuzyilma.GetName()
                  << ", hitpoints:" << kuzyilma.GetHitpoints()
                  << ", energypoints:" << kuzyilma.GetEnergypoints()
                  << ", attackdamage:" << kuzyilma.GetAttackdamage() << std::endl;

        std::cout << "\n---- copy constructor test -----\n";
        printTrapStats(kuzyilma, "Original (kuzyilma)");
        printTrapStats(copy_kuzyilma, "Copy (copy_kuzyilma)");

        bool exactCopy =
            (copy_kuzyilma.GetName() == kuzyilma.GetName()) &&
            (copy_kuzyilma.ClapTrap::GetName() == kuzyilma.ClapTrap::GetName()) &&
            (copy_kuzyilma.GetHitpoints() == kuzyilma.GetHitpoints()) &&
            (copy_kuzyilma.GetEnergypoints() == kuzyilma.GetEnergypoints()) &&
            (copy_kuzyilma.GetAttackdamage() == kuzyilma.GetAttackdamage());

        std::cout << (exactCopy ? "Copy constructor test PASSED\n" : "Copy constructor test FAILED\n");



        std::cout << "\n---- assignment (operator=) and beRepaired function test -----\n";

        test = default_Fragtrap;
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
        test.highFivesGuys();

        std::cout << "\n---- zero energy points test -----\n";

        kuzyilma.SetEnergypoints(3);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.Attack("test");
        kuzyilma.TakeDamage(1);
        kuzyilma.highFivesGuys();

        std::cout << '\n';
    }
}
