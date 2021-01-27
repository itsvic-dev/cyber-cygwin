import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import MeuiKit 1.0 as Meui

Page {
    id: page

    property alias headerVisible: headerItem.visible
    property string headerTitle

    background: Rectangle {
        color: "transparent"
    }

    header: Item {
        id: headerItem
        width: headerLayout.implicitWidth
        height: headerLayout.implicitHeight + Meui.Units.largeSpacing

        RowLayout {
            id: headerLayout
            anchors.topMargin: Meui.Units.largeSpacing
            anchors.leftMargin: Meui.Units.largeSpacing * 2
            anchors.rightMargin: Meui.Units.largeSpacing * 2
            anchors.bottomMargin: Meui.Units.largeSpacing * 2
            anchors.fill: parent
            spacing: Meui.Units.largeSpacing

            Label {
                id: headerLabel
                text: page.headerTitle
                font.pointSize: 18
                font.bold: true
                Layout.fillWidth: true
            }
        }
    }
}
