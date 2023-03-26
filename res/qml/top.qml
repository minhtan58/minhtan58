//import related modules
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import "Components"
Item {
    id: topbar
//  visible: true
//    height: 55
    height: 60
//  width: Layout.maximumWidth
//    color: "lightgray"
    Rectangle {
        border.width: 1
        border.color: "#cccccc"
        anchors {
            top: parent.top; left: parent.left ; right: parent.right ; bottom: parent.bottom
            topMargin: -1; leftMargin: -1; rightMargin: -1
        }
    }
    Image {
        source: '/logo'
        anchors.left: parent.left
        anchors.top: parent.top
    }
    Text {
        id: txtTopbar
        anchors.horizontalCenter: parent.horizontalCenter
        text: "DATALOGGER CONFIGURATOR"
        font.pointSize: 20
        font.bold: true
    }
}
