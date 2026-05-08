#include "validator.h"
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <conio.h>
#include <stdexcept>
using namespace std;
namespace Validator
{
    void validateName(const string &name)
    {
        if (name.empty() || !all_of(name.begin(), name.end(), ::isalpha))
            throw invalid_argument("Name must contain only letters.");
    }

    void validateCNIC(const string &cnic)
    {
        if (cnic.length() != 13 || !all_of(cnic.begin(), cnic.end(), ::isdigit))
            throw length_error("CNIC must be exactly 13 digits.");
    }

    void validateEmail(const string &email)
    {
        const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
        if (!regex_match(email, pattern))
            throw invalid_argument("Invalid email format.");
    }
    void validatephone(const string &phone)
    {
        const regex pattern(R"(03\d{2}-\d{7})");
        if (!regex_match(phone, pattern))
        {
            throw invalid_argument("Phone Number Must In The Format (03XX-XXXXXXX)");
        }
    }

    void validatePassword(const string &pass)
    {
        const regex pattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{8,}$)");
        if (!regex_match(pass, pattern))
            throw logic_error("Weak Password! Use 8+ chars with Upper, Lower, and Number.");
    }

    void validateID(const string &ID)
    {
        if (ID.length() <= 3 && ID.length() >= 10 && !(all_of(ID.begin(), ID.end(), ::isdigit)))
        {
            throw invalid_argument("ID length must lies between (4-9) digits.");
        }
    }
    void validateDeposit(double amount)
    {
        if (amount < 1000)
            throw runtime_error("Minimum 1000 Rs deposit required.");
    }
    void validateNotEmpty(const string &input)
    {
        if (input.empty())
        {
            throw runtime_error("This field cannot be empty.");
        }
    }
    void validateonlydigit(const string &digit){
        validateNotEmpty(digit);
        if(!(all_of(digit.begin(),digit.end(), ::isdigit))){
            throw invalid_argument("Must Contain Only Digit.");
        }
    }
}
namespace
{
    string validatestring(const string &prompt, void (*Validate)(const string &), int max_try = 5)
    {
        string value;
        int tries = 0;
        while (true)
        {

            cout << prompt;
            getline(cin >> ws, value);
            try
            {
                string cleanvalue = trim(value);
                Validate(cleanvalue);
                return cleanvalue;
            }
            catch (invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
                if (tries > 0 && ++tries <= max_try)
                {
                    throw runtime_error("You have failed to many attempts");
                }
            }
        }
    }

    double validatdouble(const string &prompt, void (*validate)(const double), int max_try = 5)
    {
        double value;
        int tries = 0;
        while (true)
        {
            cout << prompt;
            cin >> ws;
            cin.ignore();
            cin >> value;
            try
            {
                validate(value);
                return value;
            }
            catch (runtime_error &e)
            {
                cout << "Error: " << e.what() << endl;
                if (tries > 0 && tries >= max_try)
                {
                    throw runtime_error("You have failed to many attempts");
                }
            }
        }
    }
    string validatePassword(const string &prompt, void (*validate)(const string &), int maxTries = 5)
    {
        int tries = 0;
        while (true)
        {
            string password = "";
            char ch;
            cout << prompt;
            while (true)
            {
                ch = _getch();
                if (ch == '\r')
                {
                    cout << endl;
                    break;
                }
                else if (ch == '\b')
                {
                    if (!password.empty())
                    {
                        password.pop_back();
                        cout << "\b \b";
                    }
                }
                else
                {
                    password += ch;
                    cout << '*';
                }
            }
            try
            {
                validate(password);
                return password;
            }
            catch (const exception &e)
            {
                cout << "  [!] " << e.what() << "\n";
                if (maxTries > 0 && ++tries >= maxTries)
                    throw runtime_error("Too many failed attempts.");
            }
        }
    }
}
string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r");

    return str.substr(first, (last - first + 1));
}