import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

Dialog {
    id: root
    title: "Generate bricks"
    standardButtons: StandardButton.Ok | StandardButton.Cancel
    GridLayout {
        anchors.fill: parent
        columns: 2
        Text {
            text: "Amount"
        }
        SpinBox {
            id: amountSpinBox
            editable: true
            from: 0
            to: 2000 * 1000 * 1000
            value: 100
        }
        Text {
            text: "Min value"
        }
        DoubleSpinbox {
            id: minSpinBox
            value: 100
        }
        Text {
            text: "Max value"
        }
        DoubleSpinbox {
            id: maxSpinBox
            value: 10000
        }
    }
    
    onAccepted: generate(amountSpinBox.value, minSpinBox.realValue, maxSpinBox.realValue)
    
    signal generate(int amount, real minValue, real maxValue)
}
