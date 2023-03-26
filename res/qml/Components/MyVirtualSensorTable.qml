import QtQuick 2.12
import QtQuick.Controls 2.12
import "Global.js" as Global

MyTable {
//    signal refresh(int idx, int sensorIndex, int dataFieldIndex)
    signal refresh(int idx)
    function updateSensor(idx, elm) {
        if (idx >= model.count) return;
        console.log("Update sensor", idx, JSON.stringify(elm));
        model.set(idx, elm);
    }

    function showType(idx, vsType) {
        if (idx === 0) return vsType;
        console.log(idx, vsType);
        return Global.vsInputChannelConfigs[+vsType].type;
    }
    header: `{
        "vsType": "Type", "channel": "Channel", "status": "Status"
    }`
    delegate: Row {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: -1
        height: undefined

        BorderedText {
            label: channel
            width: 135
            isHeader: index === 0
            isSelected: selected
            isDisabled: status !== "Enabled"
            onTriggered: doSelect(index)
        }
        BorderedText {
            label: showType(index, vsType)
            width: 180
            isHeader: index === 0
            isSelected: selected
            isDisabled: status !== "Enabled"
            onTriggered: doSelect(index)
        }

//        BorderedText {
//            label: name
//            isHeader: index === 0
//            isSelected: selected
//            isDisabled: status !== "Enabled"
//            onTriggered: doSelect(index)
//        }

        BorderedText {
            label: status
            isHeader: index === 0
            isSelected: selected
            isDisabled: status !== "Enabled"
            onTriggered: doSelect(index)
            width: 135
        }
    }
}
