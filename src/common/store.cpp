#include <QSettings>
#include <QDebug>
#include "store.h"
QSettings _settings("config.ini", QSettings::IniFormat);
void storeWrite(const QString &group, const QString &key, const QString &value) {
    _settings.setValue(group + "/" + key, value);
}
QVariant storeRead(const QString &group, const QString &key) {
    return _settings.value(group + "/" + key);
}

QStringList getGroups() {
    return _settings.childGroups();
}

QStringList getKeys(const QString &group) {
    _settings.beginGroup(group);
    QStringList keys = _settings.childKeys();
    _settings.endGroup();
    return keys;
}
