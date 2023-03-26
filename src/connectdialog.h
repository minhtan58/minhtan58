#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include "datalogger.h"

class ConnectDialog: public QDialog
{
    Q_OBJECT
public:
    ConnectDialog(DataLogger *_datalogger, QWidget *parent = nullptr);
public slots:
    void accept() override;
private:
    QComboBox *portNameInput;
    QComboBox *baudrateInput;
    QLineEdit *urlInput;

    DataLogger *datalogger;
};

#endif // CONNECTDIALOG_H
