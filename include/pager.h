#pragma once

#include <fstream>
#include <string>
#include <cstdint>

#include "constants.h"

class Pager
{
public:
    explicit Pager(const std::string& filename);
    ~Pager();
    void* getPage(uint32_t page_number);
    void flushPage(uint32_t page_number);
    void markDirty(uint32_t page_number);

private:
    std::fstream file;
    std::size_t file_length;
    std::size_t num_pages;

    char* pages[TABLE_MAX_PAGES];
    bool dirty[TABLE_MAX_PAGES];
};