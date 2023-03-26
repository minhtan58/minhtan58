//import related modules
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12
import "Components"
import "Components/Global.js" as Global
Rectangle {
    signal switchContent(string content)
    function downIt(idx) {
        for (let i = 0; i < menuItems.count; i++) {
            menuItems.setProperty(i, "isdown", false);
        }
        menuItems.setProperty(idx, "isdown", true);
        switchContent(menuItems.get(idx).name);
    }
    function toggleChildren(idx) {
        var temp = menuItems.get(idx).hideChildren;
        menuItems.setProperty(idx, "hideChildren", !temp);
        for (let i = 0; i < menuItems.count; i++) {
            let item = menuItems.get(i);
            if (item.parentIdx === idx) {
                item.hidden = !temp;
            }
        }
    }
    function formatDate1(d) {
        d.toString();
    }
    function getDayOfWeek(d) {
        let day = d.getDay();
        if (day === 0) return 'CN';
        return "T" + (day + 1);
    }
    function norm2(n) {
        return ("0" + Math.abs(n)).slice(-2);
    }
    function getTimezone(d) {
        let off = d.getTimezoneOffset() / 60;
        let sign = (off <= 0)?"+":"-";
        return "GMT" + sign + norm2(off) + "00";
    }
    function formatDate(d) {
        let dayOfWeek = getDayOfWeek(d);
        let month = "Thg" + (d.getMonth() + 1);
        let date = d.getDate();
        let hh = d.getHours();
        let mm = d.getMinutes();
        let ss = d.getSeconds();
        let YYYY = d.getFullYear();
        let tz = getTimezone(d);
        return `${dayOfWeek} ${month} ${date} ${norm2(hh)}:${norm2(mm)}:${norm2(ss)} ${YYYY} ${tz}`;
    }

    id: top
    clip: true
//    color: "lightgreen"
    ListModel {
        id: menuItems
        ListElement {
            label: "Overview"
            name: "overview"
            isdown: false
        }
        ListElement {
            label: "System Settings"
            name: "system"
            isdown: false
        }
        ListElement {
            label: "IO Settings"
            name: "io"
            isdown: false
            hasChildren: true
            hideChildren: false
        }
        ListElement {
            label: "Analog Channel"
            name: "analog"
            isdown: false
            level: 1
            hidden: false
            parentIdx: 2
        }
        ListElement {
            label: "Digital Channel"
            name: "digital"
            isdown: false
            level: 1
            hidden: false
            parentIdx: 2
        }
        ListElement {
            label: "Serial Channel"
            name: "serial"
            isdown: false
            level: 1
            hidden: false
            parentIdx: 2
        }
        ListElement {
            label: "Virtual Channels"
            name: "virtual"
        }
        ListElement {
            label: "Sensor Status"
            name: "sensor"
            isdown: false
        }
        ListElement {
            label: "Transmission Settings"
            name: "transmission"
            isdown: false
        }
        ListElement {
            label: "Cellular Settings"
            name: "cellular"
        }
        ListElement {
            label: "Channel Sorting"
            name: "sorting"
        }
        ListElement {
            label: "Logs"
            name: "logs"
            isdown: false
//            hasChildren: true
//            hideChildren: false
        }
    }
    width: 600
    ColumnLayout {
        width: parent.width
        spacing: 4
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        Item {
            Layout.preferredHeight: 10
            Layout.preferredWidth: 10
        }
        Repeater {
            model: menuItems
            Layout.preferredWidth: top.width - 8
            CustomMenuItem {
                cText: label
                cActive: isdown
                cLevel: level | 0
                cSource: hasChildren ? (hideChildren ? "/svg/down.svg":"/svg/right.svg") : null
                primaryColor: Global.primaryColor
                cVisible: !hidden
                Layout.preferredWidth: parent.width - 8
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    if (!hasChildren) downIt(index)
                    else toggleChildren(index)
                }
            }
        }
    }
    Rectangle {
        height: 60
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

//        color: "navy"
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: parent.width
        Text {
            id: idClock
            text: formatDate(new Date())
            color: "green"
            font.pointSize: Global.fontSize - 2
            font.bold: true
            anchors.centerIn: parent
        }
        Timer {
            interval: 1000
            repeat: true
            running: true
            onTriggered: idClock.text = formatDate(new Date())
        }
    }
}
