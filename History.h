#ifndef HISTORY_H
#define HISTORY_H
#include "Constants.h"

class History {
private:
    char** undo_stack[MAX_HISTORY];
    int undo_top;

    char** redo_stack[MAX_HISTORY];
    int redo_top;

public:
    History();
    ~History();

    void save(char* lines[], int line_count);
    bool can_undo() const;
    bool can_redo() const;
    char** undo(char* lines[], int& line_count);
    char** redo(char* lines[], int& line_count);

private:
    char** clone_state(char* lines[], int line_count);
    void free_state(char** state);
};

#endif