import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import MeuiKit 1.0 as Meui
import Cyber.FileManager 1.0

ApplicationWindow {
    id: control
    width: mainLayout.implicitWidth + Meui.Units.largeSpacing * 4
    height: mainLayout.implicitHeight + Meui.Units.largeSpacing * 4

    minimumWidth: width
    minimumHeight: height
    maximumHeight: height
    maximumWidth: width

    flags: Qt.Dialog
    modality: Qt.WindowModal

    background: Rectangle {
        color: Meui.Theme.backgroundColor
    }

    property int index: -1
    signal accepted()

    onIndexChanged: {
        control.title = folderModel.get(index, FolderListModel.FileNameRole)
    }

    onVisibleChanged: {
        if (visible)
            okButton.forceActiveFocus()
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.leftMargin: Meui.Units.largeSpacing * 2
        anchors.rightMargin: Meui.Units.largeSpacing * 2
        anchors.topMargin: Meui.Units.largeSpacing
        anchors.bottomMargin: Meui.Units.largeSpacing
        spacing: Meui.Units.largeSpacing

        Item {
            id: image
            width: 128
            height: width
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            Image {
                id: icon
                source: "image://icontheme/application-x-desktop"
                visible: status == Image.Ready
                sourceSize.width: image.height
                sourceSize.height: image.height
                width: sourceSize.width
                height: sourceSize.height
                fillMode: Image.PreserveAspectFit
                asynchronous: true
                smooth: true
            }
        }

        Label {
            text: qsTr("This file is executable, do you want to execute it?")
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            id: buttonsLayout
            spacing: Meui.Units.smallSpacing

            Button {
                id: okButton
                text: qsTr("Execute")
                Layout.fillWidth: true
                focus: true
                onClicked: {
                    control.accepted()
                    control.close()
                }
            }

            Button {
                text: qsTr("Cancel")
                Layout.fillWidth: true
                onClicked: control.close()
            }
        }
    }
}
