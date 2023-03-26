import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "Components"
import "Components/Global.js" as Global
Content {
    title: "Setting Virtual channels"
    signal saveVirtualSensorSettings(string jsonSettings);
    function allChannelsClear() {
        allChannels.clear();
    }
    function allChannelsAddItem(elm) {
        if (!elm.datasequence) {
            elm.text = `${elm.channel} (${elm.name}) - ${elm.status}`
            allChannels.append(elm);
            return;
        }
        let dataFields = Global.parseDataSequence(elm.datasequence);
        for (let i = 0; i < dataFields.length; i++) {
            if (dataFields[i].name.length >0) {
                let elmClone = JSON.parse(JSON.stringify(elm));
                elmClone.name = dataFields[i].name;
                elmClone.unit = dataFields[i].unit;
    //            elmClone.sensorValue = getData( elm.data, dataFields[i].index );
                elmClone.dataFieldIndex = i;
                elmClone.text = `${elmClone.channel} (${elmClone.name}) - ${elmClone.status}`;
                allChannels.append(elmClone);
            }
        }
    }
    function allChannelsFindIndex(sensorName, channelIdx, listModel) {
        for (let i = 0; i < listModel.count; i++ ) {
            let elm = listModel.get(i);
            if (sensorName.startsWith("AI") || sensorName.startsWith("DI")) {
                if (elm.channel === sensorName) {
                    return i;
                }
            }
            else {
                if (elm.channel === sensorName && elm.dataFieldIndex === +channelIdx) {
                    return i;
                }
            }
        }
    }
    function updateModel(sensorInfo) {
        for (let i = 0; i < myTable.model.count; i++) {
            let sensor = myTable.model.get(i);
            if (sensor.channel === sensorInfo.channel) {
                for (let p in sensorInfo) {
                    sensor[p] = sensorInfo[p];
                }
                return;
            }
        }
    }
    function resetForm() {
        setFormValues(configDialog.channelInfoStr);
    }
    function addItem(elm) {
        myTable.addItem(elm);
    }
    function labelInputChannelFn(propName) {
        return Global.vsInputChannelConfigs[idVsType.currentIndex][propName];
    }
    function visibleInputChannelFn(propName) {
        return Global.vsInputChannelConfigs[idVsType.currentIndex][propName] > 0 ||
                Global.vsInputChannelConfigs[idVsType.currentIndex][propName].length > 0
    }
    function labelParamFn(propName) {
        return Global.vsParamConfigs[idVsType.currentIndex][propName];
    }
    function visibleParamFn(propName) {
        return Global.vsParamConfigs[idVsType.currentIndex][propName] > 0 ||
                Global.vsParamConfigs[idVsType.currentIndex][propName].length > 0
    }
    function labelOutputFn(propName) {
        return Global.vsOutputConfigs[idVsType.currentIndex][propName];
    }
    function visibleOutputFn(propName) {
        return Global.vsOutputConfigs[idVsType.currentIndex][propName] > 0 ||
                Global.vsOutputConfigs[idVsType.currentIndex][propName].length > 0
    }
    function inputMaskFn(propName) {
        return Global.vsInputMaskConfig[propName] || "";
    }
    function regExValidatorFn(propName) {
        return Global.vsRegExValidatorConfig[propName] || Global.intNumberRegEx;
    }

    ListModel {
        id: virtualTypeList
        ListElement {
            text: "MET Wind"
        }
        ListElement {
            text: "Dew Point"
        }
        ListElement {
            text: "QNH"
        }
        ListElement {
            text: "Solar Radiation Acc"
        }
        ListElement {
            text: "Sunshine Duration"
        }
        ListElement {
            text: "Rain Acc"
        }
        ListElement {
            text: "Minimum"
        }
        ListElement {
            text: "Maximum"
        }
        ListElement {
            text: "Average"
        }
    }
    ListModel {
        id: allChannels
    }

    function setFormValuesObj(channelInfo) {
        configDialog.visible = true;
        idStatus.currentIndex = Global.findIndex(channelInfo.status, idStatus.model);
        configDialog.channelName = channelInfo.name;
        idVsType.currentIndex = +channelInfo.vsType
        inpRepeater.itemAt(0).currentIndex = allChannelsFindIndex(channelInfo.inSensor1, channelInfo.channelIndex1, allChannels);
        inpRepeater.itemAt(1).currentIndex = allChannelsFindIndex(channelInfo.inSensor2, channelInfo.channelIndex2, allChannels);
        for (let j = 0; j < Global.vsParamProps.length; j++ ) {
            paramRepeater.itemAt(j).text = channelInfo[Global.vsParamProps[j]];
        }
        let dataFields = Global.parseDataSequence(channelInfo.datasequence);
        for (let i = 0; i < dataFields.length; i++) {
            outputRepeater.itemAt(i).text = dataFields[i].name;
        }
    }

    function setFormValues(json) {
        let channelInfo = JSON.parse(json);
        setFormValuesObj(channelInfo);
    }
    MyVirtualSensorTable {
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
        id: configDialog
        property string channelName: ""
        property string channelInfoStr: "{}"
        function makeTitle() {
            return `Virtual Channel (${channelName})`
        }

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
//            anchors {
//                centerIn: parent
//            }
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter

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
                cWidth: 200
                cHeight: Global.condensedHeight
                Layout.columnSpan: 3
            }

    //        ------------------------------------------------
            MyLabel {
                text: "Type"
                Layout.columnSpan: 2
//                Layout.alignment: Qt.AlignRight
            }
            MyText {
                text: ":"
            }
            MyComboBox {
                id: idVsType
                Layout.columnSpan: 3
                model: virtualTypeList
                enabled: idStatus.currentIndex === 0
                cWidth: idStatus.width
                cHeight: idStatus.height
            }
            Rectangle {
                Layout.preferredHeight: 10
                Layout.columnSpan: 6
            }
            // ------------------------------------------------
            Repeater {
                model: Global.vsInputChannelProps
                MyLabel {
                    text: labelInputChannelFn(modelData)
                    visible: visibleInputChannelFn(modelData)
                    Layout.column: 0
                    Layout.row: index + 3
                    Layout.columnSpan: 2
    //                Layout.alignment: Qt.AlignRight
                }
            }
            Repeater {
                model: Global.vsInputChannelProps
                MyText {
                    text: ":"
                    visible: visibleInputChannelFn(modelData)
                    Layout.column: 2
                    Layout.row: index + 3
                }
            }

            Repeater {
                id: inpRepeater
                model: Global.vsInputChannelProps

                MyComboBox {
                    visible: visibleInputChannelFn(modelData)
                    enabled: idStatus.currentIndex === 0
                    model: allChannels
                    Layout.column: 3
                    Layout.row: index + 3
                    Layout.columnSpan: 3
                    cHeight: Global.condensedHeight
                    cWidth: idStatus.width
                    textRole: "text"
                }
            }
            // ------------------------------------------------
            Repeater {
                model: Global.vsParamProps
                MyLabel {
                    text: labelParamFn(modelData)
                    visible: visibleParamFn(modelData)
                    Layout.column: 0
                    Layout.row: index + 5
                    Layout.columnSpan: 2
    //                Layout.alignment: Qt.AlignRight
                }
            }
            Repeater {
                model: Global.vsParamProps
                MyText {
                    text: ":"
                    visible: visibleParamFn(modelData)
                    Layout.column: 2
                    Layout.row: index + 5
                }
            }

            Repeater {
                id: paramRepeater
                model: Global.vsParamProps
                MyTextEdit {
                    visible: visibleParamFn(modelData)
                    enabled: idStatus.currentIndex === 0
                    text: modelData
                    Layout.column: 3
                    Layout.row: index + 5
                    Layout.columnSpan: 3
                    Layout.preferredHeight: Global.condensedHeight
                    inputMask: inputMaskFn(modelData)

                    validator: RegExpValidator
                    {
                      regExp: regExValidatorFn(modelData)
                    }
                }
            }
            // ------------------------------------------------
            Repeater {
                model: Global.vsOutputProps
                MyLabel {
                    text: labelOutputFn(modelData)
                    visible: visibleOutputFn(modelData)
                    Layout.column: 0
                    Layout.row: index + 8
                    Layout.columnSpan: 2
    //                Layout.alignment: Qt.AlignRight
                }
            }
            Repeater {
                model: Global.vsOutputProps
                MyText {
                    text: ":"
                    visible: visibleOutputFn(modelData)
                    Layout.column: 2
                    Layout.row: index + 8
                }
            }

            Repeater {
                id: outputRepeater
                model: Global.vsOutputProps
                MyTextEdit {
                    visible: visibleOutputFn(modelData)
                    enabled: idStatus.currentIndex === 0
                    text: modelData
                    Layout.column: 3
                    Layout.row: index + 8
                    Layout.columnSpan: 3
                    Layout.preferredHeight: Global.condensedHeight
                }
            }
        }
        RowLayout {
            height: okButton.height;

            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 20

//            Button {
//                flat: true
//                text: "Sensor Select"
//                onClicked: {
//                    console.log("Sensor select", idInputRange.currentIndex, idInputRange.currentText);
//                }
//            }
            Button {
                id: idResetBtn
                flat: true
                text: "Reset"
                onClicked: {
                    resetForm();
                }
                Layout.preferredHeight: Global.condensedHeight
            }
            Button {
                id: okButton
                Layout.preferredHeight: Global.condensedHeight
                text: "Ok"
                highlighted: true
                onClicked: {
                    let channelInfo = JSON.parse(configDialog.channelInfoStr);
                    channelInfo.vsType = "" + idVsType.currentIndex;
                    channelInfo.status = idStatus.currentText;
                    for (let k = 0; k < Global.vsInputChannelProps.length; k++) {
                        let idx = inpRepeater.itemAt(k).currentIndex;
                        let channel = allChannels.get(idx);
                        console.log("Ac ac ", channel.dataFieldIndex);
                        channelInfo["inSensor" + (k+1)] = channel.channel;
                        channelInfo["channelIndex" + (k+1)] = "" + channel.dataFieldIndex;
                    }
                    for (let i = 0; i < Global.vsParamProps.length; i++) {
                        channelInfo[Global.vsParamProps[i]] = paramRepeater.itemAt(i).text;
                    }
                    let dataFields = Global.parseDataSequence(channelInfo.datasequence);
                    for (let j = 0; j < dataFields.length; j++) {
                        dataFields[j].index = j+1;
                        if (outputRepeater.itemAt(j).visible)
                            dataFields[j].name = outputRepeater.itemAt(j).text;
                        else
                            dataFields[j].name = "";
                    }
                    channelInfo.datasequence = Global.toDataSequence(dataFields);

                    saveVirtualSensorSettings(JSON.stringify(channelInfo));
                }
            }
        }
    }
}
