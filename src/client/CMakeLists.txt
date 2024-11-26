# Client 模块 CMakeLists.txt
add_executable(client)

# 包含头文件路径
target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 添加源文件
file(GLOB CLIENT_SOURCES ${CMAKE_SOURCE_DIR}/src/client/*.cpp)
target_sources(client PRIVATE ${CLIENT_SOURCES})

# 链接 Common 和外部库
target_link_libraries(client PRIVATE common ${CMAKE_SOURCE_DIR}/lib/libGameNetworkingSockets.so)
