/**
 * @file EditorWidget.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-02
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef EDITOR_WIDGET_H
#define EDITOR_WIDGET_H

#include "Editor.h"

const auto HoverTimerInterval = 1000;

/// @brief line number gutter
class LineNumberGutter : public QWidget {
public:
  explicit LineNumberGutter(Editor *editor)
      : QWidget(editor), editor_(editor) {}

  QSize sizeHint() const override {
    return QSize(editor_->lineNumberGutterWidth(), 0);
  }

protected:
  void paintEvent(QPaintEvent *event) override {
    editor_->paintLineNumberGutter(event);
  }

private:
  Editor *editor_;
};

/// @brief fold region gutter
class FoldRegionGutter : public QWidget {
public:
  explicit FoldRegionGutter(Editor *editor)
      : QWidget(editor), editor_(editor) {}

  // TODO: implement this class

protected:
private:
  Editor *editor_;
};

/// @brief debounce
class DebounceTimer : public QTimer {
public:
  explicit DebounceTimer(Editor *editor) : QTimer(editor), editor_(editor) {}

  // TODO: implement this class

protected:
private:
  Editor *editor_;
};

/// @brief hover timer
class HoverTimer : public QTimer {
public:
  explicit HoverTimer(Editor *editor) : QTimer(editor), editor_(editor) {
    setInterval(HoverTimerInterval);
  }

protected:
private:
  Editor *editor_;
};

#endif // EDITOR_WIDGET_H
