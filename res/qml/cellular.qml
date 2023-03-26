import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "Components"
import "Components/Global.js" as Global
Content {
    title: "Cellular Settings"
    signal setCellularMode(bool state);

    function setCellularInfo(info) {
        console.log(info.cellularMode, JSON.stringify(info));
        idCellularMode.currentIndex = Global.findIndex(info.cellularMode, idCellularMode.model);
        idModemStatus.text = info.modemStatus;
        idOperator.text = info.operator;
        idModemAccess.text = info.modemAccess;
        idBand.text = info.band;
        idPhoneNumber.text = info.phoneNumber;
        idIpAddress.text = info.ipAddress;
        idSignalLevel.text = info.signalLevel;
    }
    GridLayout {
        anchors {
            centerIn: parent
        }
        columns: 9
        columnSpacing: 6
        rowSpacing: 4
        MyLabel {
            text: "Cellular Mode"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyComboBox {
            id: idCellularMode
            model: ListModel {
                ListElement { text: "Enabled" }
                ListElement { text: "Disabled" }
            }
            currentIndex: 0
            cWidth: idModemStatus.width
            cHeight: idModemStatus.height
            Layout.columnSpan: 5
        }

//        ------------------------------------------------
        MyLabel {
            text: " "
            Layout.columnSpan: 9
//            Layout.alignment: Qt.AlignRight
        }
        MyLabel {
            text: "Cellular Status"
            Layout.columnSpan: 9
//            Layout.alignment: Qt.AlignHCenter
        }
        MyLabel {
            text: " "
            Layout.columnSpan: 9
//            Layout.alignment: Qt.AlignRight
        }

        // ------------------------------------------------
        MyLabel {
            text: "Modem Status"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idModemStatus
            text: "Ready"
            readOnly: true
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }
//        MyComboBox {
//            id: idModemStatus
//            model: ListModel {
//                ListElement { text: "Ready" }
//                ListElement { text: "Not ready" }
//            }
//            currentIndex: 0
//            cWidth: idPhoneNumber.width
//            cHeight: idPhoneNumber.height
//            Layout.columnSpan: 5
//        }
        // ------------------------------------------------
        MyLabel {
            text: "Operator"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idOperator
            text: "Ready"
            readOnly: true
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }
//        MyComboBox {
//            id: idOperator
//            model: ListModel {
//                ListElement { text: "Viettel" }
//                ListElement { text: "MobiFone" }
//                ListElement { text: "VinaPhone" }
//                ListElement { text: "GTel" }
//                ListElement { text: "Vietnammobile" }
//            }
//            currentIndex: 0
//            cWidth: idPhoneNumber.width
//            cHeight: idPhoneNumber.height
//            Layout.columnSpan: 5
//        }
        // ------------------------------------------------
        MyLabel {
            text: "Modem Access"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idModemAccess
            text: "HSPA"
            readOnly: true
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }
//        MyComboBox {
//            id: idModemAccess
//            model: ListModel {
//                ListElement { text: "HSPA" }
//                ListElement { text: "LTE" }
//                ListElement { text: "GPRS" }
//            }
//            currentIndex: 0
//            cWidth: idPhoneNumber.width
//            cHeight: idPhoneNumber.height
//            Layout.columnSpan: 5
//        }
        // ------------------------------------------------
        MyLabel {
            text: "Band"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idBand
            text: "Band 3"
            readOnly: true
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }
//        MyComboBox {
//            id: idBand
//            model: ListModel {
//                ListElement { text: "Band 3" }
//                ListElement { text: "Unknown band" }
//            }
//            currentIndex: 0
//            cWidth: idPhoneNumber.width
//            cHeight: idPhoneNumber.height
//            Layout.columnSpan: 5
//        }
        // ------------------------------------------------
        MyLabel {
            text: "Phone number"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idPhoneNumber
            text: ""
            readOnly: true
//            validator: RegExpValidator {
//                regExp:/^[0-9]+$/
//            }
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }
        // ------------------------------------------------
        MyLabel {
            text: "IP Address"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idIpAddress
            text: ""
            readOnly: true
//            validator: RegExpValidator
//            {
//              regExp:/^(([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))\.){3}([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))$/
//            }
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }
        // ------------------------------------------------
        MyLabel {
            text: "Signal level"
            Layout.columnSpan: 2
//            Layout.alignment: Qt.AlignRight
        }
        MyText {
            text: ":"
        }
        MyTextEdit {
            id: idSignalLevel
            text: ""
            readOnly: true
            Layout.preferredWidth: Global.largeTextFieldWidth
            Layout.columnSpan: 5
        }
//        MyComboBox {
//            id: idSignalLevel
//            model: ListModel {
//                ListElement { text: "Strong" }
//                ListElement { text: "Medium hight" }
//                ListElement { text: "Medium low" }
//                ListElement { text: "Weak" }
//                ListElement { text: "Very weak" }
//            }
//            currentIndex: 0
//            cWidth: idPhoneNumber.width
//            cHeight: idPhoneNumber.height
//            Layout.columnSpan: 5
//        }
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
                console.log("reset");
            }
        }

        Button {
            id: okButton
            text: "Ok"
            highlighted: true
            onClicked: {
                setCellularMode(idCellularMode.currentIndex === 0);
            }
        }
    }
}
