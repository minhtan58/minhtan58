#ifndef STORE_H
#define STORE_H
#include <QString>
#include <QVariant>
#include <QStringList>
QStringList getGroups();
QStringList getKeys(const QString &group);
void storeWrite(const QString &group, const QString &key, const QString &value);
QVariant storeRead(const QString &group, const QString &key);
#endif // STORE_H
