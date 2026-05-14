# 你的代码在哪里？

frontend文件夹下包含词法分析与语法分析模块  
semantic文件夹下包含语法分析模块  
codegen文件夹下包含目标代码生成模块  
testing文件夹下包含自动化测试内容

# 如何编译出程序？

在根目录下配置并构建：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

这会自动：

- 用 `bison` 生成词法/语法分析相关代码
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

- `cmake`
- `c++`
- `flex`
- `bison`  



# 程序怎么用？
假设你已经执行构建命令生成了 `build/bin/pascc`，并且这时你在同目录下有 `program.pas`  
则执行 `./build/bin/pascc -i program.pas` 即可在目录下得到 `program.c`   
(Windows下可能是 `build/bin/pascc.exe -i program.pas`)
