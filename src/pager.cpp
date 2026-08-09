#include "pager.h"

#include <iostream>

Pager::Pager(const std::string& filename)
    : file_length(0),
      num_pages(0)
{
    file.open(
        filename,
        std::ios::in |
        std::ios::out |
        std::ios::binary
    );

    if (!file.is_open())
    {
        std::cout << "Database file not found. Creating...\n";

        std::ofstream creator(filename, std::ios::binary);
        creator.close();

        file.open(
            filename,
            std::ios::in |
            std::ios::out |
            std::ios::binary
        );
    }

    if (file.is_open())
    {
        std::cout << "Database file opened successfully.\n";
    }

    file.seekg(0, std::ios::end);
    file_length = file.tellg();
    file.seekg(0, std::ios::beg);
    num_pages = file_length / PAGE_SIZE;
    std::cout << "File length: " << file_length << " bytes\n";
    std::cout << "Number of pages: " << num_pages << "\n";

    for (std::size_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        pages[i] = nullptr;
    }

}

Pager::~Pager()
{
    if (file.is_open())
    {
        file.close();
    }

    std::cout << "Pager closed file.\n";
}