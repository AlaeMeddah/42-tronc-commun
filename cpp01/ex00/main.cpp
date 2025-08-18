#include "Zombie.hpp"

Zombie *newZombie(std::string name);
void randomChump(std::string name);

int main()
{
	Zombie *zombie1;

	zombie1 = newZombie("zombie1");
	randomChump("zombie2");
	zombie1->announce();
	delete zombie1;
	return 0;
}