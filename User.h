#pragma once
#include "Person.h"
#include <iostream>

class User : public Person
{
private:
    int maxBooksAllowed;
    int currentBorrowed;
    double unpaidFines;

public:
    // Constructors
    User();

    // Borrow control
    bool canBorrow() const;
    void borrowBook();
    void returnBook();

    // Fine handling
    void addFine(double amount);
    void payFine(double amount);

    // Getters
    int getBorrowedCount() const;
    int getMaxLimit() const;
    double getFine() const;

    // Setters (optional)
    void set_Maxlimit(int limit);
    void set_current_Borrowed(int count);
    void set_fine(double fine);

    // Display
    void display() const;
};