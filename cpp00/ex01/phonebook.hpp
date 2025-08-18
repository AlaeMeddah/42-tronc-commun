#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "contact.hpp"

class PhoneBook
{
    private:
        Contact contacts[8];

    public:
        PhoneBook() {}

        void ADD();
        void SEARCH();
};

#endif
