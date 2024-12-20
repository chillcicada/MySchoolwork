/**
 * @file Editor.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-02
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "Editor.h"
#include "EditorHighlighter.h"
#include "EditorWidget.h"
#include "qobject.h"

#include <QPainter>
#include <QRegularExpression>
#include <QScrollBar>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocumentFragment>

const auto LineNumberGutterPadding = 15;
const auto HighlightedLineColor = QColor(255, 255, 255, 50);

const auto DebounceInterval = 500; // ms

const auto EditorMiniWidth = 360;

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent) {
  lineNumberGutter_ = new LineNumberGutter(this);
  foldRegionGutter_ = new FoldRegionGutter(this);
  debounceTimer_ = new DebounceTimer(this);
  hoverTimer_ = new HoverTimer(this);

  /// @brief basic settings
  setMouseTracking(true);
  setMinimumWidth(EditorMiniWidth);

  highlighter_ = new EditorHighlighter(document());

  /**
   * @brief connect signals
   *
   */

  /// @brief line number gutter
  connect(this, &Editor::blockCountChanged, this,
          &Editor::updateLineNumberGutterWidth);
  connect(this, &Editor::updateRequest, this, &Editor::updateLineNumberGutter);
  connect(this, &Editor::cursorPositionChanged, this,
          &Editor::highlightCurrentLine);

  /**
   * @brief initialize
   *
   */

  /// @brief line number gutter
  updateLineNumberGutterWidth(0);
  highlightCurrentLine();
}

/**
 * @brief Public
 *
 */

/// @brief line number gutter
void Editor::paintLineNumberGutter(QPaintEvent *event) {
  QPainter painter(lineNumberGutter_);

  auto block = firstVisibleBlock();
  auto blockNumber = block.blockNumber();
  auto top = static_cast<int>(
      blockBoundingGeometry(block).translated(contentOffset()).top());
  auto bottom = top + static_cast<int>(blockBoundingRect(block).height());

  while (block.isValid() && top <= event->rect().bottom()) {
    if (block.isVisible() && bottom >= event->rect().top()) {
      auto number = QString::number(blockNumber + 1);
      /// FIXME: set color
      painter.setPen(Qt::lightGray);
      painter.drawText(0, top,
                       lineNumberGutter_->width() - LineNumberGutterPadding,
                       fontMetrics().height(), Qt::AlignRight, number);
    }

    block = block.next();
    top = bottom;
    bottom = top + static_cast<int>(blockBoundingRect(block).height());
    ++blockNumber;
  }

  painter.end();
}

/// @brief line number gutter
int Editor::lineNumberGutterWidth() const {
  auto digits = 1; // default
  auto max = qMax(1, blockCount());
  while (max >= 10) {
    max /= 10;
    ++digits;
  }

  // minimum width
  if (digits < 3) {
    digits = 3;
  }

  auto space = 35 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

  return space;
}

/**
 * @brief Public slots
 *
 */

void Editor::goToBlock(int blockNum, int charOffset) {
  QTextCursor cursor = textCursor();
  cursor.setPosition(document()->findBlockByNumber(blockNum).position() +
                     charOffset);
  setTextCursor(cursor);
}

void Editor::onCursorPositionChanged() {}

void Editor::zoomReset() {
  auto font = this->font();
  font.setPointSize(12); // DEFAULT_FONT_SIZE
  setFont(font);
}

/**
 * @brief Protected
 *
 */
void Editor::resizeEvent(QResizeEvent *event) {
  QPlainTextEdit::resizeEvent(event);

  QRect cr = contentsRect();
  lineNumberGutter_->setGeometry(
      QRect(cr.left(), cr.top(), lineNumberGutterWidth(), cr.height()));
}

void Editor::keyPressEvent(QKeyEvent *event) {
  auto modifier = event->modifiers();
  auto key = Qt::Key(event->key());

  auto flag = false;

  if (modifier) {
    handleKeyWithModifier(modifier, key);
  }

  if (key) {
    flag = handleKey(key);
  }

  if (!flag) {
    QPlainTextEdit::keyPressEvent(event);
  }
}

void Editor::wheelEvent(QWheelEvent *event) {
  auto delta = event->angleDelta();
  auto keyModifiers = event->modifiers();

  switch (keyModifiers) {
  case Qt::KeyboardModifier::ControlModifier: {
    if (delta.y() > 0) {
      zoomIn(2);
    } else {
      zoomOut(2);
    }
    break;
  }
  default:
    break;
  } // switch

  QPlainTextEdit::wheelEvent(event);
}

