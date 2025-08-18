#include "Weapon.hpp"

std::string &Weapon::getType()
{
	std::string &type = this->type;

	return (type);
}

void Weapon::setType(std::string type)
{
	this->type = type;
}
