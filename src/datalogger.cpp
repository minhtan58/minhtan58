#include <QDebug>
#include "datalogger.h"
#include "common/utils.h"
#include <QVariantMap>
#include "common/store.h"
#include "common/fileio.h"
#include "unistd.h"
#include "string.h"
#include <QJsonDocument>

#define MOCK_TEST 0

QString getChannelSlotFromIndex(int idx) {
    if(idx < 22 && idx > 17) {
        return "COM" + QString::number(idx + 1 - 18);
    }
    else if (idx == 22) {
        return "RS485";
    }
    else if (idx == 23) {
        return "SDI-12";
    }
    else if (idx > 23 ) {
        return QString("VS") + QString::number(idx - 23);
    }
    exit(-1);
    return "";
}
DataLogger::DataLogger() : sensorCache(),deviceCache(), transmissionCache(), cellularCache(), orderCache(), serialPort(NULL)
{
    fileio_init(&log, "log.txt");
}

void DataLogger::setPort(const QString &_port) {
    port = _port;
}

void DataLogger::setBaudrate(int b) {
    baudrate = b;
}
void DataLogger::write(const QString &s, const QString &dir, bool end) {
    char buff[1024*5];
    memset(buff, 0, sizeof(buff));
    if (end) {
        sprintf(buff, "%s: %s%c", dir.toUtf8().data(), s.toUtf8().data(), DATA_DELIM);
    }
    else {
        sprintf(buff, "%s: %s", dir.toUtf8().data(), s.toUtf8().data());
    }
    fileio_write(&log, buff);
}
#define APPDIR "Configurator"
#define DLDIR "Data-Logger "

QString DataLogger::read() {
    return "";
}
void DataLogger::writeCOM(const QString &s, bool end) {
    char buff[1024*5];
    write(s, APPDIR, end);
    memset(buff, 0, sizeof(buff));
    if (end) {
        sprintf(buff, "%s%c", s.toUtf8().data(), DATA_DELIM);
    }
    else {
        sprintf(buff, "%s", s.toUtf8().data());
    }
#if !MOCK_TEST
    serialPort->write(buff);
#endif
}
QString DataLogger::readCOM() {
    bool endCmd = false;
    int cnt = 0;
    QByteArray data;
    while ((!endCmd) && cnt < 3) {
        if (serialPort->waitForReadyRead(1000)) {
            data.append(serialPort->readAll());
            if (data.endsWith(DATA_DELIM)) {
                endCmd = true;
            }
        }
        else {
            cnt++;
        }
    }
    write(QString::fromUtf8(data), DLDIR, false);
    if (endCmd) {
        data.chop(1);
        return QString::fromUtf8(data);
    }
    showError("Wrong Format", "No response");
    return "";
}
bool DataLogger::testConnection() {
#if !MOCK_TEST
    qDebug() << port << baudrate;
    if (serialPort) {
        serialPort->close();
        delete serialPort;
    }
    serialPort = new QSerialPort();
    serialPort->setPortName(port);
    serialPort->setBaudRate(baudrate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        writeCOM("LN");
        QString out = readCOM();
        return out == "OK";
    }
    else {
        showError("Error", serialPort->errorString());
        return false;
    }
#else
    return true; // TEST
#endif
}
bool DataLogger::applyConfig(const QString &command, const QStringList &data) {
    qDebug() << command << data.join(";");
    return true;
}

bool DataLogger::saveChannel(const QString &group, const QString &channelName, const QStringList &data) {
    storeWrite(group, channelName, data.join(";"));
    sensorCache.remove(channelName);
    QString command = "S91";
    if (group == "digital") {
        command = "S92";
    }
    else if (group == "serial") {
        command = "S9R";
    }
    else if (group == "virtual") {
        command = "S13";
    }
    writeCOM(command + FRAME_DELIM + channelName + FRAME_DELIM + data.join(FRAME_DELIM));
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = "91_OK"; // TEST
#endif
    return response == "91_OK" || response == "92_OK" || response == "9R_OK" || response == "13_OK";
}

