/**
 * @file EditorHighlighter.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-05
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "EditorHighlighter.h"

EditorHighlighter::EditorHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
  HighlightingRule rule;

  keywordFormat_.setForeground(Qt::darkBlue);
  keywordFormat_.setFontWeight(QFont::Bold);
  QStringList keywordPatterns;
  keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                  << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                  << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                  << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                  << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                  << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                  << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                  << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                  << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                  << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b"
                  << "\\btrue\\b" << "\\bfalse\\b" << "\\bif\\b"
                  << "\\belse\\b" << "\\bfor\\b" << "\\bwhile\\b"
                  << "\\bdo\\b" << "\\breturn\\b" << "\\bswitch\\b"
                  << "\\bcase\\b" << "\\bdefault\\b" << "\\bbreak\\b"
                  << "\\bcontinue\\b" << "\\btry\\b" << "\\bcatch\\b"
                  << "\\bthrow\\b" << "\\bdelete\\b" << "\\bnew\\b"
                  << "\\bthis\\b" << "\\busing\\b" << "\\bnamespace\\b";
  for (const QString &pattern : keywordPatterns) {
    rule.pattern = QRegularExpression(pattern);
    rule.format = keywordFormat_;
    highlightingRules_.append(rule);
  }

  classFormat_.setFontWeight(QFont::Bold);
  classFormat_.setForeground(Qt::darkMagenta);
  rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
  rule.format = classFormat_;
  highlightingRules_.append(rule);

  singleLineCommentFormat_.setForeground(Qt::red);
  rule.pattern = QRegularExpression("//[^\n]*");
  rule.format = singleLineCommentFormat_;
  highlightingRules_.append(rule);

  multiLineCommentFormat_.setForeground(Qt::red);

  quotationFormat_.setForeground(Qt::darkGreen);
  rule.pattern = QRegularExpression("\".*\"");
  rule.format = quotationFormat_;
  highlightingRules_.append(rule);

  functionFormat_.setFontItalic(true);
  functionFormat_.setForeground(Qt::blue);
  rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
  rule.format = functionFormat_;
  highlightingRules_.append(rule);

  commentStartExpression_ = QRegularExpression("/\\*");
  commentEndExpression = QRegularExpression("\\*/");
}

void EditorHighlighter::highlightBlock(const QString &text) {
  for (const HighlightingRule &rule : highlightingRules_) {
    QRegularExpressionMatchIterator matchIterator =
        rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
      QRegularExpressionMatch match = matchIterator.next();
      setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
  }

  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1) {
    startIndex = text.indexOf(commentStartExpression_);
  }

  while (startIndex >= 0) {
    QRegularExpressionMatch match =
        commentEndExpression.match(text, startIndex);
    int endIndex = match.capturedStart();
    int commentLength = 0;
    if (endIndex == -1) {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    } else {
      commentLength = endIndex - startIndex + match.capturedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat_);
    startIndex =
        text.indexOf(commentStartExpression_, startIndex + commentLength);
  }
}
