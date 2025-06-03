// TextEditor.cpp
#include "TextEditor.h"
#include "Constants.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

TextEditor::TextEditor() : line_count(0), cursor_line(0), cursor_index(0) {
    for (int i = 0; i < MAX_LINES; ++i) lines[i] = nullptr;
}

TextEditor::~TextEditor() {
    for (int i = 0; i < line_count; ++i) free(lines[i]);
}

void TextEditor::print_assist() const {
    printf("\nCommands:\n");
    printf("1 - Append text\n2 - New line\n3 - Save\n4 - Load\n5 - Print\n6 - Insert\n7 - Search\n8 - Delete\n");
    printf("9 - Cut\n10 - Copy\n11 - Paste\n12 - Undo\n13 - Redo\n14 - Set cursor\n15 - Insert with replacement\n0 - Exit\n");
}

void TextEditor::print_text() const {
    for (int i = 0; i < line_count; ++i) {
        printf("%s\n", lines[i]);
    }
}

void TextEditor::append_text(const char* text) {
    if (line_count == 0) new_line();
    history.save(lines, line_count);
    strcat(lines[line_count - 1], text);
}

void TextEditor::new_line() {
    if (line_count >= MAX_LINES) return;
    lines[line_count] = (char*)malloc(MAX_LINE_LENGTH);
    lines[line_count][0] = '\0';
    line_count++;
}

void TextEditor::insert_text(int line, int index, const char* text) {
    if (line < 0 || line >= line_count) return;
    history.save(lines, line_count);
    char* old_line = lines[line];
    char new_line[MAX_LINE_LENGTH];
    strncpy(new_line, old_line, index);
    new_line[index] = '\0';
    strcat(new_line, text);
    strcat(new_line, old_line + index);
    strcpy(lines[line], new_line);
}

void TextEditor::delete_range(int line, int index, int count) {
    if (line < 0 || line >= line_count) return;
    history.save(lines, line_count);
    int len = strlen(lines[line]);
    if (index < 0 || index >= len) return;
    if (index + count > len) count = len - index;
    memmove(&lines[line][index], &lines[line][index + count], len - index - count + 1);
}

void TextEditor::search_text(const char* query) const {
    for (int i = 0; i < line_count; ++i) {
        const char* pos = lines[i];
        while ((pos = strstr(pos, query)) != nullptr) {
            int offset = pos - lines[i];
            printf("Found at line %d, index %d\n", i, offset);
            pos++;
        }
    }
}

void TextEditor::save_to_file(const char* filename) const {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    for (int i = 0; i < line_count; ++i) {
        fputs(lines[i], file);
        fputc('\n', file);
    }
    fclose(file);
}

void TextEditor::load_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    for (int i = 0; i < line_count; ++i) free(lines[i]);
    line_count = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file) && line_count < MAX_LINES) {
        buffer[strcspn(buffer, "\n")] = '\0';
        lines[line_count] = (char*)malloc(MAX_LINE_LENGTH);
        strcpy(lines[line_count], buffer);
        line_count++;
    }
    fclose(file);
}

void TextEditor::copy(int line, int index, int count) {
    if (line < 0 || line >= line_count) return;
    clipboard.copy(&lines[line][index], count);
}

void TextEditor::cut(int line, int index, int count) {
    copy(line, index, count);
    delete_range(line, index, count);
}

void TextEditor::paste(int line, int index) {
    insert_text(line, index, clipboard.paste());
}

void TextEditor::set_cursor(int line, int index) {
    if (line >= 0 && line < line_count) cursor_line = line;
    if (index >= 0 && index < MAX_LINE_LENGTH) cursor_index = index;
}

void TextEditor::insert_with_replacement(const char* text) {
    if (cursor_line < 0 || cursor_line >= line_count) return;
    history.save(lines, line_count);
    int len = strlen(text);
    int original_len = strlen(lines[cursor_line]);
    if (cursor_index + len >= MAX_LINE_LENGTH) return;
    for (int i = 0; i < len; ++i) {
        lines[cursor_line][cursor_index + i] = text[i];
    }
    if (cursor_index + len > original_len)
        lines[cursor_line][cursor_index + len] = '\0';
}

void TextEditor::undo() {
    char** state = history.undo(lines, line_count);
    if (state) {
        for (int i = 0; i < line_count; ++i) free(lines[i]);
        line_count = 0;
        for (int i = 0; i < MAX_LINES && state[i]; ++i) {
            lines[i] = (char*)malloc(MAX_LINE_LENGTH);
            strcpy(lines[i], state[i]);
            line_count++;
        }
        free(state);
    }
}

void TextEditor::redo() {
    char** state = history.redo(lines, line_count);
    if (state) {
        for (int i = 0; i < line_count; ++i) free(lines[i]);
        line_count = 0;
        for (int i = 0; i < MAX_LINES && state[i]; ++i) {
            lines[i] = (char*)malloc(MAX_LINE_LENGTH);
            strcpy(lines[i], state[i]);
            line_count++;
        }
        free(state);
    }
}