QVariantMap *DataLogger::getSensor(int idx) {
#if 0
    write("RSS_" + QString::number(idx + 1), APPDIR);
    if (idx < 12) {
        QStringList channels = getAnalogChannels();
        QString channel = channels[idx];
        QVariantMap *sensorChannel = getAnalogSensorConfig("analog", channel);
        return sensorChannel;
    }
    else if (idx < 18) {
        QStringList channels = getDigitalChannels();
        QString channel = channels[idx - 12];
        QVariantMap *sensorChannel = getDigitalSensorConfig("digital", channel);
        return sensorChannel;
    }
    else if (idx < 24) {
        QStringList channels = getSerialChannels();
        QString channel = channels[idx - 18];
        QVariantMap *sensorChannel = getSerialSensorConfig("serial", channel);
        return sensorChannel;
    }
    return NULL;
#else
    if (idx < 12) {
        QString channelIdx = "0" + QString::number(idx + 1);
        writeCOM(QString("RSS") + FRAME_DELIM + channelIdx.right(2));
#if !MOCK_TEST
        QString response = readCOM();
#else
        QString response = "AI" + QString::number(idx + 1) + ";Mua1;Enabled;0 - 1 VDC;222;44;333;2;mm;NA"; // TEST
        QVariant v = storeRead("analog", "AI" + QString::number(idx + 1));
        response = "AI" + QString::number(idx + 1) + ";" + v.toString();
        qDebug() << response;
#endif
        return parseAnalogSensorResponse(response);
    }
    else if (idx < 18) {
        writeCOM(QString("RSS") + FRAME_DELIM + QString::number(idx + 1));
#if !MOCK_TEST
        QString response = readCOM();
#else
        QString response = "DI" + QString::number(idx - 12 + 1) + ";Mua1;Enabled;Counter;222;44;333;2;mm;NA"; // TEST
        QVariant v = storeRead("digital", "DI" + QString::number(idx - 12 + 1));
        response = "DI" + QString::number(idx - 12 + 1) + ";" + v.toString();
#endif
        return parseDigitalSensorResponse(response);
    }
    else if (idx < 24) {
        QString key = getChannelSlotFromIndex(idx);
        writeCOM(QString("RSS") + FRAME_DELIM + QString::number(idx + 1));
        QString datasequence = "";
#if !MOCK_TEST
        QString response = readCOM();
#else
        QString response = key + ";COM 3;Enabled;115200;8;None;1;None;S;0;eol;cmd;%;NA=NA=mm&NA=NA=mm";
        QVariant v = storeRead("serial", key);
        if (!v.isNull()) {
            QString s = v.toString();
            response = key + ";" + s;
        }
        else {
            showError("No serial channel " + key, "Error");
        }
#endif
        QString data = getSensorData(idx);
        return parseSerialSensorResponse(response, datasequence, data);
    }
    else if (idx < 39) {
        QString key = getChannelSlotFromIndex(idx);
        writeCOM(QString("RSS") + FRAME_DELIM + QString::number(idx + 1));
        QString datasequence = "";
#if !MOCK_TEST
        QString response = readCOM();
#else
        QString response = key + "";
        QVariant v = storeRead("virtual", key);
        if (!v.isNull()) {
            QString s = v.toString();
            response = key + ";" + s;
        }
        else {
            showError("No serial channel " + key, "Error");
        }
#endif
        QString data = getSensorData(idx);
        return parseVirtualSensorResponse(response, datasequence, data);
    }
    return NULL;
#endif
}
QString DataLogger::getSensorData(int idx) {
    if (idx > 17 && idx < 24) {
        writeCOM(QString("RSSDATA") + FRAME_DELIM + QString::number(idx+1));
#if !MOCK_TEST
        return readCOM();
#else
        return "SWS" + QString::number(idx-17) + ";clear;low;55;66"; // TEST
#endif
    }
    else if (idx < 39) {
        writeCOM(QString("RSSDATA") + FRAME_DELIM + QString::number(idx + 1));
#if !MOCK_TEST
        return readCOM();
#else
        return "val" + QString::number(idx-23) + ";v2;v3;v4;v5;v6;v7;v8";
#endif
    }
    else {
        return "";
    }
}
QStringList DataLogger::getAnalogChannels() {
    return getKeys("analog");
}

