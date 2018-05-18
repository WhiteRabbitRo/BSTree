cmake_minimum_required(VERSION 3.9) #версия cmake

project(BSTree) #название проекта

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall") #версия 14 и предупреждения

include_directories("include/") #подключаем хэдэры

add_executable(bstree sources/main.cpp) #собираем main

if(BUILD_EXAMPLES) #если включены примеры
    file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp") #собрать в один список
    add_executable(example "${EXAMPLE_SOURCES}")
endif()

if(BUILD_TESTS) #если включены тесты
	enable_testing()
	file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
	add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
	add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()
