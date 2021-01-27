import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Recorder 1.0
import MeuiKit 1.0 as Meui

Item {
    id: control

    signal recordClicked()

    ColumnLayout {
        anchors.fill: parent
        spacing: Meui.Units.largeSpacing

        ListView {
            id: recordingView
            model: RecordingModel
            leftMargin: Meui.Units.largeSpacing
            rightMargin: Meui.Units.largeSpacing
            topMargin: Meui.Units.largeSpacing
            bottomMargin: Meui.Units.largeSpacing
            spacing: Meui.Units.largeSpacing
            clip: true
            currentIndex: -1

            Layout.fillHeight: true
            Layout.fillWidth: true

            ScrollBar.vertical: ScrollBar {}

            onCurrentIndexChanged: {
                AudioPlayer.stop()
                AudioPlayer.setPosition(0)
            }

            Label {
                anchors.centerIn: parent
                text: qsTr("No recordings yet")
                visible: recordingView.count === 0
            }

            delegate: MouseArea {
                id: item

                property Recording recording: modelData
                property bool isSelected: recordingView.currentIndex === index
                property bool isLast: index === recordingView.count - 1
                property bool isPlaying: AudioPlayer.state === AudioPlayer.PlayingState
                property var path: recording.filePath

                height: childrenRect.height
                width: parent ? parent.width : undefined
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: {
                    if (recordingView.currentIndex === index)
                        recordingView.currentIndex = -1
                    else
                        recordingView.currentIndex = index
                }

                Behavior on height {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }

                ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    RowLayout {
                        Label {
                            text: recording.fileName
                            color: Meui.Theme.darkMode ? "#FFFFFF" : "#000000"
                            elide: Label.ElideLeft
                            Layout.fillWidth: true
                        }

                        Label {
                            text: recording.recordingLength
                        }
                    }

                    Label {
                        text: recording.recordDate
                        color: Meui.Theme.disabledTextColor
                    }

                    Item {
                        height: Meui.Units.largeSpacing
                        visible: isSelected
                    }

                    Slider {
                        id: playerSlider
                        from: 0
                        to: AudioPlayer.duration
                        value: AudioPlayer.position
                        onMoved: AudioPlayer.setPosition(value)
                        visible: isSelected
                        Layout.fillWidth: true
                    }

                    Item {
                        height: Meui.Units.smallSpacing
                        visible: isSelected
                    }

                    // Play control
                    RowLayout {
                        id: bottomLayout
                        visible: isSelected
                        spacing: Meui.Units.largeSpacing

                        Item {
                            width: 32
                            height: width
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        IconButton {
                            id: controlButton
                            source: isPlaying ? Meui.Theme.darkMode ? "qrc:/images/pause-dark.svg" : "qrc:/images/pause-light.svg"
                                              : Meui.Theme.darkMode ? "qrc:/images/start-dark.svg" : "qrc:/images/start-light.svg"
                            width: 32
                            height: width

                            onClicked: {
                                var path = item.recording.filePath
                                console.log("Play: " + path)
                                if (path === AudioPlayer.mediaPath) {
                                    AudioPlayer.state === AudioPlayer.PlayingState ? AudioPlayer.pause() : AudioPlayer.play()
                                } else {
                                    AudioPlayer.setVolume(100);
                                    AudioPlayer.setMediaPath(recording.filePath)
                                    AudioPlayer.play()
                                }
                            }
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        IconButton {
                            id: deleteButton
                            source: "qrc:/images/delete.svg"
                            width: 32
                            height: width

                            onClicked: {
                                deletePromptDialog.deleteIndex = index
                                deletePromptDialog.open()
                            }
                        }

                    }

                    Rectangle {
                        width: item.width
                        height: 1
                        color: isLast ? "transparent" : Qt.rgba(Meui.Theme.textColor.r,
                                                                Meui.Theme.textColor.g,
                                                                Meui.Theme.textColor.b, 0.1)
                        visible: true
                    }
                }
            }
        }

        Item {
            height: 100
            Layout.fillWidth: true

            Rectangle {
                anchors.fill: parent
                color: Meui.Theme.secondBackgroundColor
            }

            IconButton {
                id: recordButton
                Layout.alignment: Qt.AlignHCenter
                anchors.centerIn: parent
                onClicked: control.recordClicked()
                source: Meui.Theme.darkMode ? "qrc:/images/recorder-dark.svg" : "qrc:/images/recorder-light.svg"
            }
        }
    }

    Dialog {
        id: deletePromptDialog
        modal: true

        x: (control.width - deletePromptDialog.width) / 2
        y: (control.height - deletePromptDialog.height) / 2

        property var deleteIndex: -1

        ColumnLayout {
            anchors.fill: parent

            Label {
                text: qsTr("Are you sure you want to delete this recording?")
            }

            RowLayout {
                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: qsTr("Delete")
                    onClicked: {
                        // Reset current index
                        recordingView.currentIndex = -1
                        // Delete file
                        RecordingModel.deleteRecording(deletePromptDialog.deleteIndex)
                        // Close dialog
                        deletePromptDialog.close()
                    }
                }

                Button {
                    text: qsTr("Canel")
                    onClicked: deletePromptDialog.close()
                }

                Item {
                    Layout.fillWidth: true
                }
            }
        }
    }
}
