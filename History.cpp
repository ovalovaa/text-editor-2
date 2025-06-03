#include "History.h"
#include <cstdlib>
#include <cstring>

History::History() : undo_top(0), redo_top(0) {
    for (int i = 0; i < MAX_HISTORY; ++i) {
        undo_stack[i] = nullptr;
        redo_stack[i] = nullptr;
    }
}

History::~History() {
    for (int i = 0; i < MAX_HISTORY; ++i) {
        free_state(undo_stack[i]);
        free_state(redo_stack[i]);
    }
}

char** History::clone_state(char* lines[], int line_count) {
    char** clone = (char**)malloc(sizeof(char*) * MAX_LINES);
    for (int i = 0; i < line_count; ++i) {
        clone[i] = (char*)malloc(MAX_LINE_LENGTH);
        strcpy(clone[i], lines[i]);
    }
    for (int i = line_count; i < MAX_LINES; ++i) clone[i] = nullptr;
    return clone;
}

void History::free_state(char** state) {
    if (!state) return;
    for (int i = 0; i < MAX_LINES && state[i]; ++i) {
        free(state[i]);
    }
    free(state);
}

void History::save(char* lines[], int line_count) {
    if (undo_top < MAX_HISTORY) {
        undo_stack[undo_top++] = clone_state(lines, line_count);
        for (int i = 0; i < redo_top; ++i) {
            free_state(redo_stack[i]);
            redo_stack[i] = nullptr;
        }
        redo_top = 0;
    }
}

bool History::can_undo() const {
    return undo_top > 0;
}

bool History::can_redo() const {
    return redo_top > 0;
}

char** History::undo(char* lines[], int& line_count) {
    if (!can_undo()) return nullptr;
    redo_stack[redo_top++] = clone_state(lines, line_count);
    return undo_stack[--undo_top];
}

char** History::redo(char* lines[], int& line_count) {
    if (!can_redo()) return nullptr;
    undo_stack[undo_top++] = clone_state(lines, line_count);
    return redo_stack[--redo_top];
}
