#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <iostream>
#include "validator.h"
using namespace std;
class Resource
{
protected:
    string ResourceID, Title, Author, Category;
    bool isavailable;
    static long unique_resource_id;

public:
    Resource(string title, string author, string category);
    Resource(string resourceID, string title, string author, string category);
    virtual ~Resource();
    // void Add_Resource(string resourceID, string title, string author, string category);
    bool matchID(const string &ID) const;
    // void authenticate(const string &ID) const;
    // void Update_resource();

    void set_ID();
    void set_Title(const string &title);
    void set_Author(const string &author);
    void set_Category(const string &cat);
    void set_availability(bool value);
    string get_ID() const;
    string get_title() const;
    string get_Author() const;
    string get_category() const;
    bool get_availability() const;

    static void setNextID(int value);
    string generate_ID();

    virtual void display() const;
};
#endif