#pragma once
#include <vector>
#include <string>
#include "BorrowRecord.h"
#include "Resource.h"
#include "User.h"

class BorrowManager
{
private:
    std::vector<BorrowRecord*> records;

public:
    BorrowManager();
    ~BorrowManager();

    void issueBook(User* user, Resource* resource);
    void returnBook(User* user, const std::string& resourceID);

    Resource* searchByID(const std::vector<Resource*>& resources, const std::string& id);

    void showAvailableBooks(const std::vector<Resource*>& resources);
    void showUserRecords(User* user);
    void showAllRecords();

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename,
                      const std::vector<User*>& users,
                      const std::vector<Resource*>& resources);
};