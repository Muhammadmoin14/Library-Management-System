#include "User.h"
#include "Person.h"
#include "BorrowRecord.h"
#include "UserManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

UserManager::UserManager()
{
    currentUser = nullptr;
    adminCounter = 0;
    userCounter = 0;
}
UserManager::~UserManager()
{
    for (auto &u : users)
    {
        delete u;
    }
}

User *UserManager::registerUser(
    const std::string &username,
    const std::string &password,
    const std::string &firstname,
    const std::string &lastname,
    const std::string &email,
    const std::string &cnic,
    const std::string &address,
    const std::string &phone,
    Role role)
{
    if (findUserByUsername(username) != nullptr)
        return nullptr;

    User *user = new User();
    string id;
    id = user->generate_id(to_string(role), &userCounter, &adminCounter);
    user->set_id(id);
    user->set_Username(username);
    user->set_password(password);
    user->set_FirstName(firstname);
    user->set_LastName(lastname);
    user->set_Email(email);
    user->set_CNIC(cnic);
    user->set_Address(address);
    user->set_Phone(phone);

    users.emplace_back(user);
    return user;
}

User *UserManager::login(const std::string &username, const std::string &password)
{
    for (auto &u : users)
    {
        if (u->authenticate(username, password))
        {
            currentUser = u;
            return u;
        }
    }
    return nullptr;
}
void UserManager::logout()
{
    currentUser = nullptr;
}

User *UserManager::getCurrentUser() const
{
    return currentUser;
}

User *UserManager::findUserByUsername(const std::string &username) const
{
    for (auto &user : users)
    {
        if (user->get_Username() == username)
        {
            return user;
        }
    }
    return nullptr;
}

const std::vector<User *> &UserManager::getAllUsers() const
{
    return users;
}

void UserManager::load_from_file(const string& filename)
{
    ifstream file(filename);
    if (!file) return;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id, username, password, firstname,
        lastname,email, cnic, address, phone,balanceStr,
        borrowedStr, fineStr;

        getline(ss, id, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        getline(ss, email, ',');
        getline(ss, cnic, ',');
        getline(ss, address, ',');
        getline(ss, phone, ',');
        getline(ss, balanceStr, ',');
        getline(ss, borrowedStr, ',');
        getline(ss, fineStr);

        User* user = new User();

        user->set_id(id);
        user->set_Username(username);
        user->set_password(password);
        user->set_FirstName(firstname);
        user->set_LastName(lastname);
        user->set_Email(email);
        user->set_CNIC(cnic);
        user->set_Address(address);
        user->set_Phone(phone);

        user->add_balance(stod(balanceStr));
        user->set_current_Borrowed(stoi(borrowedStr));
        user->set_fine(stod(fineStr));
        users.push_back(user);

        if (id[0] == 'U')
            userCounter = max(userCounter, stoi(id.substr(2)) + 1);
        else if (id[0] == 'A')
            adminCounter = max(adminCounter, stoi(id.substr(2)) + 1);
    }

    file.close();
}
void UserManager::save_in_file(const string &filename) const
{
    ofstream file(filename);

    for (auto u : users)
    {
        file << u->get_ID() << ","
             << u->get_Username() << ","
             << u->get_password() << ","
             << u->get_firstname() << ","
             << u->get_lastname() << ","
             << u->get_Email() << ","
             << u->get_CNIC() << ","
             << u->get_address() << ","
             << u->get_phone() << ","
             << u->get_balance() << ","
             << u->getBorrowedCount() << ","
             << u->getFine()
             << "\n";
    }
    file.close();
}