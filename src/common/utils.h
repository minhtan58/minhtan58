#ifndef __UTILS_H__
#define __UTILS_H__

#include <QMessageBox>
void showError(const QString &text1, const QString &text2);
void showSuccess();
void saveToFile(char *fileName, char *content);
QString readFromFile(char *fileName);
#endif
