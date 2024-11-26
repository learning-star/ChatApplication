cmake_minimum_required(VERSION 3.16)

# 项目名称
project(ChatApplication)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置默认构建类型（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
endif()

# 打印当前构建类型
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 设置 Debug 和 Release 配置的编译选项
# Debug 配置：启用调试信息，禁用优化
set(CMAKE_CXX_FLAGS_DEBUG "-g" CACHE STRING "Debug compile flags" FORCE)

# Release 配置：启用优化，禁用调试信息
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING "Release compile flags" FORCE)

# 根据构建类型设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mid/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mid/${CMAKE_BUILD_TYPE})

# 打印输出目录
message(STATUS "Runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# 添加子目录
add_subdirectory(src/common)
add_subdirectory(src/server)
add_subdirectory(src/client)
