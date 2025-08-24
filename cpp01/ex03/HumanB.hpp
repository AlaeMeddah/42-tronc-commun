#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
	private:
		std::string name;
		Weapon *weapon;

	public:
		HumanB (std::string name) 
		{
			this->name = name;
			this->weapon = NULL;
		}
		HumanB (std::string name, Weapon &weapon)
		{
			this->name = name;
			this->weapon = &weapon;
		}
		void attack();
		void setWeapon(Weapon &weapon);
};

#endif