#include "mainwindow.h"
#include <QtDebug>
#include <QQuickItem>
#include <QMetaObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "common/utils.h"

bool MainWindow::saveVirtualSensorSettings(const QString &jsonSettings) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonSettings.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QString channelName = jsonObj["channel"].toString();

    QStringList tokens;
    tokens.append(jsonObj["channel"].toString());
    tokens.append(jsonObj["status"].toString());
    tokens.append(jsonObj["vsType"].toString());
    tokens.append(jsonObj["inSensor1"].toString());
    tokens.append(jsonObj["channelIndex1"].toString());
    tokens.append(jsonObj["inSensor2"].toString());
    tokens.append(jsonObj["channelIndex2"].toString());
    tokens.append(jsonObj["startTime"].toString());
    tokens.append(jsonObj["interval"].toString());
    tokens.append(jsonObj["sensorHeight"].toString());
    tokens.append(jsonObj["datasequence"].toString());

    if (dataLogger->saveChannel("virtual", channelName, tokens)) {
        QVariant arg(jsonObj);
        QMetaObject::invokeMethod( sender(), "updateModel", Q_ARG(QVariant, arg));
    }
    else {
        showError("Datalogger Error", "Error in applying configuration");
        QMetaObject::invokeMethod( sender(), "resetForm");
    }


    return true;
}
void MainWindow::updateViewVirtual(QQuickWidget *w) {
    qDebug() << "updateViewVirtual";
    QMetaObject::invokeMethod(w->rootObject(), "allChannelsClear");
    for ( int i = 0; i < dataLogger->allSensorCount; i++ ) {
        QVariantMap *elem = dataLogger->getSensor(i);
        QMetaObject::invokeMethod(w->rootObject(), "allChannelsAddItem", Q_ARG(QVariant, QVariant::fromValue(*elem)));
    }
}
