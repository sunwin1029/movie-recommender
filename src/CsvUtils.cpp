#include "CsvUtils.h"

#include <stdexcept>

namespace CsvUtils {
std::vector<std::string> parseCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;

    for(size_t i = 0; i < line.size(); i++) {
        char c = line[i];

        if(c == '"') {
            if(inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                i++;
            } else {
                inQuotes = !inQuotes;
            }
        } else if(c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }

    if(inQuotes) {
        throw std::invalid_argument("CSV 따옴표 닫힘 누락");
    }

    fields.push_back(field);
    return fields;
}

std::string escapeCsvField(const std::string& value) {
    bool needQuotes = value.find(',') != std::string::npos ||
                      value.find('"') != std::string::npos ||
                      value.find('\n') != std::string::npos ||
                      value.find('\r') != std::string::npos;

    if(!needQuotes) {
        return value;
    }

    std::string escaped = "\"";
    for(char c : value) {
        if(c == '"') {
            escaped += "\"\"";
        } else {
            escaped += c;
        }
    }
    escaped += "\"";

    return escaped;
}

std::string quoteCsvField(const std::string& value) {
    std::string quoted = "\"";
    for(char c : value) {
        if(c == '"') {
            quoted += "\"\"";
        } else {
            quoted += c;
        }
    }
    quoted += "\"";

    return quoted;
}
}