QStringList DataLogger::getDigitalChannels() {
    return getKeys("digital");
}

QStringList DataLogger::getSerialChannels() {
    return getKeys("serial");
}

QVariantMap *DataLogger::parseAnalogSensorResponse(QString &response) {
    QStringList values = response.split(FRAME_DELIM);
    QString key = values[0];
    if (!sensorCache.contains(key)) {
        QVariantMap *item = new QVariantMap();
        item->insert("selected", false);
        sensorCache.insert(key, item);
    }
    QVariantMap *item = sensorCache[key];

    (*item)["channel"] = key;
    (*item)["name"] = values[1];
    (*item)["status"] = values[2];
    (*item)["inputRange"] = values[3];
    (*item)["interval"] = values[4];
    (*item)["slope"] = values[5];
    (*item)["offset"] = values[6];
    (*item)["rightDigits"] = values[7];
    (*item)["unit"] = values[8];
    if (values.count() > 9)
        (*item)["sensorValue"] = values[9];
    else
        (*item)["sensorValue"] = "NA";
    return item;
}
QVariantMap *DataLogger::parseDigitalSensorResponse(QString &response) {
    QStringList values = response.split(FRAME_DELIM);
    qDebug() << response;
    QString key = values[0];
    if (!sensorCache.contains(key)) {
        QVariantMap *item = new QVariantMap();
        item->insert("selected", false);
        sensorCache.insert(key, item);
    }
    QVariantMap *item = sensorCache[key];
    (*item)["channel"] = key;
    (*item)["name"] = values[1];
    (*item)["status"] = values[2];
    (*item)["mode"] = values[3];
    (*item)["interval"] = values[4];
    (*item)["slope"] = values[5];
    (*item)["offset"] = values[6];
    (*item)["rightDigits"] = values[7];
    (*item)["unit"] = values[8];
    if (values.count() > 9)
        (*item)["sensorValue"] = values[9];
    else
        (*item)["sensorValue"] = "NA";
    qDebug() << "done";
    return item;
}
QVariantMap *DataLogger::parseSerialSensorResponse(QString &response,QString &datasequence, QString &data) {
    QStringList values = response.split(FRAME_DELIM);
    QString key = values[0];
    if (!sensorCache.contains(key)) {
        QVariantMap *item = new QVariantMap();
        item->insert("selected", false);
        sensorCache.insert(key, item);
    }
    QVariantMap *item = sensorCache[key];
    (*item)["channel"] = key;
    (*item)["name"] = values[1];
    (*item)["status"] = values[2];
    (*item)["baudrate"] = values[3];
    (*item)["databits"] = values[4];
    (*item)["parity"] = values[5];
    (*item)["stopbits"] = values[6];
    (*item)["flowcontrol"] = values[7];
    (*item)["leadchar"] = values[8];
    (*item)["eol"] = values[9];
    (*item)["interval"] = values[10];
    (*item)["getdatacommand"] = values[11];
    (*item)["unit"] = values[12];
    (*item)["datasequence"] = values[13];
//    (*item)["datasequence"] = datasequence;
    (*item)["sensorValue"] = "330";
    (*item)["data"] = data;
    return item;
}
QVariantMap *DataLogger::parseVirtualSensorResponse(QString &response, QString &datasequence, QString &data) {
    QStringList values = response.split(FRAME_DELIM);
    QString key = values[0];
    if (!sensorCache.contains(key)) {
        QVariantMap *item = new QVariantMap();
        item->insert("selected", false);
        sensorCache.insert(key, item);
    }
    QVariantMap *item = sensorCache[key];
    (*item)["channel"] = key;
    (*item)["name"] = values[1];
    (*item)["status"] = values[2];
    (*item)["vsType"] = values[3];
    (*item)["inSensor1"] = values[4];
    (*item)["channelIndex1"] = values[5];
    (*item)["inSensor2"] = values[6];
    (*item)["channelIndex2"] = values[7];
    (*item)["startTime"] = values[8];
    (*item)["interval"] = values[9];
    (*item)["sensorHeight"] = values[10];
    (*item)["datasequence"] = values[11];
    (*item)["sensorValue"] = "330";
    (*item)["data"] = data;
    return item;
}
QVariantMap *DataLogger::getAnalogSensorConfig(QString g, QString key) {
    QVariant v = storeRead(g, key);
    QString s = v.toString();
    QStringList values = s.split("|");
    if (!sensorCache.contains(key)) {
        QVariantMap *item = new QVariantMap();
        item->insert("channel", key);
        item->insert("name", values[0]);
        item->insert("status", values[1]);
        item->insert("inputRange", values[2]);
        item->insert("interval", values[3]);
        item->insert("slope", values[4]);
        item->insert("offset", values[5]);
        item->insert("selected", false);
        item->insert("sensorValue", "33");
        item->insert("unit", values[6]);
        sensorCache.insert(key, item);
    }
    write(values.join(FRAME_DELIM), DLDIR);
    return sensorCache[key];
}
QVariantMap *DataLogger::buildAnalogSensorProfile(QString g, QString key) {
    QVariant v = storeRead(g, key);
    QString s = v.toString();
    QStringList values = s.split("|");
    QVariantMap *item = new QVariantMap();
    item->insert("inputRange", values[0]);
    item->insert("interval", values[1]);
    item->insert("slope", values[2]);
    item->insert("offset", values[3]);
    item->insert("unit", values[4]);
    return item;
}

