/**
 * @file EditorHighlighter.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-03
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef EDITOR_HIGHLIGHTER_H
#define EDITOR_HIGHLIGHTER_H

#include "mystl.h"

#include <QRegularExpression>
#include <QSyntaxHighlighter>

class EditorHighlighter : public QSyntaxHighlighter {
  Q_OBJECT

public:
  explicit EditorHighlighter(QTextDocument *parent = nullptr);
  ~EditorHighlighter() = default;

protected:
  void highlightBlock(const QString &text) override;

private:
  struct HighlightingRule {
    QRegularExpression pattern;
    QTextCharFormat format;
  };

  mystl::vector<HighlightingRule> highlightingRules_;

  QRegularExpression commentStartExpression_;
  QRegularExpression commentEndExpression;

  QTextCharFormat keywordFormat_;
  QTextCharFormat classFormat_;
  QTextCharFormat singleLineCommentFormat_;
  QTextCharFormat multiLineCommentFormat_;
  QTextCharFormat quotationFormat_;
  QTextCharFormat functionFormat_;
};

#endif // EDITOR_HIGHLIGHTER_H
