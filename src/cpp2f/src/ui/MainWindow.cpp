/**
 * @file MainWindow.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-22
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "MainWindow.h"

#include "Editor.h"
#include "EditorUtils.h"
#include "LspClient.h"
#include "OutputWidget.h"
#include "PreviewWidget.h"

#include <QDesktopServices>
#include <QDockWidget>
#include <QFileDialog>
#include <QFont>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolButton>
#include <QVBoxLayout>

const auto SCREEN_DEFAULT_OPACITY = 0.95;

const auto SCREEN_DEFAULT_WIDTH = 1920;
const auto SCREEN_DEFAULT_HEIGHT = 1080;

const auto SCREEN_MIN_WIDTH = 680;
const auto SCREEN_MIN_HEIGHT = 480;

const auto STAUTS_BAR_MSG_TIMEOUT_MS = 2000;

const auto DEFAULT_FONTS =
    "MesloLGL Nerd Font Mono, LXGW WenKai Mono, Monospace";
const auto DEFAULT_FONT_SIZE = 12;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setupUi();
  setupActions();
  setupStatusBar();
  setupLsp();
  connectSignals();
  setupWatchers();
}

/**
 * @brief init function
 *
 */

/// @brief setup ui
void MainWindow::setupUi() {
  setWindowTitle(tr("%1[*]").arg(QCoreApplication::applicationName()));
  setWindowOpacity(SCREEN_DEFAULT_OPACITY);
  resize(SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT);
  setMinimumSize(SCREEN_MIN_WIDTH, SCREEN_MIN_HEIGHT);
  setDockOptions(QMainWindow::AnimatedDocks);

  auto centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  /// @brief main editor
  editor_ = new Editor(centralWidget);
  editor_->setFocus();

  /// @brief previewer view
  preview_ = new PreviewWidget();

  previewerDock_ = new QDockWidget(tr("Previewer"), this);
  previewerDock_->setObjectName("PreviewerDock");
  previewerDock_->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea |
                                  Qt::DockWidgetArea::RightDockWidgetArea);
  previewerDock_->setWidget(preview_);

  addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, previewerDock_);

  /// @brief output view
  output_ = new OutputWidget();

  outputDock_ = new QDockWidget(tr("Output"), this);
  outputDock_->setObjectName("OutputDock");
  outputDock_->setAllowedAreas(Qt::DockWidgetArea::BottomDockWidgetArea);
  outputDock_->setWidget(output_);

  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, outputDock_);

  /// @brief layout
  auto layout = new QVBoxLayout(centralWidget);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->setStretch(0, 1);
  layout->addWidget(editor_);
  centralWidget->setLayout(layout);

  /// @brief misc
  QFont font(DEFAULT_FONTS, DEFAULT_FONT_SIZE);
  font.setStyleHint(QFont::StyleHint::SansSerif);
  editor_->setFont(font);
  output_->setFont(font);
}

