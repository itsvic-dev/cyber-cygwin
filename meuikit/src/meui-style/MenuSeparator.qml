import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Templates 2.2 as T
import MeuiKit 1.0 as Meui

T.MenuSeparator {
    id: control

    implicitHeight: Meui.Units.smallSpacing + separator.height
    width: parent.width

    background: Rectangle {
        id: separator
        anchors.centerIn: control
        width: control.width - Meui.Units.largeSpacing
        height: 1
        color: Meui.Theme.textColor
        opacity: 0.3
    }
}