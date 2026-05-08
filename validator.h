#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <string>
using namespace std;
namespace Validator
{
    void validateName(const string &name);
    void validateCNIC(const string &cnic);
    void validateEmail(const string &email);
    void validatephone(const string &phone);
    void validatePassword(const string &pass);
    void validateID(const string &ID);
    void validateDeposit(double amount);
    void validateNotEmpty(const string &input);
    void validateonlydigit(const string &digit);
}
namespace
{
    string validatestring(const string &prompt, void (*validate)(const string &), int max_try);
    double validatdouble(const string &prompt, void (*validate)(const double), int max_try);
    string validatePassword(const string &prompt, void (*validate)(const string &), int maxTries);
}
string trim(const string &str);
#endif