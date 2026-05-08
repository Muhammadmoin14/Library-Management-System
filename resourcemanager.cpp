#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "resourcemanager.h"
#include "Resource.h"
#include "Book.h"
#include "validator.h"

enum class categoryfield
{
    SCIENCE,
    FICTION,
    HISTORY,
    REFERENCE
};
using namespace std;
/*

*/

ResourceManager::ResourceManager() {}

void ResourceManager::Add_Resource(Resource *r)
{
    resource.emplace_back(r);
}

bool ResourceManager::Remove_Resource(const string &id)
{
    for (int i = 0; i < resource.size(); i++)
    {
        if (resource[i]->get_ID() == id)
        {
            delete resource[i];
            resource.erase(resource.begin() + i);
            return true;
        }
    }
    return false;
}

void ResourceManager::Update_Resource(Resource *r, const string &value, resourcefield field)
{
    if (!r) return;
    Book *b = dynamic_cast<Book *>(r);

    switch (field)
    {
    case resourcefield::ID:
        r->set_ID(); 
        break; 

    case resourcefield::PUBLISHER:
        if (!b) throw runtime_error("Error: This resource is not a Book.");
        b->set_publisher(value);
        break;

    case resourcefield::ISBN:
        if (!b) throw runtime_error("Error: This resource is not a Book.");
        b->set_ISBN(value);
        break;

    case resourcefield::AUTHOR:
        r->set_Author(value);
        break;

    case resourcefield::TITLE:
        r->set_Title(value);
        break;

    case resourcefield::CATEGORY:
        r->set_Category(value);
        break;
    }
    cout << "Successfully Updated. 🎉" << endl;
}

Resource *ResourceManager::search_by_id(const string &id)
{
    for (auto r : resource)
    {
        if (r->get_ID() == id)
        {
            return r;
        }
    }
    throw invalid_argument("ERROR: \"ID not found.\"");
}
void ResourceManager::display_All()
{
    for (auto r : resource)
    {
        r->display();
    }
}

void ResourceManager::Load_File(string File_name)
{
    ifstream fload(File_name);
    if (!fload.is_open())
    {
        cout << "Error:- File Not Found!";
        return;
    }

    string line;
    getline(fload, line);
    getline(fload, line);

    while (getline(fload, line))
    {
        if (line.empty())
            continue;

        string id = trim(line.substr(0, 15));
        string title = trim(line.substr(15, 35));
        string auth = trim(line.substr(50, 25));
        string cat = trim(line.substr(75, 20));
        string pub = trim(line.substr(95, 25));
        string isbn = trim(line.substr(120, 20));
        resource.push_back(new Book(pub, isbn, id, title, auth, cat));
    }
    fload.close();
}

void ResourceManager::Store_file(string File_name)
{
    ofstream fstore(File_name, ios::out);
    if (!fstore.is_open())
    {
        cout << "Error:- File Doesnot found." << endl;
        return;
    }
    fstore << left << setw(15) << "Book ID"
           << left << setw(35) << "Title"
           << left << setw(25) << "Author"
           << left << setw(20) << "Category"
           << left << setw(25) << "Publisher"
           << left << setw(20) << "ISBN" << endl;
    fstore << string(140, '-') << endl;
    for (auto r : resource)
    {
        fstore << left << setw(15) << r->get_ID()
               << left << setw(35) << r->get_title()
               << left << setw(25) << r->get_Author()
               << left << setw(20) << r->get_category();

        Book *b = dynamic_cast<Book *>(r);
        if (b)
        {
            fstore << left << setw(25) << b->get_publisher()
                   << left << setw(20) << b->get_ISBN();
        }
        else
        {
            fstore << left << setw(25) << "N/A"
                   << left << setw(20) << "N/A";
        }
        fstore << endl;
    }
    fstore.close();
}
ResourceManager::~ResourceManager()
{
    for (auto r : resource)
        delete r;
}