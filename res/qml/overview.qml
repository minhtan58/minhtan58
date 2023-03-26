import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "Components"

Content {
    title: "Overview"
    property string modelName: "Some model Nameee"
    property string stationName: "Some model Name"
    property string stationId: "station Id"
    property string serialNumber: "serial number"
    property string firmwareVersion: "0.0.1"
    property string macAddress: "Some model Name"
    property string ipAddress: "127.0.0.1"
    property string batteryVoltage: "120V"
    function setInformation(obj) {
        console.log("setInformation", obj);
        modelName = obj.modelName;
        stationName = obj.stationName;
        stationId = obj.stationId;
        serialNumber = obj.serialNumber;
        firmwareVersion = obj.firmwareVersion;
        macAddress = obj.macAddress;
        ipAddress = obj.ipAddress;
        batteryVoltage = obj.batteryVoltage;
    }
    GridLayout {
        anchors {
            centerIn: parent
        }
        columns: 6
        columnSpacing: 6
        MyLabel {
            text: "Model Name"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: modelName
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
//        ------------------------------------------------
        MyLabel {
            text: "Station Name"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: stationName
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
//        ------------------------------------------------
        MyLabel {
            text: "Station ID"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: stationId
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "Serial Number"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: serialNumber
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "Firmware Version"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: firmwareVersion
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "MAC Address"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: macAddress
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "IP Address"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: ipAddress
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "Battery Voltage"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyText {
            text: batteryVoltage
            Layout.columnSpan: 3
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
    }
}
