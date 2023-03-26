import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12

import "Components"
import "Components/Global.js" as Global
Content {
    title: "Channel sorting"
    signal saveOrder(string jsonSettings);
    function clear() {
        myTable.clear();
    }
    function getData(dataStr, index) {
        if (!(index > 0)) return "N/A";
        let tokens = dataStr.split(/[,\.;]/);
        return tokens[(+index) - 1] || "N/A";
    }
    function addItem(elmStr) {
//        if (elm.status !== "Enabled") return;
        console.log(elmStr);
        let elm = JSON.parse(elmStr);
        elm.selected = false;
        myTable.addItem(elm);
    }
    function moveUp(idx) {
        if (myTable.model.count <= 1) return;
        if (idx <= 1) return;
        myTable.model.move(idx, idx - 1, 1);
    }
    function moveDown(idx) {
        if (myTable.model.count <= 1) return;
        if (idx >= myTable.model.count - 1 || idx < 1) return;
        myTable.model.move(idx, idx + 1, 1);
    }
    function findSelected() {
        for (let i = 1; i < myTable.model.count; i++) {
            let obj = myTable.model.get(i);
            console.log(obj.name, obj.selected);
            if (obj.selected) return i;
        }
        return -1;
    }
    MyTable {
        id: myTable

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: Global.topMargin1 * 2
        anchors.bottomMargin: 10
        anchors.right: parent.right

        header: `{
            "sensor": "Channel Slot", "name": "Name", "status": "Status", "channelIndex": "cOrder"
        }`
        delegate: Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: -1
            height: undefined
            BorderedText {
                label: sensor
                width: 135
                isHeader: index === 0
                isSelected: selected
                isDisabled: status !== "Enabled"
                onTriggered: myTable.doSelect(index);
            }

            BorderedText {
                label: name
                width: 250
                isHeader: index === 0
                isSelected: selected
                isDisabled: status !== "Enabled"
                onTriggered: myTable.doSelect(index);
            }

//            BorderedText {
//                label: status
//                width: 80
//                isHeader: index === 0
//                isSelected: selected
//                isDisabled: status !== "Enabled"
//                onTriggered: myTable.doSelect(index);
//            }

//            BorderedText {
//                label: channelIndex
//                width: 80
//                isHeader: index === 0
//                isSelected: selected
//                isDisabled: status !== "Enabled"
//                onTriggered: myTable.doSelect(index)
//            }

            BorderedText {
                label: index ? index : "SeqNo"
                width: 120
                isHeader: index === 0
                isSelected: selected
                isDisabled: status !== "Enabled"
                onTriggered: myTable.doSelect(index);
            }
        }
    }
    Item {
        anchors.right: parent.right
        anchors.top: parent.top
        width: 600
        height: 30

        RowLayout {
            spacing: 0
            anchors.fill: parent
            Item {
                Layout.fillWidth: true
            }
            Button {
                Layout.preferredWidth: 100
                text: "SAVE"
                flat: true
                onClicked: {
                    let arr = [];
                    for (let i = 1; i < myTable.model.count; i++ ) {
                        let item = myTable.model.get(i);
                        arr.push(item.sensor + "&" + item.channelIndex + "&" + i);
                    }
                    saveOrder(arr.join(";"));
                }
            }
            Button {
                text: ""
                Layout.preferredWidth: 50
                ColorIcon {
                    visible: iconSource
                    anchors.centerIn: parent
                    source: "/svg/up-arrow.svg"
                    cColor: "black"
                }
//                flat: true
                onClicked: moveUp(findSelected())
            }
            Button {
                text: ""
                Layout.preferredWidth: 50
                ColorIcon {
                    visible: iconSource
                    anchors.centerIn: parent
                    source: "/svg/down-arrow.svg"
                    cColor: "black"
                }
//                flat: true
                onClicked: moveDown(findSelected())
            }
            Item {
                Layout.preferredWidth: 5
            }
        }
    }
}
