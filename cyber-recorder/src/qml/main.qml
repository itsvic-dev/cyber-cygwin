import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Recorder 1.0
import MeuiKit 1.0 as Meui

ApplicationWindow {
    id: root

    minimumWidth: 400
    minimumHeight: 550
    width: 400
    height: 550

    visible: true
    title: qsTr("Recorder")

    HomePage {
        id: homePage

        onRecordClicked: {
            AudioRecorder.record()
            stackView.push(recordPage)
        }
    }

    RecordPage {
        id: recordPage
        visible: false

        onFinished: {
            stackView.pop()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Meui.Theme.backgroundColor
        StackView {
            id: stackView
            anchors.fill: parent
            initialItem: homePage
        }
    }
}
