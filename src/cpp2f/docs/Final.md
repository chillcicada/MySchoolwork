# Qode

<center>刘宽 探微-分21 2022013189</center>

仓库地址：<https://git.tsinghua.edu.cn/liukuan22/qode>

## 主要功能

- 基本的源代码编辑功能
  - 撤销、重做，剪切、粘贴
  - 跳转到行
  - 行高亮与行号

- 基本的代码高亮（c/c++）
- 基础的 lsp 功能
- 自动保存功能与文件系统
- ui 界面
  - 缩放
  - 布局调整


## 代码框架

### 项目核心结构

```txt
.
├── include
├── justfile
├── LICENSE
├── README.md
├── src
│   ├── core
│   ├── main.cpp
│   └── ui
├── tests
└── xmake.lua
```

### 构建系统

配置环境后运行 `xmake` 即可构建，更多构建命令参考 [justfile](../justfile)。

#### Linux

使用 nix + flake 作为系统级的环境管理，xmake 作为构建工具，justfile 作为脚本工具。

依赖 qt6.full。

#### Windows

xmake 作为构建工具，justfile 作为脚本工具，依赖基础 qt6 库及扩展库。

### 文件描述

#### xmake.lua

构建程序，包含项目依赖描述、核心程序和测试的构建。

#### justfile

记录常用的构建命令

#### include/

mystl 目录，其中 mystl 头由 `mystl.h` 作为索引导出，提供类似 std 的接口。

#### core/

- `Editor.h` 编辑器核心。
- `EditorHighlighter.h` 定义编辑器语法高亮，由传统 Qt 高亮方法实现。
- `EditorSettings.h` 定义编辑器设置。
- `EditorUtils.h` 定义工具函数，解决路径解析问题。
- `EditorWidget.h` 编辑器组件。
- `LspClient.h` lsp 客户端实现，定义核心客户端功能。
- `LspProtocol.h` lsp 协议实现，从基础类型逐层搭建起 lsp 的通信结构体，同时提供 json - string 互转函数。
- `LspUri.h` 提供 uri 类和部分基础类型，用于 lsp 协议实现。

#### ui/

- `MainWindow.h` 主程序，包含核心的一些编辑器功能、顶栏和状态栏、小型的文件系统等。
- `OutputWidget.h` 接收 lsp 返回的日志信息，包含一个日志高亮器。
- `PreviewWidget.h` 本意是用于渲染 tinymist preview 的网页，但几番调试下来发现就这个网页无法正确渲染，目前功能定位类似于 vscode 的 webview，但没想好具体的容器对象。
- ` SettingsDialog.h` 设置对话框。

#### main.cpp

入口函数

#### tests/

- `lsp` 测试（lspuri 和 lspprotocol）
- `lspclient` 客户端测试
- `misc` 杂项测试
- `mystl` mystl 测试

### 完整项目结构