/// @brief setup actions
void MainWindow::setupActions() {
  /**
   * @brief File Menu
   *
   */
  auto fileMenu = menuBar()->addMenu(tr("&File"));

  /// @brief New File Action
  auto newAct = fileMenu->addAction(tr("&New"), this, &MainWindow::newFile);
  newAct->setShortcut(QKeySequence::New);
  newAct->setMenuRole(QAction::NoRole);

  /// @brief separator
  fileMenu->addSeparator();

  /// @brief Open File Action
  auto openAct =
      fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile);
  openAct->setShortcut(QKeySequence::Open);
  openAct->setMenuRole(QAction::NoRole);

  /// @brief separator
  fileMenu->addSeparator();

  /// @brief Save File Action
  auto saveAct = fileMenu->addAction(tr("&Save"), this, &MainWindow::saveFile);
  saveAct->setShortcut(QKeySequence::Save);
  saveAct->setMenuRole(QAction::NoRole);

  /// @brief Save As Action
  auto saveAsAct =
      fileMenu->addAction(tr("Save &As..."), this, &MainWindow::saveFileAs);
  saveAsAct->setShortcut(QKeySequence::SaveAs);
  saveAsAct->setMenuRole(QAction::NoRole);

  /// @brief separator
  fileMenu->addSeparator();

  /// @brief Exit Action
  auto exitAct = fileMenu->addAction(tr("E&xit"), this, &QMainWindow::close);
  exitAct->setShortcut(QKeySequence::Quit);
  exitAct->setMenuRole(QAction::QuitRole);

  /**
   * @brief Edit Menu
   *
   */
  auto editMenu = menuBar()->addMenu(tr("&Edit"));

  /// @brief Undo Action
  auto undoAct = editMenu->addAction(tr("&Undo"), editor_, &Editor::undo);
  undoAct->setShortcut(QKeySequence::Undo);
  undoAct->setMenuRole(QAction::NoRole);
  undoAct->setEnabled(false);
  connect(editor_, &Editor::undoAvailable, undoAct, &QAction::setEnabled);

  /// @brief Redo Action
  auto redoAct = editMenu->addAction(tr("&Redo"), editor_, &Editor::redo);
  redoAct->setShortcut(QKeySequence::Redo);
  redoAct->setMenuRole(QAction::NoRole);
  redoAct->setEnabled(false);
  connect(editor_, &Editor::redoAvailable, redoAct, &QAction::setEnabled);

  /// @brief separator
  editMenu->addSeparator();

  /// @brief Select All Action
  auto selectAllAct =
      editMenu->addAction(tr("Select &All"), editor_, &Editor::selectAll);
  selectAllAct->setShortcut(QKeySequence::SelectAll);
  selectAllAct->setMenuRole(QAction::NoRole);

  /// @brief Cut Action
  auto cutAct = editMenu->addAction(tr("Cu&t"), editor_, &Editor::cut);
  cutAct->setShortcut(QKeySequence::Cut);
  cutAct->setMenuRole(QAction::NoRole);
  cutAct->setEnabled(false);
  connect(editor_, &Editor::copyAvailable, cutAct, &QAction::setEnabled);

  /// @brief Copy Action
  auto copyAct = editMenu->addAction(tr("&Copy"), editor_, &Editor::copy);
  copyAct->setShortcut(QKeySequence::Copy);
  copyAct->setMenuRole(QAction::NoRole);
  copyAct->setEnabled(false);
  connect(editor_, &Editor::copyAvailable, copyAct, &QAction::setEnabled);

  /// @brief Paste Action
  auto pasteAct = editMenu->addAction(tr("&Paste"), editor_, &Editor::paste);
  pasteAct->setShortcut(QKeySequence::Paste);
  pasteAct->setMenuRole(QAction::NoRole);
  connect(editor_, &Editor::copyAvailable, pasteAct, &QAction::setEnabled);

  /// @brief separator
  editMenu->addSeparator();

  /**
   * @brief View Menu
   *
   */
  auto viewMenu = menuBar()->addMenu(tr("&View"));

  /// @brief Output Action
  auto outputAct =
      viewMenu->addAction(tr("&Output"), output_, &OutputWidget::setVisible);
  outputAct->setMenuRole(QAction::NoRole);

  /// @brief Previewer Action
  auto previewerAct = viewMenu->addAction(tr("&Previewer"), preview_,
                                          &PreviewWidget::setVisible);
  previewerAct->setMenuRole(QAction::NoRole);

  /// @brief separator
  viewMenu->addSeparator();

  /// @brief Zoom In Action
  auto zoomInAct =
      viewMenu->addAction(tr("Zoom &In"), editor_, &Editor::zoomIn);
  zoomInAct->setShortcut(QKeySequence::ZoomIn);
  zoomInAct->setMenuRole(QAction::NoRole);

  /// @brief Zoom Out Action
  auto zoomOutAct =
      viewMenu->addAction(tr("Zoom &Out"), editor_, &Editor::zoomOut);
  zoomOutAct->setShortcut(QKeySequence::ZoomOut);
  zoomOutAct->setMenuRole(QAction::NoRole);

  auto zoomResetAct =
      viewMenu->addAction(tr("Zoom &Reset"), editor_, &Editor::zoomReset);
  zoomResetAct->setMenuRole(QAction::NoRole);

  /**
   * @brief Tool Menu
   *
   */
  auto toolMenu = menuBar()->addMenu(tr("&Tool"));

  /// @brief Export Action
  auto exportAct = toolMenu->addAction(tr("&Export"));
  exportAct->setMenuRole(QAction::NoRole);

  /// @brief Export As Action
  auto exportAsAct = toolMenu->addAction(tr("Export &As..."));
  exportAsAct->setMenuRole(QAction::NoRole);

  /**
   * @brief Help Menu
   *
   */
  auto helpMenu = menuBar()->addMenu(tr("&Help"));

  /// @brief Show Docs
  auto docsAct = helpMenu->addAction(tr("&Docs"), this, &MainWindow::openDocs);
  docsAct->setMenuRole(QAction::NoRole);

  /// @brief Show License
  auto licenseAct =
      helpMenu->addAction(tr("&License"), this, &MainWindow::showLicense);

  /// @brief separator
  helpMenu->addSeparator();

  /// @brief About Action
  auto aboutAct =
      helpMenu->addAction(tr("&About"), this, &MainWindow::showAbout);
  aboutAct->setMenuRole(QAction::AboutRole);

  /**
   * @brief Undo/Redo Button
   *
   */
  auto undoBtn = menuBar()->addAction(tr("←"), editor_, &Editor::undo);
  undoBtn->setEnabled(false);
  undoBtn->setMenuRole(QAction::NoRole);
  connect(editor_, &Editor::undoAvailable, undoBtn, &QAction::setEnabled);

  auto redoBtn = menuBar()->addAction(tr("→"), editor_, &Editor::redo);
  redoBtn->setEnabled(false);
  redoBtn->setMenuRole(QAction::NoRole);
  connect(editor_, &Editor::redoAvailable, redoBtn, &QAction::setEnabled);
}

