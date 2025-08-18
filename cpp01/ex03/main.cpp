#include "HumanA.hpp"
#include "HumanB.hpp"

int main(void)
{
	Weapon club = Weapon("spiked club");

	HumanA bob("bob", club);
	bob.attack();
	club.setType("other club");
	bob.attack();

	HumanB jim("Jim");
	jim.attack();
	jim.setWeapon(club);
	jim.attack();
	club.setType("some other type of club");
	jim.attack();
	return 0;
}
