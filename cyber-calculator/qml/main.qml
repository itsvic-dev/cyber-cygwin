import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.cyber.calculator 1.0
import MeuiKit 1.0 as Meui

ApplicationWindow {
    visible: true
    width: 350
    height: 550
    minimumWidth: 350
    minimumHeight: 550
    title: qsTr("Calculator")
    id: rootWindow

    property var edgeMargin: 10

    CalcEngine {
        id: calcEngine

        Component.onCompleted: {
            console.log("load calc engine finished")
        }
    }

    background: Rectangle {
        color: Meui.Theme.backgroundColor
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: edgeMargin
        // Layout.fillWidth: true
        // Layout.fillHeight: true
        // Layout.margins: edgeMargin

        Zone {
            id: zone
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        ButtonsPanel {
            id: buttonsPanel
        }
    }

    function calculate(evalText) {
        var res = calcEngine.eval(evalText)
        return res
    }

}
