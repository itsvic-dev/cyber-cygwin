import QtQuick 2.0
import org.cyber.launcher 1.0

PagedGrid {
    id: gridView

    // property alias query: appsProxyModel.filterPattern
    property int sideMargin: root.width * 0.1
    property int itemSize: root.height * 0.18

    columns: Math.ceil((root.width - sideMargin * 2) / itemSize)
    rows: (root.height - textField.height * 4) / itemSize

    width: columns * itemSize
    height: rows * itemSize

    model: launcherModel

    delegate: Item {
        width: gridView.itemSize
        height: width

        LauncherGridDelegate {
            id: delegate

            anchors {
                fill: parent
                margins: 10
            }
        }
    }
}
