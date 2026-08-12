#include "database.h"
#include <iostream>

int main()
{
    Database db("database.db");
    
    char* page0 = static_cast<char*>(db.getPager().getPage(0));


    db.getPager().markDirty(0);

    std::cout << page0[0] << page0[1] << '\n';

    db.run();

    return 0;
}