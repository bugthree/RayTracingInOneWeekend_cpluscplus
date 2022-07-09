cmake_minimum_required(VERSION 3.10)
project(RayTracingProject)
message(STATUS "\n ################################")
message(STATUS "\n output project name:")# 打印项目名字
message(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

# 查找指定目录下的所有.cpp与.h文件 并存放到指定变量名SC_FILES中
file(GLOB SRC_H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src" */*.h )
file(GLOB SRC_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src" */*.cpp)
message(STATUS "\n output all CPP FILES:")# 打印项目名字
message(${SRC_CPP_FILES})
SOURCE_GROUP("SOURCES FILES" FILES ${SRC_CPP_FILES})# 设置一组
SOURCE_GROUP("Header FILES" FILES ${SRC_H_FILES})

# 将查找到的所有文件，生成可执行文件
add_executable( ${PROJECT_NAME}
				${SRC_CPP_FILES}
				${SRC_H_FILES}
)

# 添加lib(静态库)
target_link_libraries(${PROJECT_NAME}  

)

# 添加附加包含目录
INCLUDE_DIRECTORIES(

)

