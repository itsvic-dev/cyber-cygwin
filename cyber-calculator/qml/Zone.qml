import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import MeuiKit 1.0 as Meui

Item {
    id: zone

    ColumnLayout {
        id: layout
        anchors.fill: parent

        ListView {
            id: listView
            model: ListModel { id: historyModel }
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true

            flickableDirection: Flickable.VerticalFlick
            // boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar {}

            onCountChanged: {
                // Automatically scroll list to end / bottom
                listView.currentIndex = count - 1
            }

            delegate: Row {
                Label {
                    horizontalAlignment: Qt.AlignRight
                    leftPadding: 10
                    rightPadding: 24
                    topPadding: 10
                    text: historyModel.get(index).text
                    elide: Text.ElideMiddle
                    width: rootWindow.width
                    height: 50
                    color: Meui.Theme.disabledTextColor

                    MouseArea {
                        hoverEnabled: true
                    }
                }
            }
        }

        CTextField {
            id: textField
            height: 50
            Layout.fillWidth: true
            Keys.onReturnPressed: appendToTextField('=')
            Keys.onEnterPressed: appendToTextField('=')
        }
    }

    function appendToTextField(text) {
        if (text === '=') {
            var res = calculate(textField.text)
            if (res !== '') {
                var expressionText = textField.text
                textField.text = res;

                // If the expression and the result area equal,
                // it will not be added to the ListView
                if (expressionText !== res) {
                    expressionText = expressionText + " = " + res
                    historyModel.append({"text": expressionText})
                }
            }
        } else if (text === 'AC') {
            textField.clear()
        } else if (text === 'BACK') {
            // backspace
            textField.remove(textField.cursorPosition, textField.cursorPosition - 1)
        } else {
            textField.insert(textField.cursorPosition, text)
        }
    }
}
