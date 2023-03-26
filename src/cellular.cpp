#include "mainwindow.h"
#include <QtDebug>
#include <QQuickItem>
#include <QMetaObject>
#include <QJsonDocument>
#include "common/utils.h"

void MainWindow::updateViewCellular(QQuickWidget *w) {
    QVariantMap *info = dataLogger->infoCellular();
    QMetaObject::invokeMethod(w->rootObject(), "setCellularInfo", Q_ARG(QVariant, QVariant::fromValue(*info)));
}

void MainWindow::setCellularMode(bool state) {
    qDebug() << (state?"true":"false");
    dataLogger->setCellularMode(state);
}
