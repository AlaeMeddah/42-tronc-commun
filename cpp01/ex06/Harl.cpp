#include "Harl.Hpp"

void Harl::debug()
{
	std::cout << "Harl is complaining about some debugging" << std::endl;
}

void Harl::info()
{
	std::cout << "Harl is complaining about some info" << std::endl;
}

void Harl::warning()
{
	std::cout << "Harl is complaining about some warning " << std::endl;
}

void Harl::error()
{
	std::cout << "Harl is complaining about some error" << std::endl;
}

void Harl::complain(std::string level)
{
	std::string array[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void (Harl::*function[4])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	int i = -1;

	while (++i < 4)
	{
		if (array[i] == level)
			break ;
	}

	switch (i)
	{
		case 0:
			(this->*function[0])();
		case 1:
			(this->*function[1])();
		case 2:
			(this->*function[2])();
		case 3:
			(this->*function[3])();
			break;
		default:
			std::cout << "Harl is complaining about insignificant problems" << std::endl;
			break;
	}
}
