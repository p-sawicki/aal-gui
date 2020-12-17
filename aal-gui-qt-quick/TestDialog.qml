import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtCharts 2.0
import backend 1.0

Dialog {
    modality: Qt.NonModal
    title: "Test"
    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            GridLayout {
                columns: 2
                Text {
                    text: "Min size"
                }
                SpinBox {
                    id: minSpinBox
                    from: 0
                    to: 2000 * 1000 * 1000
                    editable: true
                    value: 1000
                }
                Text {
                    text: "Max size"
                }
                SpinBox {
                    id: maxSpinBox
                    from: 0
                    to: 2000 * 1000 * 1000
                    editable: true
                    value: 20000
                }
                Text {
                    text: "Step"
                }
                SpinBox {
                    id: stepSpinBox
                    from: 0
                    to: 2000 * 1000 * 1000
                    editable: true
                    value: 1000
                }
                Text {
                    text: "Repeat"
                }
                SpinBox {
                    id: repeatSpinBox
                    from: 0
                    to: 2000 * 1000 * 1000
                    editable: true
                    value: 1
                }
            }
            ComboBox {
                id: algorithmComboBox
                model: ["Dynamic programming", "Graph-based", "Brute force",]
            }

            RowLayout {
                Button {
                    id: startButton
                    text: "Start"
                    onClicked: {
                        chart.removeAllSeries();
                        chart.createSeries(ChartView.SeriesTypeLine,
                                                        algorithmComboBox.currentText, axisX, axisY)
                        runner.start()
                        progress.visible = true
                    }
                }
                Button {
                    id: stopButton
                    text: "Stop"
                    onClicked: runner.cancel()
                }
            }

            ProgressBar {
                id: progress
                padding: 2
                visible: false
                from: minSpinBox.value
                to: maxSpinBox.value
            }
        }

        ChartView {
            id: chart
            antialiasing: true
            width: 400
            height: 300

            ValueAxis {
                id: axisY
                gridVisible: true
                tickCount: 5
                min: 0
                max: 1
            }

            ValueAxis {
                id: axisX
                min: 0
                max: 1
                gridVisible: true
                tickCount: 5
            }
        }
    }

    TestRunner {
        id: runner
        min: minSpinBox.value
        max: maxSpinBox.value
        step: stepSpinBox.value
        repeats: repeatSpinBox.value
        algorithm: algorithmComboBox.currentIndex

        onUpdated: {
            chart.series(0).append(bricks, time)
            axisY.max = time
            chart.setAxisY(axisY, chart.series(0))
            axisX.max = bricks
            chart.setAxisX(axisX, chart.series(0))
            progress.value = bricks
        }

        onFinished: progress.visible = false
    }
}