void Editor::contextMenuEvent(QContextMenuEvent *event) {
  QPlainTextEdit::contextMenuEvent(event);
}

void Editor::mousePressEvent(QMouseEvent *event) {
  QPlainTextEdit::mousePressEvent(event);
}

void Editor::mouseMoveEvent(QMouseEvent *event) {
  QPlainTextEdit::mouseMoveEvent(event);
}

void Editor::mouseReleaseEvent(QMouseEvent *event) {
  QPlainTextEdit::mouseReleaseEvent(event);
}

void Editor::focusInEvent(QFocusEvent *event) {
  QPlainTextEdit::focusInEvent(event);
}

void Editor::focusOutEvent(QFocusEvent *event) {
  QPlainTextEdit::focusOutEvent(event);
}

void Editor::paintEvent(QPaintEvent *event) {
  QPlainTextEdit::paintEvent(event);

  lineNumberGutter_->update();
}

// void Editor::settingChanged(EditorSettings setting) {}

/**
 * @brief Private slots
 *
 */

/// @brief line number gutter
void Editor::updateLineNumberGutterWidth(int /* newBlockCount */) {
  setViewportMargins(lineNumberGutterWidth(), 0, 0, 0);
}

/// @brief line number gutter
void Editor::updateLineNumberGutter(const QRect &rect, int dy) {
  if (dy) {
    lineNumberGutter_->scroll(0, dy);
  } else {
    lineNumberGutter_->update(0, rect.y(), lineNumberGutter_->width(),
                              rect.height());
  }

  if (rect.contains(viewport()->rect())) {
    updateLineNumberGutterWidth(0);
  }
}

/// @brief highlight current line
void Editor::highlightCurrentLine() {
  QList<QTextEdit::ExtraSelection> extraSelections;

  if (!isReadOnly()) {
    QTextEdit::ExtraSelection selection;

    QColor lineColor = HighlightedLineColor;
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);
  }

  setExtraSelections(extraSelections);
}

/// @brief debounce
void Editor::debounce() {
  // TODO: debounce
}

/**
 * @brief Private
 *
 */

/// @brief misc
bool Editor::handleKey(Qt::Key key) {
  auto flag = false;

  auto getNextChar = [this](int offset = 1) {
    auto cursor = textCursor();
    cursor.movePosition(QTextCursor::MoveOperation::Right,
                        QTextCursor::MoveMode::KeepAnchor, offset);
    return cursor.selectedText();
  };

  switch (key) {
  case Qt::Key::Key_ParenLeft: {
    insertPlainText(")");
    moveCursor(QTextCursor::MoveOperation::PreviousCharacter);
    break;
  }
  case Qt::Key::Key_ParenRight: {
    auto nextChar = getNextChar();
    if (nextChar == ")") {
      moveCursor(QTextCursor::MoveOperation::Right);
      flag = true;
    }
    break;
  }
  case Qt::Key::Key_QuoteDbl: {
    insertPlainText("\"");
    moveCursor(QTextCursor::MoveOperation::PreviousCharacter);
    break;
  }
  case Qt::Key::Key_Apostrophe: {
    insertPlainText("'");
    moveCursor(QTextCursor::MoveOperation::PreviousCharacter);
    break;
  }
  case Qt::Key::Key_BraceLeft: {
    insertPlainText("}");
    moveCursor(QTextCursor::MoveOperation::PreviousCharacter);
    break;
  }
  case Qt::Key::Key_BraceRight: {
    auto nextChar = getNextChar();
    if (nextChar == "}") {
      moveCursor(QTextCursor::MoveOperation::Right);
      flag = true;
    }
    break;
  }
  case Qt::Key::Key_BracketLeft: {
    insertPlainText("]");
    moveCursor(QTextCursor::MoveOperation::PreviousCharacter);
    break;
  }
  case Qt::Key::Key_BracketRight: {
    auto nextChar = getNextChar();
    if (nextChar == "]") {
      moveCursor(QTextCursor::MoveOperation::Right);
      flag = true;
    }
    break;
  }
  case Qt::Key::Key_Tab: {
    insertPlainText("  ");
    flag = true;
    break;
  }
  case Qt::Key::Key_Return: {
    // updateIndentation();
    break;
  }
  default:
    break;
  } // switch

  return flag;
}

void Editor::handleKeyWithModifier(Qt::KeyboardModifiers modifier,
                                   Qt::Key key) {
  switch (modifier) {
  case Qt::KeyboardModifier::ControlModifier: {
    handleKeyWithCTRL(key);
    break;
  }
  default:
    break;
  } // switch
}

