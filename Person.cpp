#include "Person.h"
#include "validator.h"
using namespace std;

int Person::nxt_id = 1;
Person::Person() : balance(0.0) {}

Person::~Person() {}

string Person::generate_id(const string &user_role , int *u_c , int *a_c){
    if (user_role == "1")           // Changes occur 
    {
        *a_c++;
        return "A-" + to_string(*a_c) ;     
    }
    else{
        *u_c++;
        return "U-" + to_string(*u_c) ;
    }
}

void Person::set_ID(const std::string& id)
{
    ID = id;
}

// set_id (lowercase) — public version called by UserManager
void Person::set_id(const std::string& id)
{
    ID = id;
}

std::string Person::get_ID() const
{
    return ID;
}

string Person::get_password() const{
    return Password;
}

bool Person::authenticate(const std::string& uname, const std::string& pass) const
{
    return (Username == uname && Password == pass);
}

void Person::set_Username(const std::string& username)
{
    Validator::validateName(username);
    Username = username;
}

void Person::set_password(const std::string& password)
{
    Validator::validatePassword(password);
    Password = password;
}

void Person::set_FirstName(const std::string& firstname)
{
    Validator::validateName(firstname);
    FirstName = firstname;
}

void Person::set_LastName(const std::string& lastname)
{
    Validator::validateName(lastname);
    LastName = lastname;
}

void Person::set_CNIC(const std::string& cnic)
{
    Validator::validateCNIC(cnic);
    CNIC = cnic;
}

void Person::set_Email(const std::string& email)
{
    Validator::validateEmail(email);
    Email = email;
}

void Person::set_Address(const std::string& address)
{
    Validator::validateNotEmpty(address);
    Address = address;
}

void Person::set_Phone(const std::string& phone)
{
    Validator::validatephone(phone);
    phone_number = phone;
}

string Person::get_Username() const { return Username; }
string Person::get_firstname() const { return FirstName; }
string Person::get_lastname() const { return LastName; }
string Person::get_Email() const { return Email; }
string Person::get_CNIC() const { return CNIC; }
string Person::get_address() const { return Address; }
string Person::get_phone() const { return phone_number; }


void Person::add_balance(double amount)
{
    if (amount > 0)
        balance += amount;
}

double Person::get_balance() const
{
    return balance;
}