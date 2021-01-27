import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import MeuiKit 1.0 as Meui

ApplicationWindow {
    visible: true
    width: 950
    height: 650
    title: qsTr("Settings")
    id: rootWindow

    minimumWidth: 900
    minimumHeight: 600
    // hideHeaderOnMaximize: true

    /*headerBar: Item {
        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            implicitWidth: 260
            color: Meui.Theme.secondBackgroundColor
        }
    }*/

    background: Rectangle {
        color: Meui.Theme.backgroundColor
    }

    RowLayout {
        anchors.fill: parent

        SideBar {
            id: sideBar
            Layout.fillHeight: true

            onCurrentIndexChanged: {
                switchPageFromIndex(currentIndex)
            }
        }

        StackView {
            id: stackView
            Layout.fillWidth: true
            Layout.fillHeight: true
            initialItem: Qt.resolvedUrl(sideBar.model.get(0).page)
            clip: true

            pushEnter: Transition {}
            pushExit: Transition {}
        }
    }

    function switchPageFromIndex(index) {
        stackView.push(Qt.resolvedUrl(sideBar.model.get(index).page))
    }

    function switchPageFromName(pageName) {
        for (var i = 0; i < sideBar.model.count; ++i) {
            if (pageName === sideBar.model.get(i).name) {
                switchPageFromIndex(i)
                sideBar.view.currentIndex = i

                // If the window is minimized, it needs to be displayed agin.
                rootWindow.show()
                rootWindow.raise()
            }
        }
    }
}
