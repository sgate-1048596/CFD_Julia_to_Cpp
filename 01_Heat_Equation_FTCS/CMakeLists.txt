# main/CMakeLists.txt
cmake_minimum_required(VERSION 3.18)
project(MainProject LANGUAGES CXX)

# 添加子模块目录
add_subdirectory(calculate)

# 收集主程序的源文件
add_executable(main_program main.cpp)

# 链接子模块库（关键步骤）
target_link_libraries(main_program PRIVATE calculate)

# 可选：全局设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
