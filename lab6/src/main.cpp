#include <iostream>
#include "Dungeon.h"

void printMenu() {
    std::cout << "\nBalagur Fate 3 - Dungeon Editor\n";
    std::cout << "1. Add NPC\n";
    std::cout << "2. List NPCs\n";
    std::cout << "3. Save to file\n";
    std::cout << "4. Load from file\n";
    std::cout << "5. Run battle mode\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    DungeonEditor editor;
    bool running = true;

    while (running) {
        printMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cerr << "Invalid input\n";
            return 1;
        }

        if (choice == 1) {
            std::string type, name;
            double x, y;
            std::cout << "Enter type (Dragon/Frog/Knight): ";
            std::cin >> type;
            std::cout << "Enter name (unique): ";
            std::cin >> name;
            std::cout << "Enter x y (0..500): ";
            std::cin >> x >> y;
            editor.addNPC(type, name, x, y);
        } else if (choice == 2) {
            editor.listNPCs();
        } else if (choice == 3) {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            if (editor.saveToFile(filename)) {
                std::cout << "Saved.\n";
            } else {
                std::cout << "Save failed.\n";
            }
        } else if (choice == 4) {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            if (editor.loadFromFile(filename)) {
                std::cout << "Loaded.\n";
            } else {
                std::cout << "Load failed.\n";
            }
        } else if (choice == 5) {
            double dist;
            std::cout << "Enter battle distance: ";
            std::cin >> dist;
            editor.runBattleMode(dist);
        } else if (choice == 0) {
            running = false;
        } else {
            std::cout << "Unknown choice.\n";
        }
    }

    return 0;
}
