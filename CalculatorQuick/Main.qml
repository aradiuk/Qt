import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic


ApplicationWindow {
    id: window
    width: 450
    height: 225
    minimumWidth: 450
    minimumHeight: 225
    maximumWidth: 450
    maximumHeight: 225
    visible: true
    color: "gray"
    title: qsTr("Calculator")
    property string leftArgument: ""
    property string rightArgument: ""
    property string operation: ""

    function clear() {
        leftArgument = "";
        rightArgument = "";
        operation = "";
        output.text = leftArgument + " " + operation + " " + rightArgument
    }

    function calculate() {
        if (leftArgument == "" || rightArgument == "" || operation == "") {
            return
        }
        let left = parseInt(leftArgument, 10)
        let right = parseInt(rightArgument, 10)
        let result
        switch (operation) {
            case "+":
                result = left + right
                break
            case "-":
                result = left - right
                break
            case "*":
                result = left * right
                break
            case "/":
                if (right == 0) {
                    result = 0;
                    break;
                }
                result = left / right
                break
        }
        output.text = String(result)
        leftArgument = output.text;
        rightArgument = "";
        operation = "";
    }

    function setOperation(newOperation: string) {
        operation = newOperation
        output.text = leftArgument + " " + operation + " " + rightArgument
    }

    function addNum(num: string) {
        if (operation == "") {
            if (leftArgument != "" || num != "0") {
                leftArgument += num
            }
        } else {
            if (rightArgument != "" || num != "0") {
                rightArgument += num
            }
        }
        output.text = leftArgument + " " + operation + " " + rightArgument
    }

    component MyButton: Button {
        width: 100
        height: 40
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        Rectangle {
            id: output
            property alias text: result.text
            anchors.horizontalCenter: parent.horizontalCenter
            width: 420
            height: 40
            color: "lightgray"
            radius: 10

            Text {
                id: result
                font.pixelSize: 20
                anchors.centerIn: parent
                color: "black"
            }
        }
        RowLayout {
            anchors.top: output.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            GridLayout {
                id: numPanel
                columns: 3
                Repeater {
                    model: 9
                    MyButton {
                        text: index + 1
                        onClicked: addNum(text)
                    }
                }
                MyButton {
                    text: "Clear"
                    onClicked: clear()
                }
                MyButton {
                    text: "0"
                    onClicked: addNum(text)
                }
                MyButton {
                    text: "="
                    onClicked: calculate()
                }
            }
            GridLayout {
                anchors.left: numPanel.right
                anchors.top: numPanel.top
                anchors.leftMargin: 5
                columns: 1
                MyButton {
                    text: "+"
                    onClicked: setOperation(text)
                }
                MyButton {
                    text: "-"
                    onClicked: setOperation(text)
                }
                MyButton {
                    text: "*"
                    onClicked: setOperation(text)
                }
                MyButton {
                    text: "/"
                    onClicked: setOperation(text)
                }
            }
        }
    }

}
