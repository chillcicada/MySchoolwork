/**
 * @file EditorSettings.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-22
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef EDITOR_SETTINGS_H
#define EDITOR_SETTINGS_H

#include <QFont>
#include <QString>

#include <optional>

class EditorSettings {
  Q_GADGET

public:
  EditorSettings() = default;

  bool operator==(const EditorSettings &) const = default;

  QString fontFamily() const;
  int fontSize() const;
  QFont font() const;

  void setFontFamily(const QString &fontFamily) noexcept;
  void setFontSize(int fontSize) noexcept;

  void merge(const EditorSettings &other);

private:
  std::optional<QString> fontFamily_;
  std::optional<int> fontSize_;
};

#endif // EDITOR_SETTINGS_H
