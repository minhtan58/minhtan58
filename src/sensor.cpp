#include "mainwindow.h"
#include <QtDebug>
#include <QQuickItem>
#include <QMetaObject>
void MainWindow::getSensorData(const int itemIdx, const int sensorIdx, const int dataFieldIdx) {
    QVariantMap *sensorData = dataLogger->getSensor(sensorIdx);
//    qDebug() << "getSensorData" << sensorIdx - 1 << (*sensorData)["sensorValue"].toString() << (*sensorData)["channel"].toString();
//    (*sensorData)["sensorValue"] = QString::number( (*sensorData)["sensorValue"].toString().toInt() + 1);
//    qDebug() << (*sensorData)["sensorValue"];
    QMetaObject::invokeMethod(sender(), "updateSensor", Q_ARG(QVariant, itemIdx), Q_ARG(QVariant, sensorIdx), Q_ARG(QVariant, dataFieldIdx), Q_ARG(QVariant, QVariant::fromValue(*sensorData)));
}

void MainWindow::updateViewSensor(QQuickWidget *w) {
    QMetaObject::invokeMethod(w->rootObject(), "clear");
    for ( int i = 0; i < dataLogger->allSensorCount; i++ ) {
        QVariantMap *elem = dataLogger->getSensor(i);
        QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, QVariant::fromValue(*elem)));
    }
}
