#pragma once
#include "GameWidget.h"
#include "ScoreBoard.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

private slots:
  void startNewGame();
  void showAbout();

private:
  GameWidget *gameWidget;
  ScoreBoard *scoreBoard;

  void setupUI();
  void createMenus();
  void createDockWidgets();
};
