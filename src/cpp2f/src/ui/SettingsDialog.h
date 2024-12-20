/**
 * @file SettingsDialog.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-20
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include "EditorSettings.h"

#include <QDialog>

class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = nullptr) {
    setWindowTitle(tr("Settings"));
  };

  void setSettings(const EditorSettings &settings);
  EditorSettings settings() const;
};

#endif // SETTINGS_DIALOG_H
