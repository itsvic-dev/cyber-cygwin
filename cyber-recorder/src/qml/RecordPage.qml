import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Recorder 1.0
import MeuiKit 1.0 as Meui

Page {
    id: control

    property bool isStopped: AudioRecorder.state === AudioRecorder.StoppedState
    property bool isPaused: AudioRecorder.state === AudioRecorder.PausedState

    signal finished()

    function record() {
        if (isStopped || isPaused) {
            AudioRecorder.record()
        } else {
            AudioRecorder.pause()
        }
    }

    function stop() {
        AudioRecorder.pause()
    }

    Connections {
        target: AudioRecorder
        function onError(error) {
            console.warn("Error on the recorder", error)
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: Meui.Units.largeSpacing

                Label {
                    id: timeText
                    Layout.alignment: Qt.AlignHCenter
                    text: isStopped ? "00:00:00" : Utils.formatTime(AudioRecorder.duration)
                }

                Visualization {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    showLine: true
                    height: Meui.Units.gridUnit * 15
                    maxBarHeight: Meui.Units.gridUnit * 5
                    animationIndex: AudioRecorder.prober.animationIndex
                    volumes: AudioRecorder.prober.volumesList
                }
            }
        }

        Item {
            id: bottomBar
            Layout.fillWidth: true
            height: 100

            Rectangle {
                anchors.fill: parent
                color: Meui.Theme.secondBackgroundColor
            }

            RowLayout {
                anchors.fill: parent

                IconButton {
                    source: Meui.Theme.darkMode ? "qrc:/images/stop-dark.svg" : "qrc:/images/stop-light.svg"
                    Layout.alignment: Qt.AlignCenter
                    onClicked: {
                        saveDialog.open()
                        control.stop()
                        saveDialog.open()
                    }
                }
            }
        }
    }

    Dialog {
        id: saveDialog
        modal: true

        x: (control.width - saveDialog.width) / 2
        y: (control.height - saveDialog.height) / 2

        onVisibleChanged: {
            if (visible)
                recordingName.text = RecordingModel.nextDefaultRecordingName()
        }

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                Label {
                    Layout.alignment: Qt.AlignVCenter
                    text: qsTr("Name")
                }

                TextField {
                    id: recordingName
                    placeholderText: RecordingModel.nextDefaultRecordingName()
                    text: RecordingModel.nextDefaultRecordingName()
                }
            }

            RowLayout {
                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: qsTr("Done")
                    onClicked: {
                        AudioRecorder.setRecordingName(recordingName.text)
                        AudioRecorder.stop();
                        recordingName.text = ""
                        saveDialog.close()
                        control.finished()
                    }
                }

                Button {
                    text: qsTr("Delete")
                    onClicked: {
                        AudioRecorder.reset()
                        saveDialog.close()
                        control.finished()
                    }
                }

                Item {
                    Layout.fillWidth: true
                }
            }
        }
    }
}
