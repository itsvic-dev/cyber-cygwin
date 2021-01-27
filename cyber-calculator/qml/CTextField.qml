import QtQuick 2.0
import QtQuick.Controls 2.2

TextField {
    id: textField
    selectByMouse: true
    horizontalAlignment: TextInput.AlignRight
    focus: Qt.StrongFocus
    font.pixelSize: 24

    property int selectStart
    property int selectEnd
    property int curPos

    background: Rectangle {
        border.width: 0
        color: "transparent"
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.IBeamCursor
        acceptedButtons: Qt.RightButton

        onClicked: {
            selectStart = textField.selectionStart;
            selectEnd = textField.selectionEnd;
            curPos = textField.cursorPosition;
            contextMenu.x = mouse.x;
            contextMenu.y = mouse.y;
            contextMenu.open();
            textField.cursorPosition = curPos;
            textField.select(selectStart, selectEnd);
        }
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: "Cut"
            onTriggered: {
                textField.cut()
            }
        }
        MenuItem {
            text: "Copy"
            onTriggered: {
                textField.copy()
            }
        }
        MenuItem {
            text: "Paste"
            onTriggered: {
                textField.paste()
            }
        }
    }
}
