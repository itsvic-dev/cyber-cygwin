cmake_minimum_required(VERSION 3.14)

project(cyber-fm LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Concurrent DBus REQUIRED)
find_package(MeuiKit REQUIRED)

add_executable(cyber-fm
    main.cpp
    folderlistmodel.cpp
    fileitem.cpp
    fileloader.cpp
    filelauncher.cpp
    placesmodel.cpp
    dateutils.cpp
    dirselection.cpp
    dirlister.cpp
    xdgmimeapps.cpp
    xdgdesktopfile.cpp
    qml.qrc
)

target_link_libraries(cyber-fm
    PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Concurrent
    Qt5::DBus
    MeuiKit
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)
install(FILES cyber-fm.desktop DESTINATION "/usr/share/applications")
