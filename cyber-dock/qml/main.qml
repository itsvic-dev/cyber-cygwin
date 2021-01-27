import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.cyber.Dock 1.0
import MeuiKit 1.0 as Meui

Item {
    visible: true
    id: root
    clip: true

    property color backgroundColor: Meui.Theme.darkMode ? Qt.rgba(0, 0, 0, 0.1) : Qt.rgba(255, 255, 255, 0.45)
    property color borderColor: Meui.Theme.darkMode ? Qt.rgba(255, 255, 255, 0.1) : Qt.rgba(0, 0, 0, 0.05)
    property color activateDotColor: Meui.Theme.highlightColor
    property color inactiveDotColor: Meui.Theme.darkMode ? Qt.rgba(255, 255, 255, 0.6) : Qt.rgba(0, 0, 0, 0.9)
    property real windowRadius: (Settings.direction === DockSettings.Left) ? root.width * 0.3 : root.height * 0.3

    Rectangle {
        id: outerFrame
        anchors.fill: parent
        radius: windowRadius
        color: backgroundColor
        border.color: Qt.rgba(0, 0, 0, 0.4)
        border.width: 1
        antialiasing: true
        smooth: true

        Behavior on color {
            ColorAnimation {
                duration: 250
            }
        }
    }

    Rectangle {
        id: innerBorder
        anchors.fill: parent
        anchors.margins: 1
        radius: windowRadius
        color: "transparent"
        border.color: Qt.rgba(255, 255, 255, 0.2)
        border.width: 1
        antialiasing: true
        smooth: true
        visible: true
    }

    Meui.PopupTips {
        id: popupTips
    }

    GridLayout {
        anchors.fill: parent
        rows: (Settings.direction === DockSettings.Left) ? 3 : 1
        columns: (Settings.direction === DockSettings.Left) ? 1 : 3
        rowSpacing: 0
        columnSpacing: 0

        DockItem {
            id: launcherItem
            enableActivateDot: false
            iconName: "qrc:/svg/launcher.svg"
            popupText: qsTr("Launcher")
            onClicked: process.start("cyber-launcher")
        }

        ListView {
            id: appItemView
            orientation: (Settings.direction === DockSettings.Left) ? Qt.Vertical : Qt.Horizontal
            snapMode: ListView.SnapToItem
            clip: true
            model: appModel
            delegate: AppItem { }
            interactive: false

            moveDisplaced: Transition {
                NumberAnimation {
                    properties: "x, y"
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        DockItem {
            id: trashItem
            popupText: qsTr("Trash")
            enableActivateDot: false
            iconName: "user-trash-empty"
            onClicked: process.start("gio", ["open", "trash:///"])
        }
    }

    Connections {
        target: Settings
        function onDirectionChanged() {
            popupTips.hide()
        }
    }
}
