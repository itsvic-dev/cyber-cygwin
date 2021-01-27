cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME cyber-settings)
project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT Core Gui Quick QuickControls2 DBus Xml Concurrent)
find_package(Qt5 REQUIRED ${QT})
find_package(MeuiKit REQUIRED)
find_package(Freetype REQUIRED)
find_package(PkgConfig REQUIRED)

#find_package(KF5NetworkManagerQt REQUIRED)
#find_package(KF5ModemManagerQt REQUIRED)
find_package(KF5CoreAddons REQUIRED)

pkg_search_module(FontConfig REQUIRED fontconfig IMPORTED_TARGET)
pkg_search_module(ICU REQUIRED icu-i18n)

include_directories(${ICU_INCLUDE_DIRS})

set(SRCS
    src/application.cpp
    src/main.cpp
    src/appearance.cpp
    src/battery.cpp
    src/brightness.cpp
    src/fontsmodel.cpp
    src/language.cpp
    src/about.cpp
    src/background.cpp
)

set(RESOURCES
    src/resources.qrc
)

qt5_add_dbus_adaptor(DBUS_SOURCES
                     src/org.cyber.SettingsUI.xml
                     src/application.h Application)
set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

execute_process(
  COMMAND git rev-list --count HEAD 
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE COMMIT_COUNT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(
  ${CMAKE_SOURCE_DIR}/src/version.h.in
  ${CMAKE_BINARY_DIR}/generated/version.h
)

include_directories(${CMAKE_BINARY_DIR}/generated)

add_executable(${PROJECT_NAME} ${DBUS_SOURCES} ${SRCS} ${RESOURCES})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::DBus
        Qt5::Xml
        Qt5::Concurrent
        MeuiKit

        KF5::CoreAddons

        PkgConfig::FontConfig
        ${FREETYPE_LIBRARIES}
        ${ICU_LDFLAGS}
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)

install(FILES
    cyber-settings.desktop
    DESTINATION /usr/share/applications/
    COMPONENT Runtime
)
