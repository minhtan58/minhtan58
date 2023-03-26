import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "Components"
Content {
    property string logName: "system"
    property string logKey: "L1"
    property var currentDate: new Date()
    property var allLogs: []

    function zeroPadding(n) {
        return ("0" + n).slice(-2);
    }
    function formatDate(d) {
        return d.getFullYear() + "/" + zeroPadding(d.getMonth() + 1) + "/" + zeroPadding(d.getDate())
    }
    function addItem(elm) {
        console.log("addItem-Log:" + JSON.stringify(elm));
        allLogs.push(elm);
//        myTable.addItem(elm);
    }
    signal filterLogs(string logKey, string logName, string from, string to)
    function clear() {
        allLogs.length = 0;
        myTable.clear();
    }
    function updateLogModel() {
        myTable.clear();
        for (let i = 0; i < allLogs.length; i++) {
            let item = allLogs[i];
            let d = new Date(item.time.substr(0,10));
            if( isNaN(d) || d.getFullYear() !== currentDate.getFullYear() || d.getMonth() !== currentDate.getMonth() || d.getDate() !== currentDate.getDate()) {
                console.log("Not added");
            }
            else {
                console.log(JSON.stringify(item));
                myTable.addItem(item);
            }
        }
//        for (let i = 0; i < myTable.model.count; i++) {
//            let item = myTable.model.get(i);
//            let d = new Date(item.time.substr(0,10));
//            item.hidden = isNaN(d) || d.getFullYear() !== currentDate.getFullYear() || d.getMonth() !== currentDate.getMonth() || d.getDate() !== currentDate.getDate();
//            console.log(JSON.stringify(item));
//            myTable.model.set(i, item);
//        }
    }

    title: logName + " logs"
//    Button {
//        text: "Filter"
//        onClicked: {
//            console.log("Retrieve logs");
//            filterDialog.visible = true;
//        }
//        anchors {
//            top: parent.top
//            right: parent.right
//            topMargin: 10
//            rightMargin: 10
//        }
//    }
    Dialog {
        id: filterDialog
        title: "Filter logs"
        modal: true
        visible: false
        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            clear();
            filterLogs(logKey, logName, idFrom.text, idTo.text);
            filterDialog.visible = false
        }
        onRejected: filterDialog.visible = false
        GridLayout {
            anchors {
                centerIn: parent
            }
            columns: 6
            columnSpacing: 4
            MyLabel {
                text: "From"
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyTextEdit {
                id: idFrom
                text: "2021/01/01 00:00:00"
                inputMask: "9999/99/99 99:99:99"
    //            validator: DateTimeValidator {}
                Layout.columnSpan: 3
            }
            Item {
                height: 10
                Layout.columnSpan: 6
            }
    //        ------------------------------------------------
            MyLabel {
                text: "To"
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyTextEdit {
                id: idTo
                text: "2021/01/01 00:00:00"
                inputMask: "9999/99/99 99:99:99"
    //            validator: DateTimeValidator {}
                Layout.columnSpan: 3
            }
            Item {
                height: 10
                Layout.columnSpan: 6
            }
        }
    }
    MyLogTable {
        id: myTable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 100
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10
    }
    Button {
        text: "Prev"
        anchors.top: parent.top
        anchors.left: parent.left

        onClicked: {
            console.log("Previous");
            currentDate = new Date(+currentDate - 24 * 3600 * 1000);
            dateInput.text = formatDate(currentDate);
            updateLogModel();
        }
    }
    MyTextEdit {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        id: dateInput
        text: ""
        placeholderText: "yyyy/mm/dd"
        //inputMask: "9999/99/99"

        onAccepted: {
            console.log("Accepted");
            let d = new Date(dateInput.text);
            if (isNaN(d)) {
                console.log("invalid date");
                dateInput.text = formatDate(currentDate);
            }
            else {
                currentDate = d;
                updateLogModel();
            }
        }
    }
    Button {
        anchors.top: parent.top
        anchors.right: parent.right

        text: "Next"
        onClicked: {
            console.log("Next");
            currentDate = new Date(+currentDate + 24 * 3600 * 1000);
            dateInput.text = formatDate(currentDate);
            updateLogModel();
        }
    }
}
