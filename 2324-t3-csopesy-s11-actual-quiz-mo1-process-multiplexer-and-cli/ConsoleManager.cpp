#include "ConsoleManager.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

ConsoleManager::ConsoleManager() : currentConsole(nullptr), previousConsole(nullptr), console_handle_(GetStdHandle(STD_OUTPUT_HANDLE)) {
    // Create a Console object for the main menu
    std::shared_ptr<Console> mainConsole(new Console("MAIN_MENU", 1, 1, 0));
    consoles.push_back(mainConsole);
    currentConsole = mainConsole;
    GetConsoleScreenBufferInfo(console_handle_, &csbi_info_);
}

void ConsoleManager::addConsole(const std::shared_ptr<Console>& console) {
    consoles.push_back(console);
}

ConsoleManager::~ConsoleManager() {}

std::string ConsoleManager::getCurrentConsoleName() const {
    if (currentConsole) {
        return currentConsole->getName();
    }
    else {
        return "MAIN_MENU";
    }
}

void ConsoleManager::setCurrentConsole(std::shared_ptr<Console> console)
{
    this->currentConsole = console;
}

void ConsoleManager::drawAllConsoles() {
   
    for (const auto& consolePtr : consoles) {
        Console& console = *consolePtr;

        // Now you can access properties of the console object
        std::cout << "Name: " << console.getName() << std::endl;
        
        //consolePtr->drawProcess();
    }

    std::cout << "Currently Selected Console: " << std::endl;
    std::cout << currentConsole->getName();
}

std::vector<std::shared_ptr<Console>> ConsoleManager::getConsoles()
{
    return this->consoles;
}

std::shared_ptr<Console> ConsoleManager::getCurrentConsole()
{
    return this->currentConsole;
}

COORD ConsoleManager::GetCursorPosition() {
    return csbi_info_.dwCursorPosition;
}

SMALL_RECT ConsoleManager::GetDisplayWindowBounds() {
    return csbi_info_.srWindow;
}

void ConsoleManager::ClearConsole() {
    SMALL_RECT scroll_rect = { 0, 0, csbi_info_.srWindow.Right, csbi_info_.srWindow.Bottom };
    COORD scroll_target = { 0, (SHORT)(0 - csbi_info_.dwSize.Y) };
    CHAR_INFO fill = { { TEXT(' ') },  csbi_info_.wAttributes };
    ScrollConsoleScreenBuffer(console_handle_, &scroll_rect, NULL, scroll_target, &fill);
}

void ConsoleManager::PollKeyboard(char& key_pressed) {
    if (_kbhit()) {
        key_pressed = _getch();
    }
}


void ConsoleManager::SetCursorPosition(int pos_x, int pos_y) {
    COORD coord = { pos_x, pos_y };
    SetConsoleCursorPosition(console_handle_, coord);
}

void ConsoleManager::WriteAtPosition(const std::string& text, int pos_x, int pos_y) {
    SetCursorPosition(pos_x, pos_y);
    WriteConsoleA(console_handle_, text.c_str(), text.size(), NULL, NULL);
}
