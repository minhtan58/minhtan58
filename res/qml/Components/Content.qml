import QtQuick 2.12
import QtQuick.Controls 2.12
Rectangle {
    property string title: "value"
    property int titleFontSize: 14
    property string titleColor: "black"
    property double titlePaddingFactor: 2
    property bool isInverted: false
    property bool borderLeft : true
    property bool borderRight : false
    property bool borderTop : false
    property bool borderBottom : false
    clip: true
    Rectangle {
        border.width: 1
        border.color: "#cccccc"
//        color: "yellow"
        anchors {
            left: parent.left; right: parent.right; top: parent.top; bottom: parent.bottom
            rightMargin: borderRight ? 0: -1
            topMargin: borderTop ? 0: -1
            bottomMargin: borderBottom ? 0: -1
            leftMargin: borderLeft ? 0: -1
        }
    }
    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: titleFontSize * titlePaddingFactor
        color: isInverted ? titleColor : "transparent"
//        anchors.topMargin: 12

        Text {
            anchors.centerIn: parent
            color: isInverted ? "white" : titleColor
            text: title
            font.pointSize: titleFontSize
            font.bold: true
            font.capitalization: Font.AllUppercase
            font.family: "Monospace"
        }
    }
}
