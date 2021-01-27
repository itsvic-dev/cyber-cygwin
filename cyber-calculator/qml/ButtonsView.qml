import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import MeuiKit 1.0 as Meui

Rectangle {
    id: buttonsView
    implicitHeight: grid.implicitHeight
    implicitWidth: grid.implicitWidth

    property var labels
    property var targets
    property int rowsCount: 5
    property int fontSize: 17

    signal buttonClicked(string strToAppend)
    signal buttonLongPressed(string strToAppend)

    color: "transparent"

    Grid {
        id: grid
        columns: getColumnsCount()
        rows: buttonsView.rowsCount

        Repeater {
            model: buttonsView.labels

            MouseArea {
                id: buttonRect
                width: (rootWindow.width - rootWindow.edgeMargin * 2) / 4
                height: 50
                onClicked: buttonsView.buttonClicked(targets[index])
                onPressAndHold: buttonsView.buttonLongPressed(targets[index])

                Rectangle {
                    anchors.centerIn: parent
                    radius: 5
                    width: parent.width - radius
                    height: parent.height - radius
                    color: buttonRect.pressed ? Meui.Theme.highlightColor : Meui.Theme.secondBackgroundColor

                    Behavior on color {
                        ColorAnimation {
                            duration: 50
                        }
                    }
                }

                Text {
                    anchors.fill: parent
                    text: modelData
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    font.pixelSize: buttonsView.fontSize

                    color: text === "+" || text === "−" || text === "×" || text === "÷"
                    ? buttonRect.pressed
                        ? Meui.Theme.textColor
                        : Meui.Theme.highlightColor
                    : Meui.Theme.textColor
                    font.bold: text === "+" || text === "−" || text === "×" || text === "÷"
                }
            }
        }
    }

    function getColumnsCount() {
        return Math.ceil(buttonsView.labels.length / buttonsView.rowsCount);
    }
}