QVariantMap *DataLogger::getDigitalSensorConfig(QString g, QString key) {
    QVariant v = storeRead(g, key);
    QString s = v.toString();
    QStringList values = s.split("|");

    if (!sensorCache.contains(key)) {
        QVariantMap *item = new QVariantMap();
        item->insert("channel", key);
        item->insert("name", values[0]);
        item->insert("status", values[1]);
        item->insert("mode", values[2]);
        item->insert("interval", values[3]);
        item->insert("slope", values[4]);
        item->insert("offset", values[5]);
        item->insert("unit", values[6]);
        item->insert("selected", false);
        item->insert("sensorValue", "330");
        sensorCache.insert(key, item);
    }
    write(values.join(FRAME_DELIM), DLDIR);
    return sensorCache[key];
}
QVariantMap *DataLogger::buildDigitalSensorProfile(QString g, QString key) {
    QVariant v = storeRead(g, key);
    QString s = v.toString();
    QStringList values = s.split("|");
    QVariantMap *item = new QVariantMap();
    item->insert("mode", values[0]);
    item->insert("interval", values[1]);
    item->insert("slope", values[2]);
    item->insert("offset", values[3]);
    item->insert("unit", values[4]);
    return item;
}

QVariantMap *DataLogger::getSerialSensorConfig(QString g, QString key) {
    QVariant v = storeRead(g, key);
    QString s = v.toString();
    QStringList values = s.split("|");
    if (!sensorCache.contains(key)) {
        QVariantMap *item = new QVariantMap();
        item->insert("channel", key);
        item->insert("name", values[0]);
        item->insert("status", values[1]);
        item->insert("baudrate", values[2]);
        item->insert("databits", values[3]);
        item->insert("parity", values[4]);
        item->insert("stopbits", values[5]);
        item->insert("flowcontrol", values[6]);
        item->insert("leadchar", values[7]);
        item->insert("eol", values[8]);
        item->insert("interval", values[9]);
        item->insert("getdatacommand", values[10]);
        item->insert("unit", values[11]);
        item->insert("datasequence", values[12]);
        item->insert("selected", false);
        item->insert("sensorValue", "330");
        sensorCache.insert(key, item);
    }
    write(values.join(";"), DLDIR);
    return sensorCache[key];
}

