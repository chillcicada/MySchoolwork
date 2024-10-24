#include "OperationWidget.h"
#include <QPushButton>
#include <QVBoxLayout>

OperationWidget::OperationWidget(QWidget *parent) : QWidget(parent) {
  auto layout = new QVBoxLayout(this);

  startButton_ = std::make_shared<QPushButton>("开始游戏", this);
  undoButton_ = std::make_shared<QPushButton>("悔棋", this);

  layout->addWidget(startButton_.get());
  layout->addWidget(undoButton_.get());

  connect(startButton_.get(), &QPushButton::clicked, this,
          &OperationWidget::startGameRequested);
  connect(undoButton_.get(), &QPushButton::clicked, this,
          &OperationWidget::undoRequested);
}
