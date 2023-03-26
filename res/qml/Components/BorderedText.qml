import QtQuick 2.12
import "Global.js" as Global
Rectangle {
    property string label: ""
    property string iconSource: null
    property string primaryColor: 'steelblue'
    property string selectedColor: '#008888'
    property bool isCenter: true
    property bool isHeader: false
    property bool isSelected: false
    property bool isDisabled: false
    signal triggered();
    function cColor() {
        if (isHeader) return primaryColor;
        if (isSelected) return selectedColor;
        return "transparent";
    }
    id: root
    width: 150
    height: 35
    border.color: isHeader || isSelected ? "white" : primaryColor
    border.width: 1
    color: cColor()
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            if (!iconSource)
                isHeader || isSelected ? false : triggered()
            else triggered();
        }
        cursorShape: iconSource ? Qt.PointingHandCursor : 0
    }
    states: [
        State {
            name: "clicked"
            when: mouseArea.pressed && iconSource
            PropertyChanges {
                target: root; color: "lightgray"
            }
        }
    ]
    Text {
        anchors {
            centerIn: isCenter || isHeader ? parent : null
            verticalCenter: parent.verticalCenter
            left: isCenter ? undefined : parent.left
            leftMargin: 10
        }
        visible: !iconSource
        text: label
        font.bold: isHeader
        color: isDisabled? "lightgray" :( isHeader || isSelected ? "white" : primaryColor )
        font.pointSize: Global.fontSize
    }
    ColorIcon {
        visible: iconSource
        anchors.centerIn: parent
        source: iconSource
        cColor: isSelected ? "white":primaryColor
    }
}
