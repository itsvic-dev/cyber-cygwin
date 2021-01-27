import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import MeuiKit 1.0 as Meui
import Cyber.FileManager 1.0

Item {
    id: control
    implicitWidth: 201

    PlacesModel {
        id: placesModel
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: placesView
                anchors.fill: parent
                model: placesModel
                clip: true
                spacing: Meui.Units.largeSpacing

                ScrollBar.vertical: ScrollBar {}
                flickableDirection: Flickable.VerticalFlick

                delegate: SidebarItem {
                    id: listItem
                    text: displayName
                    onClicked: folderModel.setPath(path)
                    highlighted: folderModel.path === path
                }
            }
        }
    }
}
