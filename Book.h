#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Resource.h"

class Book : public Resource
{
private:
    std::string Publisher;
    std::string ISBN;

public:
    Book(std::string publisher, std::string isbn,std::string id, std::string title,
         std::string author,  std::string category);

    void set_publisher(const std::string &publisher);
    void set_ISBN(const std::string &isbn);

    std::string get_publisher() const;
    std::string get_ISBN() const;

    void display() const override;
};

#endif
