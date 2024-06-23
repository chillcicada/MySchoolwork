/**
 * @file ui.hpp
 * @author chillcicada (2210227279@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-06-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __UI_HPP__
#define __UI_HPP__

#include "map.hpp"

#include <conio.h>
#include <string>

// avoid redefinition of max and min macro
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

/**
 * an example of the console coordinate system:
 * .-----------> x
 * |
 * |
 * |
 * |
 * v
 * y
 */

/**
 * @brief UI class
 */
class UI {
public:
  /**
   * @brief construct a new UI object
   * - get the console handle
   * - set the console title
   * - set the console size
   *
   */
  UI();

  /**
   * @brief delete the copy constructor
   *
   */
  UI(const UI &) = delete;

  /**
   * @brief destruct a UI object
   * - show the cursor
   * - close the console handle
   *
   */
  ~UI();

  /**
   * @brief main menu enum class
   *
   */
  enum class mainMenu : short {
    Start,
    About,
    Exit,
    None,
  };

  /**
   * @brief pause menu enum class
   *
   */
  enum class pauseMenu : short {
    Continue,
    Restart,
    End,
    None,
  };

  /**
   * @brief error code
   *
   */
  enum class ErrorType : short {
    None, // 0 means no error
    TooSmallConsole,
    InvalidMapConfig,
    InvalidMove,
    InvalidKeycode,
  };

  /**
   * @brief clear the console buffer
   * note that this function will not clear the console screen
   * it will only clear the buffer
   *
   */
  void clear();

  /**
   * @brief print the main menu
   *
   * @return the selected main menu
   */
  mainMenu printMainMenu();

  /**
   * @brief print the pause menu
   *
   */
  pauseMenu printPauseMenu();

  /**
   * @brief print the initial map
   *
   * @param map
   */
  void printMap(Map &map);

  /**
   * @brief print the about information
   *
   */
  void printAbout();

  /**
   * @brief print the start page
   *
   */
  void printStart();

  /**
   * @brief print the end page
   *
   */
  void printEnd();

  /**
   * @brief the map config input
   *
   */
  struct MapConfig {
    short width;  ///< width of the map
    short height; ///< height of the map
    /**
     * here we use {-1, -1} to represent the start and end point are not set
     * for the default value of the start point and end point is defined in the
     * @c Map class
     */
    Point start{-1, -1}; ///< start point of the map
    Point end{-1, -1};   ///< end point of the map
  };

  /**
   * @brief validate the map config
   *
   * @param cfg the map config
   * @return true is valid
   * @return false is invalid
   */
  bool cfgValid(const MapConfig &cfg);

  /**
   * @brief get the map config input
   *
   */
  MapConfig getMapConfig();

  /**
   * @brief get the key pressed and return the corresponding move
   *
   * @param map the map
   */
  void useMove(Map &map);

  /**
   * @brief Get the Error object
   *
   * @return true if there is an error
   * @return false
   */
  bool getError();

  /**
   * @brief Error handling,
   * this function works like a listener to handle the error
   *
   */
  void handleError();

  /**
   * @brief reset help height
   *
   */
  void resetHelpHeight();

  /**
   * @brief print the move help
   *
   */
  void printMoveHelp();

private:
  /**
   * @brief color
   *
   */
  enum class Color : short {
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGrey,
    DarkGrey,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White,

    Blink = 128,
  };

  /**
   * @brief config
   *
   */
  constexpr static const short MinConsoleWidth{80};
  constexpr static const short MinConsoleHeight{40};

  /**
   * @brief console handle
   *
   */
  HANDLE hOut;

  /**
   * @brief console buffer info
   *
   */
  CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

  /**
   * @brief center of x axis
   */
  short centerX;

  /**
   * @brief default help height
   *
   */
  constexpr static const short DefaultHelpHeight{23};

  /**
   * @brief help height, default is @c DefaultHelpHeight
   *
   */
  short helpHeight{DefaultHelpHeight};

  /**
   * @brief default help content inner height, default is 6
   *
   */
  constexpr static const short DefaultHelpInnerHeight{10};

  /**
   * @brief error code
   *
   */
  ErrorType errorType{ErrorType::None};

