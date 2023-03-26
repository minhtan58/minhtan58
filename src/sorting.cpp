#include "mainwindow.h"
#include <QtDebug>
#include <QQuickItem>
#include <QMetaObject>
#include <QJsonDocument>
#include "common/utils.h"
bool fnLessThan(QVariantMap *m1, QVariantMap *m2) {
    QVariant vchannel1 = m1->value("channel", NULL);
    QVariant vchannel2 = m2->value("channel", NULL);
    QString channel1 = vchannel1.value<QString>();
    QString channel2 = vchannel2.value<QString>();

    return channel1 < channel2;
}
void MainWindow::saveOrder(const QString &orderSetting) {
    dataLogger->saveChannelOrder(orderSetting);
}
void MainWindow::loadOrder() {
    dataLogger->loadChannelOrder();
}

QString __getKeyFromSensorInfo(QVariantMap *elm, int subChanIdx) {
    QVariant vChannel = elm->value("channel", NULL);
    QString sChannel = vChannel.value<QString>();
    return sChannel + "-" + QString::number(subChanIdx);
}
void MainWindow::updateViewSorting(QQuickWidget *w) {
//    QMetaObject::invokeMethod(w->rootObject(), "startUp");
    QMetaObject::invokeMethod(w->rootObject(), "clear");
    dataLogger->loadChannelOrder();

    for ( auto s : dataLogger->orderCache.values() ) {
        QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, s));
    }
}
