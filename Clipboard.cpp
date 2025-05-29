#include "Clipboard.h"

void Clipboard::copy(const std::string& text) {
    buffer = text;
}

const std::string& Clipboard::paste() const {
    return buffer;
}

bool Clipboard::is_empty() const {
    return buffer.empty();
}
