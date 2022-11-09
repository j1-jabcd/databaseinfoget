#cmake最低版本
cmake_minimum_required (VERSION 2.8)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#project (vector)
#include_directories(/home/jlc/mavlink_c++)
include_directories(/home/jlc/c++database/include)
#LINK_LIBRARIES(math) 
#add_executable(vector src/vector.cpp)
#add_executable(dimit src/dimit.cpp)
#add_executable(client client.cpp)
#add_executable(mavlink_test src/mavlink_test.cpp)
#add_executable(server src/server.cpp)
#add_executable(udp_cilent src/udp_cilent.cpp)
#add_executable(Astar src/Astar.cpp)
#add_library(Astar SHARED src/Astar.cpp)   #STATIC  or SHARED
add_executable(DataMessageGet src/DataMessageGet.cpp)
#add_executable(adrc_main src/adrc_main.cpp)
#target_link_libraries(main Astar)
#target_sources(main PUBLIC "src/Astar.cpp")
#target_sources(adrc_main PUBLIC "src/adrc.cpp")
#add_executable(daemon1 src/shouhu_pid.cpp)
#add_executable(bingfa src/highgoing_server.cpp)
#set定义变量
#例子：set(SRC sayhello.cpp hello.cpp)
#include_directories ——向工程添加多个特定的头文件搜索路径 ————相当于指定g++编译器的-l参数
#例如：include_directories(/usr/include/mylibfolder ./include)包含头文件的文间夹

#link_directories -向工程添加多个库文件搜索路径
#add_library 生成库文件
#例子add_library(hello SHARED ${SRC})//shared为动态共享库，STATIC为静态库
#add_compile_options(-wall -std=c++11 -02) 添加编译参
#add_executable(main main.cpp)生成可执行文件
#target_link_libraies 为目标添加共享库 如 target_link_libraies（main hello）将上诉生成的静态库连接到main 添加SHARED 为动态链接库
#动态链接库生成后直接包含头文件即可使用 ，或者同时编译
#add_subdirectory 添加子目录 子目录中要有cmkelist.txt
#aux_source_directory -发现一个目录下所有源文件放到一个变量中
#set(CAMKE_BUILD_TYPE DEBUG)设定编译类型
#EXECUTABLE_OUTPUT_PATH:可执行文件输出的存放路径

