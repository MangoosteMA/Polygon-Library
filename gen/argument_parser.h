// TODO: parse intervals format like n=[10,100]

#pragma once

#include "global/global.h"

#include <exception>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <string>

/*
 * Simple argument parser. For exmple:
   "gen n=10 m=1e5 k=2.5e5 shuffle random"
    will be parsed as
    1. Parameters: {"n": "10", "m": "1e5", k: "2.5e5"}
    2. Flags: {"shuffle", "random"}
 * Throws and log an exception in case something went wrong.
 */

class ArgumentParser {
public:
    ArgumentParser();
    ArgumentParser(int argc, char* argv[]);

    bool hasFlag(const std::string &flagName) const;
    bool hasParameter(const std::string &parameterName) const;

    std::string getString(const std::string &parameterName, std::optional<std::string> defaultValue = std::nullopt) const;
    int getInt(const std::string &parameterName, std::optional<int> defaultValue = std::nullopt) const;
    long long getLong(const std::string &parameterName, std::optional<long long> defaultValue = std::nullopt) const;
    double getDouble(const std::string &parameterName, std::optional<double> defaultValue = std::nullopt) const;

private:
    std::map<std::string, std::string> parameters_;
    std::set<std::string> flags_;
};
