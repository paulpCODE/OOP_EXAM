import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Exam 1.0


Window {
    id: window
    visible: true
    width: 640
    height: 640
    title: qsTr("Hello World")
    minimumHeight: 640
    minimumWidth: 480
    color: "lightsteelblue"

    SwipeView {
        id: mainView

        anchors.fill:parent
        interactive: false

        Item {
            id: zero
            visible: mainView.currentIndex == 0 ? true : false
            Button {
                id: conrainerB
                text: "Container"
                font.pixelSize: 40
                width: parent.width/2
                height: parent.height/4
                anchors.bottom: setB.top
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: mainView.currentIndex = 1
            }
            Button {
                id: setB
                text: "Set"
                font.pixelSize: 40
                width: parent.width/2
                height: parent.height/4
                anchors.centerIn: parent
                onClicked: mainView.currentIndex = 2
            }
            Button {
                id: sortsB
                text: "Sorts"
                font.pixelSize: 40
                width: parent.width/2
                height: parent.height/4
                anchors.top: setB.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: mainView.currentIndex = 3
            }
        }
        SwipeView {
            id: container
            interactive: false
            visible: mainView.currentIndex == 1 ? true : false

            Component.onCompleted: {
                choiceBaseC.i.connect(plusIndex)
                choiceDataC.i.connect(plusIndex)
            }

            ChoiceBase {
                id: choiceBaseC
                visible: container.currentIndex == 0 ? true : false
                signal i()
                linkedlist.onClicked: {
                    //ENUM LINKED_LIST_CONTAINER
                    i()
                }
                rbtree.onClicked: {
                    //ENUM RB_TREE_CONTAINER
                    i()
                }
                splaytree.onClicked: {
                    //ENUM SPLAY_TREE_CONTAINER
                    i()
                }
                linearprobinghash.onClicked: {
                    //ENUM LINEAR_PROBINNG_HASH_CONTAINER
                    i()
                }
                separatechaininghash.onClicked: {

                    i()
                }
            }

            ChoiceData {
                id:choiceDataC
                visible: container.currentIndex == 1 ? true : false
            }

            Operations {
                id: operationsC
                keyT: choiceDataC.keyT
                valueT: choiceDataC.valueT
                visible: container.currentIndex == 2 ? true : false
                combobox.model: [
                    "Get Element by Key",
                    "Edit Element by Key",
                    "Add Element by Key",
                    "Delete Element by Key",
                    "Gey All Keys",
                    "Get All Values",
                    "Get Pairs <Key, Value>"
                ]
                combobox.onCurrentIndexChanged: {
                    keyfields.clearFields()
                    valfields.clearFields()
                    switch(combobox.currentIndex) {
                    case 0: keyUse = true; valUse = false;
                        break;
                    case 1: keyUse = true; valUse = true;
                        break;
                    case 2: keyUse = true; valUse = true;
                        break;
                    case 3: keyUse = true; valUse = false;
                        break;
                    case 4: keyUse = false; valUse = false;
                        break;
                    case 5: keyUse = false; valUse = false;
                        break;
                    case 6: keyUse = false; valUse = false;
                        break;
                    default: break;
                    }
                }
            }

            function plusIndex() {
                choiceDataC.onAllElements()
                container.currentIndex += 1;
            }

            function startOperation() {
                switch(operationsC.combobox.currentIndex) {
                    //CALL OPERATIONS
                }
            }
        }
        SwipeView {
            id: set
            interactive: false
            visible: mainView.currentIndex == 2 ? true : false

            Component.onCompleted: {
                choiceBaseS.i.connect(plusIndex)
                choiceDataS.i.connect(plusIndex)
            }

            ChoiceBase {
                id: choiceBaseS
                visible: set.currentIndex == 0 ? true : false
                signal i()
                linkedlist.onClicked: {
                    //ENUM LINKED_LIST_CONTAINER
                    i()
                }
                rbtree.onClicked: {
                    //ENUM RB_TREE_CONTAINER
                    i()
                }
                splaytree.onClicked: {
                    //ENUM SPLAY_TREE_CONTAINER
                    i()
                }
                linearprobinghash.onClicked: {
                    //ENUM LINEAR_PROBINNG_HASH_CONTAINER
                    i()
                }
                separatechaininghash.onClicked: {

                    i()
                }
            }
            ChoiceData {
                id: choiceDataS
                visible: set.currentIndex == 1 ? true : false
            }

            Operations {
                id: operationsS
                keyT: choiceDataS.keyT
                valueT: choiceDataS.valueT
                visible: set.currentIndex == 2 ? true : false
                combobox.model: [
                    "Check Belong by Key",
                    "Insert Element by Key",
                    "Delete Element by Key"
                ]
                combobox.onCurrentIndexChanged: {
                    keyfields.clearFields()
                    valfields.clearFields()
                    switch(combobox.currentIndex) {
                    case 0: keyUse = true; valUse = false;
                        break;
                    case 1: keyUse = true; valUse = true;
                        break;
                    case 2: keyUse = true; valUse = false;
                        break;
                    default: break;
                    }
                }
            }


            function plusIndex() {
                choiceDataS.onAllElements()
                set.currentIndex += 1;
            }
            function startOperation() {
                switch(operationsS.combobox.currentIndex) {
                    //CALL OPERATIONS
                }
            }
        }
        SwipeView {
            id: sorts
            interactive: false
            visible: mainView.currentIndex == 3 ? true : false

            Component.onCompleted: {
                choiceDataSort.i.connect(plusIndex)
            }

            ChoiceData {
                id:choiceDataSort
                visible: sorts.currentIndex == 0 ? true : false
                keyUse: false
                addElement.onClicked: {
                    parent.selectSortType()
                    if(valueT == "BOOK")
                        UiController.addDataToSort(value.firstfield.text,
                                                   value.secondfield.text,
                                                   value.thirdfield.text,
                                                   value.fourfield.text,
                                                   value.fivefield.text)
                    else
                       UiController.addDataToSort(value.firstfield.text)
                }
                continueButton.onClicked: {
                    if(generateChecked) {
                        parent.selectSortType()
                        UiController.fillSortVectorWithRandomData(amount.text)
                    }
                    UiController.flushDataToSort()
                }

            }

            Operations {
                id: operationsSort
                keyT: choiceDataSort.keyT
                valueT: choiceDataSort.valueT
                visible: sorts.currentIndex == 1 ? true : false
                Component.onCompleted: start.connect(parent.startOperation)
                combobox.model: [
                    "SELECTION SORT",
                    "INSERTION SORT",
                    "QUICK SORT",
                    "RECURSIVE MERGE SORT",
                    "ITERATIVE MERGE SORT"
                ]
                combobox.onCurrentIndexChanged: {
                    keyfields.clearFields()
                    valfields.clearFields()
                    switch(combobox.currentIndex) {
                    case 0: keyUse = false; valUse = false; UiController.selectSort(SortChoice.SELECTION_SORT)
                        break;
                    case 1: keyUse = false; valUse = false; UiController.selectSort(SortChoice.INSERTION_SORT)
                        break;
                    case 2: keyUse = false; valUse = false; UiController.selectSort(SortChoice.QUICK_SORT)
                        break;
                    case 3: keyUse = false; valUse = false; UiController.selectSort(SortChoice.MERGE_RECURSIVE_SORT)
                        break;
                    case 4: keyUse = false; valUse = false; UiController.selectSort(SortChoice.MERGE_ITERATIVE_SORT)
                        break;
                    default: console.log("WRONG ENUM IN SORT SELECT")
                        break;
                    }
                }
            }

            function plusIndex() {
                choiceDataSort.onAllElements()
                sorts.currentIndex += 1;
            }
            function startOperation() {
                UiController.startSort()
            }
            function selectSortType() {
                if(choiceDataSort.valueT == "INT")
                    UiController.selectSortType(DataTypes.INT)
                else if (choiceDataSort.valueT == "STRING")
                    UiController.selectSortType(DataTypes.STRING)
                else if (choiceDataSort.valueT == "BOOK")
                    UiController.selectSortType(DataTypes.BOOK)
                else
                    console.log("WRONG DATA TYPE")
            }
        }
    }
}
