#include "contact.hpp"

void Contact::SetFirstName()
{
    std::cout << "Enter FirstName: ";
    std::getline(std::cin, FirstName);
    while (FirstName.empty())
    {
        std::cout << "FirstName can't be empty, please enter a valid input: ";
        std::getline(std::cin, FirstName);
    }
}

void Contact::SetLastName()
{
    std::cout << "Enter LastName: ";
    std::getline(std::cin, LastName);
    while (LastName.empty())
    {
        std::cout << "LastName can't be empty, please enter a valid input: ";
        std::getline(std::cin, LastName);
    }
}

void Contact::SetNickName()
{
    std::cout << "Enter Nickname: ";
    std::getline(std::cin, Nickname);
    while (Nickname.empty())
    {
        std::cout << "NickName can't be empty, please enter a valid input: ";
        std::getline(std::cin, Nickname);
    }
}

void Contact::SetPhoneNumber()
{
    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, PhoneNumber);
    while (PhoneNumber.empty())
    {
        std::cout << "PhoneNumber can't be empty, please enter a valid input: ";
        std::getline(std::cin, PhoneNumber);
    }
}

void Contact::SetDarkestSecret()
{
    std::cout << "Enter Darkest Secret: ";
    std::getline(std::cin, DarkestSecret);
    while (DarkestSecret.empty())
    {
        std::cout << "Darkest Secret can't be empty, please enter a valid input: ";
        std::getline(std::cin, DarkestSecret);
    }
}

std::string Contact::GetFirstName()
{
    return FirstName;
}

std::string Contact::GetLastName()
{
    return LastName;
}

std::string Contact::GetNickName()
{
    return Nickname;
}

std::string Contact::GetPhoneNumber()
{
    return PhoneNumber;
}

std::string Contact::GetDarkestSecret()
{
    return DarkestSecret;
}