/// @brief setup status bar
void MainWindow::setupStatusBar() {
  /// @brief status bar config
  statusBar()->setSizeGripEnabled(false); // disable resize grip

  /// @brief Button provider
  auto BtnProvider = []() {
    auto btn = new QToolButton();
    btn->setAutoRaise(true);
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn->setMaximumHeight(18);
    return btn;
  };

  /**
   * @brief lsp status
   *
   */
  lspStatusBtn_ = BtnProvider();
  // connect
  statusBar()->addPermanentWidget(lspStatusBtn_);

  /**
   * @brief build status
   *
   */
  buildStatusBtn_ = BtnProvider();
  // connect
  statusBar()->addPermanentWidget(buildStatusBtn_);

  /**
   * @brief cursor position
   *
   */
  cursorPosBtn_ = BtnProvider();
  connect(cursorPosBtn_, &QToolButton::clicked, this, &MainWindow::gotoLine);
  statusBar()->addPermanentWidget(cursorPosBtn_);

  statusBar()->showMessage(tr("Ready"), STAUTS_BAR_MSG_TIMEOUT_MS);
}

/// @brief setup lsp client
void MainWindow::setupLsp() {
  timer_ = new QTimer(this);
  timer_->setInterval(500);
  timer_->start();
  timer_->setSingleShot(true);

  QString lspProgram = "clangd";
  lsp_ = new LSPClient(lspProgram, QStringList(), this);

  lsp_->Initialize();
  lsp_->Initialized();
  lsp_->DidOpen(util::uriForFile(currentFileName_).str(), "", "cpp");
}

