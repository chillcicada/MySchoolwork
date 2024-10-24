#pragma once

#include <QWidget>
#include <memory>

class QPushButton;

class OperationWidget : public QWidget {
  Q_OBJECT

public:
  OperationWidget(QWidget *parent = nullptr);

signals:
  void startGameRequested();
  void undoRequested();

private:
  std::shared_ptr<QPushButton> startButton_;
  std::shared_ptr<QPushButton> undoButton_;
};
