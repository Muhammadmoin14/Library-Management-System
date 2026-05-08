#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include "Resource.h"
#include "User.h"
#include <chrono>

using namespace std::chrono;

class BorrowRecord
{
private:
    system_clock::time_point issue_date;
    system_clock::time_point return_date;
    double fine;
    User *user;
    Resource *resource;

public:
    BorrowRecord(User *u, Resource *r);
    BorrowRecord(User* u, Resource* r,system_clock::time_point issue,
        system_clock::time_point ret,double fine);
    void set_ReturnDate(system_clock::time_point t);
    void set_IssueDate(system_clock::time_point t);

    system_clock::time_point get_ReturnDate() const;
    system_clock::time_point get_IssueDate() const;
    
    bool returned(){
        return fine == 0;
    }
    double get_Fine() const;

    double calculateFine();
    bool isOverdue() const;

    void display() const;

    User *getUser() const;
    Resource *getResource() const;
};

#endif