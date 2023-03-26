import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "Components"
import "Components/Global.js" as Global
Content {
    title: "Setting Digital channels"
//    titlePaddingFactor: 1.5
//    isInverted: true
    signal saveDigitalSensorSettings(string jsonSettings)
    signal loadDigitalSensorSettings(string sensorName)
    function addSensorModelItem(sensorName) {
        console.log('addSensorModelItem', sensorName);
        sensorList.append({text: sensorName});
    }
    function addItem(elm) {
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
        console.log(JSON.stringify(channelInfo));
        configDialog.channelName = channelInfo.channel || configDialog.channelName;
        if (channelInfo.status)
            idStatus.currentIndex = channelInfo.status === "Enabled" ? 0 : 1;
        idName.text = channelInfo.name || idName.text;
        idMode.currentIndex = findIndex(channelInfo.mode, idMode.model) || 0;
        idInterval.text = channelInfo.interval;
        idSlope.text = channelInfo.slope;
        idOffset.text = channelInfo.offset;
        idRightDigits.text = channelInfo.rightDigits;
        idUnit.currentIndex = findIndex(channelInfo.unit,idUnit.model);
    }
    function setFormValues(json) {
        console.log(json);
        let channelInfo = JSON.parse(json);
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
//        ListElement {
//            text: "Thies/1.1005.54.000"
//        }
//        ListElement {
//            text: "Campbell/EE181-L"
//        }
//        ListElement {
//            text: "Campbell/CS100"
//        }
//        ListElement {
//            text: "YoungUSA/41342LC"
//        }
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
            return `Digital Channel (${channelName})`
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
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
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
                Layout.columnSpan: 3
            }
    //        ------------------------------------------------
            MyLabel {
                text: "Name"
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyTextEdit {
                id: idName
                text: "N/A"
                validator: RegExpValidator {
                    regExp: Global.nameRegEx
                }
                Layout.columnSpan: 3
                enabled: idStatus.currentIndex === 0
            }
            // ------------------------------------------------
            MyLabel {
                text: "Mode"
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyComboBox {
                id: idMode
                cWidth: idName.width
                cHeight: idName.height
                enabled: idStatus.currentIndex === 0
                model: ListModel {
                    ListElement { text: "Counter" }
                    ListElement { text: "Frequency" }
                }
                currentIndex: 1
                Layout.columnSpan: 3
            }
            // ------------------------------------------------
            MyLabel {
                text: "Interval (second)"
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyTextEdit {
                id: idInterval
                enabled: idStatus.currentIndex === 0
                text: "60"
                Layout.columnSpan: 3
                validator: RegExpValidator
                {
                  regExp: Global.intNumberRegEx
                }
            }
            // ------------------------------------------------
            MyLabel {
                text: "Slope"
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyTextEdit {
                id: idSlope
                text: ""
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 3
                validator: RegExpValidator
                {
                  regExp: Global.floatNumberRegEx
                }
            }
            // ------------------------------------------------
            MyLabel {
                text: "Offset"
                visible: idMode.currentIndex !== 0
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
                visible: idMode.currentIndex !== 0
            }
            MyTextEdit {
                id: idOffset
                text: ""
                enabled: idStatus.currentIndex === 0
                visible: idMode.currentIndex !== 0
                Layout.columnSpan: 3
                validator: RegExpValidator
                {
                  regExp: Global.floatNumberRegEx
                }
            }

            // ------------------------------------------------
            MyLabel {
                text: "Right Digits"
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyTextEdit {
                id: idRightDigits
                text: ""
                enabled: idStatus.currentIndex === 0
                Layout.columnSpan: 3
                validator: RegExpValidator
                {
                  regExp: Global.intNumberRegEx
                }
            }

            // ------------------------------------------------
            MyLabel {
                text: "Unit"
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
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
                Layout.columnSpan: 3
            }
        }
        RowLayout {
            height: okButton.height;

            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 20

            MyComboBox {
                cWidth: 1.7*idResetBtn.width
                cHeight: idResetBtn.height
                model: sensorList
                currentIndex: 0
                enabled: idStatus.currentIndex === 0
                displayText: "Sensor Selection"
                onSelected: {
                    loadDigitalSensorSettings(currentText);
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
            Button {
                id: okButton
                text: "Ok"
                highlighted: true
                onClicked: {
                    let channelInfo = {
                        channel: configDialog.channelName,
                        name: idName.text,
                        status: idStatus.currentText,
                        mode: idMode.currentText,
                        interval: idInterval.text,
                        slope: idSlope.text,
                        offset: idOffset.text,
                        rightDigits: idRightDigits.text,
                        unit: idUnit.currentText
                    };
                    saveDigitalSensorSettings(JSON.stringify(channelInfo));
                }
            }
        }
    }
}
