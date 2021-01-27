import QtQuick 2.4
import MeuiKit 1.0 as Meui

Item
{
    id: indicator
    implicitWidth: 38
    implicitHeight: 32

    property Item control
    property alias handle: handle
    property color bgColor : control.checked ? Meui.Theme.highlightColor : Qt.rgba(Meui.Theme.textColor.r, 
                                                                                   Meui.Theme.textColor.g,
                                                                                   Meui.Theme.textColor.b, 0.2)
    Rectangle {
        width: parent.width
        height: 20
        radius: height / 2
        y: parent.height / 2 - height / 2
        color: control.enabled ? bgColor : "transparent"
    }

    Rectangle {
        id: handle
        x: Math.max(2, Math.min(parent.width - width, control.visualPosition * parent.width - (width / 2)) - 2)
        y: (parent.height - height) / 2
        width: 16
        height: 16
        radius: width / 2
        color: control.enabled ? "white" : "transparent"
        Behavior on x {
            enabled: !control.pressed
            SmoothedAnimation {
                duration: 300
            }
        }
    }
}
