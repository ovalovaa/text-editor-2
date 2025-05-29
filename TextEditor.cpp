#include "TextEditor.h"
#include <iostream>
#include <fstream>

void TextEditor::set_cursor(int line, int index) {
    if (line >= 0 && line < (int)lines.size() && index >= 0 && index <= (int)lines[line].size()) {
        cursor_line = line;
        cursor_index = index;
    } else {
        std::cout << "❌ Invalid cursor position: line " << line << ", index " << index << "\n";
    }
}

void TextEditor::append_text(const std::string& text) {
    if (lines.empty()) lines.emplace_back("");
    history.save(lines);
    lines.back() += text;
}

void TextEditor::new_line() {
    history.save(lines);
    lines.emplace_back("");
}

void TextEditor::insert_text(const std::string& text) {
    history.save(lines);
    lines[cursor_line].insert(cursor_index, text);
    cursor_index += text.length();
}

void TextEditor::insert_replacement(const std::string& text) {
    history.save(lines);
    lines[cursor_line].replace(cursor_index, text.length(), text);
    cursor_index += text.length();
}

void TextEditor::delete_text(int count) {
    history.save(lines);
    lines[cursor_line].erase(cursor_index, count);
}

void TextEditor::cut(int count) {
    history.save(lines);
    clipboard.copy(lines[cursor_line].substr(cursor_index, count));
    lines[cursor_line].erase(cursor_index, count);
}

void TextEditor::copy(int count) {
    clipboard.copy(lines[cursor_line].substr(cursor_index, count));
}

void TextEditor::paste() {
    history.save(lines);
    lines[cursor_line].insert(cursor_index, clipboard.paste());
    cursor_index += clipboard.paste().length();
}

void TextEditor::undo() {
    if (history.can_undo())
        lines = history.undo(lines);
}

void TextEditor::redo() {
    if (history.can_redo())
        lines = history.redo(lines);
}

void TextEditor::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& line : lines)
        file << line << '\n';
}

void TextEditor::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Error opening file: " << filename << "\n";
        return;
    }

    std::string buffer;
    lines.clear();

    while (std::getline(file, buffer)) {
        std::cout << "[DEBUG] Read line: \"" << buffer << "\"\n";
        lines.push_back(buffer);
    }

    std::cout << "✅ Text has been loaded successfully\n";
}

void TextEditor::print_text() const {
    for (const auto& line : lines)
        std::cout << line << '\n';
}
void TextEditor::search_text(const std::string& query) const {
    for (int i = 0; i < (int)lines.size(); ++i) {
        const std::string& line = lines[i];
        size_t pos = 0;
        while ((pos = line.find(query, pos)) != std::string::npos) {
            std::cout << "Text is present in this position: " << i << " " << pos << "\n";
            ++pos;
        }
    }
}

