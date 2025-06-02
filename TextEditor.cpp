#include "TextEditor.h"
#include <cstdio>

TextEditor::TextEditor() {
    text[0] = '\0';
    text_length = 0;
    clipboard[0] = '\0';
    undo_top = 0;
    redo_top = 0;
}

void TextEditor::copy_state(char dest[MAX_TEXT_LEN], const char src[MAX_TEXT_LEN]) {
    int i = 0;
    while ((dest[i] = src[i]) != '\0') i++;
}

void TextEditor::push_undo() {
    if (undo_top < MAX_HISTORY) {
        copy_state(undo_stack[undo_top++], text);
    }
}

void TextEditor::push_redo() {
    if (redo_top < MAX_HISTORY) {
        copy_state(redo_stack[redo_top++], text);
    }
}

void TextEditor::restore_from(char dest[MAX_TEXT_LEN]) {
    copy_state(text, dest);
    int i = 0;
    while (text[i] != '\0') i++;
    text_length = i;
}

void TextEditor::print() {
    printf("%s\n", text);
}

void TextEditor::insert(int index, const char* str) {
    push_undo();
    redo_top = 0;

    int len = 0;
    while (str[len] != '\0') len++;

    if (index < 0 || index > text_length || text_length + len >= MAX_TEXT_LEN) return;

    for (int i = text_length - 1; i >= index; i--) {
        text[i + len] = text[i];
    }

    for (int i = 0; i < len; i++) {
        text[index + i] = str[i];
    }

    text_length += len;
    text[text_length] = '\0';
}

void TextEditor::delete_range(int index, int count) {
    push_undo();
    redo_top = 0;

    if (index < 0 || index >= text_length) return;
    if (index + count > text_length) count = text_length - index;

    for (int i = index + count; i <= text_length; i++) {
        text[i - count] = text[i];
    }

    text_length -= count;
}

void TextEditor::copy(int index, int count) {
    if (index < 0 || index >= text_length || count <= 0) return;

    if (index + count > text_length) count = text_length - index;

    int i;
    for (i = 0; i < count && i < MAX_CLIPBOARD_LEN - 1; i++) {
        clipboard[i] = text[index + i];
    }
    clipboard[i] = '\0';
}

void TextEditor::cut(int index, int count) {
    copy(index, count);
    delete_range(index, count);
}

void TextEditor::paste(int index) {
    insert(index, clipboard);
}

void TextEditor::undo() {
    if (undo_top == 0) return;
    push_redo();
    restore_from(undo_stack[--undo_top]);
}

void TextEditor::redo() {
    if (redo_top == 0) return;
    push_undo();
    restore_from(redo_stack[--redo_top]);
}
