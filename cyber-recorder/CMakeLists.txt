cmake_minimum_required(VERSION 3.14)

project(cyber-recorder LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Multimedia REQUIRED)
find_package(MeuiKit)

add_subdirectory(src)

install(FILES cyber-recorder.desktop DESTINATION "/usr/share/applications")