#include <iostream>
#include "TextEditor.h"

int main() {
    TextEditor editor;
    int cmd;
    char buffer[256];
    int idx, count;

    while (true) {
        std::cout << "> Choose command:\n"
                  << "1: Print\n2: Insert\n3: Delete\n"
                  << "4: Cut\n5: Copy\n6: Paste\n"
                  << "7: Undo\n8: Redo\n0: Exit\n> ";
        std::cin >> cmd;

        if (cmd == 0) break;

        switch (cmd) {
            case 1:
                editor.print();
                break;
            case 2:
                std::cout << "> Enter index and text:\n";
                std::cin >> idx;
                std::cin.ignore();
                std::cin.getline(buffer, 256);
                editor.insert(idx, buffer);
                break;
            case 3:
                std::cout << "> Enter index and count:\n";
                std::cin >> idx >> count;
                editor.delete_range(idx, count);
                break;
            case 4:
                std::cout << "> Enter index and count to cut:\n";
                std::cin >> idx >> count;
                editor.cut(idx, count);
                break;
            case 5:
                std::cout << "> Enter index and count to copy:\n";
                std::cin >> idx >> count;
                editor.copy(idx, count);
                break;
            case 6:
                std::cout << "> Enter index to paste:\n";
                std::cin >> idx;
                editor.paste(idx);
                break;
            case 7:
                editor.undo();
                break;
            case 8:
                editor.redo();
                break;
            default:
                std::cout << "Unknown command\n";
        }
    }

    return 0;
}
