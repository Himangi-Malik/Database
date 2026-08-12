#pragma once

#include <string>
#include "pager.h"

class Database
{
public:
    explicit Database(const std::string& filename);
    Pager& getPager();
    ~Database();

    void run();

private:
    Pager pager;
};