project(cyber-settings-daemon)
set(TARGET cyber-settings-daemon)

#find_package(PulseAudio)

file (GLOB_RECURSE SRCS
  "*.cpp"
  "*.h"
  "theme/*.h"
  "theme/*.cpp"
  "brightness/*.h"
  "brightness/*.cpp"
  "brightness/*.c"
  "battery/*.cpp"
  "battery/*.h"
  "language/*.cpp"
  "language/*.h"
)

set(SOURCES ${SRCS})
set(HEADERS "")
set(FORMS "")
set(RESOURCES "")

qt5_add_dbus_adaptor(DBUS_SOURCES
                     brightness/org.cyber.Brightness.xml
                     brightness/brightnessmanager.h BrightnessManager)
qt5_add_dbus_adaptor(DBUS_SOURCES
                     theme/org.cyber.Theme.xml
                     theme/thememanager.h ThemeManager)
qt5_add_dbus_adaptor(DBUS_SOURCES
                     battery/org.cyber.PrimaryBattery.xml
                     battery/battery.h Battery)
qt5_add_dbus_adaptor(DBUS_SOURCES
                     language/org.cyber.Language.xml
                     language/language.h Language)

set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

add_executable(${TARGET} ${SOURCES} ${DBUS_SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::DBus
        Qt5::X11Extras
        ${PULSEAUDIO_LIBRARY}
)

install(TARGETS ${TARGET} DESTINATION /usr/bin)
