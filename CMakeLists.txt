cmake_minimum_required(VERSION 3.9) #версия cmake

project(BSTree) #название проекта

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS OFF) #линкуем динамически
set(Boost_USE_MULTITHREADED ON) #подключаем треды

option(BUILD_EXAMPLES "Build examples" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall") #версия 14 и предупреждения

include_directories("include/" "sources/") #подключаем хэдэры

add_executable(main sources/main.cpp) #собираем main

if(BUILD_EXAMPLES) #если включены примеры
    file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp") #собрать в один список
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        include_directories("include/" "sources/")
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        set(EXAMPLE_TARGET_NAME example_${EXAMPLE_NAME})
        add_executable(${EXAMPLE_TARGET_NAME} ${EXAMPLE_SOURCE})
        target_link_libraries(${EXAMPLE_TARGET_NAME} ${PROJECT_NAME})
        set_target_properties(${EXAMPLE_TARGET_NAME} PROPERTIES OUTPUT_NAME ${EXAMPLE_NAME})
        install(TARGETS ${EXAMPLE_TARGET_NAME}
                RUNTIME DESTINATION bin
                )
    endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

