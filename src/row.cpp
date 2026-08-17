#include "row.h"

#include <cstring>

void serializeRow(const Row& source, char* destination)
{
    std::memcpy(destination,
                &source.id,
                ID_SIZE);

    std::memcpy(destination + ID_SIZE,
                source.username,
                USERNAME_SIZE);

    std::memcpy(destination + ID_SIZE + USERNAME_SIZE,
                source.email,
                EMAIL_SIZE);
}

void deserializeRow(const char* source, Row& destination)
{
    std::memcpy(&destination.id,
                source,
                ID_SIZE);

    std::memcpy(destination.username,
                source + ID_SIZE,
                USERNAME_SIZE);

    std::memcpy(destination.email,
                source + ID_SIZE + USERNAME_SIZE,
                EMAIL_SIZE);
}