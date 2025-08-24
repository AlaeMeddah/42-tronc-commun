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

	std::ifstream infile(argv[1]);
	if (!infile.is_open())
	{
		std::cout << "Failed to open " << argv[1] << std::endl;
		return 0;
	}

	std::string outfile_name = std::string(argv[1]) + ".replace";
	std::ofstream outfile(outfile_name.c_str());
	if (!outfile)
	{
		std::cout << "Failed to create " << argv[1] << std::endl;
		return 0;		
	}

	std::string line;
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	size_t s1_len = s1.length();
	size_t s2_len = s2.length();
	size_t pos;
	while (getline (infile, line))
	{
		pos = line.find(s1);
		while (pos != std::string::npos)
		{
			line.erase(pos, s1_len);
			line.insert(pos, s2);
			pos = line.find(s1, pos + s2_len);
		}
		outfile << line << std::endl;
	}
	outfile.close();
	infile.close();
}
