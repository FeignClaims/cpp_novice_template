# CMake file overview

- `add_program.cmake`: Wraps cmake to simplify the work of adding a new program.
- `cpp_novice_fetch_project_options.cmake`: Fetches [aminya/project_options](https://github.com/aminya/project_options) from [the mirror repository](https://gitlab.com/FeignClaims/project_options).
- `cpp_novice_custom_project_options.cmake`: Customizes and runs `dynamic_project_options(...)` in [aminya/project_options](https://github.com/aminya/project_options).
- `detect_std_module.cmake`: Detects whether the ``import std;`` feature since C++23 is usable in the current toolchain and enables it if possible.
- `enable_cpp_module.cmake`: Enables the experimental C++ module feature since C++20.
- `ppp_check_compiler`: Detects whether the current toolchain supports C++20, which is the minimum version required by *Programming: Principles and Practice Using C++ (3rd Edition)*.

Currently, this project template for novices only provides detailed explanations of the configuration file in Chinese. It serves as an appendix to my C++ tutorial for configuring VSCode on Windows, MacOS or Linux, which I have been maintaining since 2020. See [对学习模板的解释](https://vscode-cpp-starter.readthedocs.io/appendix/explain.html).
