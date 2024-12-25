---
theme: seriph
layout: cover
background: https://images.unsplash.com/photo-1621237023000-6a628c285938
export:
  format: pptx
exportFilename: 刘宽-Qode-v0.0.0
---

# Qode

一个简单的文本编辑器

<div class="text-sm tracking-widest">
探微书院 刘宽 liukuan22@mails.tsinghua.edu.cn
</div>

---
layout: intro
title: Outline
---

# 概述

仿 vscode 的文本编辑器，实现了基本的编辑功能和基础 lsp 功能。

## Table of Contents

- 主 ui
  - Actions
  - StatusBar
- lsp 与 lspClient
- 编辑器
- 其他

---
title: Introduction
---

# 基础功能实现

对 `QPlainTextEdit` 的探索。

```cpp
MainWindow(QWidget *parent) : QMainWindow(parent) {
  // 绘制 UI
  setupUi();

  // 绘制 Menu
  setupActions();

  // 绘制 StatusBar
  setupStatusBar();

  // 启动 Lsp
  setupLsp();

  // 连接信号槽
  connectSignals();

  // 启动 Watcher
  setupWatchers();
}
```

---

# UI

```cpp
void MainWindow::setupUi() {
  /// @brief config
  // ...
  auto centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  /// @brief main editor
  editor_ = new Editor(centralWidget);
  /// @brief previewer view
  preview_ = new PreviewWidget();
  previewerDock_ = new QDockWidget(tr("Previewer"), this);
  // ...
  addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, previewerDock_);
  /// @brief output view
  output_ = new OutputWidget();
  outputDock_ = new QDockWidget(tr("Output"), this);
  // ...
  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, outputDock_);
  /// @brief layout
  auto layout = new QVBoxLayout(centralWidget);
  // ...
  centralWidget->setLayout(layout);
  /// @brief 配置字体等
  // ...
}
```

---
title: image
layout: image
image: https://img.chillcicada.com/i/2024/12/23/6768eb892ec21.png
---

---
layout: image-right
image: https://img.chillcicada.com/i/2024/12/23/6768ed5b63407.png
backgroundSize: contain
---

# Actions

模块化管理

```cpp
void MainWindow::setupActions() {
  /**
   * @brief File Menu
   *
   */
  auto fileMenu = menuBar()->addMenu(tr("&File"));

  /// @brief New File Action
  auto newAct = fileMenu->addAction(
    tr("&New"), this, &MainWindow::newFile);
  newAct->setShortcut(QKeySequence::New);
  newAct->setMenuRole(QAction::NoRole);

  /// @brief separator
  fileMenu->addSeparator();

  // ...
}
```

---

# StatusBar

模块化管理

```cpp
void MainWindow::setupStatusBar() {
  /// @brief status bar config
  statusBar()->setSizeGripEnabled(false); // disable resize grip

  /// @brief Button provider
  auto BtnProvider = []() {/* ... */};

  /**
   * @brief cursor position
   *
   */
  cursorPosBtn_ = BtnProvider();
  connect(cursorPosBtn_, &QToolButton::clicked, this, &MainWindow::gotoLine);
  statusBar()->addPermanentWidget(cursorPosBtn_);

  statusBar()->showMessage(tr("Ready"), STAUTS_BAR_MSG_TIMEOUT_MS);
}
```

---

# Lsp

“积木式”层层构建 + 实现 json-string 的互相转换

结构拆解：

```cpp
struct CodeActionKind {
  std::vector<std::string> valueSet;
};
JSON_Convert_Declaration(CodeActionKind);

struct CodeActionLiteralSupport {
  CodeActionKind codeActionKind;
};
JSON_Convert_Declaration(CodeActionLiteralSupport);
```

json-string 转化实现：

```cpp
JSON_Convert_Definition(CodeActionKind, MAP_JSON(MAP_KEY(valueSet)), {});
JSON_Convert_Definition(CodeActionLiteralSupport, MAP_JSON(MAP_KEY(codeActionKind)), {});
```

---

# LspClient

继承自 `QProcess`，实现了与 lsp 通信方法和与编辑器通信方法。

与 lsp 通信：

```cpp
RequestID Initialize(option<DocumentUri> rootUri = {}) {
  InitializeParams params;
  // ...
  return SendRequest("initialize", params);
}
// ...
```

与编辑器通信（信号函数）：

```cpp
signals:
  void onNotify(QString method, QJsonObject param);
  void onResponse(QJsonObject id, QJsonObject response);
  void onRequest(QString method, QJsonObject param, QJsonObject id);
  void onError(QJsonObject id, QJsonObject error);
  void onServerError(QProcess::ProcessError error);
  void onServerFinished(int exitCode, QProcess::ExitStatus status);
  void newStderr(const QString &content);
  // ...
```

---

# 编辑器

单例模式：实现组件间模块化

```cpp
#include "EditorWidget.h"

class Editor : public QPlainTextEdit {
// ...
private:
  LineNumberGutter *lineNumberGutter_;

  EditorSettings *settings_;

  EditorHighlighter *highlighter_;

  // ...
};
```

---

# 其他

- 简单的文件系统
- output 模块，继承自 `QPlainTextEdit`，类似 vscode 的 Output
- Preview 模块，继承自 `QWebEngineView`，类似 vscode 的 WebView

```cpp
PreviewWidget(QWidget *parent) : QWebEngineView(parent) {
  setMinimumWidth(MINI_WIDTH);

  setUrl(QUrl("http://127.0.0.1:23625/"));
}
```

> 页面无法正常渲染，于是把需求搁置。

- 基于 nix，xmake 的可完整复现且快捷的构建系统
- justfile 作为脚本管理工具
- 全程使用 c++20 标准，clangd 和 clang-format 作为代码检查和格式化工具

---
layout: two-cols
---

# 总结

- 单例模式 => 实现组件间分离化
- 模块化管理 => 便于维护和扩展
- 使用 utest 和 qtest 测试，同时导出 snapshot 测试结果
- AI 对大型项目、复杂逻辑的理解有限，需要学会正确的提问

##  不足之处

- 应用功能更多直接调用 `QPlainTextEdit` 的接口，单独实现的功能较少
- 编辑器部分还尚不完善，例如智能缩进等功能
- lsp 和编辑器的完全绑定还未实现
- 一些功能和 bug 未能完全实现或解决
- 重复声明的问题

::right::

<br />

项目结构：

```txt
.
├── default.nix
├── docs
├── flake.lock
├── flake.nix
├── include
├── justfile
├── LICENSE
├── README.md
├── shell.nix
├── src
│   ├── core
│   ├── main.cpp
│   └── ui
├── tests
│   ├── mystl
│   └── mystl.snap
├── TODO.md
└── xmake.lua
```

---

# 探索：TextMate

TextMate 是 Apple 推出的编辑器，也是 vscode 使用的语法高亮工具，旨在把语法高亮、主题和编辑器分离。

两种文件格式：

- plist：XML 格式
- JSON：JSON 格式

两种模式：

- tmLanguage：提供具体的语法信息
- tmTheme：提供具体的颜色信息

难点：

1. 没有现成的 cpp 实现
2. 涉及到文本的序列化和反序列化，以及块级匹配和正则匹配

---
layout: end
title: Thanks
---

# Thanks For Watching! <br /><h2>感谢观看，欢迎指正</h2>

2024/12/23
