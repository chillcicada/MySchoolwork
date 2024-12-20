# Qode

## Build

```bash
xmake -a
```

see more command in [justfile](justfile).

## Project Architecture

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
│   ├── assets
│   ├── core
│   ├── main.cpp
│   └── ui
├── tests
│   ├── lsp
│   ├── lsp.snap
│   ├── mystl
│   └── mystl.snap
├── TODO.md
└── xmake.lua
```

## MySTL

Path: `include/mystl.h`

Usage: `std -> mystl`

```cpp
#include "mystl.h"

int main() {
  mystl::vector<int> v;
  v.push_back(1);
}
```

## Acknowledgements

This project is inspired by the following projects:

- [clangd][clangd]: provides the original implementation of the language server protocol, author: Alex L and llvm community.
- [katvan][katvan]: an typst editor based on the qt6, author: lgKh.
- [Tinymist][Tinymist]: the lsp of the typst language, author: Myriad-Dreamin.
- [Kate][Kate]: the editor of the KDE project, author: KDE Community.

## License

[GPLv3](LICENSE)

[clangd]: https://clangd.llvm.org/
[katvan]: https://github.com/IgKh/katvan
[Tinymist]: https://github.com/Myriad-Dreamin/tinymist
[Kate]: https://kate-editor.org/
