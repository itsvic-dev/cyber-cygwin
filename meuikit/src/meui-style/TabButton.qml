import QtQuick 2.9
import QtQuick.Templates 2.2 as T
import MeuiKit 1.0 as Meui

T.TabButton {
    id: control

    // implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
    //                         implicitContentWidth + leftPadding + rightPadding)
    // implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
    //                          implicitContentHeight + topPadding + bottomPadding)
    implicitHeight: Meui.Units.iconSizes.medium + Meui.Units.smallSpacing

    padding: 0
    spacing: 0

    contentItem: Text {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        text: control.text
        font: control.font
        color: !control.enabled ? control.Meui.Theme.disabledTextColor : control.checked ? control.Meui.Theme.textColor : control.Meui.Theme.textColor
    }
}