void Editor::handleKeyWithCTRL(Qt::Key key) {
  switch (key) {
  case Qt::Key::Key_Slash: {
    commentBlock();
    break;
  }
  default:
    break;
  } // switch
}

void Editor::updateIndentation() {
  auto cursor = textCursor();
  auto block = cursor.block();
  auto text = block.text();

  QRegularExpression leadingSpacesRegex("^\\s*");
  QRegularExpression trailingSpacesRegex("\\s*$");

  auto leadingSpacesMatch = leadingSpacesRegex.match(text);
  auto trailingSpacesMatch = trailingSpacesRegex.match(text);

  auto leadingSpaces = leadingSpacesMatch.captured(0);
  auto trailingSpaces = trailingSpacesMatch.captured(0);

  auto indent = QString();
  for (auto i = 0; i < leadingSpaces.size(); ++i) {
    if (leadingSpaces[i] == ' ') {
      indent += ' ';
    } else {
      break;
    }
  }

  auto cursorPosition = cursor.positionInBlock();
  auto cursorLine = cursor.blockNumber();
  auto cursorColumn = cursorPosition - indent.size();

  if (cursorColumn == 0) {
    return;
  }

  auto previousBlock = block.previous();
  auto previousText = previousBlock.text();
  auto previousLeadingSpacesMatch = leadingSpacesRegex.match(previousText);
  auto previousLeadingSpaces = previousLeadingSpacesMatch.captured(0);

  if (previousLeadingSpaces.size() < indent.size()) {
    return;
  }

  auto previousIndent = QString();
  for (auto i = 0; i < previousLeadingSpaces.size(); ++i) {
    if (previousLeadingSpaces[i] == ' ') {
      previousIndent += ' ';
    } else {
      break;
    }
  }

  if (previousIndent.size() < indent.size()) {
    return;
  }

  auto previousCursor = cursor;
  previousCursor.movePosition(QTextCursor::MoveOperation::PreviousBlock);
  previousCursor.movePosition(QTextCursor::MoveOperation::EndOfBlock);

  auto previousCursorLine = previousCursor.blockNumber();
  auto previousCursorColumn = previousCursor.positionInBlock();

  if (previousCursorLine == cursorLine) {
    return;
  }

  auto spaces = QString();
  for (auto i = 0; i < previousCursorColumn; ++i) {
    spaces += ' ';
  }

  cursor.insertText(spaces);
}

void Editor::commentLine() {
  auto cursor = textCursor();
  auto block = cursor.block();
  auto text = block.text();

  if (text.isEmpty()) {
    return;
  }

  // typst comment style
  QString commentChars = "// ";

  if (text.trimmed().startsWith(commentChars)) {
    // Uncomment the line
    text.remove(0, commentChars.length());
  } else {
    // Comment the line
    text.insert(0, commentChars);
  }

  cursor.select(QTextCursor::LineUnderCursor);
  cursor.insertText(text);
}

void Editor::commentBlock() {
  auto cursor = textCursor();
  if (cursor.hasSelection()) {
    auto start = cursor.selectionStart();
    auto end = cursor.selectionEnd();

    cursor.setPosition(start);
    auto startBlock = cursor.block();
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    auto endBlock = cursor.block();

    auto startBlockNumber = startBlock.blockNumber();
    auto endBlockNumber = endBlock.blockNumber();

    QString commentChars = "// ";

    cursor.setPosition(startBlock.position());
    cursor.movePosition(QTextCursor::MoveOperation::StartOfBlock);

    // check if the block is already commented
    auto text = cursor.block().text();
    if (text.trimmed().startsWith(commentChars)) {
      // Uncomment the block
      for (auto i = startBlockNumber; i <= endBlockNumber; ++i) {
        cursor.movePosition(QTextCursor::MoveOperation::StartOfBlock);
        cursor.movePosition(QTextCursor::MoveOperation::Right,
                            QTextCursor::MoveMode::KeepAnchor,
                            commentChars.length());
        cursor.removeSelectedText();
        cursor.movePosition(QTextCursor::MoveOperation::EndOfBlock);
        cursor.movePosition(QTextCursor::MoveOperation::NextBlock);
      }
      return;
    }

    for (auto i = startBlockNumber; i <= endBlockNumber; ++i) {
      cursor.movePosition(QTextCursor::MoveOperation::StartOfBlock);
      cursor.insertText(commentChars);
      cursor.movePosition(QTextCursor::MoveOperation::EndOfBlock);
      cursor.movePosition(QTextCursor::MoveOperation::NextBlock);
    }
  } else {
    commentLine();
  }
}
