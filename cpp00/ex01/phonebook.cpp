#include <iostream>
#include <string>

class Contact
{
private:
    std::string FirstName;
    std::string LastName;
    std::string Nickname;
    std::string PhoneNumber;
    std::string DarkestSecret;

public:
    Contact();

    void SetFirstName();
    void SetLastName();
    void SetNickName();
    void SetPhoneNumber();
    void SetDarkestSecret();

    std::string GetFirstName();
    std::string GetLastName();
    std::string GetNickName();
    std::string GetPhoneNumber();
    std::string GetDarkestSecret();
};

Contact::Contact()
{
    FirstName = "";
    LastName = "";
    Nickname = "";
    PhoneNumber = "";
    DarkestSecret = "";
}

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
}

void Contact::SetNickName()
{
    std::cout << "Enter Nickname: ";
    std::getline(std::cin, Nickname);
}

void Contact::SetPhoneNumber()
{
    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, PhoneNumber);
}

void Contact::SetDarkestSecret()
{
    std::cout << "Enter Darkest Secret: ";
    std::getline(std::cin, DarkestSecret);
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

class PhoneBook
{
    private:
        Contact contacts[8];

    public:
        PhoneBook();
        void ADD();
        void SEARCH();
};

PhoneBook::PhoneBook() {}

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

void PhoneBook::SEARCH()
{
    std::string input;
    int index;

    //display
     
    //display 
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

}

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