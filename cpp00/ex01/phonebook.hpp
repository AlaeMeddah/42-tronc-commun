#ifndef PHONEBOOK_H
# define PHONEBOOK_H

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
