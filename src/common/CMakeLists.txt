# Common 模块 CMakeLists.txt
add_library(common STATIC)

# 包含头文件路径
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 添加源文件
file(GLOB COMMON_SOURCES ${CMAKE_SOURCE_DIR}/src/common/*.cpp)
target_sources(common PRIVATE ${COMMON_SOURCES})

# 链接依赖库
target_link_libraries(common PUBLIC ${CMAKE_SOURCE_DIR}/lib/libGameNetworkingSockets.so)

# 设置输出路径
set_target_properties(common PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mid)