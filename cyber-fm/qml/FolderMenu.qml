import QtQuick 2.4
import QtQuick.Controls 2.2

Menu {
    id: control
    modal: true

    MenuItem {
        id: newFolderAction
        text: qsTr("New Folder")

        onTriggered: {

        }
    }

    MenuItem {
        id: pasteAction
        text: qsTr("Paste")
    }

    MenuItem {
        id: selectAllAction
        text: qsTr("Select All")
        onTriggered: selection.selectAll()
    }

    MenuSeparator { }

    MenuItem {
        id: openInTerminal
        text: qsTr("Open in Terminal")
        onTriggered: folderModel.openTerminal(folderModel.path)
    }
}
