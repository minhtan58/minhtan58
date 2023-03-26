#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QUrl>
#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QDesktopWidget>
#include <QStackedWidget>
#include <QResizeEvent>
#include "datalogger.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr, DataLogger *dataLogger = nullptr, QQmlApplicationEngine *engine = nullptr);
public slots:
    void switchContent(const QString &value);

    void saveTransmissionSettings(const QString &jsonSettings);
    void importTransmissionSettings(const QString &url);
    void exportTransmissionSettings(const QString &url, const QString &jsonSettings);

    void saveSystemSettings(const QString &jsonSettings);
    void importSystemSettings(const QString &url);
    void exportSystemSettings(const QString &url, const QString &jsonSettings);

    bool saveAnalogSensorSettings(const QString &jsonSettings);
    bool loadAnalogSensorSettings(const QString &sensorName);
    bool saveDigitalSensorSettings(const QString &jsonSettings);
    bool loadDigitalSensorSettings(const QString &sensorName);
    bool saveSerialSensorSettings(const QString &jsonSettings);
    bool loadSerialSensorSettings(const QString &sensorName);
    bool saveVirtualSensorSettings(const QString &jsonSettings);
    void getSensorData(const int itemIdx, const int sensorIdx, const int dataFieldIdx);
    void filterLogs(const QString &logKey, const QString &logName, const QString &from, const QString &to);
    void saveOrder(const QString &jsonSettings);
    void loadOrder();
    void setCellularMode(bool state);
private:
    void initContentWidget(const QString &name, const int &w, const int &h, const QUrl &path);
    void updateView(const QString &viewName);

    void updateViewSystem(QQuickWidget *w);
    void updateViewOverview(QQuickWidget *w);
    void updateViewAnalog(QQuickWidget *w);
    void updateViewDigital(QQuickWidget *w);
    void updateViewSerial(QQuickWidget *w);
    void updateViewSensor(QQuickWidget *w);
    void updateViewTransmission(QQuickWidget *w);
    void updateViewCellular(QQuickWidget *w);
    void updateViewLogs(QQuickWidget *w, int logType);
    void updateViewSorting(QQuickWidget *w);
    void updateViewVirtual(QQuickWidget *w);
    void resizeEvent(QResizeEvent* event);

    QWidget *root;
    QQuickWidget *menu;
    QQuickWidget *topbar;
    QQuickWidget *bottomBar;
    QStackedWidget *content;
    QMap<QString, QQuickWidget *> view;
    DataLogger *dataLogger;
    QQmlApplicationEngine *_engine;
signals:

};

#endif // MAINWINDOW_H
