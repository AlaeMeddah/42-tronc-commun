#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main()
{
	Zombie *horde;
	int i;

	horde = zombieHorde(5, "Zombie");
	i = -1;
	horde[0].announce();
	while (++i < 5)
		horde[i].announce();
	delete[] horde;
	return 0;
}
