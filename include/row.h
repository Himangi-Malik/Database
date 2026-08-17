#pragma once
#include "constants.h"
#include <cstdint>

constexpr uint32_t ID_SIZE = sizeof(uint32_t);
constexpr uint32_t USERNAME_SIZE = 32;
constexpr uint32_t EMAIL_SIZE = 64;

constexpr uint32_t ROW_SIZE =
    ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

constexpr uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;

struct Row
{
    uint32_t id;
    char username[USERNAME_SIZE];
    char email[EMAIL_SIZE];
};

void serializeRow(const Row& source, char* destination);
void deserializeRow(const char* source, Row& destination);