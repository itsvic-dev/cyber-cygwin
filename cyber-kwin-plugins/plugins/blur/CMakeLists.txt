set(TARGET "panda-blur")

find_package(KF5Config REQUIRED)

add_library(
    ${TARGET} MODULE
    blur.cpp
    blurshader.cpp
    main.cpp
)

target_link_libraries(
    ${TARGET}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    PRIVATE
    KF5::CoreAddons
    KF5::WindowSystem
    KF5::ConfigCore
)

install(TARGETS ${TARGET} DESTINATION "${QT_PLUGINS_DIR}/kwin/effects/plugins")
