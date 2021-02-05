# CMakeList.txt: проект CMake для Test1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 2.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Test1 "Test1.cpp" "container.cpp" "container.h" "client.cpp" "client.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")