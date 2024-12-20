/**
 * @file MainWindow.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-22
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QJsonObject>
#include <QProcess>

QT_BEGIN_NAMESPACE
class QToolButton;
class QTimer;
class QSessionManager;
class QDockWidget;
QT_END_NAMESPACE

class Editor;
class OutputWidget;
class PreviewWidget;
class LSPClient;

/**
 * @brief main window
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  /**
   * @brief Construct a new Main Window object
   *
   * @param parent
   */
  explicit MainWindow(QWidget *parent = nullptr);

  /// @brief external functions for loading files in command line

  /**
   * @brief load file
   *
   * @param fileName file name
   */
  void loadFile(const QString &fileName);

public slots:
  /// @brief external functions for session management

  /**
   * @brief commit session
   *
   * @param manager session manager
   */
  void commitSession(QSessionManager &manager);

  /**
   * @brief create new file, default create `main.cpp` by @see newFileWithName
   *
   */
  void newFile();

  /**
   * @brief create new file with name
   *
   * @param fileName file name
   */
  void newFileWithName(const QString &fileName);

  void onNotify(QString method, QJsonObject param);
  void onResponse(QJsonObject id, QJsonObject response);
  void onRequest(QString method, QJsonObject param, QJsonObject id);
  void onError(QJsonObject id, QJsonObject error);
  void onServerError(QProcess::ProcessError error);
  void onServerFinished(int exitCode, QProcess::ExitStatus status);

  void textChanged();
  void requestDiagonistics();

private slots:
  /// @brief file menu

  /**
   * @brief open file
   *
   */
  void openFile();

  /**
   * @brief save file
   *
   * @return true successful
   * @return false failed
   */
  bool saveFile();

  /**
   * @brief save file as
   *
   * @return true successful
   * @return false failed
   */
  bool saveFileAs();

  /// @brief help menu

  /**
   * @brief show about dialog
   *
   */
  void showAbout();

  /**
   * @brief open docs
   *
   */
  void openDocs();

  /**
   * @brief show license
   *
   */
  void showLicense();

  /// @brief status bar

  /**
   * @brief go to line
   *
   */
  void gotoLine();

  /**
   * @brief cursor position changed slot
   *
   */
  void cursorPositionChanged();

private:
  /// @brief state data

  /**
   * @brief store current file name
   *
   */
  QString currentFileName_;

  /// @brief main editor

  /**
   * @brief main editor
   *
   */
  Editor *editor_;

  /// @brief output view

  /**
   * @brief output widget (editor)
   *
   */
  OutputWidget *output_;

  /**
   * @brief output dock
   *
   */
  QDockWidget *outputDock_;

  /// @brief preview view

  /**
   * @brief preview widget
   * TODO: support preview
   */
  PreviewWidget *preview_;

  /**
   * @brief preview dock
   *
   */
  QDockWidget *previewerDock_;

  /// @brief lsp client

  /**
   * @brief lsp client
   *
   */
  LSPClient *lsp_;

  /**
   * @brief Timer
   *
   */
  QTimer *timer_;

  /// @brief inner functions

  /**
   * @brief Set the Current File object
   *
   * @param fileName
   */
  void setCurrentFile(const QString &fileName);

  /**
   * @brief the status of the current file
   *
   * @return true should save
   * @return false don't need to save (not modified or saved)
   */
  bool maybeSave();

  /// @brief init functions

  /**
   * @brief setup ui
   *
   */
  void setupUi();

  /**
   * @brief setup actions, menu bar
   *
   */
  void setupActions();

  /**
   * @brief setup status bar
   *
   */
  void setupStatusBar();

  /**
   * @brief setup lsp client
   *
   */
  void setupLsp();

  /**
   * @brief connect signals
   *
   */
  void connectSignals();

  /**
   * @brief setup watchers
   *
   */
  void setupWatchers();

  /// @brief status bar button

  /**
   * @brief lsp status button
   *
   */
  QToolButton *lspStatusBtn_;

  /**
   * @brief build status button
   *
   */
  QToolButton *buildStatusBtn_;

  /**
   * @brief cursor position button, click to go to line @see gotoLine
   *
   */
  QToolButton *cursorPosBtn_;
};

#endif // MAINWINDOW_H
