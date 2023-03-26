import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import "Components"
import "Components/Global.js" as Global
Content {
    title: "system settings"

    property alias stationName: idStationName.text
    property alias stationId: idStationId.text
    property alias dateTime: idDateTime.text
    property alias ipAddress: idIpAddress.text
    property alias netmask: idNetmask.text
    property alias gateway: idGateway.text
    property bool bImport: false
    signal importSystemSettings(string url)
    signal exportSystemSettings(string url, string jsonSettings)
    signal saveSystemSettings(string jsonSettings)
    function setInformation(obj) {
        stationName = obj.stationName;
        stationId = obj.stationId;
        dateTime = obj.dateTime;
        ipAddress = obj.ipAddress;
        netmask = obj.netmask;
        gateway = obj.gateway;
    }
    FileDialog {
        id: fileDialog
        title: bImport ? "Choose file to load" : "Choose file to save"
        folder: shortcuts.home
        selectMultiple: false
        selectExisting: bImport
        nameFilters: ["Data file (*.dat)"]
        visible: false
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
            if (bImport) {
                importSystemSettings(fileDialog.fileUrl);
            }
            else
                exportSystemSettings(fileDialog.fileUrl, JSON.stringify({
                    stationName: idStationName.text, 
                    stationId: idStationId.text, 
                    dateTime: idDateTime.text, 
                    ipAddress: idIpAddress.text, 
                    netmask: idNetmask.text, 
                    gateway:idGateway.text
                }));
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    GridLayout {
        anchors {
            centerIn: parent
        }
        columns: 6
        columnSpacing: 6
        MyLabel {
            text: "Station Name"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idStationName
            text: "station name"
            Layout.columnSpan: 3
            validator: RegExpValidator {
                regExp: Global.nameRegEx
            }
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
        MyTextEdit {
            id: idStationId
            text: "station id"
            Layout.columnSpan: 3
            validator: RegExpValidator {
                regExp: /^[0-9]{0,5}$/
            }
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "Date and Time"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idDateTime
            text: "2021/01/01 00:00:00"
            inputMask: "9999/99/99 99:99:99"
//            validator: DateTimeValidator {}

            Layout.columnSpan: 2
        }
        Button {
            flat: true
            text: "Now"
            Layout.columnSpan: 1
            onClicked: {
                let d = new Date();
                idDateTime.text = d.getFullYear() + "/" + (d.getMonth() + 1) + "/" + d.getDate() + " " +
                        ("0" + d.getHours()).slice(-2) + ":" + ("0" + d.getMinutes()).slice(-2) + ":" +
                        ("0" + d.getSeconds()).slice(-2);
            }
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
        MyTextEdit {
            id: idIpAddress
            text: "127.0.0.1"
            Layout.columnSpan: 3
            validator: RegExpValidator
            {
              regExp:/^(([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))\.){3}([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))$/
            }
//            inputMask: "000.000.000.000"
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "Subnet Mask"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idNetmask
            text: "255.255.255.0"
            Layout.columnSpan: 3
            validator: RegExpValidator
            {
              regExp: /^(((255\.){3}(255|254|252|248|240|224|192|128|0+))|((255\.){2}(255|254|252|248|240|224|192|128|0+)\.0)|((255\.)(255|254|252|248|240|224|192|128|0+)(\.0+){2})|((255|254|252|248|240|224|192|128|0+)(\.0+){3}))$/
            }
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
        MyLabel {
            text: "Gateway"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idGateway
            text: "127.0.0.1"
            Layout.columnSpan: 3
            validator: RegExpValidator
            {
              regExp:/^(([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))\.){3}([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))$/
            }
        }
        Item {
            height: 10
            Layout.columnSpan: 6
        }
        // ------------------------------------------------
    }
    RowLayout {
        height: okButton.height;

        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 20

        Button {
            flat: true
            text: "Reset"
            onClicked: {
                idStationName.text = "";
                idStationId.text = "";
                idIpAddress.text = "";
                idNetmask.text = "";
                idGateway.text = "";
            }
        }
        Button {
            flat: true
            text: "Import"
            onClicked: {
                bImport = true;
                fileDialog.open();
            }
        }
        Button {
            flat: true
            text: "Export"
            onClicked: {
                bImport = false;
                fileDialog.open();
            }
        }
        Button {
            id: okButton
            text: "Ok"
            highlighted: true
            onClicked: {
                saveSystemSettings(JSON.stringify({
                                                      stationName,
                                                      stationId,
                                                      dateTime,
                                                      ipAddress,
                                                      netmask,
                                                      gateway
                                                  }));
            }
        }
    }
}
