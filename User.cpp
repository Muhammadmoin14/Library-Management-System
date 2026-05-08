#include "User.h"

User::User() : maxBooksAllowed(3), currentBorrowed(0), unpaidFines(0.0) {}

bool User::canBorrow() const
{
    return currentBorrowed < maxBooksAllowed;
}

void User::borrowBook()
{
    if (canBorrow())
        currentBorrowed++;
}

void User::returnBook()
{
    if (currentBorrowed > 0)
        currentBorrowed--;
}

void User::addFine(double amount)
{
    if (amount > 0)
        unpaidFines += amount;
}

void User::payFine(double amount)
{
    if (amount <= 0)
        return;

    if (amount > unpaidFines)
        unpaidFines = 0;
    else
        unpaidFines -= amount;
}

int User::getBorrowedCount() const
{
    return currentBorrowed;
}

int User::getMaxLimit() const
{
    return maxBooksAllowed;
}

double User::getFine() const
{
    return unpaidFines;
}

void User::set_Maxlimit(int limit)
{
    if (limit > 0)
        maxBooksAllowed = limit;
}
void User::set_current_Borrowed(int count){
    if (count >= 0)
    currentBorrowed = count;
}
void User::set_fine(double fine){
    if (fine >= 0)
    unpaidFines = fine;
}