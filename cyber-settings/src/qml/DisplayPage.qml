import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Cyber.Settings 1.0
import MeuiKit 1.0 as Meui

ItemPage {
    headerTitle: qsTr("Display")

    Appearance {
        id: appearance
    }

    Brightness {
        id: brightness
    }

    Timer {
        id: brightnessTimer
        interval: 100
        onTriggered: {
            brightness.setValue(brightnessSlider.value)
        }
    }

    Scrollable {
        anchors.fill: parent
        contentHeight: layout.implicitHeight

        ColumnLayout {
            id: layout
            anchors.fill: parent

            Label {
                text: qsTr("Brightness")
                color: Meui.Theme.disabledTextColor
                bottomPadding: Meui.Units.largeSpacing
            }

            RowLayout {
                spacing: Meui.Units.largeSpacing

                Image {
                    width: brightnessSlider.height
                    height: width
                    sourceSize.width: width
                    sourceSize.height: height
                    source: "qrc:/images/" + (Meui.Theme.darkMode ? "dark" : "light") + "/display-brightness-low-symbolic.svg"
                }

                Slider {
                    id: brightnessSlider
                    Layout.fillWidth: true
                    value: brightness.value
                    from: 0
                    to: 100
                    stepSize: 1
                    onMoved: brightnessTimer.start()
                }

                Image {
                    width: brightnessSlider.height
                    height: width
                    sourceSize.width: width
                    sourceSize.height: height
                    source: "qrc:/images/" + (Meui.Theme.darkMode ? "dark" : "light") + "/display-brightness-symbolic.svg"
                }
            }

            Item {
                height: Meui.Units.largeSpacing
            }

            HorizontalDivider {}

            Label {
                text: qsTr("Scale")
                color: Meui.Theme.disabledTextColor
                bottomPadding: Meui.Units.smallSpacing
            }


            TabBar {
                id: dockSizeTabbar
                Layout.fillWidth: true

                TabButton {
                    text: qsTr("100%")
                }

                TabButton {
                    text: qsTr("125%")
                }

                TabButton {
                    text: qsTr("150%")
                }

                TabButton {
                    text: qsTr("175%")
                }

                TabButton {
                    text: qsTr("200%")
                }

                currentIndex: {
                    var index = 0

                    if (appearance.devicePixelRatio <= 1.0)
                        index = 0
                    else if (appearance.devicePixelRatio <= 1.25)
                        index = 1
                    else if (appearance.devicePixelRatio <= 1.50)
                        index = 2
                    else if (appearance.devicePixelRatio <= 1.75)
                        index = 3
                    else if (appearance.devicePixelRatio <= 2.0)
                        index = 4

                    return index
                }

                onCurrentIndexChanged: {
                    var value = 1.0

                    switch (currentIndex) {
                    case 0:
                        value = 1.0
                        break;
                    case 1:
                        value = 1.25
                        break;
                    case 2:
                        value = 1.50
                        break;
                    case 3:
                        value = 1.75
                        break;
                    case 4:
                        value = 2.0
                        break;
                    }

                    appearance.setDevicePixelRatio(value)
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }
}
