#pragma once

#include <string>
#include "pager.h"

class Database
{
public:
    explicit Database(const std::string& filename);
    ~Database();

    void run();

private:
    Pager pager;
};