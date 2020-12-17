import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

Dialog {
    id: root
    title: "Add a brick"
    standardButtons: StandardButton.Ok | StandardButton.Cancel

    GridLayout {
        anchors.fill: parent
        columns: 2
        Text {
            text: "Width"
        }
        DoubleSpinbox {
            id: widthSpinBox
            value: 100
        }
        Text {
            text: "Height"
        }
        DoubleSpinbox {
            id: heightSpinBox
            value: 100
        }
        Text {
            text: "Depth"
        }
        DoubleSpinbox {
            id: depthSpinBox
            value: 100
        }
    }

    onAccepted: added(widthSpinBox.realValue, heightSpinBox.realValue, depthSpinBox.realValue)

    signal added(real brickWidth, real brickHeight, real brickDepth)
}
