#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>
# include <iomanip>
# include <sstream>

class Zombie
{
    private:
        std::string Name;

    public:
        Zombie() {}
        Zombie(std::string Name)
        {
            this->Name = Name;
        }
		~Zombie()
		{
			std::cout << "Destructor called for " << Name << std::endl;
		}
        void setname(std::string Name);
		void announce();
};

#endif
