#ifndef CONTACT_H
# define CONTACT_H

# include <iostream>
# include <string>
# include <iomanip>
# include <sstream>

class Contact
{
    private:
        std::string FirstName;
        std::string LastName;
        std::string Nickname;
        std::string PhoneNumber;
        std::string DarkestSecret;

    public:
        Contact()
        {
            FirstName = "";
            LastName = "";
            Nickname = "";
            PhoneNumber = "";
            DarkestSecret = "";
        }

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

#endif
