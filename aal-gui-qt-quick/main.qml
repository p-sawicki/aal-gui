import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Dialogs 1.0
import backend 1.0

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("AAL project GUI")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Bricks")
            Action {
                text: qsTr("&New")
                onTriggered: brickInfo.visible = true
            }
            Action {
                text: qsTr("&Clear")
                onTriggered: tableModel.clearBricks()
            }

            Action {
                text: qsTr("&Import")
                onTriggered: importDialog.visible = true
            }
            Action {
                text: qsTr("&Export")
                onTriggered: exportDialog.visible = true
            }
            Action {
                text: qsTr("&Generate")
                onTriggered: generateDialog.visible = true
            }
        }
        Menu {
            title: qsTr("&Solve")
            Action {
                text: qsTr("&Dynamic Programming")
                onTriggered: tableModel.solve(0)
                enabled: !tableModel.solving
            }
            Action {
                text: qsTr("&Graph-based")
                onTriggered: tableModel.solve(1)
                enabled: !tableModel.solving
            }
            Action {
                text: qsTr("&Brute force")
                onTriggered: tableModel.solve(2)
                enabled: !tableModel.solving
            }
            MenuSeparator {}
            Action {
                id: undoAction
                enabled: tableModel.canUnsolve
                text: qsTr("&Undo")
                onTriggered: tableModel.unsolve()
            }
        }
        Menu {
            title: qsTr("&Test")
            Action {
                text: qsTr("T&est")
                onTriggered: testDialog.visible = true
            }
        }
    }

    TableView {
        id: tableView
        anchors.fill: parent
        interactive: false
        ScrollBar.vertical: ScrollBar {

        }

        model: BricksTableModel {
            id: tableModel
            onSolved: {
                resultText.text = "Result: " + depth + "\nTime: " + time + "s"
                resultDialog.visible = true
            }
        }

        delegate: Rectangle {
            implicitWidth: 200
            implicitHeight: 50
            Text {
                text: parseFloat(display).toFixed(2)
                font.pointSize: 10
                anchors.centerIn: parent
            }
        }
    }

    FileDialog {
        id: importDialog
        title: "Select a file to import from"
        onAccepted: tableModel.import(fileUrl)
    }

    FileDialog {
        id: exportDialog
        title: "Select a file to export to"
        onAccepted: tableModel.export(fileUrl)
    }

    BrickInfoDialog {
        id: brickInfo
        onAdded: tableModel.addBrick(brickWidth, brickHeight, brickDepth)
    }

    GenerateDialog {
        id: generateDialog
        onGenerate: tableModel.generateBricks(amount, minValue, maxValue)
    }

    TestDialog {
        id: testDialog
    }

    Dialog {
        id: resultDialog
        anchors.centerIn: parent
        Text {
            id: resultText
            anchors.fill: parent
        }
    }
}
