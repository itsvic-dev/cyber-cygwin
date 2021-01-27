cmake_minimum_required(VERSION 3.5)

project(statusbar)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT Core DBus Concurrent X11Extras Quick QuickControls2)
find_package(Qt5 REQUIRED ${QT})
find_package(KF5WindowSystem REQUIRED)
find_package(MeuiKit REQUIRED)

add_subdirectory(src)
