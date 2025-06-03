#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "Constants.h"
#include "Clipboard.h"
#include "History.h"

class TextEditor {
private:
    char* lines[MAX_LINES];
    int line_count;
    int cursor_line;
    int cursor_index;
    Clipboard clipboard;
    History history;

public:
    TextEditor();
    ~TextEditor();

    void print_assist() const;
    void print_text() const;

    void append_text(const char* text);
    void new_line();
    void insert_text(int line, int index, const char* text);
    void delete_range(int line, int index, int count);
    void search_text(const char* query) const;

    void save_to_file(const char* filename) const;
    void load_from_file(const char* filename);

    void copy(int line, int index, int count);
    void cut(int line, int index, int count);
    void paste(int line, int index);

    void set_cursor(int line, int index);
    void insert_with_replacement(const char* text);

    void undo();
    void redo();
};

#endif // TEXTEDITOR_H
