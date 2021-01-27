project(cyber-shutdown)

add_executable(cyber-shutdown
    main.cpp
    actions.cpp
    qml.qrc
)

target_link_libraries(cyber-shutdown
        Qt5::Core
        Qt5::Widgets
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::DBus
)

install(TARGETS cyber-shutdown RUNTIME DESTINATION /usr/bin)
