#pragma once

#include <fstream>
#include <string>

#include "constants.h"

class Pager
{
public:
    explicit Pager(const std::string& filename);
    ~Pager();

private:
    std::fstream file;
    std::size_t file_length;
    std::size_t num_pages;

    char* pages[TABLE_MAX_PAGES];
};