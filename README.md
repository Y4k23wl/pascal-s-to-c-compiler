# 项目结构

`frontend/` 包含词法分析与语法分析模块  
`semantic/` 包含语义分析模块  
`codegen/` 包含目标代码生成模块  
`testing/` 包含自动化测试内容
`docs/` 包含项目各阶段以及最终提交用的全部文档
`pascal_s_driver.cpp` 程序入口

# 程序编译

在根目录下配置并构建：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

这会自动：

- 用 `bison` 生成语法分析相关代码
- 用 `flex` 生成词法分析器代码
- 编译并链接生成 `build/bin/pascc`
- 此时程序会在`build/bin/pascc`

如果需要从干净目录重新全量构建：

```bash
rm -rf build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

构建依赖：

- `cmake` ≥ 3.16
- 支持 C++17 的 C++ 编译器（GCC / Clang / MSVC 均可）
- `flex` ≥ 2.5.30，**推荐使用 2.6.x**
- `bison` ≥ 2.4

## Windows 构建注意事项

在 Windows 上使用 MSVC 构建时，请确认以下几点，否则可能配置或编译失败：

1. **flex / bison 必须用 Windows 原生版本，强烈推荐 `win_flex_bison`**。
   - `win_flex_bison` 的可执行文件叫 `win_flex.exe` / `win_bison.exe`，CMake 的 `FindFLEX` / `FindBISON` 模块**已经识别这两个名字**，不需要重命名也不需要 `-DFLEX_EXECUTABLE` 显式指定。
   - **不要使用 MSYS / MSYS2 移植版的 `flex.exe` / `bison.exe`**：那些是 POSIX 仿真二进制，依赖 `msys-2.0.dll`，在 Visual Studio 构建链下调用 `--version` 会因为找不到运行时 DLL 而失败，CMake 会报 `Command "..bison.exe --version" failed with output:` 后面空白。
   - 同理也不要使用 Cygwin、Git Bash 自带的 flex/bison。
2. **不要用 codepage 936 (GBK) 构建**。项目源文件统一是 UTF-8，CMake 已经在 `if(MSVC)` 分支里加了 `/utf-8` 选项让 MSVC 按 UTF-8 解析，无需额外配置。
3. **想让控制台正确显示中文错误提示**，pascc 在 `main()` 入口已自动调用 `SetConsoleOutputCP(CP_UTF8)`。如果终端字体不支持中文，请改用 Windows Terminal 或 PowerShell 7。
4. **修改了 CMake 配置或更换了 flex/bison 工具链后**，请先 `rmdir /s /q build` 删除整个 `build\` 目录再重新 `cmake -S . -B build ...`，否则 `CMakeCache.txt` 会缓存旧的工具路径继续报错。



# 程序用法
假设你已经执行构建命令生成了 `build/bin/pascc`，并且这时你在同目录下有 `program.pas`  
则执行 `./build/bin/pascc -i program.pas` 即可在目录下得到 `program.c`   
(Windows下可能是 `build/bin/pascc.exe -i program.pas`)

## 阶段性中间产物 dump

驱动支持单独 dump 语法分析和语义分析的中间产物，方便分阶段查看 / 测试。所有 dump 都写到 **stderr**，不会污染落盘的 `.c` 文件。

可用命令行选项：

| 选项 | 作用 |
|---|---|
| `--dump-ast` | 在语法分析（含 `ast_validate`）之后，把 AST 打印出来 |
| `--dump-symbols` | 在语义分析成功之后，把全部作用域和符号表打印出来 |
| `--stop-after=parse` | 语法分析完成后立即退出，不跑语义、不生成 `.c` |
| `--stop-after=semantic` | 语义分析完成后立即退出，不生成 `.c` |

常见用法（假设源程序是 `a.pas`）：

```bash
# 只看 AST（语法成功即可，语义有错也能拿到）
./build/bin/pascc -i a.pas --stop-after=parse --dump-ast 2> a.ast

# 只看符号表（需要语法 + 语义都通过）
./build/bin/pascc -i a.pas --stop-after=semantic --dump-symbols 2> a.sym

# 两个都打，并保留完整编译到 .c
./build/bin/pascc -i a.pas --dump-ast --dump-symbols 2> a.dump

# 想同时在终端看 + 存文件
./build/bin/pascc -i a.pas --stop-after=parse --dump-ast 2>&1 | tee a.ast
```

不加 `2>` 时 dump 内容会直接打到终端，跟编译器自身的提示混排——分析时建议重定向到文件。

AST dump 里每个节点末尾形如 `[起始行:起始列-结束行:结束列]` 的方括号是该节点对应的源代码位置区间，由词法/语法阶段填入，后续语义错误的行列号也来自这里。