/// @brief connect signals
void MainWindow::connectSignals() {
  connect(editor_, &Editor::cursorPositionChanged, this,
          &MainWindow::cursorPositionChanged);
  connect(editor_, &Editor::textChanged, this, &MainWindow::textChanged);

  connect(lsp_, &LSPClient::newStderr, output_, &OutputWidget::appendPlainText);
  connect(timer_, &QTimer::timeout, this, &MainWindow::requestDiagonistics);
  connect(lsp_, &LSPClient::onError, this, &MainWindow::onError);
  connect(lsp_, &LSPClient::onNotify, this, &MainWindow::onNotify);
  connect(lsp_, &LSPClient::onResponse, this, &MainWindow::onResponse);
  connect(lsp_, &LSPClient::onRequest, this, &MainWindow::onRequest);
  connect(lsp_, &LSPClient::onServerError, this, &MainWindow::onServerError);
  connect(lsp_, &LSPClient::onServerFinished, this,
          &MainWindow::onServerFinished);
}

/// @brief setup watchers
void MainWindow::setupWatchers() { cursorPositionChanged(); }

/**
 * @brief public
 *
 */

void MainWindow::loadFile(const QString &fileName) {
  QFile file(fileName);

  if (!file.exists())
    newFileWithName(fileName);

  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(
        this, tr("Open File"),
        tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
    return;
  }

  QTextStream in(&file);
  editor_->setPlainText(in.readAll());

  file.close();

  setCurrentFile(fileName);

  statusBar()->showMessage(tr("Loaded %1").arg(util::formatFilePath(fileName)),
                           STAUTS_BAR_MSG_TIMEOUT_MS);
}

/**
 * @brief public slots
 *
 */

// TODO
void MainWindow::commitSession(QSessionManager &manager) {
  qDebug() << "commit session";
}

void MainWindow::newFile() { newFileWithName("main.cpp"); }

void MainWindow::newFileWithName(const QString &fileName) {
  editor_->clear();
  setCurrentFile(fileName);
}

void MainWindow::onNotify(QString method, QJsonObject param) {
  qDebug() << "notify" << method << param;
}

void MainWindow::onError(QJsonObject id, QJsonObject error) {
  qDebug() << "error" << id << error;
}

void MainWindow::onResponse(QJsonObject id, QJsonObject response) {
  qDebug() << "response" << id << response;
}

void MainWindow::onRequest(QString method, QJsonObject param, QJsonObject id) {
  qDebug() << "request";
}

void MainWindow::onServerError(QProcess::ProcessError error) {
  qDebug() << "server error" << error;
}

void MainWindow::onServerFinished(int exitCode, QProcess::ExitStatus status) {
  qDebug() << "server finished" << exitCode << status;
}

void MainWindow::textChanged() {
  statusBar()->showMessage(tr("Modified"), STAUTS_BAR_MSG_TIMEOUT_MS);

  auto cursor = editor_->textCursor();

  auto pos = cursor.position();

  // lsp_->Completion(
  //     "file:///"
  //     "D:\\Desktop\\Projects\\qode\\build\\windows\\x64\\release\\main.cpp",
  //     )
}

void MainWindow::requestDiagonistics() {
  std::vector<TextDocumentContentChangeEvent> ch;
  TextDocumentContentChangeEvent ev;
  ev.text = editor_->toPlainText().toStdString();
  ch.push_back(ev);
  lsp_->DidChange(util::uriForFile(currentFileName_).str(), ch, true);
}

/**
 * @brief private slots
 *
 */

/// @brief file menu

void MainWindow::openFile() {
  QFileDialog dlg(this, tr("Open Document"));
  dlg.setAcceptMode(QFileDialog::AcceptOpen);
  dlg.setNameFilter(tr("C Plus Plus files (*.cpp)"));

  if (dlg.exec() == QDialog::Accepted) {
    auto files = dlg.selectedFiles();
    if (files.size() == 1) {
      loadFile(files[0]);
    }
  }
}

