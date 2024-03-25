#include "global.h"

namespace global {
    void logAndThrowException(const std::string &error) {
        std::cerr << error << std::endl;
        throw std::runtime_error(error);
    }

    void assertf(bool cond, const std::string &error) {
        if (!cond) {
            logAndThrowException(error);
        }
    }
} // nemsapce global
