cmake_minimum_required(VERSION 3.5)

project(cyber-disk-usage)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT Core Gui Widgets Quick QuickControls2)
find_package(Qt5 REQUIRED ${QT})

set(SRCS
    main.cpp
    backend.cpp
)

set(RESOURCES
    qml.qrc
)

add_executable(cyber-disk-usage ${SRCS} ${RESOURCES})
target_link_libraries(cyber-disk-usage
    Qt5::Core
    Qt5::Widgets
    Qt5::Quick
    Qt5::QuickControls2
)

install(TARGETS cyber-disk-usage RUNTIME DESTINATION /usr/bin)

install(FILES
    cyber-disk-usage.desktop
    DESTINATION /usr/share/applications/
    COMPONENT Runtime
)
