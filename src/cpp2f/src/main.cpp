/**
 * @file main.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief main function of the editor
 * @version 0.0.0
 * @date 2024-11-12
 *
 * @copyright Copyright (C) 2024 MIT License
 *
 */

#include "ui/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
