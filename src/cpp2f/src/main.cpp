/**
 * @file main.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-18
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "MainWindow.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  // a.setStyleSheet(styleSheet);
  a.setOrganizationName("chillcicada");
  a.setApplicationName("Qode");
  a.setApplicationVersion("0.0.0");

  QCommandLineParser p;
  p.addPositionalArgument("FILE", "The file / folder to open.");
  p.addVersionOption();
  p.addHelpOption();
  p.process(a);

  a.connect(&a, &QGuiApplication::commitDataRequest, &w,
            &MainWindow::commitSession);

  w.show();

  if (!p.positionalArguments().empty())
    w.loadFile(p.positionalArguments().front());
  else
    w.newFile();

  return a.exec();
}
