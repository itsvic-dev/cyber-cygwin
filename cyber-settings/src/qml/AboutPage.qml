import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import MeuiKit 1.0 as Meui
import Cyber.Settings 1.0

ItemPage {
    headerTitle: qsTr("About")

    About {
        id: about
    }

    Scrollable {
        anchors.fill: parent
        contentHeight: layout.implicitHeight

        ColumnLayout {
            id: layout
            anchors.fill: parent

            Image {
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                width: 128
                height: width
                sourceSize: Qt.size(width, height)
                source: "qrc:/images/cyber-logo.svg"
            }

            Label {
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                text: qsTr("CyberOS")
                font.pointSize: 24
                font.bold: true
                bottomPadding: Meui.Units.largeSpacing * 2
                leftPadding: Meui.Units.largeSpacing * 2
                rightPadding: Meui.Units.largeSpacing * 2
            }

            // OS
            Label {
                text: qsTr("OS Info")
                color: Meui.Theme.disabledTextColor
                topPadding: Meui.Units.largeSpacing
                bottomPadding: Meui.Units.smallSpacing
            }

            StandardItem {
                key: qsTr("Operating System")
                value: about.osName
            }

            StandardItem {
                key: qsTr("Kernel Version")
                value: about.kernelVersion
            }

            StandardItem {
                key: qsTr("RAM Size")
                value: about.memorySize
            }

            StandardItem {
                key: qsTr("Username")
                value: about.userName
            }

            StandardItem {
                key: qsTr("Hostname")
                value: about.hostname
            }

            HorizontalDivider {}

            // Cyber Info
            Label {
                text: qsTr("Other Info")
                color: Meui.Theme.disabledTextColor
                topPadding: Meui.Units.largeSpacing * 2
                bottomPadding: Meui.Units.smallSpacing
            }

            StandardItem {
                key: qsTr("Cyber Settings Build")
                value: about.settingsVersion
            }

            StandardItem {
                key: qsTr("Developers")
                value: about.developers
            }
        }
    }
}
