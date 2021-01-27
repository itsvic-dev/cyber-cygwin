import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import MeuiKit 1.0 as Meui

Item {
    id: control

    property var model: folderModel
    property var path: filePath

    signal leftClicked
    signal rightClicked
    signal doubleClicked
    signal pressed

    Drag.active: mouseArea.drag.active
    Drag.dragType: Drag.Automatic
    Drag.supportedActions: Qt.CopyAction
    Drag.keys: ["text/uri-list"]
    Drag.mimeData: { "text/uri-list": "file://" + filePath }
    Drag.hotSpot.x: control.width / 2
    Drag.hotSpot.y: control.height / 2

    property color hoveredColor: Qt.rgba(Meui.Theme.textColor.r,
                                         Meui.Theme.textColor.g,
                                         Meui.Theme.textColor.b,
                                         0.1)

    Rectangle {
        id: bg
        anchors.fill: parent
        anchors.margins: Meui.Units.largeSpacing
        radius: Meui.Theme.bigRadius
        color: isSelected ? Meui.Theme.highlightColor
                          : mouseArea.containsMouse
                            ? hoveredColor: "transparent"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        anchors.margins: Meui.Units.largeSpacing
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        drag.axis: Drag.XAndYAxis
        hoverEnabled: true

        onClicked: {
            if (mouse.button == Qt.LeftButton)
                control.leftClicked()
            else if (mouse.button == Qt.RightButton)
                control.rightClicked()
        }

        onDoubleClicked: control.doubleClicked()

        onPressed: {
            control.pressed()

            if (mouse.source !== Qt.MouseEventSynthesizedByQt) {
                if (selection.counter < 2) {
                    selection.clear()
                    selection.setIndex(index, true)
                }

                drag.target = mouseArea
                control.grabToImage(function(result) {
                    control.Drag.imageSource = result.url
                })
            } else {
                drag.target = null
            }
        }

        onReleased: {
            drag.target = null
        }
    }

    DropArea {
        id: dropArea
        anchors.fill: bg
        enabled: fileIsDir

        onEntered: {
//            if (drag.source.path === control.path)
//                enabled = false
        }

        onDropped: {
            if (drag.source) {
                // Do Move
                folderModel.model.cut(drag.source.path, filePath)
            } else {
                if (drop.hasUrls) {
                    // Do Copy
                    folderModel.model.copy(drop.urls, filePath)
                }
            }
        }
    }

    Item {
        id: contents
        anchors.fill: parent
        anchors.margins: Meui.Units.largeSpacing

        Item {
            id: iconItem
            height: parent.height * 0.7
            width: height

            anchors {
                top: parent.top
                topMargin: 2
            }

            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: icon
                anchors.fill: parent
                sourceSize: Qt.size(width, height)
                source: iconName
                visible: !image.visible
                asynchronous: true
            }

            Image {
                id: image
                anchors.fill: parent
                source: iconSource
                sourceSize: Qt.size(width, height)
                fillMode: Image.PreserveAspectFit
                visible: status === Image.Ready
                asynchronous: true
            }
        }

        Label {
            anchors {
                left: parent.left
                right: parent.right
                top: iconItem.bottom
                bottom: parent.bottom
            }

            font.pointSize: 12

            text: fileName
            // wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            elide: Text.ElideMiddle
            horizontalAlignment: Text.AlignHCenter
            color: isSelected
            ? Meui.Theme.highlightedTextColor
            : Meui.Theme.textColor
        }
    }
}
