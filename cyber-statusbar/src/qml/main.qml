import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.0

import MeuiKit 1.0 as Meui

Item {
    id: root

    Rectangle {
        id: background
        anchors.fill: parent
        radius: 0
        opacity: 0.5
        color: Meui.Theme.backgroundColor

        Behavior on color {
            ColorAnimation {
                duration: 250
            }
        }
    }

    MouseArea {
        id: emptyArea
        anchors.fill: parent
        z: -1
        onDoubleClicked: WindowControl.toggleMaximize()
    }

    Item {
        id: leftArea
        anchors.left: parent.left
        anchors.right: separator.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: Meui.Units.largeSpacing
        anchors.rightMargin: Meui.Units.largeSpacing

        Label {
            id: appTitle
            anchors.fill: parent
            color: Meui.Theme.textColor
            text: WindowControl.title
            clip: true
            elide: Text.ElideRight
        }
    }

    Item {
        id: separator
        anchors.centerIn: parent
    }

    Item {
        id: rightArea
        anchors.left: separator.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: Meui.Units.largeSpacing
        anchors.rightMargin: Meui.Units.largeSpacing

        RowLayout {
            id: layout
            anchors.fill: parent
            spacing: Meui.Units.largeSpacing

            Item {
                Layout.fillWidth: true
            }

            ListView {
                id: systemTrayView
                orientation: Qt.Horizontal
                model: StatusNotifierModel
                layoutDirection: Qt.RightToLeft
                interactive: false
                clip: true

                spacing: Meui.Units.largeSpacing

                Layout.fillHeight: true
                implicitWidth: count * root.height + (count - 1) * spacing

                delegate: IconButton {
                    width: systemTrayView.height
                    height: width
                    source: iconName ? "image://icontheme/" + iconName
                                     : iconBytes ? "data:image/png;base64," + iconBytes
                                                 : "image://icontheme/application-x-desktop"
                    onLeftButtonClicked: StatusNotifierModel.leftButtonClick(id)
                    onRightButtonClicked: StatusNotifierModel.rightButtonClick(id)
                    popupText: toolTip ? toolTip : title
                }
            }

            IconButton {
                id: volumeButton
                implicitWidth: layout.height
                implicitHeight: layout.height
                visible: Volume.isValid
                source: "qrc:/icons/" + (Meui.Theme.darkMode ? "dark/" : "light/") + Volume.iconName + ".svg"
                popupText: qsTr("Current Volume: ") + Volume.volume
                onLeftButtonClicked: VolumeControlWindow.popup(volumeButton.mapToGlobal(0, 0))
            }

            IconButton {
                id: batteryIcon
                visible: Battery.available
                implicitWidth: batteryLayout.width
                implicitHeight: layout.height
                popupText: Battery.statusString
                onLeftButtonClicked: Process.startDetached("cyber-settings", ["-m", "battery"])

                RowLayout {
                    id: batteryLayout
                    anchors.centerIn: parent
                    spacing: 7

                    Label {
                        text: Battery.chargePercent + "%"
                        color: Meui.Theme.textColor
                    }

                    Image {
                        id: iconLabel
                        source: "qrc:/icons/" + (Meui.Theme.darkMode ? "dark/" : "light/") + Battery.iconSource
                        Layout.fillHeight: true
                        width: root.height
                        sourceSize: Qt.size(width, height)
                        asynchronous: true
                    }
                }
            }

            IconButton {
                id: powerOffButton
                implicitWidth: layout.height
                implicitHeight: layout.height
                source: "qrc:/icons/" + (Meui.Theme.darkMode ? "dark/" : "light/") + "system-shutdown-symbolic.svg"
                onLeftButtonClicked: Process.startDetached("cyber-shutdown")
            }

            IconButton {
                id: localeTimeLabel
                implicitWidth: timeLabel.width + Meui.Units.largeSpacing
                implicitHeight: parent.height

                Label {
                    id: timeLabel
                    anchors.centerIn: parent

                    Timer {
                        interval: 1000
                        repeat: true
                        running: true
                        triggeredOnStart: true
                        onTriggered: {
                            timeLabel.text = new Date().toLocaleTimeString(Qt.locale(), Locale.ShortFormat)
                        }
                    }
                }
            }

            Item {
                id: windowControl

                implicitHeight: layout.height
                implicitWidth: controlLayout.implicitWidth

                visible: WindowControl.isMaximized

                RowLayout {
                    id: controlLayout
                    anchors.fill: parent
                    anchors.margins: 0
                    spacing: Meui.Units.largeSpacing

                    IconButton {
                        id: minimizeButton
                        implicitWidth: windowControl.height
                        implicitHeight: windowControl.height
                        source: "qrc:/icons/" + (Meui.Theme.darkMode ? "dark/" : "light/") + "minimize_normal.svg"
                        onLeftButtonClicked: WindowControl.minimize()
                    }

                    IconButton {
                        id: restoreButton
                        implicitWidth: windowControl.height
                        implicitHeight: windowControl.height
                        source: "qrc:/icons/" + (Meui.Theme.darkMode ? "dark/" : "light/") + "restore_normal.svg"
                        onLeftButtonClicked: WindowControl.restore()
                    }

                    IconButton {
                        id: closeButton
                        implicitWidth: windowControl.height
                        implicitHeight: windowControl.height
                        source: "qrc:/icons/" + (Meui.Theme.darkMode ? "dark/" : "light/") + "close_normal.svg"
                        onLeftButtonClicked: WindowControl.close()

                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
