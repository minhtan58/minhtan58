#include "mainwindow.h"
#include <QQuickWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QDesktopWidget>
#include <QQuickItem>
#include <QStackedWidget>
#include <QMetaObject>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include "common/utils.h"
#include "common/store.h"
#define TOP_HEIGHT (65 + 60 + 120)
void MainWindow::updateViewSystem(QQuickWidget *w) {
    QVariantMap *info = dataLogger->infoOverview();
    QMetaObject::invokeMethod(w->rootObject(), "setInformation", Q_ARG(QVariant, QVariant::fromValue(*info)));
}
void MainWindow::updateViewOverview(QQuickWidget *w) {
    QVariantMap *info = dataLogger->infoOverview();
    QMetaObject::invokeMethod(w->rootObject(), "setInformation", Q_ARG(QVariant, QVariant::fromValue(*info)));
}

void MainWindow::updateView(const QString &viewName) {
    qDebug() << "updateView - " << viewName;
    if (viewName == "overview" ) {
        updateViewOverview(view[viewName]);
    }
    if (viewName == "system" ) {
        updateViewSystem(view[viewName]);
    }
    if (viewName == "analog" ) {
        updateViewAnalog(view[viewName]);
    }
    if (viewName == "digital" ) {
        updateViewDigital(view[viewName]);
    }
    if (viewName == "serial" ) {
        updateViewSerial(view[viewName]);
    }
    if (viewName == "sensor" ) {
        updateViewSensor(view[viewName]);
    }
    if (viewName == "transmission" ) {
        updateViewTransmission(view[viewName]);
    }
    if (viewName == "cellular") {
        updateViewCellular(view[viewName]);
    }
    if (viewName == "systemlogs" ) {
        updateViewLogs(view[viewName], 1);
    }
    if (viewName == "networklogs" ) {
        updateViewLogs(view[viewName], 2);
    }
    if (viewName == "sensorlogs" ) {
        updateViewLogs(view[viewName], 3);
    }
    if (viewName == "logs" ) {
        updateViewLogs(view[viewName], 0);
    }
    if (viewName == "sorting") {
        updateViewSorting(view[viewName]);
    }
    if (viewName == "virtual") {
        updateViewVirtual(view[viewName]);
    }
}
void MainWindow::switchContent(const QString &viewName) {
    updateView(viewName);
    content->setCurrentWidget(view[viewName]);
}

