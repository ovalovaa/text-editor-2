#include "TextEditor.h"
#include <iostream>
#include <string>

void print_assist() {
    std::cout << "\nCommands:\n";
    std::cout << "1 - Append text to the end\n";
    std::cout << "2 - Start new line\n";
    std::cout << "3 - Save text to file\n";
    std::cout << "4 - Load text from file\n";
    std::cout << "5 - Print current text\n";
    std::cout << "6 - Insert text by line and index\n";
    std::cout << "7 - Search text\n";
    std::cout << "8 - Undo\n";
    std::cout << "9 - Redo\n";
    std::cout << "10 - Cut text\n";
    std::cout << "11 - Copy text\n";
    std::cout << "12 - Paste text\n";
    std::cout << "13 - Replace text\n";
    std::cout << "14 - Set cursor position\n";
    std::cout << "0 - Exit\n";
}

int main() {
    TextEditor editor;
    int command;
    std::string input;

    while (true) {
        print_assist();
        std::cout << "> Choose the command: ";
        std::cin >> command;
        std::cin.ignore();

        if (command == 0) break;

        switch (command) {
            case 1:
                std::cout << "Enter text to append: ";
                std::getline(std::cin, input);
                editor.append_text(input);
                break;

            case 2:
                editor.new_line();
                std::cout << "New line is started\n";
                break;

            case 3:
                std::cout << "Enter the file name for saving: ";
                std::getline(std::cin, input);
                editor.save_to_file(input);
                std::cout << "Text has been saved successfully\n";
                break;

            case 4:
                std::cout << "Enter the file name for loading: ";
                std::getline(std::cin, input);
                editor.load_from_file(input);
                std::cout << "Text has been loaded successfully\n";
                break;

            case 5:
                editor.print_text();
                break;

            case 6: {
                int line, index;
                std::cout << "Choose line and index: ";
                std::cin >> line >> index;
                std::cin.ignore();
                std::cout << "Enter text to insert: ";
                std::getline(std::cin, input);
                editor.set_cursor(line, index);
                editor.insert_text(input);
                break;
            }

            case 7:
                std::cout << "Enter text to search: ";
                std::getline(std::cin, input);
                editor.search_text(input);
                break;

            case 8:
                editor.undo();
                std::cout << "Undo executed\n";
                break;

            case 9:
                editor.redo();
                std::cout << "Redo executed\n";
                break;

            case 10: {
                int line, index, count;
                std::cout << "Choose line, index and count: ";
                std::cin >> line >> index >> count;
                std::cin.ignore();
                editor.set_cursor(line, index);
                editor.cut(count);
                break;
            }

            case 11: {
                int line, index, count;
                std::cout << "Choose line, index and count: ";
                std::cin >> line >> index >> count;
                std::cin.ignore();
                editor.set_cursor(line, index);
                editor.copy(count);
                break;
            }

            case 12: {
                int line, index;
                std::cout << "Choose line and index: ";
                std::cin >> line >> index;
                std::cin.ignore();
                editor.set_cursor(line, index);
                editor.paste();
                break;
            }

            case 13: {
                int line, index;
                std::cout << "Choose line and index: ";
                std::cin >> line >> index;
                std::cin.ignore();
                std::cout << "Enter replacement text: ";
                std::getline(std::cin, input);
                editor.set_cursor(line, index);
                editor.insert_replacement(input);
                break;
            }

            case 14: {
                int line, index;
                std::cout << "Choose line and index: ";
                std::cin >> line >> index;
                std::cin.ignore();
                editor.set_cursor(line, index);
                break;
            }

            default:
                std::cout << "The command is not implemented\n";
        }
    }

    return 0;
}
