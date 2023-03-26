#include "mainwindow.h"
#include <QDebug>
#include <QQuickItem>
#include <QMetaObject>

void MainWindow::filterLogs(const QString &logKey, const QString &logName, const QString &from, const QString &to) {
    qDebug() << logKey << logName << from << to;
    dataLogger->retrieveLogs(logKey, logName, sender());
}

void MainWindow::updateViewLogs(QQuickWidget *w, int logType) {
    QMetaObject::invokeMethod(w->rootObject(), "clear");

    dataLogger->writeCOM(QString("S12") + FRAME_DELIM + "L" + QString::number(logType) );
//    while(true) {
//        QString event = dataLogger->readCOM();
//        if (event.length() == 0) {
//            break;
//        }
//        QStringList parts = event.split(FRAME_DELIM);
//        QVariantMap elem;
//        elem.insert("time", parts[0]);
//        elem.insert("type", parts[1]);
//        elem.insert("description", parts[2]);
//        elem.insert("selected", false);
//        elem.insert("hiDDen", false);
//        QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, QVariant::fromValue(elem)));
//    }
    dataLogger->retrieveLogs("L" + QString::number(logType), "Network", w->rootObject()); // TEST
    QMetaObject::invokeMethod(w->rootObject(), "updateLogModel");

    // Nothing to do
}
