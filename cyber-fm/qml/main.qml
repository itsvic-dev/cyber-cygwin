import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Cyber.FileManager 1.0

import MeuiKit 1.0 as Meui

ApplicationWindow {
    id: root
    width: settings.width
    height: settings.height
    minimumWidth: 900
    minimumHeight: 600
    visible: true
    title: qsTr("File Manager")

    //hideHeaderOnMaximize: false
    //headerBarHeight: 40 + Meui.Units.largeSpacing
    //backgroundColor: Meui.Theme.secondBackgroundColor
    background: Rectangle {
        color: Meui.Theme.secondBackgroundColor
    }

    property alias selection: folderModel.selection
    property QtObject settings: GlobalSettings { }

    onClosing: {
        settings.width = root.width
        settings.height = root.height
    }

    FolderListModel {
        id: folderModel
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: Meui.Units.largeSpacing

        Item {
            id: header
            height: 48
            Layout.fillWidth: true
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Meui.Units.largeSpacing
                anchors.rightMargin: Meui.Units.largeSpacing
                anchors.topMargin: Meui.Units.largeSpacing
                spacing: Meui.Units.smallSpacing

                IconButton {
                    Layout.fillHeight: true
                    implicitWidth: height
                    source: Meui.Theme.darkMode ? "qrc:/images/dark/go-previous.svg" : "qrc:/images/light/go-previous.svg"
                }

                IconButton {
                    Layout.fillHeight: true
                    implicitWidth: height
                    source: Meui.Theme.darkMode ? "qrc:/images/dark/go-next.svg" : "qrc:/images/light/go-next.svg"
                }

                PathBar {
                    id: pathBar
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                IconButton {
                    Layout.fillHeight: true
                    implicitWidth: height
                    source: Meui.Theme.darkMode ? "qrc:/images/dark/grid.svg" : "qrc:/images/light/grid.svg"
                    onClicked: settings.viewMethod = 1
                }

                IconButton {
                    Layout.fillHeight: true
                    implicitWidth: height
                    source: Meui.Theme.darkMode ? "qrc:/images/dark/list.svg" : "qrc:/images/light/list.svg"
                    onClicked: settings.viewMethod = 0
                }
            }
        }

        Item {
            id: bottomControls
            Layout.fillWidth: true
            Layout.fillHeight: true
            anchors.top: header.bottom
            anchors.bottom: root.bottom

            RowLayout {
                anchors.fill: parent
                anchors.topMargin: Meui.Units.largeSpacing
                anchors.leftMargin: Meui.Units.largeSpacing
                anchors.rightMargin: 0
                anchors.bottomMargin: Meui.Units.largeSpacing
                spacing: Meui.Units.largeSpacing

                SideBar {
                    Layout.fillHeight: true
                }

                FolderPage {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
}
