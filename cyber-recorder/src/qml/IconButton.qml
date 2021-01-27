import QtQuick 2.4
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

MouseArea {
    id: control
    width: 64
    height: width

    property alias source: icon.source
    property alias overlayColor: colorOverlay.color

    Image {
        id: icon
        anchors.fill: parent
        sourceSize: Qt.size(width, height)

        ColorOverlay {
            id: colorOverlay
            anchors.fill: icon
            source: icon
            color: "#FFFFFF"
            opacity: 0.3
            visible: control.pressed
        }
    }
}