  /**
   * @brief title of the game (console)
   *
   */
  constexpr static const wchar_t *Title = L"Maze";

  /**
   * @brief title height of the page
   *
   */
  short PageTitleHeight{3};

  /**
   * @brief default character to fill the console
   *
   */
  constexpr static const char DefaultChar = ' ';

  /**
   * @brief hide the cursor
   *
   */
  void hideCursor();

  /**
   * @brief show the cursor
   *
   */
  void showCursor();

  /**
   * @brief set the text color
   *
   * @param fg foreground color
   * @param bg background color
   */
  void setColor(Color fg, Color bg);
  /**
   * @brief set the text color
   *
   */
  void setColor();

  /**
   * @brief set the cursor position (left top control)
   *
   * @param x x axis
   * @param y y axis
   */
  void setPos(short x, short y);
  /**
   * @brief Set the Pos
   *
   * @param pos the position
   */
  void setPos(COORD pos);

  /**
   * @brief set the cursor with center control
   *
   * @param y y axis
   * @param length length of the string
   */
  void useCenterCursorPos(short y, short length);

  /**
   * @brief set the cursor with right control
   *
   * @param y y axis
   * @param length length of the string
   */
  void useRightCursorPos(short y, short length);

  /**
   * @brief print menu and return the selected index
   *
   * @param title menu title
   * @param items menu items
   * @param pos selected index
   * @param num number of items
   * @return selected index
   */
  short useMenu(const std::string &title, const std::string *items,
                const short *pos, const short num);

  /**
   * @brief print the input field
   *
   * @param x the start point X coordinate of the input field
   * @param y the start point Y coordinate of the input field
   * @param length the length of the input field
   * @param prompt some prompt text, default is empty
   * @return the input string
   */
  std::string printInputField(short x, short y, short length,
                              std::string prompt = "");

  /**
   * @brief print some message
   *
   * @param x the start point X coordinate of the message
   * @param y the start point Y coordinate of the message
   * @param msg content of the message, default is empty
   * @param isWarning is the message a warning, default is false
   */
  void printMsg(short x, short y, std::string msg = "", bool isWarning = false);

  /**
   * @brief print error message
   * when the error message is a multi-line message array
   *
   * @param msg
   * @param num
   */
  void printErrorMsg(const std::string *msg, const short num);
  /**
   * @brief print error message
   * when the error message is only one line
   *
   * @param msg
   */
  void printErrorMsg(const std::string &msg);

  /**
   * @brief print the header of help
   *
   */
  void printHelpTitle();

  /**
   * @brief print the header of help
   *
   */
  void printHelpTitle(short height);

  /**
   * @brief print the menu help
   * note that all help messages should end with @c std::endl to flush the
   * buffer
   *
   */
  void printMenuHelp();

  /**
   * @brief print the main menu help
   *
   */
  void printInputHelp();

  /**
   * @brief print the end help
   *
   */
  void printEndHelp();

  /**
   * @brief set the color of the specified position.
   * note that the position is based on the map.
   *
   * @param fg foreground color
   * @param bg background color
   * @param p the point of the map
   */
  void usePosColor(Color fg, Color bg, Point p, Map &map);

  /**
   * @brief Set the Pos Point object
   *
   * @param p
   * @param map
   */
  void setPointPos(Point p, Map &map);

  /**
   * @brief get the console coordinate based on the map
   * note that the position is based on the map.
   *
   * @param x the X coordinate of the map
   * @param y the Y coordinate of the map
   * @return return the corresponding console coordinate
   */
  COORD getCOORD(short x, short y, Map &map);
  /**
   * @brief get the console coordinate based on the map
   * note that the position is based on the map.
   *
   * @param p the point of the map
   * @param map the map
   * @return COORD
   */
  COORD getCOORD(Point p, Map &map);

  /**
   * @brief print the point
   *
   * @param p the point
   * @param map the map
   * @param fg the foreground color
   * @param bg the background color
   */
  void printPoint(Point p, Map &map, Color fg = Color::White,
                  Color bg = Color::Black);
};

#endif // __UI_HPP__
