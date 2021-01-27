import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Cyber.Settings 1.0
import MeuiKit 1.0 as Meui

ItemPage {
    headerTitle: qsTr("Wallpaper")

    Background {
        id: background
    }

    GridView {
        anchors.fill: parent
        topMargin: Meui.Units.smallSpacing
        leftMargin: Meui.Units.largeSpacing
        rightMargin: Meui.Units.largeSpacing

        cellWidth: 200
        cellHeight: 180

        clip: true
        model: background.backgrounds

        currentIndex: -1

        ScrollBar.vertical: ScrollBar {}

        delegate: Item {
            id: item

            //required property variant modelData
            property bool isSelected: modelData === background.currentBackgroundPath

            width: GridView.view.cellWidth
            height: GridView.view.cellHeight

            Rectangle {
                anchors.fill: parent
                anchors.leftMargin: Meui.Units.largeSpacing
                anchors.rightMargin: Meui.Units.largeSpacing
                anchors.topMargin: Meui.Units.smallSpacing
                anchors.bottomMargin: Meui.Units.smallSpacing
                color: "transparent"
                radius: Meui.Theme.bigRadius + Meui.Units.smallSpacing / 2

                border.color: Meui.Theme.highlightColor
                border.width: image.status == Image.Ready & isSelected ? 3 : 0

                Image {
                    id: image
                    anchors.fill: parent
                    anchors.margins: Meui.Units.smallSpacing
                    source: "file://" + modelData
                    sourceSize: Qt.size(width, height)
                    fillMode: Image.PreserveAspectCrop
                    asynchronous: true
                    mipmap: true
                    cache: false
                    opacity: 1.0

                    Behavior on opacity {
                        NumberAnimation {
                            duration: 125
                            easing.type: Easing.InOutQuad
                        }
                    }

                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: Item {
                            width: image.width
                            height: image.height

                            Rectangle {
                                anchors.fill: parent
                                radius: Meui.Theme.bigRadius
                            }
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton
                    hoverEnabled: true

                    onClicked: background.setBackground(item.modelData)

                    onEntered: function() {
                        image.opacity = 0.7
                    }
                    onExited: function() {
                        image.opacity = 1.0
                    }
                }
            }
        }
    }
}
