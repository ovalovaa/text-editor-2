#include <iostream>
#include <string>
#include "TextEditor.h"

int main() {
    TextEditor editor;
    int command;
    std::string buffer;

    while (true) {
        editor.print_assist();
        std::cout << "> Choose the command: ";
        std::cin >> command;
        std::cin.ignore();

        if (command == 0) break;

        switch (command) {
            case 1: {
                std::cout << "Enter text to append: ";
                std::getline(std::cin, buffer);
                editor.append_text(buffer.c_str());
                break;
            }
            case 2: {
                editor.new_line();
                std::cout << "New line is started\n";
                break;
            }
            case 3: {
                std::cout << "Enter the file name for saving: ";
                std::getline(std::cin, buffer);
                editor.save_to_file(buffer.c_str());
                std::cout << "Text has been saved successfully\n";
                break;
            }
            case 4: {
                std::cout << "Enter the file name for loading: ";
                std::getline(std::cin, buffer);
                editor.load_from_file(buffer.c_str());
                std::cout << "Text has been loaded successfully\n";
                break;
            }
            case 5: {
                editor.print_text();
                break;
            }
            case 6: {
                int line, index;
                std::cout << "Choose line and index: ";
                std::cin >> line >> index;
                std::cin.ignore();
                std::cout << "Enter text to insert: ";
                std::getline(std::cin, buffer);
                editor.insert_text(line, index, buffer.c_str());
                break;
            }
            case 7: {
                std::cout << "Enter text to search: ";
                std::getline(std::cin, buffer);
                editor.search_text(buffer.c_str());
                break;
            }
            case 8: {
                int line, index, count;
                std::cout << "Enter line, index, and count to delete: ";
                std::cin >> line >> index >> count;
                std::cin.ignore();
                editor.delete_range(line, index, count);
                break;
            }
            case 9: {
                int line, index, count;
                std::cout << "Enter line, index, and count to cut: ";
                std::cin >> line >> index >> count;
                std::cin.ignore();
                editor.cut(line, index, count);
                std::cout << "Cut completed.\n";
                break;
            }
            case 10: {
                int line, index;
                std::cout << "Enter line and index to copy: ";
                std::cin >> line >> index;
                std::cin.ignore();
                int count;
                std::cout << "Enter number of characters to copy: ";
                std::cin >> count;
                std::cin.ignore();
                editor.copy(line, index, count);
                std::cout << "Copied successfully.\n";
                break;
            }
            case 11: {
                int line, index;
                std::cout << "Enter line and index to paste: ";
                std::cin >> line >> index;
                std::cin.ignore();
                editor.paste(line, index);
                std::cout << "Pasted successfully.\n";
                break;
            }
            case 12: {
                editor.undo();
                std::cout << "Undo completed.\n";
                break;
            }
            case 13: {
                editor.redo();
                std::cout << "Redo completed.\n";
                break;
            }
            case 14: {
                int line, index;
                std::cout << "Enter line and index to set cursor: ";
                std::cin >> line >> index;
                std::cin.ignore();
                editor.set_cursor(line, index);
                std::cout << "Cursor set successfully.\n";
                break;
            }
            case 15: {
                std::cout << "Enter text to insert with replacement: ";
                std::getline(std::cin, buffer);
                editor.insert_with_replacement(buffer.c_str());
                std::cout << "Inserted with replacement.\n";
                break;
            }
            case 16: {
                std::cout << "Cursor is at line " << editor.get_cursor_line()
                          << ", index " << editor.get_cursor_index() << std::endl;
                break;
            }

            default:
                std::cout << "The command is not implemented\n";
        }
    }

    return 0;
}
