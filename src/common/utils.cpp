#include <QMessageBox>
#include <QByteArray>
#include <stdio.h>
#include <stdlib.h>

void showError(const QString &text1, const QString &text2) {
    QMessageBox msgBox;
    msgBox.setText(text2);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setInformativeText(text1);
    msgBox.exec();
}
void showSuccess() {
    QMessageBox msgBox;
    msgBox.setText("Success");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}
void saveToFile(char *fileName, char *content) {
    FILE *f = fopen(fileName, "w");
    if (f == NULL) {
        showError("", "Error open file");
        exit(-1);
    }
    fprintf(f, "%s", content);
    fclose(f);
}
QString readFromFile(char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        showError("", "Error open file");
        exit(-1);
    }
    char buff[1024];
    QByteArray strData;
    while ( NULL != fgets(buff, 1024, f) ) {
        strData.append(buff);
    }
    fclose(f);
    return QString(strData);
}
