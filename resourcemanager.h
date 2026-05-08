#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <vector>
#include "Resource.h"
using namespace std;

// Enum moved here from .cpp so LibrarySystem.cpp and main.cpp can use it
enum class resourcefield
{
    ID,
    TITLE,
    AUTHOR,
    PUBLISHER,
    ISBN,
    CATEGORY
};

class ResourceManager
{
    vector<Resource*> resource;

public:
    ResourceManager();
    void      Add_Resource(Resource* r);
    bool      Remove_Resource(const string& id);
    void      Update_Resource(Resource* r, const string& value, resourcefield field);
    Resource* search_by_id(const string& id);
    void      display_All();
    void      Load_File(string File_name);
    void      Store_file(string File_name);
    ~ResourceManager();
};

#endif