bool MainWindow::saveFile() {
  QFile file(currentFileName_);

  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("Save File"),
                         tr("Cannot write file %1:\n%2.")
                             .arg(currentFileName_)
                             .arg(file.errorString()));
    return false;
  }

  QTextStream out(&file);
  out << editor_->toPlainText();

  file.close();

  return true;
};

bool MainWindow::saveFileAs() {
  QFileDialog dlg(this, tr("Save Document"));
  dlg.setAcceptMode(QFileDialog::AcceptSave);
  dlg.setNameFilter(tr("C Plus Plus files (*.cpp)"));
  dlg.setDefaultSuffix("cpp");

  if (dlg.exec() == QDialog::Accepted) {
    auto files = dlg.selectedFiles();
    if (files.size() == 1) {
      setCurrentFile(files[0]);
      return saveFile();
    }
  }

  return false;
};

/// @brief tool menu

/// @brief help menu

void MainWindow::showAbout() {
  auto text = tr("<h1>Qode</h1>"
                 "<p>Qode is a simple source editor based on Qt.</p>"
                 "<p>Version %1 (Qt %2)</p>")
                  .arg(QCoreApplication::applicationVersion(), QT_VERSION_STR);

  QMessageBox dlg(QMessageBox::Information, tr("About Qode"), text,
                  QMessageBox::Ok, this);

  dlg.exec();
}

void MainWindow::openDocs() {
  QDesktopServices::openUrl(QUrl("https://zh.cppreference.com/w/首页"));
}

void MainWindow::showLicense() {
  auto text =
      tr("<h1>License</h1>"
         "<p>Qode is licensed under the <a href=\"%1\">GPLv3</a>.</p>"
         "<p>Source code is available at "
         "<a href=\"%2\">github</a>.</p>")
          /// FIXME: release to github
          .arg(QLatin1String("https://www.gnu.org/licenses/gpl-3.0.en.html"),
               QLatin1String("https://git.tsinghua.edu.cn/liukuan22/qode"));

  QMessageBox dlg(QMessageBox::Information, tr("License"), text,
                  QMessageBox::Ok, this);

  dlg.exec();
}

/// @brief status bar
void MainWindow::gotoLine() {
  auto blockCount = editor_->document()->blockCount();

  // set flag
  bool ok;

  /// FIXME: add column support
  int line = QInputDialog::getInt(
      this, tr("Go to Line"),
      tr("Enter a line number (max %1)").arg(blockCount),
      editor_->textCursor().blockNumber() + 1, 1, blockCount, 1, &ok);

  if (ok) {
    editor_->goToBlock(line - 1, 0);
  }
}

void MainWindow::cursorPositionChanged() {
  auto cursor = editor_->textCursor();
  auto line = cursor.blockNumber() + 1;
  auto column = cursor.columnNumber();

  cursorPosBtn_->setText(tr("Ln %1, Col %2").arg(line).arg(column));

  lsp_->Hover(util::uriForFile(currentFileName_).str(), {line, column});

  lsp_->Completion(util::uriForFile(currentFileName_).str(), {line, column});
}

/**
 * @brief inner functions
 *
 */

void MainWindow::setCurrentFile(const QString &fileName) {
  currentFileName_ = fileName;

  qDebug() << "current file" << currentFileName_;
  setWindowFilePath(currentFileName_);
  setWindowTitle(
      tr("%1 - %2").arg(QCoreApplication::applicationName()).arg(fileName));
}

bool MainWindow::maybeSave() {
  if (editor_->document()->isModified()) {
    auto ret = QMessageBox::warning(this, tr("Save Document"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save | QMessageBox::Discard |
                                        QMessageBox::Cancel);

    if (ret == QMessageBox::Save) {
      return saveFile();
    } else if (ret == QMessageBox::Cancel) {
      return false;
    }
  }

  return true;
}
