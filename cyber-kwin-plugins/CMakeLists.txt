cmake_minimum_required(VERSION 3.5)

project(cyber-kwin-config)

set(PROJECT_NAME "cyber-kwin")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(plugins)

install(FILES config/kwinrc DESTINATION /etc/xdg)
install(DIRECTORY scripts/launcher DESTINATION /usr/share/kwin/scripts)
install(DIRECTORY tabbox/thumbnail_grid DESTINATION /usr/share/kwin/tabbox)
