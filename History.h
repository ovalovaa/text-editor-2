#pragma once
#include <stack>
#include <vector>
#include <string>

class History {
private:
    std::stack<std::vector<std::string>> undo_stack;
    std::stack<std::vector<std::string>> redo_stack;

public:
    void save(const std::vector<std::string>& state);
    bool can_undo() const;
    bool can_redo() const;
    std::vector<std::string> undo(std::vector<std::string>& current);
    std::vector<std::string> redo(std::vector<std::string>& current);
};
