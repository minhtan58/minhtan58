import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "Components"
import "Components/Global.js" as Global
Content {
    id: root
    title: "Setting Serial channels"
    signal saveSerialSensorSettings(string jsonSettings)
    signal loadSerialSensorSettings(string sensorName)
    property var dataFields: [{name: "", index: 0, unit: 'mm'},{name: "", index: 0, unit: 'mm'},{name: "", index: 0, unit: 'mm'}]
    property int length: 3
    function addSensorModelItem(sensorName) {
        sensorList.append({text: sensorName});
    }
    function parseDataSequence(ds) {
        return Global.parseDataSequence(ds);
    }
    function toDataSequence(datafields) {
        return Global.toDataSequence(dataFields);
    }
    function addItem(elm) {
        console.log("addItem:" + JSON.stringify(elm));
        myTable.addItem(elm);
    }
    function findIndex(value, listModel) {
        for (let i = 0; i < listModel.count; i++) {
            if( value === listModel.get(i).text ) return i;
        }
        console.log(`Cannot find ${value} in `, listModel);
        Qt.quit();
    }
    function setFormValuesObj(channelInfo) {
        configDialog.visible = true
        configDialog.channelName = channelInfo.channel || configDialog.channelName;
        console.log(configDialog.channelName);
        if (channelInfo.status)
            idStatus.currentIndex = channelInfo.status === "Enabled" ? 0 : 1;
        idName.text = channelInfo.name || idName.text;
        if (channelInfo.channel !== "SDI12") {
            idBaudrate.currentIndex = findIndex(channelInfo.baudrate, idBaudrate.model);
            idDatabits.currentIndex = findIndex(channelInfo.databits, idDatabits.model);
            idParity.currentIndex = findIndex(channelInfo.parity, idParity.model);
            idStopbits.text = channelInfo.stopbits;
            idFlowControl.currentIndex = findIndex(channelInfo.flowcontrol, idFlowControl.model);
            idLeadChar.text = channelInfo.leadchar;
            idEol.text = channelInfo.eol;
        }
        idInterval.text = channelInfo.interval;
        idGetDataCommand.text = channelInfo.getdatacommand;
        idUnit.currentIndex = findIndex(channelInfo.unit, idUnit.model);
        root.length = 0;
        root.dataFields = parseDataSequence(channelInfo.datasequence);
        root.length = root.dataFields.length;
        idData.text = channelInfo.data; // channelInfo.sensorValue;
    }
    function setFormValues(json) {
        let channelInfo = JSON.parse(json);
        console.log(channelInfo.channel);
        setFormValuesObj(channelInfo);
    }
    function updateModel(channelInfo) {
        myTable.updateModel(channelInfo);
        configDialog.channelInfoStr = JSON.stringify(channelInfo);
    }
    function resetForm() {
        setFormValues(configDialog.channelInfoStr);
    }
    ListModel {
        id: sensorList
    }
    ListModel {
        id: unitModel
        ListElement { text: "mm" }
        ListElement { text: "ppb" }
        ListElement { text: "ppm" }
        ListElement { text: "%" }
        ListElement { text: "inch" }
        ListElement { text: "oC" }
        ListElement { text: "degree" }
        ListElement { text: "m/s" }
        ListElement { text: "kt" }
        ListElement { text: "km/h" }
        ListElement { text: "hPa" }
        ListElement { text: "mmHg" }
        ListElement { text: "m" }
        ListElement { text: "cm" }
    }
    Dialog {
        visible: false
        id: addDataFieldDialog
        title: "Config data fields"
        modal: true
        anchors.centerIn: parent
//        standardButtons: Dialog.Ok
        implicitWidth: 610
        GridLayout {
            anchors {
                centerIn: parent
            }
            columns: 10
            columnSpacing: 6
            MyLabel {
                text: "Data"
                Layout.columnSpan: 2
            }
            MyTextEdit {
                id: idData
                readOnly: true
                text: "data"
                Layout.columnSpan: 7
                Layout.fillWidth: true
            }
            Button {
                text: "Update"
                onClicked: {
//                    idData.text = "12345678"
                }
            }
//            Button {
//                text: "Add data field"
//                Layout.columnSpan: 10
//                Layout.alignment: Qt.AlignHCenter
//                Layout.fillWidth: true
//                onClicked: {
//                    root.dataFields.push({name: "", index: 0, unit: "mm"});
//                    root.length++;
//                    console.log(JSON.stringify(root.dataFields));
//                }
//            }
            Repeater {
                model: root.length
                MyText {
                    text: `${index}:`
                    Layout.row: index + 2
                    Layout.column: 0
                }
            }
            Repeater {
                model: root.length
                MyLabel {
                    Layout.row: index + 2
                    Layout.column: 1
                    text: "Name"
                }
            }
            Repeater {
                model: root.length
                MyTextEdit {
                    text: root.dataFields[index].name
                    onEditingFinished: {
                        console.log("this:", this.text);
                        root.dataFields[index].name = this.text;
                    }
                    Layout.row: index + 2
                    Layout.column: 2
                    Layout.preferredWidth: 120
                }
            }
            Repeater {
                model: root.length
                MyLabel {
                    Layout.row: index + 2
                    Layout.column: 4
                    text: "Index"
                }
            }
            Repeater {
                model: root.length
                MyTextEdit {
                    text: root.dataFields[index].index || "unknown"
                    Layout.row: index + 2
                    Layout.column: 5
                    Layout.preferredWidth: 70
                    onEditingFinished: {
                        root.dataFields[index].index = this.text;
                    }
                }
            }
            Repeater {
                model: root.length
                MyLabel {
                    Layout.row: index + 2
                    Layout.column: 7
                    text: "Unit"
                }
            }
            Repeater {
                model: root.length
//                model: root.dataFields
                MyComboBox {
                    cWidth: 100
                    model: unitModel
                    currentIndex: {
                        findIndex(root.dataFields[index].unit, unitModel);
                    }
                    Layout.row: index + 2
                    Layout.column: 8
                    onSelected: {
                        root.dataFields[index].unit = currentText;
                    }
                }
//                MyTextEdit {
//                    text: root.dataFields[index].index
//                    Layout.row: index + 2
//                    Layout.column: 8
//                    Layout.preferredWidth: 70
//                    onEditingFinished: {
//                        console.log("this1:", this.text);
//                        root.dataFields[index].index = this.text;
//                    }
//                }
            }
            Repeater {
                model: root.length
                Button {
                    text: "Remove"
                    Layout.row: index + 2
                    Layout.column: 9
                    onClicked: {
                        root.dataFields.splice(index, 1);
                        root.length--;
                    }
                }
            }

        }
        onAccepted: {
            addDataFieldDialog.visible = false;
        }
        onRejected: {
            addDataFieldDialog.visible = false;
        }
        footer: RowLayout {
            spacing: 4

            Button {
                text: "Add data field"
//                Layout.columnSpan: 10
//                Layout.alignment: Qt.AlignHCenter
//                Layout.fillWidth: true
                onClicked: {
                    root.dataFields.push({name: "", index: 0, unit: "mm"});
                    root.length++;
                }
                Layout.leftMargin: 20
                Layout.topMargin: 20
                Layout.bottomMargin: 20
            }
            Button {
                text: "Ok"
                onClicked: addDataFieldDialog.visible = false
                Layout.topMargin: 20
                Layout.bottomMargin: 20
                Layout.rightMargin: 20
                Layout.alignment: Qt.AlignRight
            }
        }
    }
    MyTable {
        id: myTable
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: Global.topMargin1
        anchors.bottomMargin: 10
        anchors.right: parent.horizontalCenter
        onSelectedItemChanged: {
            configDialog.channelInfoStr = selectedItem;
            setFormValues(selectedItem);
        }
    }
    Content {
        property string channelName: ""
        property string channelInfoStr: "{}"
        function makeTitle() {
            return `Serial Channel (${channelName})`
        }
        id: configDialog
        title: makeTitle()
        visible: false
        titleColor: Global.primaryColor
        isInverted: true
        titlePaddingFactor: 2
        borderRight: true
        borderBottom: true
        anchors.left: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: Global.topMargin1
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        GridLayout {
            anchors {
                centerIn: parent
            }
            columns: 6
            columnSpacing: 6
            rowSpacing: 4
            MyLabel {
                text: "Status"
//                Layout.alignment: Qt.AlignRight
            }
            MyComboBox {
                id: idStatus
                model: ListModel {
                    ListElement { text: "Enabled" }
                    ListElement { text: "Disabled" }
                }
                currentIndex: 0
                cWidth: idName.width
                cHeight: idName.height
                Layout.columnSpan: 5
                // Layout.fillWidth: true
            }

    //        ------------------------------------------------
            MyLabel {
                text: "Name"
//                Layout.alignment: Qt.AlignRight
            }
            MyTextEdit {
                id: idName
                text: "N/A"
                validator: RegExpValidator {
                    regExp: Global.nameRegEx
                }
                Layout.columnSpan: 5
                enabled: idStatus.currentIndex === 0
                // Layout.fillWidth: true
            }

            // ------------------------------------------------
            MyLabel {
                visible: configDialog.channelName !== "SDI12"
                text: "Baudrate (bps)"
//                Layout.alignment: Qt.AlignRight
            }

            MyComboBox {
                id: idBaudrate
                visible: configDialog.channelName !== "SDI12"
                cWidth: 90
                cHeight: idName.height
                Layout.columnSpan: 2
                model: ListModel {
                    ListElement {
                        text: "9600"
                    }
                    ListElement {
                        text: "19200"
                    }
                    ListElement {
                        text: "38400"
                    }
                    ListElement {
                        text: "57600"
                    }
                    ListElement {
                        text: "115200"
                    }
                }
                currentIndex: 0
                enabled: idStatus.currentIndex === 0
            }
            MyLabel {
                visible: configDialog.channelName !== "SDI12"
                text: "Data bits"
                Layout.alignment: Qt.AlignRight
            }

            MyComboBox {
                id: idDatabits
                visible: configDialog.channelName !== "SDI12"
                cWidth: 90
                cHeight: idName.height
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 2
                model: ListModel {
                    ListElement {
                        text: "8"
                    }
                    ListElement {
                        text: "7"
                    }
                }
                currentIndex: 0
            }

            // ------------------------------------------------
            MyLabel {
                text: "Parity"
                visible: configDialog.channelName !== "SDI12"
//                Layout.alignment: Qt.AlignRight
            }

            MyComboBox {
                id: idParity
                visible: configDialog.channelName !== "SDI12"
                cWidth: 90
                cHeight: idName.height
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 2
                model: ListModel {
                    ListElement {
                        text: "None"
                    }
                    ListElement {
                        text: "Odd"
                    }
                    ListElement {
                        text: "Even"
                    }
                    ListElement {
                        text: "Mark"
                    }
                    ListElement {
                        text: "Space"
                    }
                }
                currentIndex: 0
            }
            MyLabel {
                text: "Stop bits"
                visible: configDialog.channelName !== "SDI12"
                Layout.alignment: Qt.AlignRight
            }

            MyTextEdit {
                id: idStopbits
                visible: configDialog.channelName !== "SDI12"
                Layout.preferredWidth: 90
                text: "1"
                validator: RegExpValidator
                {
                  regExp:/^[0-9]+$/
                }
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 2
            }

            // ------------------------------------------------
            MyLabel {
                visible: configDialog.channelName !== "SDI12"
                text: "Flow Control"
//                Layout.alignment: Qt.AlignRight
            }
            MyComboBox {
                id: idFlowControl
                visible: configDialog.channelName !== "SDI12"
                cWidth: 90
                cHeight: idName.height
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 2
                model: ListModel {
                    ListElement {
                        text: "None"
                    }
                    ListElement {
                        text: "Xon/Xoff"
                    }
                }
                currentIndex: 0
            }

            MyLabel {
                text: "Lead char"
                visible: configDialog.channelName !== "SDI12"
                Layout.alignment: Qt.AlignRight
            }

            MyTextEdit {
                id: idLeadChar
                visible: configDialog.channelName !== "SDI12"
                Layout.preferredWidth: 90
                text: "S"
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 2
                validator: RegExpValidator {
                    regExp: Global.strDataRegEx10
                }
            }
            // ------------------------------------------------
            MyLabel {
                text: "End of line"
                visible: configDialog.channelName !== "SDI12"
//                Layout.alignment: Qt.AlignRight
            }

            MyTextEdit {
                id: idEol
                visible: configDialog.channelName !== "SDI12"
                Layout.preferredWidth: 90
                text: "CRLF"
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 2
                validator: RegExpValidator {
                    regExp: Global.strDataRegEx10
                }
            }
            MyLabel {
                text: "Interval (sec)"
//                Layout.alignment: Qt.AlignRight
            }

            MyTextEdit {
                id: idInterval
                Layout.preferredWidth: configDialog.channelName === "SDI12" ? idName.width: 90
                text: ""
                enabled: idStatus.currentIndex === 0
                //Layout.columnSpan: 2
                Layout.columnSpan: configDialog.channelName === "SDI12"?5:2
                validator: RegExpValidator {
                    regExp: Global.intNumberRegEx
                }
            }

            // ------------------------------------------------
            MyLabel {
                text: "Get data command"
//                Layout.alignment: Qt.AlignRight
            }
            MyTextEdit {
                id: idGetDataCommand
                text: ""
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 5
                validator: RegExpValidator {
                    regExp: Global.strDataRegEx10
                }
                // Layout.fillWidth: true
            }

            // ------------------------------------------------
            MyLabel {
                text: "Unit"
//                Layout.alignment: Qt.AlignRight
            }
            MyComboBox {
                id: idUnit
                cWidth: idName.width
                cHeight: idName.height
                enabled: idStatus.currentIndex === 0
                model: ListModel {
                    ListElement { text: "mm" }
                    ListElement { text: "ppb" }
                    ListElement { text: "ppm" }
                    ListElement { text: "%" }
                    ListElement { text: "inch" }
                    ListElement { text: "oC" }
                    ListElement { text: "degree" }
                    ListElement { text: "m/s" }
                    ListElement { text: "kt" }
                    ListElement { text: "km/h" }
                    ListElement { text: "hPa" }
                    ListElement { text: "mmHg" }
                    ListElement { text: "m" }
                    ListElement { text: "cm" }
                }
                currentIndex: 1
                Layout.columnSpan: 5
            }

        }
        RowLayout {
            height: okButton.height;

            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 20

            Button {
                flat: true
                text: "Data fields"
                onClicked: {
                    addDataFieldDialog.visible = true;
                }
            }
            Button {
                id: idResetBtn
                flat: true
                text: "Reset"
                onClicked: {
                    resetForm();
                }
            }
            MyComboBox {
                cWidth: 1.7*idResetBtn.width
                cHeight: idResetBtn.height
                model: sensorList
                currentIndex: 0
                enabled: idStatus.currentIndex === 0
                displayText: "Sensor Selection"
                onSelected: {
                    loadSerialSensorSettings(currentText);
                }
            }
            Button {
                id: okButton
                text: "Ok"
                highlighted: true
                onClicked: {
                    let channelInfo = {
                        channel: configDialog.channelName,
                        name: idName.text,
                        status: idStatus.currentText,
                        baudrate: idBaudrate.currentText,
                        databits: idDatabits.currentText,
                        parity: idParity.currentText,
                        stopbits: idStopbits.text,
                        flowcontrol: idFlowControl.currentText,
                        leadchar: idLeadChar.text,
                        eol: idEol.text,
                        getdatacommand: idGetDataCommand.text,
                        interval: idInterval.text,
                        unit: idUnit.currentText,
                        datasequence: toDataSequence(root.dataFields)
                    };
                    console.log(channelInfo);
                    saveSerialSensorSettings(JSON.stringify(channelInfo));
                }
            }
        }
    }
}