void MainWindow::initContentWidget(const QString &name, const int &_w, const int &_h, const QUrl &path) {
    QQuickWidget *w = new QQuickWidget(_engine, this);
    w->setSource(path);
    w->rootObject()->setWidth(0.75 * _w);
    w->rootObject()->setHeight(_h - TOP_HEIGHT);
    view.insert(name, w);
    content->addWidget(w);
    if (name == "overview") {
        QVariantMap *info = dataLogger->infoOverview();
        QMetaObject::invokeMethod(w->rootObject(), "setInformation", Q_ARG(QVariant, QVariant::fromValue(*info)));
    }
    if (name == "system") {
        qDebug() << "system";
        QObject::connect(w->rootObject(), SIGNAL(importSystemSettings(QString)), this,
                         SLOT(importSystemSettings(QString)));
        QObject::connect(w->rootObject(), SIGNAL(exportSystemSettings(QString, QString)), this,
                         SLOT(exportSystemSettings(QString, QString)));
        QObject::connect(w->rootObject(), SIGNAL(saveSystemSettings(QString)), this,
                         SLOT(saveSystemSettings(QString)));
    }
    if (name == "analog") {
        qDebug() << "initContentWidget - analog";
        for ( int i = 0; i < 12; i++) {
            QVariantMap *elem = dataLogger->getSensor(i);
            QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, QVariant::fromValue(*elem)));
        }
        QStringList sensorNames = dataLogger->getSensorModels("analog_sensors");
        foreach( QString sensorName, sensorNames) {
            qDebug() << sensorName;
            QMetaObject::invokeMethod(w->rootObject(), "addSensorModelItem", Q_ARG(QVariant, QVariant::fromValue(sensorName)));
        }
        QObject::connect(w->rootObject(), SIGNAL(saveAnalogSensorSettings(QString)), this,
                         SLOT(saveAnalogSensorSettings(QString)));
        QObject::connect(w->rootObject(), SIGNAL(loadAnalogSensorSettings(QString)), this,
                         SLOT(loadAnalogSensorSettings(QString)));
    }
    if (name == "digital") {
        qDebug() << "digital";
        for ( int i = 12; i < 18; i++) {
            QVariantMap *elem = dataLogger->getSensor(i);
            QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, QVariant::fromValue(*elem)));
        }
        QStringList sensorNames = dataLogger->getSensorModels("digital_sensors");
        foreach( QString sensorName, sensorNames) {
            qDebug() << sensorName;
            QMetaObject::invokeMethod(w->rootObject(), "addSensorModelItem", Q_ARG(QVariant, QVariant::fromValue(sensorName)));
        }
        QObject::connect(w->rootObject(), SIGNAL(saveDigitalSensorSettings(QString)), this,
                         SLOT(saveDigitalSensorSettings(QString)));
        QObject::connect(w->rootObject(), SIGNAL(loadDigitalSensorSettings(QString)), this,
                         SLOT(loadDigitalSensorSettings(QString)));
    }
    if (name == "serial") {
        qDebug() << "serial";
        for ( int i = 18; i < 24; i++) {
            QVariantMap *elem = dataLogger->getSensor(i);
            QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, QVariant::fromValue(*elem)));
        }
        QStringList sensorNames = dataLogger->getSensorModels("serial_sensors");
        foreach( QString sensorName, sensorNames) {
            qDebug() << sensorName;
            QMetaObject::invokeMethod(w->rootObject(), "addSensorModelItem", Q_ARG(QVariant, QVariant::fromValue(sensorName)));
        }
        QObject::connect(w->rootObject(), SIGNAL(saveSerialSensorSettings(QString)), this,
                         SLOT(saveSerialSensorSettings(QString)));
        QObject::connect(w->rootObject(), SIGNAL(loadSerialSensorSettings(QString)), this,
                         SLOT(loadSerialSensorSettings(QString)));
    }
    if (name == "transmission") {
        qDebug() << "transmission";
        QObject::connect(w->rootObject(), SIGNAL(importTransmissionSettings(QString)), this,
                         SLOT(importTransmissionSettings(QString)));
        QObject::connect(w->rootObject(), SIGNAL(exportTransmissionSettings(QString, QString)), this,
                         SLOT(exportTransmissionSettings(QString, QString)));
        QObject::connect(w->rootObject(), SIGNAL(saveTransmissionSettings(QString)), this,
                         SLOT(saveTransmissionSettings(QString)));
    }
    if (name == "cellular") {
        QObject::connect(w->rootObject(), SIGNAL(setCellularMode(bool)), this, SLOT(setCellularMode(bool)));
    }
    if (name == "sensor") {
        qDebug() << "sensor";
/*        for ( int i = 0; i < dataLogger->sensorCount; i++ ) {
            QVariantMap *elem = dataLogger->getSensor(i);
            QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, QVariant::fromValue(*elem)));
        }*/
        QObject::connect(w->rootObject(), SIGNAL(getSensorData(int, int, int)), this, SLOT(getSensorData(int, int, int)));
    }
    if (name == "systemlogs") {
        qDebug() << "systemlogs";
        w->rootObject()->setProperty("logName", "system");
        w->rootObject()->setProperty("logKey", "L1");
        QObject::connect(w->rootObject(), SIGNAL(filterLogs(QString, QString, QString, QString)), this,
                         SLOT(filterLogs(QString, QString, QString, QString)));
    }
    if (name == "networklogs") {
        qDebug() << "networklogs";
        w->rootObject()->setProperty("logName", "network");
        w->rootObject()->setProperty("logKey", "L2");
        QObject::connect(w->rootObject(), SIGNAL(filterLogs(QString, QString, QString, QString)), this,
                         SLOT(filterLogs(QString, QString, QString, QString)));
    }
//    if (name == "humlogs") {
//        qDebug() << "humlogs";
//        w->rootObject()->setProperty("logName", "hum");
//        w->rootObject()->setProperty("logKey", "L3");
//        QObject::connect(w->rootObject(), SIGNAL(filterLogs(QString, QString, QString, QString)), this,
//                         SLOT(filterLogs(QString, QString, QString, QString)));
//    }
//    if (name == "sensor1logs") {
//        qDebug() << "sensor1logs";
//        w->rootObject()->setProperty("logName", "sensor-1");
//        w->rootObject()->setProperty("logKey", "L4");
//        QObject::connect(w->rootObject(), SIGNAL(filterLogs(QString, QString, QString, QString)), this,
//                         SLOT(filterLogs(QString, QString, QString, QString)));
//    }
//    if (name == "sensor2logs") {
//        qDebug() << "sensor2logs";
//        w->rootObject()->setProperty("logName", "sensor-2");
//        w->rootObject()->setProperty("logKey", "L5");
//        QObject::connect(w->rootObject(), SIGNAL(filterLogs(QString, QString, QString, QString)), this,
//                         SLOT(filterLogs(QString, QString, QString, QString)));
//    }
    if (name == "sorting") {
        qDebug() << "------- sorting ---------";
        QObject::connect(w->rootObject(), SIGNAL(saveOrder(QString)), this, SLOT(saveOrder(QString)));
    }
    if (name == "virtual") {
        qDebug() << "------initContentWidget - virtual------";
        QObject::connect(w->rootObject(), SIGNAL(saveVirtualSensorSettings(QString)), this, SLOT(saveVirtualSensorSettings(QString)));
        for ( int i = 24; i < 39; i++) {
            QVariantMap *elem = dataLogger->getSensor(i);
            QMetaObject::invokeMethod(w->rootObject(), "addItem", Q_ARG(QVariant, QVariant::fromValue(*elem)));
        }
    }
    if (name == "sensorlogs") {
        qDebug() << "sensorlogs";
        w->rootObject()->setProperty("logName", "sensor");
        w->rootObject()->setProperty("logKey", "L3");
        QObject::connect(w->rootObject(), SIGNAL(filterLogs(QString, QString, QString, QString)), this,
                         SLOT(filterLogs(QString, QString, QString, QString)));
    }
}

