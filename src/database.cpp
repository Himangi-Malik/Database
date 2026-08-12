#include "database.h"

#include <iostream>

Database::Database(const std::string& filename)
    : pager(filename)  //member initializer list 
{
    std::cout << "Opening database...\n";
}

void Database::run()
{
    std::cout << "Database is running.\n";
}

Pager& Database::getPager()
{
    return pager;
}

Database::~Database()
{
    std::cout << "Closing database...\n";
}