#include "History.h"

void History::save(const std::vector<std::string>& state) {
    undo_stack.push(state);
    while (!redo_stack.empty()) redo_stack.pop();
}

bool History::can_undo() const {
    return !undo_stack.empty();
}

bool History::can_redo() const {
    return !redo_stack.empty();
}

std::vector<std::string> History::undo(std::vector<std::string>& current) {
    if (can_undo()) {
        redo_stack.push(current);
        auto previous = undo_stack.top();
        undo_stack.pop();
        return previous;
    }
    return current;
}

std::vector<std::string> History::redo(std::vector<std::string>& current) {
    if (can_redo()) {
        undo_stack.push(current);
        auto next = redo_stack.top();
        redo_stack.pop();
        return next;
    }
    return current;
}
