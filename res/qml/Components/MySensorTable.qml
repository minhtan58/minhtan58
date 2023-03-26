import QtQuick 2.12
import QtQuick.Controls 2.12

MyTable {
//    signal refresh(int idx, int sensorIndex, int dataFieldIndex)
    signal refresh(int idx)
    function updateSensor(idx, elm) {
        if (idx >= model.count) return;
        console.log("Update sensor", idx, JSON.stringify(elm));
        model.set(idx, elm);
    }


    header: `{
        "name": "Name", "channel": "Channel Slot", "sensorValue": "Value", "unit": "Unit", "interval": "Interval", "action": "Action"
    }`
    delegate: Row {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: -1
        height: undefined
        BorderedText {
            label: index ? index : "No"
            width: 80
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index);
        }
        BorderedText {
            label: name
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index)
        }
        BorderedText {
            label: channel
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index)
        }
        BorderedText {
            label: sensorValue
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index)
        }
        BorderedText {
            label: unit
            width: 80
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index)
        }
        BorderedText {
            label: interval
            width: 80
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index)
        }
        BorderedText {
            width: 80
            isHeader: index === 0
            isSelected: selected
            iconSource: (index === 0)? null :"/svg/sync.svg"
            label: (index === 0)?"Action":""
            onTriggered: refresh(index)
//            onTriggered: refresh(index, getSensorIndex(channel), dataFieldIndex);

        }
    }
}
