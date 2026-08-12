#include "database.h"
#include <iostream>

int main()
{
    Database db("database.db");
    auto* page0 = static_cast<char*>(db.getPager().getPage(0));
    auto* again = static_cast<char*>(db.getPager().getPage(1));

std::cout << static_cast<void*>(page0) << '\n';
std::cout << static_cast<void*>(again) << '\n';

    db.run();

    return 0;
}