#pragma once
#include <string>

class Clipboard {
private:
    std::string buffer;

public:
    void copy(const std::string& text);
    const std::string& paste() const;
    bool is_empty() const;
};
