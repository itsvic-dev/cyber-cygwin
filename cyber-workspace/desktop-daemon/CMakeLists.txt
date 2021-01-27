project(cyber-desktop-daemon)

find_package(KF5WindowSystem REQUIRED)

add_executable(cyber-desktop-daemon
    main.cpp
    desktopview.cpp
    settings.cpp
    qml.qrc
)

target_link_libraries(cyber-desktop-daemon
    Qt5::Core
    Qt5::DBus
    Qt5::Widgets
    Qt5::Quick
    Qt5::QuickControls2
    KF5::WindowSystem
    MeuiKit
)
install(TARGETS cyber-desktop-daemon RUNTIME DESTINATION /usr/bin)
