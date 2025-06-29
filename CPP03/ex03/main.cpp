#include "DiamondTrap.hpp"

void printDiamondTrapStats(const DiamondTrap& dt, const std::string& label) {
    std::cout << "---- " << label << " ----\n";
    std::cout << "DiamondTrap Name: " << dt.GetName() << '\n';
    std::cout << "ClapTrap Name: " << dt.ClapTrap::GetName() << '\n';
    std::cout << "Hitpoints: " << dt.GetHitpoints() << '\n';
    std::cout << "Energypoints: " << dt.GetEnergypoints() << '\n';
    std::cout << "Attackdamage: " << dt.GetAttackdamage() << '\n';
    std::cout << "--------------------------\n\n";
}

int main()
{
    std::cout << "\n##### DiamondTrap tests #####\n";
    {
        DiamondTrap default_diamond;
        DiamondTrap kuzyilma("kuzyilma");
        DiamondTrap copy_kuzyilma(kuzyilma);
        DiamondTrap test("test");

        std::cout << "\n---- correct values test -----\n";
        kuzyilma.whoAmI();
        std::cout << "hitpoints:" << kuzyilma.GetHitpoints()
                  << ", energypoints:" << kuzyilma.GetEnergypoints()
                  << ", attackdamage:" << kuzyilma.GetAttackdamage() << std::endl;

        std::cout << "\n---- copy constructor test -----\n";
        printDiamondTrapStats(kuzyilma, "Original (kuzyilma)");
        printDiamondTrapStats(copy_kuzyilma, "Copy (copy_kuzyilma)");

        bool exactCopy =
            (copy_kuzyilma.GetName() == kuzyilma.GetName()) &&
            (copy_kuzyilma.ClapTrap::GetName() == kuzyilma.ClapTrap::GetName()) &&
            (copy_kuzyilma.GetHitpoints() == kuzyilma.GetHitpoints()) &&
            (copy_kuzyilma.GetEnergypoints() == kuzyilma.GetEnergypoints()) &&
            (copy_kuzyilma.GetAttackdamage() == kuzyilma.GetAttackdamage());

        std::cout << (exactCopy ? "Copy constructor test PASSED\n" : "Copy constructor test FAILED\n");

        std::cout << "\n---- assignment (operator=) and beRepaired function test -----\n";
        test = default_diamond;
        test.beRepaired(10);

        std::cout << "\n---- whoAmI function test -----\n";
        kuzyilma.whoAmI();

        std::cout << "\n---- inherited FragTrap::highFivesGuys test -----\n";
        kuzyilma.highFivesGuys();

        std::cout << "\n---- inherited ScavTrap::GuardGate test -----\n";
        kuzyilma.GuardGate();

        std::cout << "\n---- attack and takeDamage function test -----\n";
        test.SetAttackdamage(5);
        test.Attack("kuzyilma");
        kuzyilma.TakeDamage(test.GetAttackdamage());

        std::cout << "\n---- zero hit points test -----\n";
        copy_kuzyilma.SetAttackdamage(999);
        copy_kuzyilma.Attack("test");
        test.TakeDamage(999);
        test.beRepaired(100);  // Should fail
        test.Attack("hello");  // Should fail
        test.TakeDamage(999);  // Should print already dead
        test.GuardGate();      // Should fail due to zero HP
        test.highFivesGuys();  // Should fail due to zero HP

        std::cout << "\n---- zero energy points test -----\n";
        kuzyilma.SetEnergypoints(3);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);
        kuzyilma.beRepaired(1);  // should do nothing (0 energy)
        kuzyilma.Attack("test"); // should fail due to no energy
        kuzyilma.TakeDamage(1);

        std::cout << '\n';
    }

    return 0;
}
