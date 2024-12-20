/**
 * @file OutputWidget.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-03
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "OutputWidget.h"
#include "qtextformat.h"

#include <QColor>
#include <QFont>

LogHighlighter::LogHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
  QTextCharFormat timeFormat;
  timeFormat.setForeground(QColor("gray"));
  QString timePattern =
      R"(\b\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:\.\d{0,9})?Z\b)";
  highlightingRules_.append({QRegularExpression(timePattern), timeFormat});

  QTextCharFormat shortTimeFormat;
  shortTimeFormat.setForeground(QColor("gray"));
  QString shortTimePattern = R"(\b\d{2}:\d{2}:\d{2}(\.\d{3})?\b)";
  highlightingRules_.append(
      {QRegularExpression(shortTimePattern), shortTimeFormat});

  QTextCharFormat urlFormat;
  urlFormat.setForeground(QColor("green"));
  urlFormat.setFontUnderline(true);
  QString urlPattern = R"(\bhttps?://\S+\b)";
  highlightingRules_.append({QRegularExpression(urlPattern), urlFormat});

  QTextCharFormat versionFormat;
  versionFormat.setForeground(QColor("purple"));
  versionFormat.setFontWeight(QFont::Weight::Bold);
  QString versionPattern = R"(\b\d+\.\d+\.\d+\b)";
  highlightingRules_.append(
      {QRegularExpression(versionPattern), versionFormat});

  QTextCharFormat infoFormat;
  infoFormat.setForeground(QColor("blue"));
  infoFormat.setFontWeight(QFont::Weight::Bold);
  QString infoPattern = R"(\bINFO\b)";
  highlightingRules_.append({QRegularExpression(infoPattern), infoFormat});

  QTextCharFormat shortInfoFormat;
  shortInfoFormat.setForeground(QColor("blue"));
  shortInfoFormat.setFontWeight(QFont::Weight::Bold);
  QString shortInfoPattern = R"(\bI\b)";
  highlightingRules_.append(
      {QRegularExpression(shortInfoPattern), shortInfoFormat});

  QTextCharFormat errorFormat;
  errorFormat.setForeground(QColor("red"));
  errorFormat.setFontWeight(QFont::Weight::Bold);
  QString errorPattern = R"(\bERROR\b)";
  highlightingRules_.append({QRegularExpression(errorPattern), errorFormat});

  QTextCharFormat shortErrorFormat;
  shortErrorFormat.setForeground(QColor("red"));
  shortErrorFormat.setFontWeight(QFont::Weight::Bold);
  QString shortErrorPattern = R"(\bE\b)";
  highlightingRules_.append(
      {QRegularExpression(shortErrorPattern), shortErrorFormat});

  QTextCharFormat warningFormat;
  warningFormat.setForeground(QColor("orange"));
  warningFormat.setFontWeight(QFont::Weight::Bold);
  QString warningPattern = R"(\bWARNING\b)";
  highlightingRules_.append(
      {QRegularExpression(warningPattern), warningFormat});

  QTextCharFormat shortWarningFormat;
  shortWarningFormat.setForeground(QColor("orange"));
  shortWarningFormat.setFontWeight(QFont::Weight::Bold);
  QString shortWarningPattern = R"(\bW\b)";
  highlightingRules_.append(
      {QRegularExpression(shortWarningPattern), shortWarningFormat});

  QTextCharFormat debugFormat;
  debugFormat.setForeground(QColor("lightgray"));
  debugFormat.setFontWeight(QFont::Weight::Bold);
  QString debugPattern = R"(\bDEBUG\b)";
  highlightingRules_.append({QRegularExpression(debugPattern), debugFormat});

  QTextCharFormat shortDebugFormat;
  shortDebugFormat.setForeground(QColor("lightgray"));
  shortDebugFormat.setFontWeight(QFont::Weight::Bold);
  QString shortDebugPattern = R"(\bD\b)";
  highlightingRules_.append(
      {QRegularExpression(shortDebugPattern), shortDebugFormat});
}

void LogHighlighter::highlightBlock(const QString &text) {
  for (const auto &rule : highlightingRules_) {
    QRegularExpressionMatchIterator matchIterator =
        rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
      QRegularExpressionMatch match = matchIterator.next();
      setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
  }
}

OutputWidget::OutputWidget(QWidget *parent) : QPlainTextEdit(parent) {
  setReadOnly(true);
  setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);
  setTabStopDistance(4);
  setPlaceholderText("Output will be shown here.");

  highlighter_ = new LogHighlighter(document());
}
