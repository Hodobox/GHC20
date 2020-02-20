#ifndef LIB_H
#define LIB_H

#include "includes.h"

struct lib {
    int nBooks;
    int signupDays;
    int booksPerDay;
    vector<int> booksIds; // possibly set
    int id;
};

#endif