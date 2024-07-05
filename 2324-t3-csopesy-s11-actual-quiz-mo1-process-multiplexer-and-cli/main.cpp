#include<iostream>
#include <string>
#include "commands.h"
#include "ConsoleManager.h";

int main() {
    displayHeader();
    std::string command;
    ConsoleManager consoleManager;
        
    while (true) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, command);
            
        // handle exit command
        if (!handleCommand(command, consoleManager)) {
            break;
        }
    }
    return 0;
}
