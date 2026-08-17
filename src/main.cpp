#include "database.h"
#include "row.h"
#include <iostream>
#include <cstring>

int main()
{
    Database db("database.db");
    
    char* page0 = static_cast<char*>(db.getPager().getPage(0));
    Row row{};
    row.id = 1;

    std::strcpy(row.username, "himangi");
    std::strcpy(row.email, "himangi@example.com");

    serializeRow(row, page0);

    db.getPager().markDirty(0);

    std::cout << "Row written.\n";
    deserializeRow(page0, row);

    std::cout << "ID: " << row.id << '\n';
    std::cout << "Username: " << row.username << '\n';
    std::cout << "Email: " << row.email << '\n';

    return 0;
}