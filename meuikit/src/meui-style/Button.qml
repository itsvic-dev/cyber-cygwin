import QtQuick 2.4
import QtQuick.Templates 2.2 as T
import MeuiKit 1.0 as Meui
import QtQuick.Controls.impl 2.2

T.Button
{
    id: control
    implicitWidth: Math.max(background.implicitWidth, contentItem.implicitWidth + Meui.Units.smallSpacing)
    implicitHeight: background.implicitHeight
    hoverEnabled: true

    /*icon.width: Meui.Units.iconSizes.small
    icon.height: Meui.Units.iconSizes.small

    icon.color: control.enabled ? (control.highlighted ? control.Meui.Theme.highlightColor : control.Meui.Theme.textColor) : control.Meui.Theme.disabledTextColor
    spacing: Meui.Units.smallSpacing*/

    contentItem: Label {
        text: control.text
        font: control.font
        //icon: control.icon
        color: !control.enabled ? control.Meui.Theme.disabledTextColor :
        control.highlighted || control.pressed ? control.Meui.Theme.highlightedTextColor : control.Meui.Theme.textColor
        //spacing: control.spacing
        //mirrored: control.mirrored
        //display: control.display
        //alignment: Qt.AlignCenter
    }

    background: Rectangle {
        implicitWidth:  (Meui.Units.iconSizes.medium * 3) + Meui.Units.largeSpacing
        implicitHeight: Meui.Units.iconSizes.medium + Meui.Units.smallSpacing

        color: control.pressed ? Meui.Theme.highlightColor : control.Meui.Theme.backgroundColor
        border.color: control.activeFocus || control.pressed ? Meui.Theme.highlightColor :
                      Qt.tint(Meui.Theme.textColor, Qt.rgba(Meui.Theme.backgroundColor.r, Meui.Theme.backgroundColor.g, Meui.Theme.backgroundColor.b, 0.7))
        border.width: Meui.Units.devicePixelRatio
        radius: Meui.Theme.smallRadius
    }
}
