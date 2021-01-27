add_executable(cyber-recorder
    main.cpp
    audiorecorder.cpp
    audioplayer.cpp
    recordingmodel.cpp
    audioprober.cpp
    utils.cpp
    settingsmodel.cpp
    qml.qrc
)

target_link_libraries(cyber-recorder
    PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Multimedia
    MeuiKit
)

install(TARGETS cyber-recorder RUNTIME DESTINATION /usr/bin)
