#include "Clipboard.h"
#include <cstring>

Clipboard::Clipboard() {
    buffer[0] = '\0';
}

void Clipboard::copy(const char* text, int length) {
    if (length >= CLIPBOARD_MAX) length = CLIPBOARD_MAX - 1;
    strncpy(buffer, text, length);
    buffer[length] = '\0';
}

const char* Clipboard::paste() const {
    return buffer;
}

bool Clipboard::is_empty() const {
    return buffer[0] == '\0';
}