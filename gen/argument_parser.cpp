#include "argument_parser.h"

namespace {
    template<typename T>
    std::optional<std::string> toOptionalString(const std::optional<T> &value) {
        std::optional<std::string> valueString;
        if (value.has_value()) {
            valueString = std::to_string(value.value());
        }
        return valueString;
    }

    // Checks whether string looks like 3e5
    std::optional<long long> tryGetDoubleToLong(std::string value) {
        bool negative = (!value.empty() && value[0] == '-');
        if (negative) {
            value = value.substr(1);
        }

        size_t splitPosition = value.find('e');
        if (splitPosition == std::string::npos || splitPosition == 0 || splitPosition == value.size() - 1 || splitPosition > 19) {
            return std::nullopt;
        }

        size_t floatingPointPosition = value.find(".");
        if (floatingPointPosition != std::string::npos && floatingPointPosition > splitPosition) {
            return std::nullopt;
        }

        for (int i = 0; i < int(value.size()); i++) {
            if (i != int(splitPosition) && i != int(floatingPointPosition) && !std::isdigit(value[i])) {
                return std::nullopt;
            }
        }

        long long result = 0;
        for (int i = 0; i < int(splitPosition); i++) {
            if (i != int(floatingPointPosition)) {
                result = result * 10 + (value[i] - '0');
            }
        }

        long long power = std::stoll(value.substr(splitPosition + 1));
        if (floatingPointPosition != std::string::npos) {
            power -= splitPosition - floatingPointPosition - 1;
        }
        if (power < 0) {
            return std::nullopt;
        }

        for (int i = 0; i < power; i++) {
            if (result > std::numeric_limits<long long>::max() / 10) {
                return std::nullopt;
            }
            result *= 10;
        }
        return negative ? -result : result;
    }
} // namespace

ArgumentParser::ArgumentParser() {}

ArgumentParser::ArgumentParser(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        std::string preset = argv[i];
        size_t splitPosition = preset.find("=");
        if (splitPosition != std::string::npos) {
            parameters_[preset.substr(0, splitPosition)] = preset.substr(splitPosition + 1);
        } else {
            flags_.emplace(std::move(preset));
        }
    }
}

bool ArgumentParser::hasFlag(const std::string &flagName) const {
    return flags_.count(flagName) != 0;
}

bool ArgumentParser::hasParameter(const std::string &parameterName) const {
    return parameters_.count(parameterName) != 0;
}

std::string ArgumentParser::getString(const std::string &parameterName, std::optional<std::string> defaultValue) const {
    auto it = parameters_.find(parameterName);
    if (!defaultValue.has_value() && it == parameters_.end()) {
        global::logAndThrowException("Incorrect parameter: " + parameterName);
    }
    return it == parameters_.end() ? defaultValue.value() : it->second;
}

int ArgumentParser::getInt(const std::string &parameterName, std::optional<int> defaultValue) const {
    std::string value = getString(parameterName, toOptionalString(defaultValue));
    if (auto result = tryGetDoubleToLong(value); result.has_value()) {
        if (std::numeric_limits<int>::min() <= result.value() && result.value() <= std::numeric_limits<int>::max()) {
            return result.value();
        }
    }

    try {
        size_t auxPos{};
        int parsedInt = std::stoi(value, &auxPos);
        global::assertf(auxPos == value.size(), "Did not fully parsed int for parameter: " + parameterName + ", value: " + value);
        return parsedInt;
    } catch (const std::invalid_argument &ex) {
        global::logAndThrowException("Did not parse int for parameter: " + parameterName + ", value: " + value);
    } catch (std::out_of_range const& ex) {
        global::logAndThrowException("Overflow happened while parsing int for parameter: " + parameterName + ", value: " + value);
    }
    return 0;
}

long long ArgumentParser::getLong(const std::string &parameterName, std::optional<long long> defaultValue) const {
    std::string value = getString(parameterName, toOptionalString(defaultValue));
    if (auto result = tryGetDoubleToLong(value); result.has_value()) {
        return result.value();
    }

    try {
        size_t auxPos{};
        long long parsedLong = std::stoll(value, &auxPos);
        global::assertf(auxPos == value.size(), "Did not fully parsed long long for parameter: " + parameterName + ", value: " + value);
        return parsedLong;
    } catch (const std::invalid_argument &ex) {
        global::logAndThrowException("Did not parse long long for parameter: " + parameterName + ", value: " + value);
    } catch (std::out_of_range const& ex) {
        global::logAndThrowException("Overflow happened while parsing long long for parameter: " + parameterName + ", value: " + value);
    }
    return 0ll;
}

double ArgumentParser::getDouble(const std::string &parameterName, std::optional<double> defaultValue) const {
    std::string value = getString(parameterName, toOptionalString(defaultValue));
    try {
        size_t auxPos{};
        double parsedDouble = std::stod(value, &auxPos);
        global::assertf(auxPos == value.size(), "Did not fully parsed double for parameter: " + parameterName + ", value: " + value);
        return parsedDouble;
    } catch (const std::invalid_argument &ex) {
        global::logAndThrowException("Did not parse double for parameter: " + parameterName + ", value: " + value);
    } catch (std::out_of_range const& ex) {
        global::logAndThrowException("Overflow happened while parsing double for parameter: " + parameterName + ", value: " + value);
    }
    return 0.;
}
