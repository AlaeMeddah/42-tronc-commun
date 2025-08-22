# include <iostream>
# include <string>
#include <fstream>

int main (int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Wrong number of args" << std::endl;
		return 0;
	}

	if (!argv[2])
	{
		std::cout << "s1 can t be NULL" << std::endl;
		return 0;
	}

	std::ifstream file(argv[1]);
	if (!file.is_open())
	{
		std::cout << "Failed to open " << argv[1] << std::endl;
		return 0;
	}
}