QVariantMap *DataLogger::buildSerialSensorProfile(QString g, QString key) {
    QVariant v = storeRead(g, key);
    QString s = v.toString();
    QStringList values = s.split("|");
    QVariantMap *item = new QVariantMap();

    item->insert("baudrate", values[0]);
    item->insert("databits", values[1]);
    item->insert("parity", values[2]);
    item->insert("stopbits", values[3]);
    item->insert("flowcontrol", values[4]);
    item->insert("leadchar", values[5]);
    item->insert("eol", values[6]);
    item->insert("interval", values[7]);
    item->insert("getdatacommand", values[8]);
    item->insert("unit", values[9]);
    item->insert("datasequence", values[10]);

    return item;
}

void DataLogger::retrieveLogs(const QString &logKey, const QString &logName, QObject *sender) {
    int count = 0;
    write("S12" + logKey, APPDIR);
    int i = 1;
    while (count < 28) {
        QString readData = "2022/02/" + QString::number(i) + " 01:23;" + logName + ";Cellular Disconnect!";
        QStringList parts = readData.split(";");
        QVariantMap elem;
        elem.insert("time", parts[0]);
        elem.insert("type", parts[1]);
        elem.insert("description", parts[2]);
        elem.insert("selected", false);
        elem.insert("hidden", false);
        QMetaObject::invokeMethod(sender, "addItem", Q_ARG(QVariant, QVariant::fromValue(elem)));
//        usleep(10 * 1000);
        qDebug() << count;
        count++; i++;
    }
    QMetaObject::invokeMethod(sender, "updateLogModel");
}

