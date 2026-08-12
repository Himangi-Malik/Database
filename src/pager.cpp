#include "pager.h"
#include <cstdint>
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


void* Pager::getPage(uint32_t page_number)
    {
        if (page_number >= TABLE_MAX_PAGES)
        {
            throw std::out_of_range("Page number exceeds maximum");
        }

        if (pages[page_number] != nullptr)
        {
            return pages[page_number];
        }

        pages[page_number] = new char[PAGE_SIZE]();

        if (page_number < num_pages)
        {
            file.seekg(static_cast<std::streamoff>(page_number) * PAGE_SIZE,
                    std::ios::beg);

            file.read(pages[page_number], PAGE_SIZE);
        }

        if (page_number >= num_pages)
        {
            num_pages = page_number + 1;
        }

        return pages[page_number];
    }


Pager::~Pager()
{
    for (char*& page : pages)
    {
        delete[] page;
        page = nullptr;
    }

    file.close();
}