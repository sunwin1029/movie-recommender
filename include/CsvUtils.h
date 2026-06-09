#pragma once

#include <string>
#include <vector>

namespace CsvUtils {
std::vector<std::string> parseCsvLine(const std::string& line);
std::string escapeCsvField(const std::string& value);
std::string quoteCsvField(const std::string& value);
}
