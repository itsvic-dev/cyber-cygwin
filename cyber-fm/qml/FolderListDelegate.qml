import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Cyber.FileManager 1.0
import MeuiKit 1.0 as Meui

Item {
    id: control
    width: ListView.view.width - Meui.Units.largeSpacing * 2
    height: 48

    property color hoverColor: Qt.rgba(Meui.Theme.textColor.r,
                                       Meui.Theme.textColor.g,
                                       Meui.Theme.textColor.b, 0.1)

    signal pressed()
    signal leftClicked()
    signal rightClicked()
    signal doubleClicked()

    Rectangle {
        anchors.fill: parent
        radius: Meui.Theme.bigRadius
        color: isSelected ? Meui.Theme.highlightColor : itemMouseArea.containsMouse ? control.hoverColor : "transparent"
    }

    MouseArea {
        id: itemMouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        drag.axis: Drag.XAndYAxis

        onPressed: control.pressed()

        onClicked: {
            if (mouse.button === Qt.LeftButton)
                control.leftClicked()
            else if (mouse.button === Qt.RightButton)
                control.rightClicked()
        }

        onDoubleClicked: control.doubleClicked()
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Meui.Units.largeSpacing
        anchors.rightMargin: Meui.Units.largeSpacing
        spacing: Meui.Units.largeSpacing

        Item {
            id: iconItem
            Layout.fillHeight: true
            width: parent.height * 0.8

            Image {
                id: icon
                anchors.centerIn: iconItem
                width: iconItem.width
                height: width
                sourceSize.width: width
                sourceSize.height: height
                source: iconName
                visible: !image.visible
                asynchronous: true
            }

            Image {
                id: image
                width: parent.height * 0.8
                height: width
                anchors.centerIn: iconItem
                sourceSize: Qt.size(icon.width, icon.height)
                source: iconSource
                visible: image.status == Image.Ready
                fillMode: Image.PreserveAspectFit
                asynchronous: true
                smooth: false
            }
        }

        Label {
            text: fileName
            Layout.fillWidth: true
            color: isSelected ? Meui.Theme.highlightedTextColor : Meui.Theme.textColor
        }

        Label {
            text: DateUtils.friendlyTime(modifiedDate)
            color: isSelected ? Meui.Theme.highlightedTextColor : Meui.Theme.textColor
        }
    }
}
