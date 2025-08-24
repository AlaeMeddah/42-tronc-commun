#include "Harl.Hpp"

int main (int argc, char **argv)
{
	Harl Harl;
	std::string level;

	if (argc != 2)
	{
		std::cout << "Wrong number of arg" << std::endl;
		return 0;
	}
	level = std::string(argv[1]);
	Harl.complain(level);
	return 0;
}