# calculate/CMakeLists.txt
cmake_minimum_required(VERSION 3.18)

# 定义子模块项目（可选，但推荐）
project(calculate LANGUAGES CXX)

# 收集源文件（仅 .cpp）
file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
)

# 创建静态库（或 SHARED 动态库）
add_library(calculate STATIC ${SRC_FILES})

# 设置头文件路径（关键：PUBLIC 属性传递路径）
target_include_directories(calculate PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # 绝对路径确保可访问性
)

# 可选：设置 C++ 标准
target_compile_features(calculate PUBLIC cxx_std_17)
