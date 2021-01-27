import QtQuick 2.9
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import MeuiKit 1.0 as Meui

Rectangle {
    color: "transparent"
    antialiasing: true

    Image {
        id: icon
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            bottom: label.top
            margins: 2 * 10
        }

        property real size: height

        source: "image://icontheme/" + model.iconName
        sourceSize.width: height
        sourceSize.height: height
        width: height
        height: width

        ColorOverlay {
            id: colorOverlay
            anchors.fill: icon
            source: icon
            color: "#000000"
            opacity: 0.5
            visible: iconMouseArea.pressed
        }
    }

    Menu {
        id: _itemMenu

        modal: true

        MenuItem {
            text: qsTr("Open")
            onTriggered: launcherModel.launch(model.appId)
        }
    }

    MouseArea {
        id: iconMouseArea
        anchors.fill: icon
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: {
            if (mouse.button == Qt.LeftButton)
                launcherModel.launch(model.appId)
            else if (mouse.button == Qt.RightButton)
                _itemMenu.popup()
        }
    }

    TextMetrics {
        id: fontMetrics
        font.family: label.font.family
        text: label.text
    }

    Label {
        id: label

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            margins: 10
        }

        text: model.name
        elide: Text.ElideRight
        textFormat: Text.PlainText
        wrapMode: "WordWrap"
        horizontalAlignment: Text.AlignHCenter
        width: parent.width - 2 * 10
        height: fontMetrics.height
        color: "white"
    }
}
