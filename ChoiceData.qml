import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id:mainI

    property var keyT: keyFields.type
    property var valueT: valueFields.type
    property bool keyUse: true

    signal i()
    Rectangle {
        anchors.centerIn: parent
        width: parent.width - 100
        height: parent.height - 50
        border.color: "black"
        radius: 10
        border.width: 2
        ComboBox {
            id: keyType
            model: ["Key type: Int", "Key type: String", "Key type: Book"]
            anchors.top: parent.top
            font.pixelSize: 16
            anchors.left: parent.left
            anchors.margins: 20
            visible: keyUse
            width: parent.width/2.5
            height: 40
            onCurrentIndexChanged: {
                keyFields.clearFields()
            }
        }
        ComboBox {
            id: valueType
            model: ["Value type: Int", "Value type: String", "Value type: Book"]
            anchors.top: parent.top
            font.pixelSize: 16
            anchors.right: parent.right
            anchors.margins: 20
            width: keyUse? parent.width / 2.5 : parent.width - 40
            height: 40
            onCurrentIndexChanged: {
                valueFields.clearFields()
            }
        }
        TextFields {
            id: keyFields
            width: parent.width / 2.5
            height: {
                if(keyT == "BOOK")
                    return 40*5 + 5*4;
                return 40
            }

            anchors.left: parent.left
            anchors.top: keyType.bottom
            anchors.leftMargin: 20
            anchors.topMargin: 5
            checkUse: keyUse
            visible: generate.checked || !keyUse ? false : true
            type: {
                switch(keyType.currentIndex) {
                case 0: return "INT";
                case 1: return "STRING";
                case 2: return "BOOK";
                default: break;
                }
            }
        }
        TextFields {
            id: valueFields
            width:keyUse? parent.width / 2.5 : parent.width - 40
            height: {
                if(valueT == "BOOK")
                    return 40*5 + 5*4;
                return 40
            }
            anchors.right: parent.right
            anchors.top: keyType.bottom
            anchors.rightMargin: 20
            anchors.topMargin: 5
            visible: generate.checked ? false : true
            type: {
                switch(valueType.currentIndex) {
                case 0: return "INT";
                case 1: return "STRING";
                case 2: return "BOOK";
                default: break;
                }
            }
        }

        TextField {
            id: amountField
            width: parent.width/2.5
            height: 40
            anchors.centerIn: parent
            placeholderText: "AMOUNT(1..100k)"
            visible: generate.checked? true : false
            validator: IntValidator {bottom: 1; top: 100000}
        }

        Button {
            id:addelB
            anchors.top: {
                if(keyT == "BOOK")
                    return keyFields.bottom
                return valueFields.bottom
            }

            anchors.topMargin: 10
            visible: {
                if(generate.checked)
                    return false;

                if(keyFields.checkFields() && valueFields.checkFields())
                    return true;
                return false;
            }
            anchors.horizontalCenter: parent.horizontalCenter
            height: 40
            width: 120
            text: "Add element"
            onClicked: {
                //ADD EL TO VECTOR
                keyType.enabled = false
                valueType.enabled = false
                keyFields.clearFields()
                valueFields.clearFields()
                amountField.text = ""
            }
        }
        Button {
            id: continueB
            width: 100
            height: 30
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 7
            text: "Continue"
            visible: generate.visible ? false : true
            onClicked: {
                if(generate.checked) {
                    //CREATE NUMBER OF ELEMENTS AND PUSH TO VECTOR
                    //CREATE STRUCTURE
                    i()
                }
                else {
                    //CREATE STRUCTURE
                    i()
                }
            }
        }



        Switch {
            id: generate
            text: "Generate"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 5
            visible: {
                if(amountField.text == "" && keyType.enabled)
                    return true
                return false
            }
        }
    }
    function onAllElements() {
        keyType.enabled = true
        valueType.enabled = true
        generate.checked = false
    }
}
