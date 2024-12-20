/**
 * @file EditorSettings.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-25
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "EditorSettings.h"

#include <QApplication>

/**
 * @brief Public
 *
 */

QString EditorSettings::fontFamily() const {
  if (fontFamily_)
    return fontFamily_.value();

  return QApplication::font().family();
}

int EditorSettings::fontSize() const {
  if (fontSize_)
    return fontSize_.value();

  return QApplication::font().pointSize();
}

QFont EditorSettings::font() const { return QFont(fontFamily(), fontSize()); }

void EditorSettings::setFontFamily(const QString &fontFamily) noexcept {
  fontFamily_ = fontFamily;
}

void EditorSettings::setFontSize(int fontSize) noexcept {
  fontSize_ = fontSize;
}

void EditorSettings::merge(const EditorSettings &other) {
  if (other.fontFamily_)
    fontFamily_ = other.fontFamily_;

  if (other.fontSize_)
    fontSize_ = other.fontSize_;
}