MainWindow::MainWindow(QWidget *parent, DataLogger *dataLogger, QQmlApplicationEngine *engine) :
    QMainWindow(parent),dataLogger(dataLogger),_engine(engine)
{
    QDesktopWidget dw;
    qDebug() << "Width:" << dw.width() << "Height: " << dw.height();
    int w = storeRead("window", "width").toInt(); // dw.width();
    int h = storeRead("window", "height").toInt(); // dw.height();
    w = w > 0?w:dw.width();
    h = h > 0?h:dw.height();
    qDebug() << "Width:" << w << "Height: " << h;
    resize(w, h);
//    showMaximized();
    topbar = new QQuickWidget(_engine, this);
    topbar->setSource(QUrl("qrc:/qml/top.qml"));
    topbar->show();
    topbar->rootObject()->setWidth(w);
    setMenuWidget(topbar);

    root = new QWidget();
    setCentralWidget(root);
    root->show();
    QVBoxLayout *layout0 = new QVBoxLayout(root);
    layout0->setContentsMargins(0,0,0,0);
    layout0->setSpacing(0);
    bottomBar = new QQuickWidget(_engine, this);
    bottomBar->setSource(QUrl("qrc:/qml/bottom.qml"));
    bottomBar->show();
    bottomBar->rootObject()->setWidth(w);
//    bottomBar->rootObject()->setHeight(60);
    layout0->addWidget(bottomBar, 1);
    QHBoxLayout *layout = new QHBoxLayout();
//    QGridLayout *layout = new QGridLayout(root);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout0->insertLayout(0, layout);
    menu = new QQuickWidget(_engine, this);
    menu->setSource(QUrl("qrc:/qml/menu.qml"));
//    menu->rootObject()->setWidth(0.25 * dw.width());
    menu->rootObject()->setHeight(h - TOP_HEIGHT);
    QObject::connect(menu->rootObject(), SIGNAL(switchContent(QString)), this, SLOT(switchContent(QString)));
    menu->show();

    content = new QStackedWidget(this);

    initContentWidget("overview", w, h, QUrl("qrc:///qml/overview.qml"));
    initContentWidget("system", w, h, QUrl("qrc:///qml/system.qml"));
    initContentWidget("analog", w, h, QUrl("qrc:///qml/analog.qml"));
    initContentWidget("digital", w, h, QUrl("qrc:///qml/digital.qml"));
    initContentWidget("serial", w, h, QUrl("qrc:///qml/serial.qml"));
    initContentWidget("sensor", w, h, QUrl("qrc:///qml/sensor.qml"));
    initContentWidget("virtual", w, h, QUrl("qrc:///qml/virtual.qml"));
    initContentWidget("transmission", w, h, QUrl("qrc:///qml/transmission.qml"));
    initContentWidget("cellular", w, h, QUrl("qrc:///qml/cellular.qml"));
    initContentWidget("sorting", w, h, QUrl("qrc:///qml/sorting.qml"));
    initContentWidget("logs", w, h, QUrl("qrc:///qml/logs.qml"));
//    initContentWidget("networklogs", dw, QUrl("qrc:///qml/logs.qml"));
//    initContentWidget("systemlogs", dw, QUrl("qrc:///qml/logs.qml"));
//    initContentWidget("humlogs", dw, QUrl("qrc:///qml/logs.qml"));
//    initContentWidget("sensor1logs", dw, QUrl("qrc:///qml/logs.qml"));
//    initContentWidget("sensor2logs", dw, QUrl("qrc:///qml/logs.qml"));
//    initContentWidget("sensorlogs", dw, QUrl("qrc:///qml/logs.qml"));

    content->show();

    QString viewName = "overview";
    content->setCurrentWidget(view[viewName]);

    layout->addWidget(menu);
    layout->addWidget(content);
//    layout->addWidget(bottomBar, 1, 0, 1, 2);
}
void MainWindow::resizeEvent(QResizeEvent *event) {
    qDebug() << "window resize" << this->width() << this->height() << root->width() << root->height();
    qDebug() << "topbar" << topbar->width() << topbar->height() << menu->width() << menu->height();

    foreach (QQuickWidget *v, view) {
        v->rootObject()->setWidth(0.75 * root->width());
        v->rootObject()->setHeight(root->height() - 120);
    }
    menu->rootObject()->setWidth(root->width() * 0.25);
    menu->rootObject()->setHeight(root->height() - 120);
//    bottomBar->rootObject()->setWidth(root->width());
//    bottomBar->rootObject()->setWidth(root->width());
    QMainWindow::resizeEvent(event);
}
