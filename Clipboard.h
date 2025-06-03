#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include "Constants.h"

class Clipboard {
private:
    char buffer[CLIPBOARD_MAX];

public:
    Clipboard();
    void copy(const char* text, int length);
    const char* paste() const;
    bool is_empty() const;
};

#endif
