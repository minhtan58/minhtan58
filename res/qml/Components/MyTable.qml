import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12

Item {
    property alias delegate: myTable.delegate
    property alias model : myTable.model
    property string header: `{
        "channel": "Channel",
        "name": "Name",
        "status": "Status",
        "selected": false
    }`;

    function addItem(elm) {
        if (model.count ===  0 ) {
            model.append(JSON.parse(header))
        }
        model.append(elm);
    }

    signal selectedItemChanged(string selectedItem)

    function doSelect(idx) {
        for (let i = 1; i < model.count; i++) {
            model.get(i).selected = false;
        }
        model.get(idx).selected = true;
        selectedItemChanged( JSON.stringify(model.get(idx)) );
    }
    function updateModel(channelInfo) {
        for (let i = 0; i < model.count; i++) {
            let item = model.get(i);
            if (channelInfo.channel === item.channel) {
                for (let prop in channelInfo) {
                    item[prop] = channelInfo[prop];
                }
                return;
            }
        }
    }
    function clear() {
        tableModel.clear();
    }
    id: root
    ListModel {
        id: tableModel
//        ListElement {
//            channel: "Channel"
//            name: "Name"
//            status: "Status"
//            selected: false
//        }
    }
    ListView {
        id: myTable
        anchors.fill: root
        model: tableModel
        spacing: -1
        delegate: Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: -1
            BorderedText {
                label: channel
                isHeader: index === 0
                isSelected: selected
                isDisabled: status !== "Enabled"
                onTriggered: doSelect(index);
            }
            BorderedText {
                label: name
                isHeader: index === 0
                isSelected: selected
                isDisabled: status !== "Enabled"
                onTriggered: doSelect(index)
            }
            BorderedText {
                label: status
                isHeader: index === 0
                isSelected: selected
                isDisabled: status !== "Enabled"
                onTriggered: doSelect(index)
            }
        }
    }
}
