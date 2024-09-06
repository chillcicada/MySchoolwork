# Python Final Homework

## Usage

> 进行了单独的打包，可以直接运行
>
> 目前只能在命令行下运行

```bash
./hw start
```

## 设计思路

### 项目结构

核心代码在 `src` 目录下，主要分为以下几个文件：

```txt
src
├── core.py     # 核心功能，定义 Record （数据）相关的类
├── fs.py       # 文件系统相关的操作，主要为保存和读取数据
├── gen.py      # 生成题目的功能和相关类
├── log.py      # 日志相关的操作
├── record.txt  # 保存数据的文件
├── utils.py    # 一些工具函数
├── __init__.py # 使 src 目录成为一个包，定义核心逻辑
└── __pycache__ # 缓存文件，可忽略
```

所有测试文件和快照在 `__tests__` 目录下

### 设计目标

主要是实现作业要求的功能

### 设计方法

主要是面向对象设计，不过对逻辑没做太多的封装，因为逻辑比较简单

## toolchain

- python312
- rye
- just

## development

安装依赖：

```bash
rye sync
```

测试：

```bash
just test
# or
# ./.venv/Scripts/python -m pytest
```

开发：

```bash
just dev
# or
# ./.venv/Scripts/python ./src/__init__.py start
```

构建：

```bash
just build
# ./.venv/Scripts/pyinstaller --onefile --name=hw ./src/__init__.py
```

build release under `build`

see more in `justfile`
