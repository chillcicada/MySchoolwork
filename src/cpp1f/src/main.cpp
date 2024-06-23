/**
 * @file main.cpp
 * @author chillcicada (2210227279@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-06-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ui.hpp"
#include <iostream>

/**
 * @brief loop function when playing the game
 *
 * @param map
 * @param ui
 */
void loop(Map &map, UI &ui);

/**
 * @brief main function
 *   - init UI
 *   - print main menu
 *   - get user choice
 *
 * @param argc num of arguments
 * @param argv arguments
 * @param envp environment variables
 * @return int
 */
int main(int argc, char *argv[], char *envp[]) {
  UI ui; // prepare the UI

  // ? 因无聊而诞生的命令行参数解析
  if (argc > 1) {
    std::string exeName = std::string(argv[0]);

    if (exeName.find_last_of("\\") != std::string::npos)
      exeName = exeName.substr(exeName.find_last_of("\\") + 1);

    std::string arg1 = std::string(argv[1]);

    if (arg1 == "-h" | arg1 == "--help")
      std::cout << "Usage: " << exeName << " [Options]" << '\n'
                << "Options:" << '\n'
                << "  -h, --help     show this help message and exit" << '\n'
                << "  -v, --version  show program's version number and exit"
                << "\n\n"
                << "Type " << exeName << " to directly start the maze game"
                << std::endl;
    else if (arg1 == "-v" | arg1 == "--version")
      std::cout << "Version: 0.1" << '\n'
                << "Made by chillcicada (2210227279@qq.com)" << std::endl;
    else
      std::cerr << "Invalid argument: " << arg1 << '\n'
                << "Try `" << exeName << " --help` for more information."
                << std::endl;

    return 0;
  }

  UI::mainMenu choice = UI::mainMenu::Start;

  while (choice = ui.printMainMenu(), choice != UI::mainMenu::Exit) {
    if (choice == UI::mainMenu::About) {
      ui.printAbout();
      continue;
    }

    if (choice == UI::mainMenu::None) {
      continue;
    }

    ui.printStart();

    UI::MapConfig config = ui.getMapConfig();

    while (!(ui.cfgValid(config))) {
      ui.handleError();
      config = ui.getMapConfig();
    }

    Map map(config.width, config.height);

    ui.printMap(map);

    loop(map, ui);
  }

  ui.clear();
  return 0;
}

void loop(Map &map, UI &ui) {
  for (;;) {
    ui.useMove(map);

    if (!(ui.getError()))
      ui.printMoveHelp();

    ui.handleError();

    if (map.getOver()) {
      ui.printEnd();
      ui.resetHelpHeight();
      Sleep(300);
      break;
    }
  }
}