QVariantMap *DataLogger::infoOverview() {
#if 0
    write("S7", APPDIR);
    QStringList keys = getKeys("device");
    deviceCache.clear();
    foreach( QString key, keys ) {
        qDebug() << key;
        QString val = storeRead("device", key).toString();
        deviceCache.insert(key, val);
    }
    write(deviceCache["modelName"].toString() + ";" + 
        deviceCache["stationName"].toString() + ";" +
        deviceCache["stationId"].toString() + ";" +
        deviceCache["serialNumber"].toString() + ";" +
        deviceCache["firmwareVersion"].toString() + ";" +
        deviceCache["macAddress"].toString() + ";" + 
        deviceCache["ipAddress"].toString() + ";" +
        deviceCache["batteryVoltage"].toString(), DLDIR
    );
    return &deviceCache;
#else
    writeCOM("S7");
    QStringList keys = getKeys("device");
    deviceCache.clear();
#if !MOCK_TEST
    QString data = readCOM();
#else
    QString data = "DSL-21;HN1234;ID1111;112;FW;2:C:A;192.168.111.102;255.255.255.255;GW;99;2022/1/26 11:54:16"; // TEST
#endif
    QStringList values = data.split(FRAME_DELIM);
    deviceCache.insert("modelName", values[0]);
    deviceCache.insert("stationName", values[1]);
    deviceCache.insert("stationId", values[2]);
    deviceCache.insert("serialNumber", values[3]);
    deviceCache.insert("firmwareVersion", values[4]);
    deviceCache.insert("macAddress", values[5]);
    deviceCache.insert("ipAddress", values[6]);
//
    deviceCache.insert("netmask", values[7]);
    deviceCache.insert("gateway", values[8]);
    deviceCache.insert("batteryVoltage", values[9]);
    deviceCache.insert("dateTime", values[10]);
//    deviceCache.insert("batteryVoltage", values[7]);
    return &deviceCache;
#endif
}
bool DataLogger::saveDevice(const QJsonObject &obj) {
#if 0
    write(QString("S8") + FRAME_DELIM +
      obj["stationName"].toString() + FRAME_DELIM +
      obj["stationId"].toString() + FRAME_DELIM +
      obj["dateTime"].toString() + FRAME_DELIM +
      obj["ipAddress"].toString() + FRAME_DELIM +
      obj["netmask"].toString() + FRAME_DELIM +
      obj["gateway"].toString(), APPDIR);

    write("S8;" +
      obj["stationName"].toString() + ";" + 
      obj["stationId"].toString() + ";" + 
      obj["dateTime"].toString() + ";" + 
      obj["ipAddress"].toString() + ";" + 
      obj["netmask"].toString() + ";" + 
      obj["gateway"].toString(), DLDIR);
    foreach (QString key, obj.keys()) {
        storeWrite("device", key, obj[key].toString());
    }
    return true;
#else
    writeCOM(QString("S8") + FRAME_DELIM +
      obj["stationName"].toString() + FRAME_DELIM +
      obj["stationId"].toString() + FRAME_DELIM +
      obj["dateTime"].toString() + FRAME_DELIM +
      obj["ipAddress"].toString() + FRAME_DELIM +
      obj["netmask"].toString() + FRAME_DELIM +
      obj["gateway"].toString());
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = "8_OK";
#endif
    return response == "8_OK";
#endif
}
bool DataLogger::setCellularMode(const bool state) {
    writeCOM(QString("S15") + FRAME_DELIM + (state?"true":"false"));
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = "15_OK";
#endif
    return response == "15_OK";
}
QVariantMap *DataLogger::infoTransmission() {
    /*
    QStringList keys = getKeys("transmission");
    transmissionCache.clear();
    foreach( QString key, keys ) {
        qDebug() << key;
        QString val = storeRead("transmission", key).toString();
        transmissionCache.insert(key, val);
    }
    return &transmissionCache;
    */
    writeCOM("RS11");
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = "2020/03/19 00:10:45;50;localhos:5000;5000;user;passwd;fname;30;789"; // TEST
#endif
    QStringList values = response.split(FRAME_DELIM);
    transmissionCache.clear();
    transmissionCache.insert("startTime", values[0]);
    transmissionCache.insert("interval", values[1]);
    transmissionCache.insert("url", values[2]);
    transmissionCache.insert("port", values[3]);
    transmissionCache.insert("userName", values[4]);
    transmissionCache.insert("password", values[5]);
    transmissionCache.insert("fileName", values[6]);
    transmissionCache.insert("headerInterval", values[7]);
    transmissionCache.insert("tcpIp", values[8]);
    return &transmissionCache;
}
bool DataLogger::saveTransmission(const QJsonObject &obj) {
#if 0
    write("S11;" + 
      obj["startTime"].toString() + ";" + 
      obj["interval"].toString() + ";" + 
      obj["url"].toString() + ";" + 
      obj["port"].toString() + ";" + 
      obj["userName"].toString() + ";" + 
      obj["password"].toString() + ";" +
      obj["fileName"].toString() + ";" +
      obj["headerInterval"].toString(), APPDIR);

    write("S11;" + 
      obj["startTime"].toString() + ";" + 
      obj["interval"].toString() + ";" + 
      obj["url"].toString() + ";" + 
      obj["port"].toString() + ";" + 
      obj["userName"].toString() + ";" + 
      obj["password"].toString() + ";" +
      obj["fileName"].toString() + ";" +
      obj["headerInterval"].toString(), DLDIR);

    foreach (QString key, obj.keys()) {
        storeWrite("transmission", key, obj[key].toString());
    }
    return true;
#else
    writeCOM(QString("S11") + FRAME_DELIM +
            obj["startTime"].toString() + FRAME_DELIM +
            obj["interval"].toString() + FRAME_DELIM +
            obj["url"].toString() + FRAME_DELIM +
            obj["port"].toString() + FRAME_DELIM +
            obj["userName"].toString() + FRAME_DELIM +
            obj["password"].toString() + FRAME_DELIM +
            obj["fileName"].toString() + FRAME_DELIM +
            obj["headerInterval"].toString() + FRAME_DELIM +
            obj["tcpIp"].toString());
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = "11_OK";
#endif
    return response == "11_OK";
#endif

}
QVariantMap *DataLogger::parseCellularInfo(QString &response) {
    cellularCache.clear();
    QStringList values = response.split(FRAME_DELIM);
    qDebug() << response;
    QString key = values[0];

    cellularCache.insert("cellularMode", values[0]);
    cellularCache.insert("modemStatus", values[1]);
    cellularCache.insert("operator", values[2]);
    cellularCache.insert("modemAccess", values[3]);
    cellularCache.insert("band", values[4]);
    cellularCache.insert("phoneNumber", values[5]);
    cellularCache.insert("ipAddress", values[6]);
    cellularCache.insert("signalLevel", values[7]);

    return &cellularCache;
}

