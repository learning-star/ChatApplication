# Server 模块 CMakeLists.txt
add_executable(server)

# 包含头文件路径
target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 添加源文件
file(GLOB SERVER_SOURCES ${CMAKE_SOURCE_DIR}/src/server/*.cpp)
target_sources(server PRIVATE ${SERVER_SOURCES})

# 链接 Common 和外部库
target_link_libraries(server PRIVATE common ${CMAKE_SOURCE_DIR}/lib/libGameNetworkingSockets.so)
