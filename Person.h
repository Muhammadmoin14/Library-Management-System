#pragma once
#include <string>
using namespace std;

class Person
{
protected:
    std::string ID;
    std::string Username;
    std::string Password;

    std::string FirstName;
    std::string LastName;
    std::string Email;
    std::string CNIC;
    std::string Address;
    std::string phone_number;

    static int nxt_id;
    double balance;

public:
    Person();
    virtual ~Person();

    // ID
    std::string get_ID() const;
    string generate_id(const string &user_role , int *u_c , int *a_c);
    // Auth
    bool authenticate(const std::string& uname, const std::string& pass) const;

    // Setters
    void set_Username(const std::string& username);
    void set_password(const std::string& password);
    void set_FirstName(const std::string& firstname);
    void set_LastName(const std::string& lastname);
    void set_CNIC(const std::string& cnic);
    void set_Email(const std::string& email);
    void set_Address(const std::string& address);
    void set_Phone(const std::string& phone);
    void set_id(const std::string& id);
    
    // Getters
    std::string get_Username() const;
    std::string get_firstname() const;
    std::string get_lastname() const;
    std::string get_Email() const;
    std::string get_CNIC() const;
    std::string get_address() const;
    std::string get_phone() const;
    string get_password() const;
    // Balance
    void add_balance(double amount);
    double get_balance() const;

protected:
    void set_ID(const std::string& id); // only UserManager can assign
};