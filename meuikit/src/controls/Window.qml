import QtQuick 2.4
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import MeuiKit 1.0 as Meui

Window {
    id: root
    width: 640
    height: 480
    visible: true
    flags: Qt.FramelessWindowHint

    property alias backgroundColor: _background.color
    property alias headerBarHeight: _titlebar.height
    property bool hideHeaderOnMaximize: false

    color: "transparent"

    property var edgeSize: Meui.Theme.bigRadius

    property alias headerBar : _header.sourceComponent
    property alias content: _content.data

    function toggleMaximized() {
        if (root.visibility === Window.Maximized) {
            root.showNormal();
        } else {
            root.showMaximized();
        }
    }

    // Left bottom edge
    MouseArea {
        height: edgeSize
        width: height
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        cursorShape: Qt.SizeBDiagCursor
        propagateComposedEvents: true
        preventStealing: false
        visible: root.visibility !== Window.Maximized
        z: 999

        onPressed: mouse.accepted = false

        DragHandler {
            grabPermissions: TapHandler.CanTakeOverFromAnything
            target: null
            onActiveChanged: if (active) { root.startSystemResize(Qt.LeftEdge | Qt.BottomEdge) }
        }
    }

    // Right bottom edge
    MouseArea {
        height: edgeSize
        width: height
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        cursorShape: Qt.SizeFDiagCursor
        propagateComposedEvents: true
        preventStealing: false
        visible: root.visibility !== Window.Maximized
        z: 999

        onPressed: mouse.accepted = false

        DragHandler {
            grabPermissions: TapHandler.CanTakeOverFromAnything
            target: null
            onActiveChanged: if (active) { root.startSystemResize(Qt.RightEdge | Qt.BottomEdge) }
        }
    }

    // Bottom edge
    MouseArea {
        height: edgeSize / 2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: edgeSize * 2
        anchors.rightMargin: edgeSize * 2
        cursorShape: Qt.SizeVerCursor
        visible: root.visibility !== Window.Maximized
        z: 999

        onPressed: mouse.accepted = false

        DragHandler {
            grabPermissions: TapHandler.CanTakeOverFromAnything
            target: null
            onActiveChanged: if (active) { root.startSystemResize(Qt.BottomEdge) }
        }
    }

    // Left edge
    MouseArea {
        width: edgeSize / 2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: edgeSize
        anchors.bottomMargin: edgeSize * 2
        cursorShape: Qt.SizeHorCursor
        visible: root.visibility !== Window.Maximized
        z: 999

        onPressed: mouse.accepted = false

        DragHandler {
            grabPermissions: TapHandler.CanTakeOverFromAnything
            target: null
            onActiveChanged: if (active) { root.startSystemResize(Qt.LeftEdge) }
        }
    }

    // Right edge
    MouseArea {
        width: edgeSize / 2
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: edgeSize
        anchors.bottomMargin: edgeSize * 2
        cursorShape: Qt.SizeHorCursor
        visible: root.visibility !== Window.Maximized
        z: 999

        onPressed: mouse.accepted = false

        DragHandler {
            grabPermissions: TapHandler.CanTakeOverFromAnything
            target: null
            onActiveChanged: if (active) { root.startSystemResize(Qt.RightEdge) }
        }
    }

    Rectangle {
        id: _background
        anchors.fill: parent
        anchors.margins: 0
        radius: root.visibility !== Window.Maximized ? Meui.Theme.bigRadius : 0
        color: Meui.Theme.backgroundColor
        antialiasing: true

        Behavior on color {
            ColorAnimation {
                duration: 250
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            radius: parent.radius
            border.color: "black"
            opacity: 0.7
            antialiasing: true
            visible: root.visibility !== Window.Maximized
            z: 999
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: 1
            color: "transparent"
            radius: parent.radius
            border.color: Meui.Theme.disabledTextColor
            antialiasing: true
            visible: root.visibility !== Window.Maximized && Meui.Theme.darkMode
            z: 999
        }

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Item {
                width: _background.width
                height: _background.height

                Rectangle {
                    anchors.fill: parent
                    radius: _background.radius
                }
            }
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Item {
                id: _titlebar
                Layout.fillWidth: true
                height: 40
                visible: hideHeaderOnMaximize ? root.visibility !== Window.Maximized : true

                Item {
                    anchors.fill: parent

                    TapHandler {
                        onTapped: if (tapCount === 2) toggleMaximized()
                        gesturePolicy: TapHandler.DragThreshold
                    }

                    DragHandler {
                        acceptedDevices: PointerDevice.GenericPointer
                        grabPermissions:  PointerHandler.CanTakeOverFromItems | PointerHandler.CanTakeOverFromHandlersOfDifferentType | PointerHandler.ApprovesTakeOverByAnything
                        onActiveChanged: if (active) { root.startSystemMove() }
                    }
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.rightMargin: Meui.Units.smallSpacing
                    spacing: Meui.Units.largeSpacing

                    Loader {
                        id: _header
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    WindowButton {
                        size: 35
                        source: "qrc:/meui/kit/images/" + (Meui.Theme.darkMode ? "dark/" : "light/") + "minimize.svg"
                        visible: root.visibility !== Window.Maximized
                        onClicked: root.showMinimized()
                    }

                    WindowButton {
                        size: 35
                        source: "qrc:/meui/kit/images/" + (Meui.Theme.darkMode ? "dark/" : "light/") + "maximize.svg"
                        visible: root.visibility !== Window.Maximized
                        onClicked: root.toggleMaximized()
                    }

                    WindowButton {
                        size: 35
                        source: "qrc:/meui/kit/images/" + (Meui.Theme.darkMode ? "dark/" : "light/") + "close.svg"
                        visible: root.visibility !== Window.Maximized
                        onClicked: root.close()
                    }
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                RowLayout {
                    id: _content
                    anchors.fill: parent
                    anchors.rightMargin: edgeSize / 2
                }
            }
        }
    }
}
