cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME cyber-launcher)
project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT Core DBus Quick QuickControls2)
find_package(Qt5 REQUIRED ${QT})

set(SRCS
    src/desktopproperties.cpp
    src/iconthemeimageprovider.cpp
    src/launcher.cpp
    src/launchermodel.cpp
    src/launcheritem.cpp
    src/main.cpp
    src/pagemodel.cpp
    src/ucunits.cpp
    src/wallpaper.cpp
)

set(RESOURCES
    qml.qrc
)

qt5_add_dbus_adaptor(DBUS_SRCS
    src/org.cyber.Launcher.xml
    src/launcher.h
    Launcher
    launcheradaptor
    LauncherAdaptor
)
set_source_files_properties(${DBUS_SRCS} PROPERTIES SKIP_AUTOGEN ON)

add_executable(${PROJECT_NAME} ${SRCS} ${DBUS_SRCS} ${RESOURCES})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::DBus
        Qt5::Quick
        Qt5::QuickControls2
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)
