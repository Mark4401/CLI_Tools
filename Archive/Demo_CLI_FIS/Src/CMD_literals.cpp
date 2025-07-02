#include <algorithm>
#include <iomanip>
#include <iostream>   // Needed for std::cerr, std::ostream
#include <sstream>    // Needed for std::stringstream
#include <CMD_literals.h>

CMD_literals::CMD_literals(std::string description)
    : mDescription(std::move(description)) {
}

void CMD_literals::addArgument(std::vector<std::string> const& flags,
    Value const& value,
    std::string const& help) {
    mArguments.emplace_back(Argument{ flags, value, help });
}

void CMD_literals::printHelp(std::ostream& os) const {
    // Print the general description.
    os << mDescription << std::endl;

    // Find the argument with the longest combined flag length to align help text.
    uint32_t maxFlagLength = 0;
    for (auto const& argument : mArguments) {
        uint32_t flagLength = 0;
        for (auto const& flag : argument.mFlags) {
            flagLength += static_cast<uint32_t>(flag.size()) + 2; // include ", "
        }
        maxFlagLength = std::max(maxFlagLength, flagLength);
    }

    // Print each argument.
    for (auto const& argument : mArguments) {
        std::string flags;
        for (auto const& flag : argument.mFlags) {
            flags += flag + ", ";
        }

        // Remove the last ", "
        if (flags.size() >= 2) {
            flags.erase(flags.end() - 2, flags.end());
        }

        std::stringstream sstr;
        sstr << std::left << std::setw(maxFlagLength) << flags;

        size_t pos = 0;
        size_t lineWidth = static_cast<size_t>(sstr.str().length());
        std::string helpText = argument.mHelp;

        while (pos < helpText.size()) {
            size_t next = helpText.find(' ', pos + 1);
            if (next == std::string::npos) next = helpText.size();

            std::string word = helpText.substr(pos, next - pos);
            if (lineWidth + word.length() > 80) {
                os << sstr.str() << std::endl;
                sstr.str("");
                sstr.clear();
                sstr << std::left << std::setw(maxFlagLength) << " ";
                lineWidth = maxFlagLength;
            }
            sstr << word << " ";
            lineWidth += word.length() + 1;
            pos = next + 1;
        }

        os << sstr.str() << std::endl;
    }
}

void CMD_literals::parse(int argc, char* argv[]) const {
    int i = 1; // skip program name
    while (i < argc) {
        std::string flag(argv[i]);
        std::string value;
        bool valueIsSeparate = false;

        // Check if value is part of flag using '='
        size_t equalPos = flag.find('=');
        if (equalPos != std::string::npos) {
            value = flag.substr(equalPos + 1);
            flag = flag.substr(0, equalPos);
        }
        else if (i + 1 < argc) {
            value = argv[i + 1];
            valueIsSeparate = true;
        }

        bool foundArgument = false;

        for (auto const& argument : mArguments) {
            if (std::find(argument.mFlags.begin(), argument.mFlags.end(), flag)
                != argument.mFlags.end()) {
                foundArgument = true;

                if (std::holds_alternative<bool*>(argument.mValue)) {
                    if (!value.empty() && value != "true" && value != "false") {
                        valueIsSeparate = false; // Not a valid boolean, rewind
                    }
                    *std::get<bool*>(argument.mValue) = (value != "false");
                }
                else if (value.empty()) {
                    throw std::runtime_error(
                        "Failed to parse command line arguments: "
                        "Missing value for argument \"" + flag + "\"!");
                }
                else if (std::holds_alternative<std::string*>(argument.mValue)) {
                    *std::get<std::string*>(argument.mValue) = value;
                }
                else {
                    std::visit([&value](auto&& arg) {
                        std::stringstream sstr(value);
                        sstr >> *arg;
                        }, argument.mValue);
                }

                break;
            }
        }

        if (!foundArgument) {
            std::cerr << "Ignoring unknown command line argument \"" << flag << "\"." << std::endl;
        }

        ++i;
        if (foundArgument && valueIsSeparate) {
            ++i;
        }
    }
}
