#include "mainwindow.h"
#include <QtDebug>
#include <QQuickItem>
#include <QMetaObject>
#include <QJsonDocument>
#include "common/utils.h"

void MainWindow::updateViewSerial(QQuickWidget *w) {
    // TODO
}

bool MainWindow::loadSerialSensorSettings(const QString &sensorName) {
    QVariantMap *sensorConfigs = dataLogger->buildSerialSensorProfile("serial_sensors", sensorName);
    qDebug() << "loadSerialSensorSettings";
    QMetaObject::invokeMethod(sender(), "setFormValuesObj", Q_ARG(QVariant, QVariant::fromValue(*sensorConfigs)));
    delete sensorConfigs;
    return true;
}

bool MainWindow::saveSerialSensorSettings(const QString &jsonSettings) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonSettings.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QString channelName = jsonObj["channel"].toString();

    QStringList tokens;
    tokens.append(jsonObj["name"].toString());
    tokens.append(jsonObj["status"].toString());
    tokens.append(jsonObj["baudrate"].toString());
    tokens.append(jsonObj["databits"].toString());
    tokens.append(jsonObj["parity"].toString());
    tokens.append(jsonObj["stopbits"].toString());
    tokens.append(jsonObj["flowcontrol"].toString());
    tokens.append(jsonObj["leadchar"].toString());
    tokens.append(jsonObj["eol"].toString());
    tokens.append(jsonObj["interval"].toString());
    tokens.append(jsonObj["getdatacommand"].toString());
    tokens.append(jsonObj["unit"].toString());
    tokens.append(jsonObj["datasequence"].toString());
    if (dataLogger->saveChannel("serial", channelName, tokens)) {
        QVariant arg(jsonObj);
        QMetaObject::invokeMethod( sender(), "updateModel", Q_ARG(QVariant, arg));
    }
    else {
        showError("Datalogger Error", "Error in applying configuration");
        QMetaObject::invokeMethod( sender(), "resetForm");
    }

    return true;
}
