#ifndef DATALOGGER_H
#define DATALOGGER_H

#define DB_PATH "datalogger.db"

#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QSerialPort>
#include "common/fileio.h"
//#include <QSqlDatabase>

// #define FRAME_DELIM ":"
//#define DATA_DELIM ';'
#define FRAME_DELIM ";"
#define DATA_DELIM '!'

class DataLogger
{
public:
    DataLogger();

    void setPort(const QString &_port);
    void setBaudrate(int b);

    bool applyConfig(const QString &command, const QStringList &data);
    bool saveChannel(const QString &group, const QString &channelName, const QStringList &data);
    QStringList getAnalogChannels();
    QStringList getDigitalChannels();
    QStringList getSerialChannels();

    QStringList getSensorModels(const QString &type);

    QVariantMap *getSensor(int idx);
    QString getSensorData(int idx);
//    QSqlQuery *getLogs();

    QVariantMap *getAnalogSensorConfig(QString g, QString key);
    QVariantMap *buildAnalogSensorProfile(QString g, QString key);
    QVariantMap *getDigitalSensorConfig(QString g, QString key);
    QVariantMap *buildDigitalSensorProfile(QString g, QString key);
    QVariantMap *getSerialSensorConfig(QString g, QString key);
    QVariantMap *buildSerialSensorProfile(QString g, QString key);

    QVariantMap *parseAnalogSensorResponse(QString &response);
    QVariantMap *parseDigitalSensorResponse(QString &response);
    QVariantMap *parseSerialSensorResponse(QString &response, QString &datasequence, QString &data);
    QVariantMap *parseVirtualSensorResponse(QString &response, QString &datasequence, QString &data);
    QVariantMap *parseCellularInfo(QString &response);
    void parseChannelOrder(QString &response);

    bool testConnection();
    bool saveDevice(const QJsonObject &obj);
    bool saveTransmission(const QJsonObject &obj);
    bool setCellularMode(const bool state);
    QVariantMap *infoOverview();
    QVariantMap *infoTransmission();
    QVariantMap *infoCellular();
    void loadChannelOrder();
    bool saveChannelOrder(const QString &orderSetting);

    void retrieveLogs(const QString &logKey, const QString &logName, QObject *sender);
    void writeCOM(const QString &s, bool end = true);
    QString readCOM();
    int sensorCount = 24;
    int allSensorCount = 39;
    QMap<int, QString> orderCache;
private:
    QMap<QString, QVariantMap *> sensorCache;
    QVariantMap deviceCache;
    QVariantMap transmissionCache;
    QVariantMap cellularCache;
    QString port;
    // FOR EMULATION
    fileio_t log;
    void write(const QString &s, const QString &dir, bool end = true);
    QString read();
    // END 
    QSerialPort *serialPort;

    int baudrate;
};

#endif // DATALOGGER_H
