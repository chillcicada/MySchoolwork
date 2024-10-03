# cpp final homework: maze

**The executable is under the `dist` folder.**

**所有的文档通过 doxygen 自动生成在 `docs` 文件夹下，可以通过 `npx serve ./docs/html` 查看 web，也可以查看 PDF。**

## design

本体大致可以拆分为三个部分：

- `map` - 地图类，负责地图的生成与迷宫的处理等
- `ui` - 用户界面类，负责用户界面的显示、交互等
- `main` - 主函数，负责整体流程的控制

```plaintext
src
├── main.cpp  # main function
├── map.cpp   # map header
├── map.hpp   # map source
├── ui.cpp    # ui header
├── ui.hpp    # ui source
└── utils.hpp # utils
```

由于设计仓促，一些模块直接仍然存在一定耦合或设计缺陷，但在整体上已经尽量分离。

### Map

- 提供了游戏相关的所有 API，包括地图生成、迷宫生成、迷宫解法等。

地图和迷宫生成思路：

1. 根据 row 和 col 创建一个 row \* col 的地图，初始化为全墙。（为了方便，此处 row 和 col 都是奇数）
2. 选定起点和一个随机的方向，使用深度优先搜索算法生成路径，即如果此方向上连续两个格子都是墙，则打通中间格子，并以第二个格子开始下一次搜索。在递归过程中，如果四个方向都无法继续搜索，则回溯到上一个格子，重新选择方向，反之，如果回到了起点，则迷宫生成完成。最后得到一条所有点都连通的路径。在此路径的基础上，选取终点，得到迷宫。

迷宫解法思路：

原理与 DFS 类似，不过转化为了栈结构，由于只需要顶层，每次调用只返回下一步方向即可。

### UI

原理：对已有接口的包装

> 通过缓冲区实现的无闪屏伪 UI 界面，不支持鼠标事件，但可以使用键盘控制。

- 提供了一些基本的 API，用以绘制界面（相当于帧）。
- 对一些常用的相关函数做了包装，如布局（layout，此处只提供了 center 和 right 布局），地图坐标于 UI 坐标转化的函数。

> UI 演示：（已标识键盘输入）

![](https://img.chillcicada.com/i/2024/06/19/66723fb68a129.gif)

### main

- main 函数 —— 一层循环，处理主菜单
- loop 函数 —— 二层循环，处理游戏流程
<!-- - pause 函数 —— 三层循环，处理暂停菜单 -->

### full demo

snapshot of the full project:

![](https://img.chillcicada.com/i/2024/06/19/6672542c40558.png)

完整构建演示：

![](https://img.chillcicada.com/i/2024/06/19/667240c7b03b6.gif)

完整游戏演示：

![](https://img.chillcicada.com/i/2024/06/21/66759caed23fd.gif)

### others | afterwords

> All magic numbers have got names or comments.🎈
>
> I hate cpp and me for choosing this problem.😭

## toolchain

- xmake and cpp environment
  - msvc or mingw64 for build
  - (optional) llvm for code
- (optional) doxygen for documentation
  - you may also need a server to host the html documentation, like `npx serve`
  - you may also need latex, and make for pdf generation, like `miktex`
- (optional) just for command runner
- (optional) node/bun for zip script

> i also provide a vs sln file for visual studio users if you don't want to build in cli. run `just xmake` to generate the sln file.

this repo is built under the windows environment, in unix-like environment, you need `conio.h` to build.

## development

> it's advised to use the same toolchain as the build environment.

dev:

```bash
just dev
```

build:

```bash
just build
```

release:

```bash
just release
```

the release is under the `dist` folder.

zip: (includes docs generation, generates the zip file for the project, which is provided for homework submission)

```bash
just zip
```

more commands in the `justfile`.

## others

This homework got 98/100 points (109 \* 0.9).

---

This zip is built via scripts, if you want to get the complete project structure and source code, please check the [github repo](https://github.com/chillcicada/MySchoolwork/tree/main/src/cpp1f).
