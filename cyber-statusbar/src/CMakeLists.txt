set(PROJECT_NAME cyber-statusbar)
project(${PROJECT_NAME})

find_package(dbusmenu-qt5 REQUIRED)

set(SRCS
    main.cpp
    mainwindow.h
    mainwindow.cpp
    volumemanager.cpp
    volumecontrolwindow.cpp
    iconthemeimageprovider.cpp
    processprovider.cpp
    windowcontrol.cpp
    battery.cpp

    statusnotifier/dbustypes.cpp
    statusnotifier/sniasync.cpp
    statusnotifier/statusnotifieriteminterface.cpp
    statusnotifier/statusnotifiermodel.cpp
    statusnotifier/statusnotifierwatcher.cpp
    statusnotifier/statusnotifieritemsource.cpp
)

#qt5_add_dbus_adaptor(DBUS_SOURCES
#                     statusnotifier/org.kde.StatusNotifierItem.xml
#                     statusnotifier/statusnotifieritem.h StatusNotifierItem
#                     statusnotifieritemadaptor StatusNotifierItemAdaptor)
#set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

set(RESOURCES resources.qrc)

add_executable(${PROJECT_NAME} ${SRCS} ${RESOURCES})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::DBus
        Qt5::X11Extras
        Qt5::Concurrent
        Qt5::Quick
        Qt5::QuickControls2
        KF5::WindowSystem

        MeuiKit
        dbusmenu-qt5
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)
