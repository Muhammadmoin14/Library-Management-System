/*
 * Resource.cpp
 * ------------
 * This file was missing from the project — that caused all the
 * "undefined reference to Resource::..." linker errors.
 *
 * Resource is the BASE CLASS for all library items (Book, etc.)
 * This demonstrates INHERITANCE — Book extends Resource.
 */

#include "Resource.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Static member must be defined once outside the class
long Resource::unique_resource_id = 1;

// ── Constructors ─────────────────────────────────────────────

// Constructor used when adding a brand new book (no ID yet)
Resource::Resource(string title, string author, string category)
    : Title(title), Author(author), Category(category), isavailable(true)
{
    // ID will be set later by calling set_ID()
    ResourceID = "";
}

// Constructor used when loading from file (ID already known)
Resource::Resource(string resourceID, string title, string author, string category)
    : ResourceID(resourceID), Title(title), Author(author),
      Category(category), isavailable(true)
{
}

// Destructor
Resource::~Resource() {}

// ── ID generation ────────────────────────────────────────────

// Auto-generate a unique ID like R-1, R-2, R-3 ...
string Resource::generate_ID()
{
    return "R-" + to_string(unique_resource_id++);
}

// Call this after constructing to assign a new auto ID
void Resource::set_ID()
{
    ResourceID = generate_ID();
}

// Update the static counter (used when loading from file)
void Resource::setNextID(int value)
{
    unique_resource_id = value;
}

// ── Setters ──────────────────────────────────────────────────

void Resource::set_Title(const string& title)
{
    Validator::validateNotEmpty(title);
    Title = title;
}

void Resource::set_Author(const string& author)
{
    Validator::validateNotEmpty(author);
    Author = author;
}

void Resource::set_Category(const string& cat)
{
    Validator::validateNotEmpty(cat);
    Category = cat;
}

void Resource::set_availability(bool value)
{
    isavailable = value;
}

// ── Getters ──────────────────────────────────────────────────

string Resource::get_ID() const       { return ResourceID; }
string Resource::get_title() const    { return Title; }
string Resource::get_Author() const   { return Author; }
string Resource::get_category() const { return Category; }
bool   Resource::get_availability() const { return isavailable; }

// ── Other ────────────────────────────────────────────────────

// Check if this resource matches a given ID
bool Resource::matchID(const string& ID) const
{
    return ResourceID == ID;
}

// Display basic info — overridden by Book::display()
// This is METHOD OVERRIDING (virtual function, OOP concept)
void Resource::display() const
{
    cout << "  ID        : " << ResourceID   << "\n";
    cout << "  Title     : " << Title        << "\n";
    cout << "  Author    : " << Author       << "\n";
    cout << "  Category  : " << Category     << "\n";
    cout << "  Available : " << (isavailable ? "Yes" : "No") << "\n";
    cout << "\n";
}