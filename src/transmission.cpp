#include "mainwindow.h"
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQuickItem>
#include <QMetaObject>
#include "common/utils.h"

void MainWindow::importTransmissionSettings(const QString &url) {
    QUrl urlObj(url);
    QString jsonContent = readFromFile(urlObj.toLocalFile().toUtf8().data());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonContent.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QMetaObject::invokeMethod(sender(), "setInformation", Q_ARG(QVariant, QVariant::fromValue(jsonObj.toVariantMap())));
}
void MainWindow::saveTransmissionSettings(const QString &jsonSettings) {
    qDebug() << jsonSettings;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonSettings.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    dataLogger->saveTransmission(jsonObj);
}
void MainWindow::exportTransmissionSettings(const QString &url, const QString &jsonSettings) {
    QUrl urlObj(url);
    saveToFile(urlObj.toLocalFile().toUtf8().data(), jsonSettings.toUtf8().data());
}

void MainWindow::updateViewTransmission(QQuickWidget *w) {
    QVariantMap *info = dataLogger->infoTransmission();
    QMetaObject::invokeMethod(w->rootObject(), "setInformation", Q_ARG(QVariant, QVariant::fromValue(*info)));
}
