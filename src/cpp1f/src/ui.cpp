/**
 * @file ui.cpp
 * @author chillcicada (2210227279@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-06-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ui.hpp"

#include "map.hpp"
#include "utils.hpp"

#include <conio.h>
#include <iostream>
#include <string>

// !! public function implementation !! //

UI::UI() {
  // set the console code page to UTF-8
  SetConsoleOutputCP(CP_UTF8);

  // get the standard output handle
  hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  // get the console screen buffer info
  GetConsoleScreenBufferInfo(hOut, &bufferInfo);

  // set the console size
  if (bufferInfo.dwSize.X < MinConsoleWidth) {
    bufferInfo.dwSize.X = MinConsoleWidth;
    errorType = ErrorType::TooSmallConsole;
  }

  if (bufferInfo.dwSize.Y < MinConsoleHeight) {
    errorType = ErrorType::TooSmallConsole;
    bufferInfo.dwSize.Y = MinConsoleHeight;
  }

  COORD bufSize = {bufferInfo.dwSize.X, bufferInfo.dwSize.Y};
  SetConsoleScreenBufferSize(hOut, bufSize);

  // get the center of X axis
  centerX = bufferInfo.dwSize.X / 2;

  // set console title
  SetConsoleTitleW(Title);

  // set console text color
  setColor(Color::White, Color::Black);

  // hide cursor
  hideCursor();
}

UI::~UI() {
  // show cursor
  showCursor();

  // close console handle
  CloseHandle(hOut);
}

void UI::clear() {
  DWORD buffer;

  for (short i{0}; i < bufferInfo.dwSize.Y; i++) {
    COORD pos = {0, i};
    FillConsoleOutputAttribute(hOut, 0x0F, bufferInfo.dwSize.X, pos, &buffer);
    FillConsoleOutputCharacter(hOut, DefaultChar, bufferInfo.dwSize.X, pos,
                               &buffer);
  }

  setPos(0, 0);
}

UI::mainMenu UI::printMainMenu() {
  clear();

  const short bannerLength{7};

  std::string banner[bannerLength] = {
      R"*( __  __           ____________ )*",
      R"*(|  \/  |   /\    |___  /  ____|)*",
      R"*(| \  / |  /  \      / /| |__   )*",
      R"*(| |\/| | / /\ \    / / |  __|  )*",
      R"*(| |  | |/ ____ \  / /__| |____ )*",
      R"*(|_|  |_/_/    \_\/_____|______|)*",
      R"*(                 By ChillCicada)*",
  };

  short maxBannerWidth = utils::getMaxLength(banner, bannerLength);

  for (short i{0}; i < bannerLength; i++) {
    useCenterCursorPos(i + PageTitleHeight, maxBannerWidth);
    std::cout << banner[i];
  }

  const short num{3};

  std::string ctx[num] = {
      "1. Start (S)",
      "2. About (A)",
      "3. Exit  (E)",
  };

  short pos[num] = {12, 15, 18};

  short idx = useMenu("Main Menu", ctx, pos, num);

  if (idx > 100) {
    idx = idx - 100 + 'A';
    switch (idx) {
    case 'A':
    case 'a':
      return mainMenu::About;
    case 'E':
    case 'e':
      return mainMenu::Exit;
    case 'S':
    case 's':
      return mainMenu::Start;
    default:
      return mainMenu::None;
    }
  }

  return mainMenu(idx);
}

UI::pauseMenu UI::printPauseMenu() {
  clear();

  const short bannerLength{6};

  std::string banner[bannerLength] = {
      R"*( _____                         _ )*",
      R"*(|  __ \                       | |)*",
      R"*(| |__) |_ _ _   _ ___  ___  __| |)*",
      R"*(|  ___/ _` | | | / __|/ _ \/ _` |)*",
      R"*(| |  | (_| | |_| \__ \  __/ (_| |)*",
      R"*(|_|   \__,_|\__,_|___/\___|\__,_|)*",
  };

  short maxBannerWidth = utils::getMaxLength(banner, bannerLength);

  for (short i{0}; i < bannerLength; i++) {
    useCenterCursorPos(i + PageTitleHeight, maxBannerWidth);
    std::cout << banner[i];
  }
  const short num{3};

  std::string ctx[num] = {
      "1. Continue (C)",
      "2. Restart  (R)",
      "3.   End    (E)",
  };

  short pos[num] = {12, 15, 18};

  short idx = useMenu("Game Paused", ctx, pos, num);

  if (idx > 100) {
    idx = idx - 100 + 'A';
    switch (idx) {
    case 'C':
    case 'c':
      return pauseMenu::Continue;
    case 'R':
    case 'r':
      return pauseMenu::Restart;
    case 'E':
    case 'e':
      return pauseMenu::End;
    default:
      return pauseMenu::None;
    }
  }

  return pauseMenu(idx);
}

void UI::printMap(Map &map) {
  clear();

  std::string MapTitle = "「 Map 」";

  short MapTitleWidth = short(MapTitle.length() - 4); // !! correct the width

  useCenterCursorPos(1, MapTitleWidth);
  std::cout << MapTitle;

  short row = map.getRow();
  short col = map.getCol();

  // print the map
  for (short i{1}; i <= row; i++)   // x
    for (short j{1}; j <= col; j++) // y
      printPoint(Point{i, j}, map);

  helpHeight = row + PageTitleHeight + 2; // 2 for better performance

  printMoveHelp();
}

void UI::printAbout() {
  clear();

  const short bannerLength{6};

  std::string banner[bannerLength] = {
      R"*(          _                   _   )*",
      R"*(    /\   | |                 | |  )*",
      R"*(   /  \  | |__   ___  _   _ _| |_ )*",
      R"*(  / /\ \ | '_ \ / _ \| | | |_   _|)*",
      R"*( / ____ \| |_) | (_) | |_| | | |_ )*",
      R"*(/_/    \_\_.__/ \___/ \__,_|  \__|)*",
  };

  short maxBannerWidth = utils::getMaxLength(banner, bannerLength);

  for (short i{0}; i < bannerLength; i++) {
    useCenterCursorPos(i + PageTitleHeight, maxBannerWidth);
    std::cout << banner[i];
  }

  std::string AboutTitle = "「 About 」";
  short AboutTitleWidth =
      short(AboutTitle.length() - 4); // !! correct the width
  useCenterCursorPos(1, AboutTitleWidth);
  std::cout << AboutTitle;

  const short num{4};
  std::string ctx[num] = {
      "Made with love by: ChillCicada",
      "Powered by MSVC 2022 / MinGW and xmake, Edited with VS Code",
      "Released under the MIT License, https://mit-license.org/",
      "Source code at https://github.com/chillcicada/MySchoolwork",
  };

  for (int i{0}; i < num; i++) {
    useCenterCursorPos(i + 12, ctx[i].length());
    std::cout << ctx[i];
  }

  printHelpTitle();
  std::cout << "Press [any key] to return to the main menu." << std::endl;
  _getch();
}

void UI::printStart() {
  clear();

  const short length{2};

  std::string ctx[length] = {
      "Well, before we start the game,",
      "we have some configurations to set.",
  };

  for (short i{0}; i < length; i++) {
    useCenterCursorPos(i + 2, ctx[i].length());
    std::cout << ctx[i];
  }

  printInputHelp();
}

void UI::printEnd() {
  clear();

  std::string EndTitle = "「 Game Over 」";

  short EndTitleWidth = short(EndTitle.length() - 4); // !! correct the width

  useCenterCursorPos(1, EndTitleWidth);
  std::cout << EndTitle;

  printEndHelp();
  _getch();
}

UI::MapConfig UI::getMapConfig() {
  std::string input = printInputField(10, 13, bufferInfo.dwSize.X - 20,
                                      "Row Col (default 25 25): ");

  if (input.empty())
    return {25, 25};

  MapConfig config;
  try {
    // * sscanf is not safe, use stoi instead
    // std::sscanf(input.c_str(), "%hd %hd", &config.first, &config.second);
    config.width = std::stoi(input.substr(0, input.find(' ')));
    config.height = std::stoi(input.substr(input.find(' ') + 1));
  } catch (std::invalid_argument &e) {
    errorType = ErrorType::InvalidMapConfig;
    return {-1, -1};
  }

  return config;
}

bool UI::cfgValid(const MapConfig &cfg) {
  if (cfg.width <= 3 || cfg.height <= 3) {
    errorType = ErrorType::InvalidMapConfig;
    return false;
  }

  // 大于 35 原则上也可以玩，但受屏幕尺寸影响效果很差
  if (cfg.width > 35 || cfg.height > 35) {
    errorType = ErrorType::InvalidMapConfig;
    return false;
  }

  return true;
}

void UI::useMove(Map &map) {
  Map backup = map; // backup the map
  Point playerPoint = map.getPlayer();

  short keycode = short(_getch());

  if (keycode == 0 || keycode == 224) {
    keycode = short(_getch());
    keycode += 1000; // make the functional keycode different from the ASCII,
                     // > 1000 means the functional keycode
  }

  switch (keycode) {
  case 1000 + 72: // up
  case 'W':
  case 'w': {
    if (map.move(playerPoint, Map::Direction::UP)) {
      printPoint(playerPoint, map);
      printPoint(map.getPlayer(), map);
    } else {
      errorType = ErrorType::InvalidMove;
    }
  } break;

  case 1000 + 80: // down
  case 'S':
  case 's': {
    if (map.move(playerPoint, Map::Direction::DOWN)) {
      printPoint(playerPoint, map);
      printPoint(map.getPlayer(), map);
    } else {
      errorType = ErrorType::InvalidMove;
    }
  } break;

  case 1000 + 75: // left
  case 'A':
  case 'a': {
    if (map.move(playerPoint, Map::Direction::LEFT)) {
      printPoint(playerPoint, map);
      printPoint(map.getPlayer(), map);
    } else {
      errorType = ErrorType::InvalidMove;
    }
  } break;

  case 1000 + 77: // right
  case 'D':
  case 'd': {
    if (map.move(playerPoint, Map::Direction::RIGHT)) {
      printPoint(playerPoint, map);
      printPoint(map.getPlayer(), map);
    } else {
      errorType = ErrorType::InvalidMove;
    }
  } break;

  case 'H':
  case 'h': {
    Point next = map.useSolve();
    usePosColor(Color::White, Color::Yellow, next, map);
  } break;

    // TODO: add pause menu
    // case 27: { // esc
    //   printPauseMenu();
    //   break;
    // }

  default: {
    errorType = ErrorType::InvalidMove;
  } break;
  }
}

void UI::handleError() {
  if (errorType == ErrorType::None)
    return;

  printHelpTitle(helpHeight);

  switch (errorType) {
  case ErrorType::InvalidMapConfig:
    std::cerr << "Invalid Map Config" << '\n'
              << "[Enter] to confirm your input." << std::endl;
    break;
  case ErrorType::InvalidMove:
    std::cerr << "Invalid Move" << '\n'
              << "[墙] is the wall, [  ] is the path," << '\n'
              << "[起] is the start, [终] is the destination," << '\n'
              << "[你] is the player." << '\n'
              << "Use [WASD] / [Arrows] to move" << '\n'
              << "Use [H] to get game help" << std::endl;
    break;
  case ErrorType::TooSmallConsole:
    std::cerr << "[Warning] Console is too small" << std::endl;
    break;
  default:
    break;
  }

  // reset the error type
  errorType = ErrorType::None;
}

void UI::resetHelpHeight() { helpHeight = DefaultHelpHeight; }

// !! private function implementation !! //

void UI::hideCursor() {
  CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
  SetConsoleCursorInfo(hOut, &cursorInfo);
}

void UI::showCursor() {
  CONSOLE_CURSOR_INFO cursorInfo = {1, 1};
  SetConsoleCursorInfo(hOut, &cursorInfo);
}

void UI::setColor(Color fg, Color bg) {
  WORD wordColor = short(fg) + (short(bg) << 4);
  SetConsoleTextAttribute(hOut, wordColor);
}
void UI::setColor() { setColor(Color::White, Color::Black); }

void UI::setPos(short x, short y) {
  COORD pos = {x, y};
  SetConsoleCursorPosition(hOut, pos);
}
void UI::setPos(COORD pos) { SetConsoleCursorPosition(hOut, pos); }

void UI::useCenterCursorPos(short y, const short length) {
  // ! make the length always even
  short _length = (length % 2 == 0 ? length : length - 1);
  setPos(centerX - _length / 2, y);
}

void UI::useRightCursorPos(short y, short length) {
  setPos(2 * centerX - length, y);
}

short UI::useMenu(const std::string &title, const std::string *items,
                  const short *pos, const short num) {
  setColor(Color::White, Color::Black);

  // set the title
  short titleLength = short(title.length());
  useCenterCursorPos(1, titleLength); // with one blank line
  std::cout << title;

  printMenuHelp();

  short maxLength = utils::getMaxLength(items, num);

  // print the choices menu
  for (short i{0}; i < num; i++) {
    useCenterCursorPos(pos[i], maxLength);
    std::cout << items[i];
  }

  DWORD buffer;

  short keycode, idx{0};

  short nLength = maxLength + 4; // 4 for better performance

  // select the first item
  FillConsoleOutputAttribute(hOut, 0xF0, nLength,
                             {short(centerX - nLength / 2), pos[idx]}, &buffer);

  while (keycode = short(_getch()), keycode != 13) { // 13 == enter
    // 224 / 0xE0 , which return before an arrow key
    if (keycode == 0 || keycode == 224) {
      keycode = short(_getch());
      keycode += 1000; // make the functional keycode different from the ASCII,
                       // > 1000 means the functional keycode
    }

    if (keycode >= '1' && keycode <= num + 1 + '0')
      return keycode - '1';

    if (keycode >= 'A' && keycode <= 'z')
      return keycode - 'A' + 100; // > 100 means the hotkey

    // unselect the current item
    FillConsoleOutputAttribute(hOut, 0x0F, nLength,
                               COORD{short(centerX - nLength / 2), pos[idx]},
                               &buffer);

    switch (keycode) {
      // 1000 means the functional keycode
    case 1000 + 72: { // up
                      // border check
      idx = (idx == 0 ? 0 : idx - 1);
      break;
    }
    case 1000 + 80: { // down
                      // border check
      idx = (idx == num - 1 ? num - 1 : idx + 1);
      break;
    }
    default:
      errorType = ErrorType::InvalidKeycode;
      break;
    }

    // select the current item
    if (keycode != 27) // 27 == esc
      FillConsoleOutputAttribute(hOut, 0xF0, nLength,
                                 COORD{short(centerX - nLength / 2), pos[idx]},
                                 &buffer);
  }

  return idx;
}

std::string UI::printInputField(short x, short y, short length,
                                std::string prompt) {
  setPos(x, y);

  // show cursor
  showCursor();

  DWORD buffer;
  COORD pos{x, y};
  FillConsoleOutputAttribute(hOut, 0x80, length, pos, &buffer);

  setColor(Color::White, Color::Black);
  std::cout << prompt;

  std::string input;
  setColor(Color::White, Color::LightGrey);

  std::getline(std::cin, input);

  // reset the color
  FillConsoleOutputAttribute(hOut, 0x0F, length, pos, &buffer);
  FillConsoleOutputCharacter(hOut, DefaultChar, length, pos, &buffer);
  setColor(Color::White, Color::Black);

  // hide cursor
  hideCursor();

  return input;
}

bool UI::getError() { return errorType != ErrorType::None; }

void UI::printMsg(short x, short y, std::string msg, bool isWarning) {
  setPos(x, y);
  setColor(Color::White, isWarning ? Color::Red : Color::Green);
  std::cout << msg;
  setColor(Color::White, Color::Black);
}

void UI::printErrorMsg(const std::string *msg, const short num) {
  printHelpTitle();

  for (short i{0}; i < num; i++) {
    std::cout << msg[i] << '\n';
  }

  std::cout << "Press [any key] to continue" << std::endl;
}
void UI::printErrorMsg(const std::string &msg) {
  printHelpTitle();

  std::cout << msg << '\n';

  std::cout << "Press [any key] to continue" << std::endl;
  _getch(); // press any key to return to the main menu
}

void UI::printMoveHelp() {
  printHelpTitle(helpHeight);

  std::cout << "[墙] is the wall, [  ] is the path," << '\n'
            << "[起] is the start, [终] is the destination," << '\n'
            << "[你] is the player." << '\n'
            << "Use [WASD] / [Arrows] to move" << '\n'
            << "Use [H] to get game help" << std::endl;
}

void UI::printHelpTitle(short height) {
  COORD pos = {0, height};
  DWORD written;

  FillConsoleOutputCharacter(hOut, DefaultChar,
                             bufferInfo.dwSize.X * DefaultHelpInnerHeight, pos,
                             &written);

  std::string HelpTitle = "-------------「 Help 」-------------";
  useCenterCursorPos(height,
                     short(HelpTitle.length()) - 4); // !! correct the width

  std::cout << HelpTitle << "\n\n"; // with two blank lines
}
void UI::printHelpTitle() { printHelpTitle(DefaultHelpHeight); }

void UI::printMenuHelp() {
  printHelpTitle();

  std::cout << "Use [Up] and [Down] to navigate," << '\n'
            << "Also can use [Number] / [Hotkey] to select," << '\n'
            << "[Enter] to select, [Esc] to unselect." << std::endl;
}

void UI::printInputHelp() {
  printHelpTitle();

  std::cout << "[Enter] to confirm your input." << std::endl;
}

void UI::printEndHelp() {
  printHelpTitle(5);

  std::cout << "Thanks for you playing the game!" << '\n'
            << "Press [any key] to return to the main menu." << std::endl;
}

void UI::usePosColor(Color fg, Color bg, Point p, Map &map) {
  // set the color
  setColor(fg, bg);
  // set the position
  setPointPos(p, map);
  // print the cell
  map.printCell(p);
  // reset the color
  setColor();
}

void UI::setPointPos(Point p, Map &map) {
  COORD pos = getCOORD(p, map);
  setPos(pos);
}

COORD UI::getCOORD(short x, short y, Map &map) {
  short row = map.getRow();

  COORD r;

  r.X = centerX - row + 2 * x; // 2 is the width of the char, like '你', '墙'
  r.Y = y + PageTitleHeight;

  return r;
}
COORD UI::getCOORD(Point p, Map &map) { return getCOORD(p.x, p.y, map); }

void UI::printPoint(Point p, Map &map, Color fg, Color bg) {
  Map::CellType type = map.getPoint(p);
  switch (type) {
  case Map::CellType::WALL:
    usePosColor(Color::Black, Color::White, p, map);
    break;
  case Map::CellType::VISITED:
  case Map::CellType::EMPTY:
    usePosColor(Color::White, Color::Cyan, p, map);
    break;
  case Map::CellType::START:
    usePosColor(Color::Brown, Color::Cyan, p, map);
    break;
  case Map::CellType::END:
    usePosColor(Color::Red, Color::Cyan, p, map);
    break;
  case Map::CellType::PLAYER:
    usePosColor(Color::Blue, Color::LightCyan, p, map);
    break;
  default:
    break;
  }
}
