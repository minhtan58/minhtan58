//import related modules
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import "Components"
Rectangle {
    id: bottomBar
    height: 120
    clip: true
    Rectangle {
        border.width: 1
        border.color: "#cccccc"
        anchors {
            top: parent.top; left: parent.left ; right: parent.right ; bottom: parent.bottom
            bottomMargin: -3; leftMargin: -1; rightMargin: -1
        }
//        color: "yellow"
    }
    GridLayout {
        anchors.centerIn: parent
        columns: 3
        columnSpacing: 24
        rowSpacing: 8
        Image {
            source: '/logo'
            Layout.rowSpan: 3
        }
        Text {
            text: "15th Floor, Hapulico Center Building, 1st Nguyen Huy Tuong Str., Thanh Xuan Dist., Hanoi, Vietnam"
            font.pointSize: 10
            font.italic: true
            Layout.columnSpan: 2
            color: "#888888"
        }
        Text {
            text: "Tel: (+84) 24 22213077"
            font.pointSize: 10
            font.italic: true
            color: "#888888"
        }
        Text {
            text: "Fax: (+84) 24 22213078"
            font.pointSize: 10
            font.italic: true
            color: "#888888"
        }
        Text {
            text: "Website: http://www.dicomhme.com"
            font.pointSize: 10
            font.italic: true
            color: "#888888"
        }
        Text {
            text: "Email: info@dicom.com"
            font.pointSize: 10
            font.italic: true
            color: "#888888"
        }
    }
}
