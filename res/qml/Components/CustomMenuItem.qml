import QtQuick 2.12
import "Global.js" as Global
Rectangle {
    id: root
    readonly property int levelOffset: 20
    property bool cActive: false
    property string cText: "xin chao"
    property int cLevel: 0
    property bool cVisible: false
    property string cSource: "/svg/right.svg"
    property string primaryColor: "blue"
    signal clicked(bool active)
    visible: cVisible
    height: 1.5 * content.height
    color: cActive ? primaryColor:"transparent"
//    border.color: mouseArea.containsMouse ? primaryColor : "transparent"
//    border.width: mouseArea.containsMouse ? 1 : 0
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
//        hoverEnabled: cVisible
        onClicked: {
            if (cActive) return;
            root.clicked(!cActive);
        }
    }
    Text {
        id: content
        text: cText
        color: cActive ? "white" : primaryColor
        font {
            pointSize: Global.fontSize
            family: "Roboto"
        }
        anchors {
            left: parent.left
            leftMargin: levelOffset * (cLevel + 1)
            verticalCenter: parent.verticalCenter
        }
    }
    ColorIcon {
        source: cSource
        cColor:  cActive? "white":primaryColor
        anchors.right: parent.right
        anchors.rightMargin: levelOffset
        anchors.verticalCenter: parent.verticalCenter
        visible: cSource ? true:false
    }
}
