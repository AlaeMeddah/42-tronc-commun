#include "phonebook.hpp"

void PhoneBook::ADD()
{
    int i = -1;

    while (++i < 8)
    {
        if (contacts[i].GetFirstName().empty())
        {
            contacts[i].SetFirstName();
            contacts[i].SetLastName();
            contacts[i].SetNickName();
            contacts[i].SetPhoneNumber();
            contacts[i].SetDarkestSecret();
            return;
        }
    }
    i = -1;
    while (++i < 7)
        contacts[i] = contacts[i + 1];
    contacts[i].SetFirstName();
    contacts[i].SetLastName();
    contacts[i].SetNickName();
    contacts[i].SetPhoneNumber();
    contacts[i].SetDarkestSecret();
}

std::string truncate(std::string str, std::size_t n)
{
    if (str.length() > n)
        str = str.substr(0, n - 1) + ".";
    return str;
}

void PhoneBook::SEARCH()
{
    std::string input;
    int index;

    std::cout << std::setw(10) << "Index" << "|";
    std::cout << std::setw(10) << "FirstName" << "|";
    std::cout << std::setw(10) << "LastName" << "|";
    std::cout << std::setw(10) << "NickName" << std::endl;
    index = -1;
    while (++index < 8)
    {
        std::cout << std::setw(10) << index << "|";
        std::cout << std::setw(10) << truncate(contacts[index].GetFirstName(), 10) << "|";
        std::cout << std::setw(10) << truncate(contacts[index].GetLastName(), 10) << "|";
        std::cout << std::setw(10) << truncate(contacts[index].GetNickName(), 10) << std::endl;
    }
    std::cout << "Enter the index of the contact you wish to display (0 to 7): ";
    std::getline(std::cin, input);    
    while (input[0] < '0' || input[0] > '7' || input.length() != 1)
    {
        std::cout << "Invalid input. Please enter a number between 0 and 7: ";
        std::getline(std::cin, input);
    }
    index = input[0] - '0';
    std::cout << "FirstName: " << contacts[index].GetFirstName() << std::endl;
    std::cout << "LastName: " << contacts[index].GetLastName() << std::endl;
    std::cout << "NickName: " << contacts[index].GetNickName() << std::endl;
    std::cout << "PhoneNumber: " << contacts[index].GetPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << contacts[index].GetDarkestSecret() << std::endl;
}
