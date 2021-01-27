import QtQuick 2.0
import org.cyber.launcher 1.0

Item {
    id: pagedGrid

    property var model

    property int rows
    property int columns

    property Component delegate

    readonly property var count: model.count

    readonly property int pageCount: rows * columns
    readonly property alias pages: pageView.count
    property alias currentPage: pageView.currentIndex

    // Scroll through pages using the mouse weel
    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true

        onWheel: {
            if (wheel.angleDelta.y > 0)
                pageView.decrementCurrentIndex();
            else
                pageView.incrementCurrentIndex();
        }
    }

    ListView {
        id: pageView

        anchors.fill: parent

        orientation: Qt.Horizontal
        snapMode: ListView.SnapOneItem
        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 350
        currentIndex: 0
        clip: true

        model: Math.ceil(pagedGrid.count / pageCount)

        delegate: Grid {
            id: page
            width: pagedGrid.width
            height: pagedGrid.height
            columns: pagedGrid.columns

            readonly property int pageIndex: index

            Repeater {
                model: PageModel {
                    id: pageModel
                    sourceModel: pagedGrid.model
                    startIndex: pageCount * pageIndex
                    limitCount: pageCount
                }

                delegate: pagedGrid.delegate
            }
        }
    }
}
