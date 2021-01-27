import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import MeuiKit 1.0 as Meui

Item {
    id: control

    property var size: 32
    height: size
    width: size

    property color hoveredColor: Meui.Theme.darkMode ? Qt.lighter(Meui.Theme.backgroundColor, 1.5)
                                                   : Qt.darker(Meui.Theme.backgroundColor, 1.2)
    property color pressedColor: Meui.Theme.darkMode ? Qt.lighter(Meui.Theme.backgroundColor, 1.3)
                                                     : Qt.darker(Meui.Theme.backgroundColor, 1.3)
    property alias source: image.source
    signal clicked()

    Rectangle {
        id: background
        anchors.fill: parent
        anchors.margins: size * 0.1
        radius: control.height / 2
        color: mouseArea.pressed ? pressedColor : mouseArea.containsMouse ? control.hoveredColor : Meui.Theme.backgroundColor
        visible: mouseArea.containsMouse
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: control.clicked()
    }

    Image {
        id: image
        objectName: "image"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        sourceSize: Qt.size(width, height)
        cache: true
        asynchronous: false
    }
}