QVariantMap *DataLogger::infoCellular() {
    writeCOM("RS15");
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = QString("Disabled") + FRAME_DELIM
            + "Ready" + FRAME_DELIM
            + "Viettel" + FRAME_DELIM
            + "HPSA" + FRAME_DELIM
            + "Band 3" + FRAME_DELIM
            + "0852465677" + FRAME_DELIM
            + "1.1.1.1" + FRAME_DELIM
            + "Strong";
#endif
    return parseCellularInfo(response);
}

QStringList DataLogger::getSensorModels(const QString &type) {
    return getKeys(type);
}
bool DataLogger::saveChannelOrder(const QString &orderSetting) {
    storeWrite("order", "channel_order", orderSetting);
    writeCOM(QString("S14") + FRAME_DELIM + orderSetting );
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = "14_OK";
#endif
    return response == "14_OK";
}
void DataLogger::loadChannelOrder() {
    writeCOM("RS14");
#if !MOCK_TEST
    QString response = readCOM();
#else
    QString response = storeRead("order", "channel_order").toString();
    qDebug() << "ac ac ac " << response;
#endif
    parseChannelOrder(response);
}

void DataLogger::parseChannelOrder(QString &response) {
    QMap<QString, QString> orderTable;
    int newOrder = 1000;
    QStringList tokens = response.split(FRAME_DELIM);
    for (int i = 0; i < tokens.length(); i++) {
        qDebug() << "++ " << tokens[i];
        QStringList fields = tokens[i].split("&");
        QString key = fields[0] + "-" + fields[1];
        qDebug() << key << fields[2];
        orderTable.insert(key, fields[2]);
    }

    orderCache.clear();
    QStringList keyList = sensorCache.keys();
    for (int i = 0; i < keyList.length(); i++) {
        QString key = keyList[i];
        QVariantMap *sensorInfo = sensorCache[key];
        if (sensorInfo->value("status").value<QString>() != "Enabled") continue;
        if ( sensorInfo->contains("datasequence")) {
            QString datasequence = sensorInfo->value("datasequence").value<QString>();
            QStringList fields = datasequence.split("&");
            for (int i = 0; i < fields.length(); i++) {
                QString k = sensorInfo->value("channel").value<QString>() + "-" + QString::number(i);
                QStringList subFields = fields[i].split("=");
                if (subFields[0].length() == 0) continue;
                QJsonObject jso;
                jso.insert("sensor", sensorInfo->value("channel").value<QString>());
                jso.insert("name", subFields[0]);
                jso.insert("status", sensorInfo->value("status").value<QString>());
                jso.insert("channelIndex", QString::number(i));
                QJsonDocument doc(jso);
                QString strJson(doc.toJson(QJsonDocument::Compact));

                if (orderTable.contains(k)) {
                    orderCache.insert(orderTable.value(k).toInt(), strJson);
                }
                else {
                    orderCache.insert(newOrder++, strJson);
                }
            }
        }
        else {
            QString k = sensorInfo->value("channel").value<QString>() + "-0";
            QJsonObject jso;
            jso.insert("sensor", sensorInfo->value("channel").value<QString>());
            jso.insert("name", sensorInfo->value("name").value<QString>());
            jso.insert("status", sensorInfo->value("status").value<QString>());
            jso.insert("channelIndex", "0");
            QJsonDocument doc(jso);
            QString strJson(doc.toJson(QJsonDocument::Compact));
            qDebug() << "key:" << k;
            if (orderTable.contains(k)) {
                orderCache.insert(orderTable.value(k).toInt(), strJson);
            }
            else {
                orderCache.insert(newOrder++, strJson);
            }
        }
    }
}
