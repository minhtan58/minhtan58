import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import "Components"
import "Components/Global.js" as Global
Content {
    signal getSensorData(int idx, int sensorIndex, int dataFieldIndex);
    function getData(dataStr, index) {
        if (!(index > 0)) return "N/A";
        let tokens = dataStr.split(/[,\.;]/);
        return tokens[(+index) - 1] || "N/A";
    }
    function addItem(elm) {
        if (elm.status !== "Enabled") return;
        if (!elm.datasequence) return myTable.addItem(elm);
        let dataFields = Global.parseDataSequence(elm.datasequence);
        for (let i = 0; i < dataFields.length; i++) {
            if (dataFields[i].name.length > 0 ) {
                let elmClone = JSON.parse(JSON.stringify(elm));
                elmClone.name = dataFields[i].name;
                elmClone.unit = dataFields[i].unit;
                elmClone.sensorValue = getData( elm.data, dataFields[i].index );
                elmClone.dataFieldIndex = i;
                myTable.addItem(elmClone);
            }
        }
    }
    function updateSensor(idx, sensorIdx, dataFieldIdx, elm) {
        if (!elm.datasequence) return myTable.updateSensor(idx, elm);
        let dataFields = Global.parseDataSequence(elm.datasequence);

        elm.name = dataFields[dataFieldIdx].name;
        elm.unit = dataFields[dataFieldIdx].unit;
        elm.sensorValue = getData( elm.data, dataFields[dataFieldIdx].index );
        elm.dataFieldIndex = dataFieldIdx;
        myTable.updateSensor(idx, elm);
    }
    function clear() {
        myTable.clear();
    }
    function getSensorIndex(channel) {
        switch(channel[0]) {
        case "A":
            return +channel.substring(2) - 1;
        case "D":
            return +channel.substring(2) - 1 + 12;
        case "C":
            return +channel.slice(-1) - 1 + 18;
        case "R": // RS 485
            return 22;
        case "S": // SDI-12
            return 23;
        case "V":
            return +channel.substring(2) - 1 + 24;
        }
        return -1;
    }

    function updateAllSensorValues() {
        console.log("update all", myTable.model.count);
        for (let i = 1; i < myTable.model.count; i++) {
            let item = myTable.model.get(i);
            console.log(JSON.stringify(item));
            getSensorData(i, getSensorIndex(item.channel), item.dataFieldIndex);
        }
    }
    property var jobQueue: []
    title: "sensor status"
    MySensorTable {
        id: myTable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 100
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        onRefresh: {
            let item = myTable.model.get(idx);
            console.log(idx, item.channel, getSensorIndex(item.channel), item.dataFieldIndex);
            getSensorData(idx, getSensorIndex(item.channel), item.dataFieldIndex);
        }
    }
    Button {
        text: "Refresh"
        anchors.right: parent.right
        anchors.top: parent.top
        flat: true
//        anchors.rightMargin: 10
//        anchors.topMargin: 5
        onClicked: {
            if (jobQueue.length < 5) {
                jobQueue.push({type: 2, doing: false});
            }
        }
    }
    Timer {
        id: workerTimer
        interval: 500
        repeat: true
        running: true
        onTriggered: {
            if (jobQueue[0] && !jobQueue[0].doing) {
                jobQueue[0].doing = true;
                console.log("update all sensor values. " + jobQueue.length + " type=" + jobQueue[0].doing);
                updateAllSensorValues();
                jobQueue.shift();
            }
        }
    }
    Timer {
        id: scheduleTimer
        interval: 5000
        repeat: true
        running: true
        onTriggered: {
            console.log("scheduler:" + jobQueue.length);
            if (jobQueue.length < 5) {
                jobQueue.push({type: 1, doing: false});
            }
        }
    }
}
