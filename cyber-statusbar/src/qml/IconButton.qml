import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import MeuiKit 1.0 as Meui

Item {
    id: control

    property url source
    property real size: 24
    property string popupText

    signal leftButtonClicked
    signal rightButtonClicked

    Meui.PopupTips {
        id: popupTips
        popupText: control.popupText
    }

    onPopupTextChanged: {
        if (popupTips.visible) {
            popupTips.popupText = control.popupText
            updatePopupTipsPosition()
        }
    }

    function updatePopupTipsPosition() {
        popupTips.position = Qt.point(control.mapToGlobal(0, 0).x + (control.width / 2 - popupTips.width / 2),
                                      control.height + 1)
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        hoverEnabled: control.visible ? true : false

        onContainsMouseChanged: {
            if (containsMouse && !VolumeControlWindow.visible) {
                popupTips.popupText = control.popupText
                updatePopupTipsPosition()
                popupTips.show()
            } else {
                popupTips.hide()
            }
        }

        onClicked: {
            if (mouse.button === Qt.LeftButton)
                control.leftButtonClicked()
            else if (mouse.button === Qt.RightButton)
                control.rightButtonClicked()

            popupTips.hide()
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 1
        radius: parent.height * 0.2

        color: {
            if (mouseArea.containsMouse) {
                if (mouseArea.containsPress)
                    return (Meui.Theme.darkMode) ? Qt.rgba(255, 255, 255, 0.3) : Qt.rgba(0, 0, 0, 0.3)
                else
                    return (Meui.Theme.darkMode) ? Qt.rgba(255, 255, 255, 0.2) : Qt.rgba(0, 0, 0, 0.2)
            }

            return "transparent"
        }
    }

    Image {
        id: iconImage
        anchors.centerIn: parent
        width: parent.height * 0.7
        height: width
        sourceSize.width: width
        sourceSize.height: width
        source: control.source
        asynchronous: true
    }
}
