import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Recorder 1.0

Item {
    id: visualization

    property int maxBarHeight
    property int animationIndex // which index rectangle is being expanded
    property var volumes: []
    property bool showLine

    Component.onCompleted: {
        AudioRecorder.prober.maxVolumes = width / 4;
        AudioPlayer.prober.maxVolumes = width / 4;
    }

    onWidthChanged: {
        AudioRecorder.prober.maxVolumes = width / 4;
        AudioPlayer.prober.maxVolumes = width / 4;
    }

    // central line
    Rectangle {
        visible: showLine
        id: centralLine
        width: parent.width
        height: 3
        anchors.verticalCenter: parent.verticalCenter
        color: "#e0e0e0"
    }

    ListView {
        id: list
        model: visualization.volumes
        orientation: Qt.Horizontal

        interactive: false
        anchors.verticalCenter: centralLine.verticalCenter
        height: maxBarHeight
        width: parent.width

        delegate: Item {
            width: 4
            height: list.height

            Rectangle {
                color: "#616161"
                width: 2
                height: index === animationIndex ? 0 : 2 * maxBarHeight * modelData / 1000
                antialiasing: true
                anchors.verticalCenter: parent.verticalCenter

                Behavior on height {
                    SmoothedAnimation {
                        duration: 500
                    }
                }
            }
        }
    }
}
