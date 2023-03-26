.pragma library

var primaryColor = "steelblue"
var labelFontSize = 10
var fontSize = 12
var condensedHeight = 30
var topMargin1 = 50
const largeTextFieldWidth = 300
const nameRegEx = /^[a-zA-Z0-9-_\s]{0,10}$/
const usernameRegEx = /^[a-zA-Z0-9-_]{0,10}$/
const filenameRegEx = /^[a-zA-Z0-9_-\.]{0,20}$/
const strDataRegEx30 = /^[a-zA-Z0-9@#\$%\^&\*\.,<>\(\)\/\\:\+\]\[=-_]{0,30}$/
const strDataRegEx10 = /^[a-zA-Z0-9@#\$%\^&\*\.,<>\(\)\/\\:\+\]\[=-_]{0,10}$/
const floatNumberRegEx = /^[-\+]?[0-9]{0,10}\.?[0-9]{0,3}$/
const intNumberRegEx = /^[0-9]{0,5}$/
const timeRegEx = /(?:[01]\d|2[0123]):(?:[012345]\d):(?:[012345]\d)/

const vsInputChannelProps = ["channel1", "channel2"]
const vsParamProps = ["startTime", "interval", "sensorHeight"]
const vsOutputProps = ["out1", "out2", "out3", "out4", "out5", "out6", "out7", "out8"]
const vsInputChannelConfigs = [{
                                  'type': "MET Wind",
                                  'channel1': "WS Channel",
                                  'channel2': "WD Channel"
                               }, {
                                  "type": "Dewpoint",
                                  'channel1': "TEMP channel",
                                  'channel2': "HUM channel"
                               }, {
                                  "type": "QNH",
                                  'channel1': "PRESS channel",
                                  'channel2': "TEMP channel"
                               }, {
                                   "type": "Solar Radiation Acc",
                                   'channel1': "RAD channel",
                                   'channel2': 0
                               }, {
                                   "type": "Sunshine Duration",
                                   'channel1': "RAD channel",
                                   'channel2': 0
                               }, {
                                   "type": "Rain Accumulation",
                                   'channel1': "RAIN channel",
                                   'channel2': 0
                               }, {
                                   "type": "Minimum",
                                   'channel1': "Channel",
                                   'channel2': 0
                               }, {
                                   "type": "Maximum",
                                   'channel1': "Channel",
                                   'channel2': 0
                               }, {
                                   "type": "Average",
                                   'channel1': "Channel",
                                   'channel2': 0
                               }]
const vsParamConfigs = [{
   'type': "MET Wind",
   "startTime": "Start time",
   "interval": 0,
   "sensorHeight": 0
}, {
   "type": "Dewpoint",
   "startTime": "Start time",
   "interval":  "Interval",
   "sensorHeight": 0
}, {
   "type": "QNH",
   "startTime": "Start time",
   "interval":  "Interval",
   "sensorHeight": "Sensor height"
}, {
   "type": "Solar Radiation Acc",
   "startTime": "Start time",
   "interval":  "Interval",
   "sensorHeight": 0
}, {
   "type": "Sunshine Duration",
   "startTime": "Start time",
   "interval":  "Interval",
   "sensorHeight": 0
}, {
   "type": "Rain Accumulation",
   "startTime": "Start time",
   "interval":  "Interval",
   "sensorHeight": 0
}, {
    "type": "Minimum",
    "startTime": "Start time",
    "interval":  "Interval",
    "sensorHeight": 0
}, {
    "type": "Maximum",
    "startTime": "Start time",
    "interval":  "Interval",
    "sensorHeight": 0
}, {
    "type": "Average",
    "startTime": "Start time",
    "interval":  "Interval",
    "sensorHeight": 0
}]
const vsInputMaskConfig = {
    "startTime": "99:99:99"
}
const vsRegExValidatorConfig = {
    "startTime": /.*/
}
const vsOutputConfigs = [{
                             'type': "MET Wind",
                             "out1": "instantWS",
                             "out2": "instantWD",
                             "out3": "2mWSMax",
                             "out4": "2mWDMax",
                             "out5": "2mMaxTime",
                             "out6": "2sWSMax",
                             "out7": "2sWDMax",
                             "out8": "2sMaxTime"
                         }, {
                             'type': "Dewpoint",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         }, {
                             'type': "QNH",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         },{
                             'type': "Solar Radiation Acc",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         }, {
                             'type': "Sunshie duration",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         }, {
                             'type': "Rain Accumulation",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         }, {
                             'type': "Minimum",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         }, {
                             'type': "Maximum",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         }, {
                             'type': "Average",
                             "out1": "Name",
                             "out2": 0,
                             "out3": 0,
                             "out4": 0,
                             "out5": 0,
                             "out6": 0,
                             "out7": 0,
                             "out8": 0
                         }]
function findIndex(value, listModel) {
    for (let i = 0; i < listModel.count; i++) {
        if( value === listModel.get(i).text ) return i;
    }
    console.log(`Cannot find ${value} in `, listModel);
    Qt.quit();
}

function parseDataSequence(ds) {
    if (!ds || !ds.length) return [];
    let tokens = ds.split('&');
    let fields = [];
    for (let s of tokens) {
        let [name, index, unit] = s.split('=');
        fields.push({name: name, index: index, unit: unit});
    }
    return fields
}
function toDataSequence(datafields) {
    let ds = [];
    for (let f of datafields) {
        ds.push(`${f.name}=${f.index}=${f.unit}`);
    }
    return ds.join("&");
}
