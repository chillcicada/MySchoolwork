## 基础

### LSP

**Language Server Protocol (LSP)是微软2016年提出的一项通讯协议方案**。 该方案定义了一套协议，用于在IDE或编辑器和提供代码补全、转到定义等功能的 Language Server 之间通信。

这里的通信，指不同进程之间的通信，通讯格式为 jsonrpc（由`json.hpp`实现），即以 jsonrpc 格式在两个进程间发送和接收信息。其中，这里的 jsonrpc 可以 `json.hpp` 构造，同时与字符串相互转化，用于传递信息和提取信息。

我要做的是实现一个 LSP 客户端，可以分为 protocol 部分和 handler 部分，前者主要是提供基础的接口格式和基础的函数 （fromJson 和 toJson），单独放到 `LspProtocol.h` 中，后者提供具体的操作和实现，放到 `LspClient.h` 中。

参考项目：clangd。

### Editor

基于 QPlainTextEdit，扩展边栏，内部渲染。

### Syntax Hightlighter

基于 TextMate。

- load tmLanguage.json file
- use qt built-in json features parse tmLanguage.json

> TODO：补充实现说明

### Previewer

基于 QWebView。

> TODO：补充实现说明

### Output

只读的 QPlainTextEdit。

### MainWindow

拆分为六个初始化函数，五个 UI 模块。

```cpp
// `MainWindow.h`

/// @brief init functions
void setupUi();         // <- 设置主 ui 和布局
void setupActions();    // <- 设置顶部 menu bar
void setupStatusBar();  // <- 设置底部 status bar
void setupLsp();        // <- 启动 lsp
void connectSignals();  // <- 链接信号与槽函数
void setupWatchers();   // <- 启用监听函数
```

---

Tinymist LSP reference: <https://myriad-dreamin.github.io/tinymist/feature/language.html>
