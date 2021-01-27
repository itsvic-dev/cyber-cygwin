import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import MeuiKit 1.0 as Meui

Item {
    implicitWidth: 260

    property int itemRadiusV: 8

    property alias view: listView
    property alias model: listModel
    property alias currentIndex: listView.currentIndex

    Rectangle {
        anchors.fill: parent
        color: Meui.Theme.secondBackgroundColor
    }

    ListModel {
        id: listModel

        ListElement {
            title: qsTr("Display")
            name: "display"
            page: "qrc:/qml/DisplayPage.qml"
            iconSource: "qrc:/images/sidebar/display.svg"
        }

        ListElement {
            title: qsTr("Appearance")
            name: "appearance"
            page: "qrc:/qml/AppearancePage.qml"
            iconSource: "qrc:/images/sidebar/appearance.svg"
        }

        ListElement {
            title: qsTr("Dock")
            name: "dock"
            page: "qrc:/qml/DockPage.qml"
            iconSource: "qrc:/images/sidebar/dock.svg"
        }

        ListElement {
            title: qsTr("Wallpaper")
            name: "wallpaper"
            page: "qrc:/qml/BackgroundPage.qml"
            iconSource: "qrc:/images/sidebar/wallpaper.svg"
        }

        ListElement {
            title: qsTr("Language")
            name: "language"
            page: "qrc:/qml/LanguagePage.qml"
            iconSource: "qrc:/images/sidebar/language.svg"
        }

        ListElement {
            title: qsTr("Battery")
            name: "battery"
            page: "qrc:/qml/BatteryPage.qml"
            iconSource: "qrc:/images/sidebar/battery.svg"
        }

        ListElement {
            title: qsTr("About")
            name: "about"
            page: "qrc:/qml/AboutPage.qml"
            iconSource: "qrc:/images/sidebar/about.svg"
        }
    }

    ColumnLayout {
        anchors {
            fill: parent
            margins: Meui.Units.largeSpacing
        }

        Label {
            text: qsTr("Settings")
            font.bold: true
            font.pointSize: 18
            leftPadding: 16
            Layout.alignment: Qt.AlignTop
        }

        Item {
            height: Meui.Units.smallSpacing
        }

        ListView {
            id: listView
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: listModel

            spacing: Meui.Units.largeSpacing

            ScrollBar.vertical: ScrollBar {}

            delegate: Item {
                id: item
                implicitWidth: listView.width
                implicitHeight: 48

                property bool isCurrent: listView.currentIndex === index

                Rectangle {
                    anchors.fill: parent

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton
                        onClicked: listView.currentIndex = index
                    }

                    radius: Meui.Theme.bigRadius
                    color: isCurrent ?
                        Meui.Theme.highlightColor
                        : mouseArea.containsMouse ?
                            Qt.rgba(Meui.Theme.textColor.r,
                                    Meui.Theme.textColor.g,
                                    Meui.Theme.textColor.b,
                                    0.1)
                            : "transparent"
                    smooth: true
                    Behavior on color {
                        ColorAnimation {
                            duration: 125
                        }
                    }
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: Meui.Units.largeSpacing * 2
                    spacing: Meui.Units.largeSpacing

                    Image {
                        id: icon
                        width: 16
                        height: width
                        source: model.iconSource
                        sourceSize: Qt.size(width, height)

                        ColorOverlay {
                            id: colorOverlay
                            anchors.fill: icon
                            source: icon
                            color: isCurrent ? Meui.Theme.highlightedTextColor : Meui.Theme.textColor
                            opacity: 1
                            visible: true
                        }
                    }

                    Label {
                        id: itemTitle
                        text: model.title
                        color: isCurrent ? Meui.Theme.highlightedTextColor : Meui.Theme.textColor

                        Behavior on color {
                            ColorAnimation {
                                duration: 125
                            }
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
