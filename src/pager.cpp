#include "pager.h"
#include <cstdint>
#include <iostream>
#include <stdexcept>

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
            dirty[i] = false;  
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

void Pager::flushPage(uint32_t page_number)
    {
        if (page_number >= TABLE_MAX_PAGES)
        {
            throw std::out_of_range("Page number exceeds maximum");
        }

        if (pages[page_number] == nullptr)
        {
            throw std::runtime_error("Cannot flush a page that is not in cache");
        }

        file.clear();

        file.seekp(
            static_cast<std::streamoff>(page_number) * PAGE_SIZE,
            std::ios::beg
        );

        file.write(pages[page_number], PAGE_SIZE);
        file.flush();

        if (!file)
        {
            throw std::runtime_error("Failed to flush page to disk");
        }

        std::streamoff end_position =
            static_cast<std::streamoff>(page_number + 1) * PAGE_SIZE;

        if (end_position > file_length)
        {
            file_length = end_position;
        }
    }

void Pager::markDirty(uint32_t page_number)
    {
        if (page_number >= TABLE_MAX_PAGES)
        {
            throw std::out_of_range("Page number exceeds maximum");
        }

        if (pages[page_number] == nullptr)
        {
            throw std::runtime_error("Cannot mark uncached page as dirty");
        }

        dirty[page_number] = true;
    }

Pager::~Pager()
    {
       for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
        {
            if (pages[i] != nullptr)
            {
                if (dirty[i])
                {
                    flushPage(i);
                }

                delete[] pages[i];
                pages[i] = nullptr;
            }
        }

        file.close();
    }