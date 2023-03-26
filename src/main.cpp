#include <QApplication>
#include <mainwindow.h>
#include <QUrl>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QQmlContext>
#include "connectdialog.h"
#include "datalogger.h"

#include <QApplication>
int main(int argc, char *argv[ ]) {
//    QVariant *v = new QVariant();
//    qDebug() << "Test variant" << v->isValid() << v->isNull();
//    delete v;
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    DataLogger dataLogger;
    ConnectDialog *connectDialog = new ConnectDialog(&dataLogger, NULL);
    if (QDialog::Accepted == connectDialog->exec()) {
        MainWindow mainWindow(NULL, &dataLogger, &engine);
        mainWindow.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
        mainWindow.show();
        return app.exec();
    }
    return 0;
}
