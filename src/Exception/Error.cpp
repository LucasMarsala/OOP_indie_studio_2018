/*
** EPITECH PROJECT, 2019
** nano
** File description:
** error
*/

#include "Error.hpp"

Error::Error(std::string const &message) : _message(message)
{
}

const char *Error::what(void) const noexcept
{
    return _message.c_str();
}
