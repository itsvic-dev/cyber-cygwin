import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import MeuiKit 1.0 as Meui

Meui.RoundedRect {
    id: root
    visible: true

    width: 300
    height: 60

    opacity: 0.9

    property var margin: 10

    RowLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: root.margin

        IconButton {
            id: volumeButton
            implicitWidth: root.height * 0.6
            implicitHeight: root.height * 0.6
            visible: Volume.isValid
            source: "qrc:/icons/" + (Meui.Theme.darkMode ? "dark" : "light") + "/" + Volume.iconName + ".svg"
            onLeftButtonClicked: Volume.toggleMute()
        }

        Slider {
            id: slider
            from: 0
            to: 100
            stepSize: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            value: Volume.volume
            onValueChanged: {
                Volume.setVolume(value)

                if (Volume.isMute && value > 0)
                    Volume.setMute(false)
            }
        }
    }
}
