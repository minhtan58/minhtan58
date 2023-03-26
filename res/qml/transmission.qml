import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import "Components/Global.js" as Global
import "Components"
Content {
    title: "transmission settings"
    property alias startTime: idStartTime.text
    property alias interval: idInterval.text
    property alias headerInterval: idHeaderInterval.text
    property alias url: idUrl.text
    property alias port: idPort.text
    property alias userName: idUserName.text
    property alias password: idPassword.text
    property alias fileName: idFileName.text
    property alias tcpIp: idTcpIp.text
    property bool bImport: false
    property bool shown: false
    signal importTransmissionSettings(string url)
    signal exportTransmissionSettings(string url, string jsonSettings)
    signal saveTransmissionSettings(string jsonSettings)
    function setInformation(obj) {
        startTime = obj.startTime;
        interval = obj.interval;
        headerInterval = obj.headerInterval;
        url = obj.url;
        port = obj.port;
        userName = obj.userName;
        password = obj.password;
        fileName = obj.fileName;
        tcpIp = obj.tcpIp;
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
                importTransmissionSettings(fileDialog.fileUrl);
            }
            else
                exportTransmissionSettings(fileDialog.fileUrl, JSON.stringify({
                                               startTime: idStartTime.text,
                                               interval: idInterval.text,
                                               headerInterval: idHeaderInterval.text,
                                               url: idUrl.text,
                                               port: idPort.text,
                                               userName: idUserName.text,
                                               password: idPassword.text,
                                               fileName: idFileName.text,
                                               tcpIp: idTcpIp.text
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
        columns: 9
        columnSpacing: 6
        rowSpacing: 4
        MyLabel {
            text: "Start Time"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idStartTime
            text: "00:00:00"
            inputMask: "99:99:99"
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }

//        ------------------------------------------------
        MyLabel {
            text: "Interval"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idInterval
//            text: "00:05:00"
            text: "5"
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
            validator: RegExpValidator {
//                regExp:/^[0-9][0-9]:[0-5][0-9]:[0-5][0-9]$/
                regExp: Global.intNumberRegEx
            }
        }

        // ------------------------------------------------
        MyLabel {
            text: "Header Interval"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idHeaderInterval
            text: "60"
            validator: RegExpValidator {
                regExp:/^[0-9]+$/
            }
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }

        // ------------------------------------------------
        MyLabel {
            text: "Url"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idUrl
            text: "url"
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
            validator: RegExpValidator {
                regExp: Global.strDataRegEx30
            }
        }

        // ------------------------------------------------
        MyLabel {
            text: "Port"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idPort
            text: "port"
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
            validator: RegExpValidator {
                regExp: Global.intNumberRegEx
            }
        }

        // ------------------------------------------------
        MyLabel {
            text: "Username"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idUserName
            text: "userName"
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
            validator: RegExpValidator {
                regExp: Global.usernameRegEx
            }
        }

        // ------------------------------------------------
        MyLabel {
            text: "Password"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idPassword
            text: ""
            echoMode: shown?TextInput.Normal:TextInput.Password
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
            validator: RegExpValidator {
                regExp: Global.strDataRegEx30
            }
        }
        Button {
            text: shown?"Hide":"Show"
            onClicked: shown = !shown
            flat: true
            Layout.preferredWidth: 70
        }

        // ------------------------------------------------
        MyLabel {
            text: "File Name"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idFileName
            text: "File name"
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
            validator: RegExpValidator {
                regExp: Global.filenameRegEx
            }
        }

        // ------------------------------------------------
        MyLabel {
            text: "TCP/IP"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idTcpIp
            text: ""
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
            validator: RegExpValidator {
                regExp: Global.intNumberRegEx
            }
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
                startTime = "";
                interval = "";
                headerInterval = "";
                url = "";
                port = "";
                userName = "";
                password = "";
                fileName = "";
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
                saveTransmissionSettings(JSON.stringify({
                    startTime: idStartTime.text,
                    interval: idInterval.text,
                    headerInterval: idHeaderInterval.text,
                    url: idUrl.text,
                    port: idPort.text,
                    userName: idUserName.text,
                    password: idPassword.text,
                    fileName: idFileName.text,
                    tcpIp: idTcpIp.text
                }));
            }
        }
    }
}
