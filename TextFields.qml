import QtQuick 2.0
import QtQuick.Controls 2.12


Item {
    property var type: "INT"
    property bool checkUse: true
    property alias firstfield: firstField
    property alias secondfield: secondField
    property alias thirdfield: thirdField
    property alias fourfield: fourField
    property alias fivefield: fiveField

    TextField {
        id: firstField
        width: parent.width
        anchors.left: parent.left
        height: 40
        //        visible: generate.checked ? false : true
        anchors.top: parent.top
        placeholderText: {
            switch(type) {
            case "INT": return "INT";
            case "STRING": return "STRING";
            case "BOOK": return "PUBLISHER";
            default: break;
            }
        }
        validator: {
            if (type == "INT")
                return v
            return r
        }
    }
    TextField {
        id: secondField
        width: parent.width
        anchors.left: parent.left
        height: 40
        visible: type == "BOOK" ? true : false
        anchors.top: firstField.bottom
        anchors.topMargin: 5
        placeholderText: "GENRE"
    }
    TextField {
        id: thirdField
        width: parent.width
        anchors.left: parent.left
        height: 40
        visible: type == "BOOK" ? true : false
        anchors.top: secondField.bottom
        anchors.topMargin: 5
        placeholderText: "YEAR OF PUBLISHING"
        validator: IntValidator {bottom: 1; top: 2020}
    }
    TextField {
        id: fourField
        width: parent.width
        anchors.left: parent.left
        height: 40
        visible: type == "BOOK" ? true : false
        anchors.top: thirdField.bottom
        anchors.topMargin: 5
        placeholderText: "AUTHOR"
    }
    TextField {
        id: fiveField
        width: parent.width
        anchors.left: parent.left
        height: 40
        visible: type == "BOOK" ? true : false
        anchors.top: fourField.bottom
        anchors.topMargin: 5
        placeholderText: "BOOK TITLE"
    }

    IntValidator {
        id: v
        bottom: 0
        top: 1000000
    }

    RegExpValidator {id: r}

    function clearFields() {
        firstField.text = ""
        secondField.text = ""
        thirdField.text = ""
        fourField.text = ""
        fiveField.text = ""
    }
    function checkFields() {
        if(!checkUse)
            return true
        if(
                firstField.text == "" ||
                (secondField.text == "" && secondField.visible) ||
                (thirdField.text == "" && thirdField.visible) ||
                (fourField.text == "" && fourField.visible) ||
                (fiveField.text == "" && fiveField.visible))
            return false;
        return true;
    }
}
