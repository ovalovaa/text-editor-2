#pragma once
#include "Clipboard.h"
#include "History.h"
#include <vector>
#include <string>

class TextEditor {
private:
    std::vector<std::string> lines;
    Clipboard clipboard;
    History history;
    int cursor_line = 0;
    int cursor_index = 0;

public:
    void set_cursor(int line, int index);
    void append_text(const std::string& text);
    void new_line();
    void insert_text(const std::string& text);
    void insert_replacement(const std::string& text);
    void delete_text(int count);
    void cut(int count);
    void copy(int count);
    void paste();
    void undo();
    void redo();
    void save_to_file(const std::string& filename) const;
    void load_from_file(const std::string& filename);
    void print_text() const;
    void search_text(const std::string& query) const;

};
