import QtQuick 2.4
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Material 2.2
import MeuiKit 1.0 as Meui

T.ScrollBar {
    id: control

    /*implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)*/

    padding: control.interactive ? 1 : 2
    visible: control.policy !== T.ScrollBar.AlwaysOff
    size: orientation == Qt.Horizontal ? height / width : width / height

    contentItem: Rectangle {
        radius: Meui.Theme.smallRadius
        implicitWidth: control.interactive ? 6 : 4
        implicitHeight: control.interactive ? 6 : 4

        color: control.pressed ? Meui.Theme.darkMode ? Qt.rgba(255, 255, 255, 0.4) : Qt.rgba(0, 0, 0, 0.5)
                               : Meui.Theme.darkMode ? Qt.rgba(255, 255, 255, 0.5) : Qt.rgba(0, 0, 0, 0.4)
        opacity: 0.0
    }

    states: State {
        name: "active"
        when: control.policy === T.ScrollBar.AlwaysOn || (control.active && control.size < 1.0)
    }

    transitions: [
        Transition {
            to: "active"
            NumberAnimation { target: control.contentItem; property: "opacity"; to: 1.0 }
        },
        Transition {
            from: "active"
            SequentialAnimation {
                PropertyAction{ target: control.contentItem; property: "opacity"; value: 1.0 }
                PauseAnimation { duration: 2450 }
                NumberAnimation { target: control.contentItem; property: "opacity"; to: 0.0 }
            }
        }
    ]
}
