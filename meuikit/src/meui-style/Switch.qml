import QtQuick 2.4
import QtQuick.Templates 2.2 as T
import MeuiKit 1.0 as Meui

T.Switch {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: implicitBackgroundHeight + topInset + bottomInset

    opacity: control.enabled ? 1.0 : 0.5

    padding: 8
    spacing: 8

    indicator: SwitchIndicator {
        x: text ? (control.mirrored ? control.width - width - control.rightPadding : control.leftPadding) : control.leftPadding + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2
        control: control
    }

    contentItem: Label {
        leftPadding: control.indicator && !control.mirrored ? control.indicator.width + control.spacing : 0
        rightPadding: control.indicator && control.mirrored ? control.indicator.width + control.spacing : 0

        text: control.text
        font: control.font
        color: control.enabled ? Meui.Theme.textColor : Meui.Theme.disabledTextColor
        elide: Label.ElideRight
        verticalAlignment: Label.AlignVCenter
    }
}