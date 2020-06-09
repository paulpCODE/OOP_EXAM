import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    property alias linkedlist: linked_list
    property alias rbtree: rb_tree
    property alias splaytree: splay_tree
    property alias linearprobinghash: linear_probing_hash
    property alias separatechaininghash: separate_chaining_hash

    Rectangle {
        id: leftR
        color: "lightsteelblue"
        width: parent.width/3
        height: parent.height
        anchors.left: parent.left
        Text {
            id: listsText
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            text: "<strong>LISTS</strong>"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: linked_list
            font.pixelSize: 22
            text: "Linked_list"
            anchors.top: listsText.bottom
            anchors.left: parent.left
            width: parent.width - 20
            anchors.margins: 10
            height: 100
        }
    }
    Rectangle {
        id: centerR
        color: "lightsteelblue"
        width: parent.width/3
        height: parent.height
        anchors.left: leftR.right
        Text {
            id: treesText
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            text: "<strong>TREES</strong>"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Button {
            id: rb_tree
            font.pixelSize: 22
            text: "RB tree"
            anchors.top: treesText.bottom
            anchors.left: parent.left
            width: parent.width - 20
            anchors.margins: 10
            height: 100
        }
        Button {
            id: splay_tree
            font.pixelSize: 22
            text: "SPLAY tree"
            anchors.top: rbtree.bottom
            anchors.left: parent.left
            width: parent.width - 20
            anchors.margins: 10
            height: 100
        }
    }
    Rectangle {
        Text {
            id: hashText
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            text: "<strong>HASH TABLES</strong>"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        id: rightR
        color: "lightsteelblue"
        width: parent.width/3
        height: parent.height
        anchors.left: centerR.right
        Button {
            id: linear_probing_hash
            font.pixelSize: 22
            text: "Linear Probing Hash"
            anchors.top: hashText.bottom
            anchors.left: parent.left
            width: parent.width - 20
            anchors.margins: 10
            height: 100
        }
        Button {
            id: separate_chaining_hash
            font.pixelSize: 22
            text: "Separate Chaining Hash"
            anchors.top: linear_probing_hash.bottom
            anchors.left: parent.left
            width: parent.width - 20
            anchors.margins: 10
            height: 100
        }
    }
}
