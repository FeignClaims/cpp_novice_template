# cpp_novice_template

[中文 (额外地, 有全网最全的 VSCode 配置教程)](请读我.md)

This is a template for novices learning C++. It requires no C++ or cmake experience.

## Software Requirements

- Git
- a C++ IDE that supports CMake (latest Visual Studio, Qt Creator, CLion, etc.)

## Download and unzip

1. Click the green `Code` button near the top of this page.
2. Click the `Download ZIP` button. This will download the latest repository as a zip file.
3. Unzip the downloaded zip file somewhere you are going to store your code.

## Usage

1. Open your IDE (latest Visual Studio, Qt Creator, CLion, etc.) or *configured* Editors (VSCode with CMake Tools, etc.).
2. In your IDE, open this unzipped folder `as a folder` or `as a cmake project`.

## How to add a new program?

### Basics

The best thing about studying C++ with cmake is that a single project can manage multiple programs: you're not required to setup a new project in order to do the next exercise.

In this template, you can simply add a program by:

1. open `CMakeLists.txt` in the root folder.
2. add `add_code(<program_name> <source_file1> [source_file2...])` (for example, `add_code(example_single src/example_single/main.cpp)`).
3. Reconfigure the project by using some button or reopening the IDE.

**It's highly recommended to put your code inside `src` folder.**

### Headers

As for header files (`.h`, `.hpp`, etc.), you can simply put them together with source files. Then source files will be able to correctly `#include "<header_file>"`. For example, in `src/example_multiple` folder, `hello.cpp` can `#include "hello.hpp"` directly.

If you want to make a header file includable globally, you can put it inside `include` folder. For example, in `src/example_single` folder, `main.cpp` can `#include "add.hpp"` which is put inside `include` folder.

## Install third-party libraries

See [README_install_thirdparty_libraries](README_install_thirdparty_libraries.md).

## References

I learnt cmake mostly from [*Modern CMake for C++*](https://github.com/PacktPublishing/Modern-CMake-for-Cpp).

What's more, this repository highly depends on [aminya/project_options](https://github.com/aminya/project_options), which improves the CMake experience a lot.

For conan 2.0, the [official documentation](https://docs.conan.io/2.0/index.html) is helpful.

Details about this repository can be found in [对配置文件的解释](https://vscode-cpp-starter.readthedocs.io/appendix/explain.html).
