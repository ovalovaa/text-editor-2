#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

const int MAX_TEXT_LEN = 1000;
const int MAX_CLIPBOARD_LEN = 256;
const int MAX_HISTORY = 3;

class TextEditor {
private:
    char text[MAX_TEXT_LEN];
    int text_length;

    char clipboard[MAX_CLIPBOARD_LEN];

    char undo_stack[MAX_HISTORY][MAX_TEXT_LEN];
    int undo_top;

    char redo_stack[MAX_HISTORY][MAX_TEXT_LEN];
    int redo_top;

    void copy_state(char dest[MAX_TEXT_LEN], const char src[MAX_TEXT_LEN]);
    void push_undo();
    void push_redo();
    void restore_from(char dest[MAX_TEXT_LEN]);

public:
    TextEditor();

    void print();
    void insert(int index, const char* str);
    void delete_range(int index, int count);
    void cut(int index, int count);
    void copy(int index, int count);
    void paste(int index);
    void undo();
    void redo();
};

#endif
