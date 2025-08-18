#ifndef Weapon_HPP
# define Weapon_HPP

# include <iostream>
# include <string>
# include <iomanip>
# include <sstream>

class Weapon
{
    private:
        std::string type;

    public:
        Weapon () {}
        Weapon (std::string type)
        {
            this->type = type;
        }
		std::string &getType();
		void setType(std::string type);
};

#endif
