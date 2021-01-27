import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Rectangle {
    id: buttonsPanel

    property alias computedHeight: view.height

    height: computedHeight

    color: "transparent"

    ButtonsView {
        id: view
        anchors.fill: parent
        labels: ['AC', '%', '←', '÷', '7', '8', '9', '×', '4', '5', '6', '−', '1', '2', '3', '+', '0', '.', '()', '=']
        targets: ['AC', '%', 'BACK', '/', '7', '8', '9', '*', '4', '5', '6', '-', '1', '2', '3', '+', '0', '.', '()', '=']
        onButtonClicked: zone.appendToTextField(strToAppend)
    }
}