```txt
$ tree -a -l3 --ignore .git
.
├── doxyfile
├── .editorconfig
├── .envrc
├── .gitignore
├── .temp
|  ├── assets
|  |  ├── icons/
|  |  ├── typst-code.tmLanguage.json
|  |  └── typst.tmLanguage.json
|  ├── EditorCompleter.cpp
|  ├── EditorCompleter.h
|  ├── EditorNaviBar.h
|  ├── EditorParser.cpp
|  ├── EditorParser.h
|  ├── EditorSemanticHighlighter.h
|  ├── EditorTheme.cpp
|  ├── EditorTheme.h
|  ├── JsonParser.cpp
|  ├── JsonParser.h
|  ├── PlistParser.cpp
|  ├── PlistParser.h
|  ├── PreviewerView.cpp
|  ├── PreviewerView.h
|  ├── SettingsManager.cpp
|  ├── SettingsManager.h
|  ├── TextGrammar.cpp
|  ├── TextGrammar.h
|  ├── TextMate.cpp
|  ├── TextMate.h
|  ├── TextTheme.cpp
|  └── TextTheme.h
├── .vscode
|  ├── .cache/
|  ├── compile_commands.json
|  └── settings.json
├── .xmake
|  └── windows
|     └── x64/
├── build
|  ├── .gens
|  |  ├── lspclient-test/
|  |  ├── misc-test/
|  |  └── qode/
|  └── windows
|     └── x64/
├── default.nix
├── docs
|  ├── Base.md
|  ├── Final.md
|  ├── InterimReport.md
|  └── ProposalReport.md
├── flake.lock
├── flake.nix
├── include
|  ├── mystl.h
|  ├── my_container.h
|  ├── my_deque.h
|  ├── my_list.h
|  ├── my_queue.h
|  ├── my_stack.h
|  └── my_vector.h
├── justfile
├── LICENSE
├── main.cpp
├── node_modules
├── package.json
├── pnpm-lock.yaml
├── README.md
├── shell.nix
├── slides.md
├── src
|  ├── core
|  |  ├── Editor.cpp
|  |  ├── Editor.h
|  |  ├── EditorHighlighter.cpp
|  |  ├── EditorHighlighter.h
|  |  ├── EditorSettings.cpp
|  |  ├── EditorSettings.h
|  |  ├── EditorUtils.h
|  |  ├── EditorWidget.h
|  |  ├── LspClient.cpp
|  |  ├── LspClient.h
|  |  ├── LspProtocol.cpp
|  |  ├── LspProtocol.h
|  |  └── LspUri.h
|  ├── main.cpp
|  └── ui
|     ├── MainWindow.cpp
|     ├── MainWindow.h
|     ├── OutputWidget.cpp
|     ├── OutputWidget.h
|     ├── PreviewWidget.cpp
|     ├── PreviewWidget.h
|     ├── SettingsDialog.cpp
|     └── SettingsDialog.h
├── tests
|  ├── lsp
|  |  ├── lsp_protocol_test.cpp
|  |  ├── lsp_uri_test.cpp
|  |  └── main.cpp
|  ├── lsp.snap
|  ├── lspclient
|  |  ├── lspclient_test.h
|  |  └── main.cpp
|  ├── lspclient.snap
|  ├── misc
|  |  ├── external_uri_test.cpp
|  |  └── main.cpp
|  ├── mystl
|  |  ├── main.cpp
|  |  ├── mystl_namespace_test.cpp
|  |  ├── my_deque_test.cpp
|  |  ├── my_list_test.cpp
|  |  ├── my_queue_test.cpp
|  |  ├── my_stack_test.cpp
|  |  └── my_vector_test.cpp
|  └── mystl.snap
└── xmake.lua

directory: 134 file: 116
```

> `.temp` 内容为编写过程中尝试实现的功能，但因为没能完善而未传入 git 管理。

## 核心逻辑

> 具体函数描述可以通过 doxygen 生成的文档查看。
>
> ```bash
> # 本地 web 版
> $ xmake doxygen -o doc
> $ npx http-server doc/html
> ```
> 

### 编辑器

基于 QPlainTextEdit，利用 Qt 提供的树形结构使用工厂模式管理子组件。

### 文件系统

基于文件名和文件状态，把内容先存到缓冲区，再保存到文件中。

### 语法高亮

使用传统的 Rule - Patten 模式进行高亮。

### LSP 客户端

Lsp 协议和客户端的实现严格按照微软的官方文档，先实现通信用到的结构体，再实现把 json 和文本互转的函数，最后基于 QProcess 实现客户端管理。

### UI 界面

高度模块化，把主 UI 渲染、次级 menu action 渲染、次级 status bar 渲染和 lsp 管理，信号-槽管理、监听器分隔管理。

### MyStl

我的做法是单独把 mystl 放到了 `include` 中，通过单独的 `mystl.h` 导出，提供与 std 一致的接口，即把 `std::vector<T>` 换成 `mystl::vector<T>` 即可使用。

## 测试

只进行单元测试，不进行端对端测试。

具体说明见 [测试文档](TestReport.md)
