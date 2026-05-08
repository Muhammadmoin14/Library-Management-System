#include "BorrowManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

BorrowManager::BorrowManager() {}

BorrowManager::~BorrowManager()
{
    for (auto r : records)
        delete r;
}

//////////////////////////////////////////////////////
// ISSUE BOOK
//////////////////////////////////////////////////////
void BorrowManager::issueBook(User *user, Resource *resource)
{
    if (!resource->get_availability())
    {
        cout << "Book not available.\n";
        return;
    }

    BorrowRecord *record = new BorrowRecord(user, resource);
    records.push_back(record);

    resource->set_availability(false);

    cout << "Book issued successfully.\n";
}

//////////////////////////////////////////////////////
// RETURN BOOK
//////////////////////////////////////////////////////
void BorrowManager::returnBook(User *user, const string &resourceID)
{
    for (auto record : records)
    {
        if (record->getUser() == user &&
            record->getResource()->get_ID() == resourceID)
        {
            double fine = record->calculateFine();

            record->getResource()->set_availability(true);

            if (fine > 0)
            {
                user->addFine(fine);  // BUG FIX: was never adding fine to user
                cout << "  Returned. Fine charged: Rs " << fine << "\n";
            }
            else
            {
                cout << "  Returned on time. No fine.\n";
            }
            return;
        }
    }
    cout << "  Record not found for that Book ID.\n";
}

//////////////////////////////////////////////////////
// SEARCH BY ID
//////////////////////////////////////////////////////
Resource *BorrowManager::searchByID(const vector<Resource *> &resources, const string &id)
{
    for (auto r : resources)
    {
        if (r->get_ID() == id)
            return r;
    }
    return nullptr;
}

//////////////////////////////////////////////////////
// SHOW AVAILABLE BOOKS
//////////////////////////////////////////////////////
void BorrowManager::showAvailableBooks(const vector<Resource *> &resources)
{
    for (auto r : resources)
    {
        if (r->get_availability())
        {
            r->display();
            cout << endl;
        }
    }
}

//////////////////////////////////////////////////////
// USER RECORDS
//////////////////////////////////////////////////////
void BorrowManager::showUserRecords(User *user)
{
    for (auto r : records)
    {
        if (r->getUser() == user)
            r->display();
    }
}

//////////////////////////////////////////////////////
// ADMIN - ALL RECORDS
//////////////////////////////////////////////////////
void BorrowManager::showAllRecords()
{
    for (auto r : records)
        r->display();
}

void BorrowManager::saveToFile(const string &filename)
{
    ofstream file(filename);

    for (auto r : records)
    {
        auto issue_tm = system_clock::to_time_t(r->get_IssueDate());
        auto return_tm = system_clock::to_time_t(r->get_ReturnDate());
        file << r->getUser()->get_Username() << ","
             << r->getResource()->get_ID() << ","
             << issue_tm << ","
             << return_tm << ","
             << r->get_Fine() << "\n";
    }

    file.close();
}

void BorrowManager::loadFromFile(const string &filename,
                                 const vector<User *> &users,
                                 const vector<Resource *> &resources)
{
    ifstream file(filename);
    string line;
    if (!file.is_open())   // BUG FIX: was checking is_open() without !
    {
        cout << "Borrow file not found, starting fresh.\n";
        return;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string username, resourceID, issueStr, returnStr, fineStr;

        getline(ss, username,   ',');
        getline(ss, resourceID, ',');
        getline(ss, issueStr,   ',');
        getline(ss, returnStr,  ',');  // BUG FIX: was reading issueStr twice, skipping returnStr
        getline(ss, fineStr);

        User *user = nullptr;
        Resource *resource = nullptr;

        // find user
        for (auto u : users)
        {
            if (u->get_Username() == username)
            {
                user = u;
                break;
            }
        }

        // find resource
        for (auto r : resources)
        {
            if (r->get_ID() == resourceID)
            {
                resource = r;
                break;
            }
        }

        if (user && resource)
        {

            time_t issue_tm = stoll(issueStr);
            time_t return_tm = stoll(returnStr);
            auto issue = system_clock::from_time_t(issue_tm);
            auto ret = system_clock::from_time_t(return_tm);
            BorrowRecord *record = new BorrowRecord(user, resource,issue,ret,stod(fineStr));
            records.push_back(record);
            resource->set_availability(false);
        }
    }
    file.close();
}