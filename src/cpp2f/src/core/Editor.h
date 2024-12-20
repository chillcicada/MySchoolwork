/**
 * @file Editor.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-29
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QPointer>
#include <QTimer>
#include <QWidget>

class EditorSettings;

class LineNumberGutter;
class FoldRegionGutter;
class DebounceTimer;
class HoverTimer;

class EditorHighlighter;

/**
 * @brief Main editor widget
 *
 */
class Editor : public QPlainTextEdit {
  Q_OBJECT

public:
  Editor(QWidget *parent = nullptr);

  /// @brief line number gutter
  void paintLineNumberGutter(QPaintEvent *event);
  int lineNumberGutterWidth() const;

  /// @brief fold region gutter

public slots:
  void goToBlock(int blockNum, int charOffset);
  void onCursorPositionChanged();
  void zoomReset();

protected:
  /// @brief built-in event handlers
  void resizeEvent(QResizeEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void contextMenuEvent(QContextMenuEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void focusInEvent(QFocusEvent *event) override;
  void focusOutEvent(QFocusEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

  /// @brief custom event handlers
  // void settingChanged(EditorSettings setting);

private slots:
  /// @brief line number gutter
  void updateLineNumberGutterWidth(int newBlockCount);
  void updateLineNumberGutter(const QRect &rect, int dy);

  /// @brief highlight current line
  void highlightCurrentLine();

  /// @brief debounce
  void debounce();

private:
  /**
   * @brief line number gutter
   *
   */
  LineNumberGutter *lineNumberGutter_;

  /**
   * @brief fold region gutter
   *
   */
  FoldRegionGutter *foldRegionGutter_;

  /**
   * @brief debounce timer
   *
   */
  DebounceTimer *debounceTimer_;

  /**
   * @brief hover timer
   *
   */
  HoverTimer *hoverTimer_;

  /**
   * @brief editor settings
   *
   */
  EditorSettings *settings_;

  /**
   * @brief highlighter
   *
   */
  EditorHighlighter *highlighter_;

  /// @brief misc
  bool handleKey(Qt::Key key);
  void handleKeyWithModifier(Qt::KeyboardModifiers modifier, Qt::Key key);
  void handleKeyWithCTRL(Qt::Key key);

  void updateIndentation();

  void commentLine();
  void commentBlock();
};

#endif // EDITOR_H
