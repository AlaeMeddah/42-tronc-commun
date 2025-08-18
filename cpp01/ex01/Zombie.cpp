#include "Zombie.hpp"

void Zombie::setname(std::string name)
{
	this->Name = name;
}

void Zombie::announce()
{
	std::cout << this->Name <<": BraiiiiiiinnnzzzZ..." << std::endl;
}
