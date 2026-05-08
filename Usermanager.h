#pragma once
#include <vector>
#include <string>
#include "User.h"

class UserManager
{
public:
    enum Role
    {
        USER,
        ADMIN
    };

private:
    std::vector<User*> users;
    User* currentUser;

    int userCounter;
    int adminCounter;

public:
    UserManager();
    ~UserManager();

    User* registerUser(
        const std::string& username,
        const std::string& password,
        const std::string& firstname,
        const std::string& lastname,
        const std::string& email,
        const std::string& cnic,
        const std::string& address,
        const std::string& phone,
        Role role
    );

    User* login(const std::string& username, const std::string& password);
    void logout();

    User* getCurrentUser() const;

    User* findUserByUsername(const std::string& username) const;

    const std::vector<User*>& getAllUsers() const;

    void load_from_file(const string &file_name) ;
    void save_in_file(const string &file_name) const;
};