import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import MeuiKit 1.0 as Meui

Item {
    id: control

    height: mainLayout.implicitHeight + Meui.Theme.smallRadius * 2

    property alias key: keyLabel.text
    property alias value: valueLabel.text
    property alias image: keyImage.source

    Layout.fillWidth: true

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.leftMargin: Meui.Units.largeSpacing
        anchors.rightMargin: Meui.Units.largeSpacing

        Image {
            id: keyImage
        }

        Label {
            id: keyLabel
            color: Meui.Theme.textColor
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            id: valueLabel
            color: Meui.Theme.disabledTextColor
        }
    }
}
