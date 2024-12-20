/**
 * @file OutputWidget.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-03
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef OUTPUT_WIDGET_H
#define OUTPUT_WIDGET_H

#include "mystl.h"

#include <QPlainTextEdit>
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

/**
 * @brief log highlighter
 *
 */
class LogHighlighter : public QSyntaxHighlighter {
  Q_OBJECT

public:
  /**
   * @brief Construct a new Log Highlighter object
   *
   * @param parent
   */
  explicit LogHighlighter(QTextDocument *parent = nullptr);

protected:
  /**
   * @brief highlight block
   *
   * @param text
   */
  void highlightBlock(const QString &text) override;

private:
  /**
   * @brief highlighting rule struct
   *
   */
  struct HighlightingRule {
    QRegularExpression pattern;
    QTextCharFormat format;
  };

  /**
   * @brief store highlighting rules
   *
   */
  mystl::vector<HighlightingRule> highlightingRules_ = {};
};

/**
 * @brief output widget
 *
 */
class OutputWidget : public QPlainTextEdit {
  Q_OBJECT

public:
  /**
   * @brief Construct a new Output Widget object
   *
   * @param parent
   */
  explicit OutputWidget(QWidget *parent = nullptr);

private:
  /**
   * @brief highlighter
   *
   */
  LogHighlighter *highlighter_ = nullptr;
};

#endif // OUTPUT_WIDGET_H
