import QtQuick 2.0
import QtQuick.Controls 2.12
import Exam 1.0

Item {
    property var keyT: "INT"
    property var valueT: "INT"
    property bool keyUse: true
    property bool valUse: true
    property alias keyfields: keyFields
    property alias valfields: valFields
    property alias combobox: comboBox

    signal start()

    Rectangle {
        id: workSpace
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 202

        Rectangle {
            id: separator
            width: 2
            color: "black"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        ComboBox {
            id: comboBox
            width: 190
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            height: 40
            anchors.margins: 5
        }
        Text {
            id: keyText
            text: "<strong>KEY</strong>"
            anchors.left: parent.left
            anchors.verticalCenter: keyFields.verticalCenter
            anchors.margins: 5
            visible: keyUse
        }
        TextFields {
            id: keyFields
            anchors.left: keyText.right
            anchors.right: separator.left
            anchors.top: comboBox.bottom
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.topMargin: 15
            type: keyT
            height: {
                if(keyT == "BOOK")
                    return 40*5 + 5*4;
                return 40
            }
            visible: keyUse
        }
        Text {
            id: valText
            text: "<strong>VAL</strong>"
            anchors.left: parent.left
            anchors.verticalCenter: valFields.verticalCenter
            anchors.margins: 5
            visible: valUse
        }
        TextFields {
            id: valFields
            anchors.left: valText.right
            anchors.right: separator.left
            type: valueT
            height: {
                if(valueT == "BOOK")
                    return 40*5 + 5*4;
                return 40
            }

            anchors.top: keyUse ? keyFields.bottom : comboBox.bottom
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.topMargin: 15
            visible: valUse
        }
        Button {
            width: 120
            height: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Start Operation"
            onClicked: start()
        }
    }
    Text {
        id: ttext
        text: "<strong>STRUCTURE(s):</strong>"
        anchors.top: parent.top
        anchors.left: workSpace.right
        anchors.margins: 5
    }
    ScrollView {
        id: scroll
        anchors.left: workSpace.right
        anchors.right: parent.right
        anchors.top: ttext.bottom
        anchors.margins: 5
        height: 200
        TextArea {
            id: structureText
            text: UiController.vectorBefore
            padding: 2
            wrapMode: TextArea.WordWrap
            readOnly: true
        }
    }
    Text {
        id: tttext
        text: "<strong>OPERATION RESULTS:</strong>"
        anchors.top: scroll.bottom
        anchors.left: workSpace.right
        anchors.margins: 5
    }
    ScrollView {
        id: sscroll
        anchors.left: workSpace.right
        anchors.right: parent.right
        anchors.top: tttext.bottom
        height: 200
        anchors.margins: 5
        TextArea {
            id: result
            readOnly: true
            text: UiController.vectorAfter
            padding: 2
            wrapMode: TextArea.WordWrap
        }
    }
    Text {
        id: ttttext
        text: "<strong>TIME:</strong>"
        anchors.left: workSpace.right
        anchors.leftMargin: 5
        anchors.verticalCenter: timeresults.verticalCenter
    }
    TextArea {
        id: timeresults
        anchors.left: ttttext.right
        anchors.right: parent.right
        anchors.top: sscroll.bottom
        anchors.margins: 5
        readOnly: true
        //TEXT TIME RESULTS
    }
}
