#pragma once

#include <exception>
#include <iostream>
#include <string>

namespace global {
    // Throws std::runtime_error
    void logAndThrowException(const std::string &error);

    // Throws std::runtime_error if !cond
    void assertf(bool cond, const std::string &error);
} // nemsapce global
