#include "BorrowRecord.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

BorrowRecord::BorrowRecord(User *u, Resource *r)
    : user(u), resource(r), fine(0.0)
{
    issue_date = system_clock::now();
    return_date = issue_date + hours(24 * 10); // 10 days allowed
}
BorrowRecord::BorrowRecord(User *u, Resource *r, system_clock::time_point issue,
    system_clock::time_point ret, double fine)
{
    user = u;
    resource = r;
    issue_date = issue;
    return_date = ret;
    this->fine = fine;
}
void BorrowRecord::set_IssueDate(system_clock::time_point t)
{
    issue_date = t;
}

void BorrowRecord::set_ReturnDate(system_clock::time_point t)
{
    return_date = t;
}

system_clock::time_point BorrowRecord::get_ReturnDate() const
{
    return return_date;
}

system_clock::time_point BorrowRecord::get_IssueDate() const
{
    return issue_date;
}

double BorrowRecord::get_Fine() const
{
    return fine;
}

double BorrowRecord::calculateFine()
{
    auto now = system_clock::now();

    // If returned on time → no fine
    if (now <= return_date)
    {
        fine = 0;
        return fine;
    }

    // Calculate overdue time only
    auto overdue_hours = duration_cast<hours>(now - return_date).count();
    int overdue_days = overdue_hours / 24;

    fine = overdue_days * 10; // 10 per day
    return fine;
}

bool BorrowRecord::isOverdue() const
{
    return system_clock::now() > return_date;
}

void BorrowRecord::display() const
{
    time_t issue_t = system_clock::to_time_t(issue_date);
    time_t return_t = system_clock::to_time_t(return_date);

    tm issue_tm = *localtime(&issue_t);
    tm return_tm = *localtime(&return_t);

    cout << "UserName: " << user->get_Username() << " | "
         << "Resource ID: " << resource->get_ID() << " | "
         << "Issued: " << put_time(&issue_tm, "%d-%m-%Y") << " | "
         << "Due: " << put_time(&return_tm, "%d-%m-%Y") << endl;
}

User *BorrowRecord::getUser() const
{
    return user;
}

Resource *BorrowRecord::getResource() const
{
    return resource;
}