#include "ClapTrap.hpp"

int main ()
{
    ClapTrap default_claptrap;
    ClapTrap kuzyilma("kuzyilma");
    ClapTrap copy_kuzyilma(kuzyilma);
    ClapTrap test("test");

	std::cout << "\n---- berepaired function test-----\n";

    test = default_claptrap;
    test.beRepaired(10);

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

	std::cout << "\n---- zero energy point test-----\n";

	kuzyilma.SetEnergypoints(3);
	kuzyilma.beRepaired(1);
	kuzyilma.beRepaired(1);
	kuzyilma.beRepaired(1);
	kuzyilma.beRepaired(1);
	kuzyilma.Attack("test");
	kuzyilma.TakeDamage(1);

	std::cout << '\n';
}