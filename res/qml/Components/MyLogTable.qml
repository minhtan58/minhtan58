import QtQuick 2.12

MyTable {
    header: `{
        "time": "Time", "type": "Type", "description": "Description"
    }`
    delegate: Row {
        anchors.horizontalCenter: parent.horizontalCenter
//        height: (index > 0 && hidden)? 0 : undefined
//        clip: true
        spacing: -1

        BorderedText {
            width: 80
            label: index ? index: "No"
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect()
        }
        BorderedText {
            width: 200
            label: time
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index);
        }
        BorderedText {
            label: type
            width: 80
            isHeader: index === 0
            isSelected: selected
            onTriggered: doSelect(index)
        }
        BorderedText {
            label: description
            isHeader: index === 0
            isSelected: selected
            isCenter: false
            width: 600
            clip: true
            onTriggered: doSelect(index)
        }
    }
}
