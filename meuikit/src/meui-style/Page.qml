import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.impl 2.2
import QtQuick.Templates 2.2 as T
import MeuiKit 1.0 as Meui

T.Page {
    id: control

    leftPadding: 0
    
    topPadding: 0
    
    rightPadding: 0
    
    bottomPadding: 0
   
    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            Math.max(contentWidth,
                                     header && header.visible ? header.implicitWidth : 0,
                                     footer && footer.visible ? footer.implicitWidth : 0) + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentHeight + topPadding + bottomPadding
                             + (header && header.visible ? header.implicitHeight + spacing : 0)
                             + (footer && footer.visible ? footer.implicitHeight + spacing : 0))

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    background: Rectangle {
        color: Meui.Theme.backgroundColor
    }
}
