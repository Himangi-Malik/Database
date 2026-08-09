#include "database.h"

#include <iostream>

Database::Database(const std::string& filename)
    : pager(filename)  //member initializer list 
{
    std::cout << "Opening database...\n";
}

Database::~Database()
{
    std::cout << "Closing database...\n";
}

void Database::run()
{
    std::cout << "Database is running.\n";
}