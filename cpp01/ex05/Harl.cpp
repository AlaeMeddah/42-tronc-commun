#include "Harl.Hpp"

void Harl::debug()
{
	std::cout << "harl is debugging" << std::endl;
}

void Harl::info()
{
	std::cout << "Harl is giving info" << std::endl;
}

void Harl::warning()
{
	std::cout << "Harl repport a warning " << std::endl;
}

void Harl::error()
{
	std::cout << "Harl repport an error" << std::endl;
}

void Harl::complain(std::string level)
{
	std::string array[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void (Harl::*function[4])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	int i = -1;

	while (++i < 4)
	{
		if (array[i] == level)
		{
			(this->*function[i])();
			return ;
		}
	}
	std::cout << "Harl didn t understand " << level << std::endl;
}
