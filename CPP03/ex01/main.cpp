#include "ScavTrap.hpp"

void printTrapStats(const ScavTrap& dt, const std::string& label) {
    std::cout << "---- " << label << " ----\n";
    std::cout << "ScavTrap Name: " << dt.GetName() << '\n';
    std::cout << "Hitpoints: " << dt.GetHitpoints() << '\n';
    std::cout << "Energypoints: " << dt.GetEnergypoints() << '\n';
    std::cout << "Attackdamage: " << dt.GetAttackdamage() << '\n';
    std::cout << "--------------------------\n\n";
}

int main ()
{
        std::cout << "\n##### ScavTrap tests #####\n";
    {
        ScavTrap default_claptrap;
        ScavTrap kuzyilma("kuzyilma");
        ScavTrap copy_kuzyilma(kuzyilma);
        ScavTrap test("test");


        std::cout << "Name:" << kuzyilma.GetName()
                  << "hitpoints:" << kuzyilma.GetHitpoints()
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


	    std::cout << "\n---- berepaired and assignment(operator=) function test-----\n";

        test = default_claptrap;
        test.beRepaired(10);

        std::cout << "\n---- guardgate function test-----\n";

        test.GuardGate();

	    std::cout << "\n---- attack and getattacked function test-----\n";
        
        test.SetAttackdamage(5);
        test.Attack("kuzyilma");
        kuzyilma.TakeDamage(test.GetAttackdamage());
        
	    std::cout <<"\n---- zero hit point test-----\n";

        copy_kuzyilma.SetAttackdamage(999);
        copy_kuzyilma.Attack("test");
	    test.TakeDamage(999);
        test.beRepaired(100);
        test.Attack("heloo");
        test.TakeDamage(999);
        test.GuardGate();

	    std::cout << "\n---- zero energy point test-----\n";

	    kuzyilma.SetEnergypoints(3);
	    kuzyilma.beRepaired(1);
	    kuzyilma.beRepaired(1);
	    kuzyilma.beRepaired(1);
	    kuzyilma.beRepaired(1);
	    kuzyilma.Attack("test");
	    kuzyilma.TakeDamage(1);
        kuzyilma.GuardGate();

	    std::cout << '\n';
    }
}