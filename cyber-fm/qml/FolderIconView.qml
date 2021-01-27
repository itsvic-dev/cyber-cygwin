import QtQuick 2.4
import QtQuick.Controls 2.2
import MeuiKit 1.0 as Meui

GridView {
    id: control

    property int itemSize: 128
    property bool enableLassoSelection: true

    signal leftClicked()
    signal rightClicked()
    signal itemDoubleClicked(var index)
    signal itemPressed()

    clip: true
    focus: true
    cellHeight: itemSize + Meui.Units.largeSpacing
    cellWidth: itemSize + Meui.Units.largeSpacing

    currentIndex: -1

    ScrollBar.vertical: ScrollBar {}

    property int size_

    Component.onCompleted: {
        control.size_ = control.itemSize
    }

    onItemSizeChanged: {
        control.adaptGrid()
    }

    onWidthChanged: {
        control.adaptGrid()
    }

    onHeightChanged: {
        control.adaptGrid()
    }

    function adaptGrid() {
        var fullWidth = control.width
        var realAmount = parseInt(fullWidth / control.size_, 10)
        var amount = parseInt(fullWidth / control.cellWidth, 10)

        var leftSpace = parseInt(fullWidth - ( realAmount * control.size_ ), 10)
        var size = Math.min(amount, realAmount) >= control.count ? Math.max(control.cellWidth, control.itemSize) : parseInt((control.size_) + (parseInt(leftSpace/realAmount, 10)), 10)

        control.cellWidth = size
    }

    delegate: FolderIconDelegate {
        width: control.cellWidth
        height: control.cellHeight

        onPressed: control.itemPressed()
        onDoubleClicked: control.itemDoubleClicked(index)

        onLeftClicked: {
            selection.clear()
            selection.toggleIndex(index)
        }

        onRightClicked: {
            if (!isSelected)
                selection.clear()

            selection.setIndex(index, true)

            folderItemMenu.popup()
        }
    }

    MouseArea {
        id: mouseArea
        z: -1
        anchors.fill: parent
        propagateComposedEvents: true
        preventStealing: true
        acceptedButtons:  Qt.RightButton | Qt.LeftButton

        onClicked: {
            if (mouse.button == Qt.LeftButton)
                control.leftClicked()
            else if (mouse.button == Qt.RightButton)
                control.rightClicked()
        }

        onPressed: {
            control.forceActiveFocus()

            if (mouse.source === Qt.MouseEventNotSynthesized) {
                if (control.enableLassoSelection && mouse.button === Qt.LeftButton) {
                    selection.clear()
                    selectLayer.visible = true;
                    selectLayer.x = mouseX;
                    selectLayer.y = mouseY;
                    selectLayer.newX = mouseX;
                    selectLayer.newY = mouseY;
                    selectLayer.width = 0
                    selectLayer.height = 0;
                }
            }
        }

        onPositionChanged: {
            if (mouseArea.pressed && control.enableLassoSelection && selectLayer.visible) {
                if (mouseX >= selectLayer.newX) {
                    selectLayer.width = (mouseX + 10) < (control.x + control.width) ? (mouseX - selectLayer.x) : selectLayer.width;
                } else {
                    selectLayer.x = mouseX < control.x ? control.x : mouseX;
                    selectLayer.width = selectLayer.newX - selectLayer.x;
                }

                if (mouseY >= selectLayer.newY) {
                    selectLayer.height = (mouseY + 10) < (control.y + control.height) ? (mouseY - selectLayer.y) : selectLayer.height;
                    if (!control.atYEnd &&  mouseY > (control.y + control.height))
                        control.contentY += 10
                } else {
                    selectLayer.y = mouseY < control.y ? control.y : mouseY;
                    selectLayer.height = selectLayer.newY - selectLayer.y;

                    if (!control.atYBeginning && selectLayer.y === 0)
                        control.contentY -= 10
                }

                // Select
                var lassoIndexes = []
                const limitX = mouse.x === selectLayer.x ? selectLayer.x + selectLayer.width : mouse.x
                const limitY =  mouse.y === selectLayer.y ?  selectLayer.y + selectLayer.height : mouse.y

                for (var i = selectLayer.x; i < limitX; i += (selectLayer.width / (control.cellWidth * 0.5))) {
                    for (var y = selectLayer.y; y < limitY; y += (selectLayer.height / (control.cellHeight * 0.5))) {
                        const index = control.indexAt(i, y + control.contentY)
                        if (!lassoIndexes.includes(index) && index>-1 && index< control.count)
                            lassoIndexes.push(index)
                    }
                }

                selection.clear()
                for (var j in lassoIndexes) {
                    selection.setIndex(lassoIndexes[j], true)
                }
            }
        }

        onReleased: {
            if (mouse.button !== Qt.LeftButton || !control.enableLassoSelection || !selectLayer.visible) {
                mouse.accepted = false
                return;
            }

            selectLayer.reset()
        }
    }

    Rectangle {
        id: selectLayer

        property int newX: 0
        property int newY: 0

        height: 0
        width: 0
        x: 0
        y: 0
        visible: false
        color: Qt.rgba(control.Meui.Theme.highlightColor.r,
                       control.Meui.Theme.highlightColor.g,
                       control.Meui.Theme.highlightColor.b, 0.2)
        opacity: 0.7

        border.width: 1
        border.color: control.Meui.Theme.highlightColor

        function reset() {
            selectLayer.x = 0;
            selectLayer.y = 0;
            selectLayer.newX = 0;
            selectLayer.newY = 0;
            selectLayer.visible = false;
            selectLayer.width = 0;
            selectLayer.height = 0;
        }
    }
}
