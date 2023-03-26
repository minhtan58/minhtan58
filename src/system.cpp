#include "mainwindow.h"
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaObject>
#include "common/utils.h"

void MainWindow::importSystemSettings(const QString &url) {
    QUrl urlObj(url);
    QString jsonContent = readFromFile(urlObj.toLocalFile().toUtf8().data());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonContent.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QMetaObject::invokeMethod(sender(), "setInformation", Q_ARG(QVariant, QVariant::fromValue(jsonObj.toVariantMap())));
}
void MainWindow::saveSystemSettings(const QString &jsonSettings) {
    qDebug() << jsonSettings;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonSettings.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    if (!dataLogger->saveDevice(jsonObj)) {
        showError("Error in setting system information", "");
    }
    else {
        showSuccess();
    }
}
void MainWindow::exportSystemSettings(const QString &url, const QString &jsonSettings) {
    QUrl urlObj(url);
    saveToFile(urlObj.toLocalFile().toUtf8().data(), jsonSettings.toUtf8().data());
    qDebug() << url << jsonSettings;
}

