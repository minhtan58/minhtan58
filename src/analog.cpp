#include "mainwindow.h"
#include <QtDebug>
#include <QQuickItem>
#include <QMetaObject>
#include <QJsonDocument>
#include "common/utils.h"
void MainWindow::updateViewAnalog(QQuickWidget *w) {

}
bool MainWindow::saveAnalogSensorSettings(const QString &jsonSettings) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonSettings.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QString channelName = jsonObj["channel"].toString();

    QStringList tokens;
    tokens.append(jsonObj["name"].toString());
    tokens.append(jsonObj["status"].toString());
    tokens.append(jsonObj["inputRange"].toString());
    tokens.append(jsonObj["interval"].toString());
    tokens.append(jsonObj["slope"].toString());
    tokens.append(jsonObj["offset"].toString());
    tokens.append(jsonObj["rightDigits"].toString());
    tokens.append(jsonObj["unit"].toString());
    //tokens.append("NA");
    if (dataLogger->saveChannel("analog", channelName, tokens)) {
        QVariant arg(jsonObj);
        QMetaObject::invokeMethod( sender(), "updateModel", Q_ARG(QVariant, arg));
    }
    else {
        showError("Datalogger Error", "Error in applying configuration");
        QMetaObject::invokeMethod( sender(), "resetForm");
    }

    return true;
}

bool MainWindow::loadAnalogSensorSettings(const QString &sensorName) {
    QVariantMap *sensorConfigs = dataLogger->buildAnalogSensorProfile("analog_sensors", sensorName);
    qDebug() << "loadSensorSettings";
    QMetaObject::invokeMethod(sender(), "setFormValuesObj", Q_ARG(QVariant, QVariant::fromValue(*sensorConfigs)));
    delete sensorConfigs;
    return true;
}
