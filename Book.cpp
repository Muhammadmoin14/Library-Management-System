#include "Book.h"
#include "validator.h"
#include <iostream>

using namespace std;

Book::Book(string publisher, string isbn, string id,
           string author, string title, string category)
    : Resource(id, title, author, category)
{
    set_publisher(publisher);
    set_ISBN(isbn);
}

void Book::display() const
{
    Resource::display();

    cout << "Publisher Name: " << Publisher << endl;
    cout << "ISBN: " << ISBN << endl;
}

void Book::set_publisher(const string &publisher)
{
    Validator::validateNotEmpty(publisher);
    Publisher = publisher;
}

void Book::set_ISBN(const string &isbn)
{
    Validator::validateonlydigit(isbn); // acceptable for now
    ISBN = isbn;
}

string Book::get_publisher() const
{
    return Publisher;
}

string Book::get_ISBN() const
{
    return ISBN;
}