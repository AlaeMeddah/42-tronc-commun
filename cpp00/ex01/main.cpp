#include "phonebook.hpp"

int main()
{
    PhoneBook phonebook;
    std::string command;

    while (true)
    {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (command == "ADD")
            phonebook.ADD();
        else if (command == "SEARCH")
            phonebook.SEARCH();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Unknown command. Please try again." << std::endl;
    }
    return 0;
}
