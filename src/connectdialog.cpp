#include "connectdialog.h"
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QComboBox>
#include <QDebug>
#include <QLineEdit>
#include <QSerialPortInfo>
#include "common/utils.h"

ConnectDialog::ConnectDialog(DataLogger *_datalogger, QWidget *parent):QDialog(parent),datalogger(_datalogger)
{
    QTabWidget *tabs = new QTabWidget(this);
    QWidget *directTab = new QWidget(this);
    tabs->addTab(directTab, "Direct");
    QWidget *ipTab = new QWidget(this);
    tabs->addTab(ipTab, "TCP/IP");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLayout->addWidget(tabs);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Connect"));

    QVBoxLayout *layout1 = new QVBoxLayout;
    directTab->setLayout(layout1);

    layout1->addWidget(new QLabel("Port Name"));

    portNameInput = new QComboBox(this);
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info: infos) {
        qDebug() << info.portName() << info.systemLocation();
        portNameInput->addItem(info.portName(), info.portName());
    }
    layout1->addWidget(portNameInput);

    layout1->addWidget(new QLabel("Baudrate"));
    baudrateInput = new QComboBox(this);
    baudrateInput->addItem("9600", 9600);
    baudrateInput->addItem("115200", 115200);
    layout1->addWidget(baudrateInput);
    layout1->addStretch(1);

    QVBoxLayout *layout2 = new QVBoxLayout;
    ipTab->setLayout(layout2);

    layout2->addWidget(new QLabel("URL"));

    urlInput = new QLineEdit(this);
    layout2->addWidget(urlInput);
    layout2->addStretch(1);
}

void ConnectDialog::accept() {
    qDebug() << "Accept button clicked";
    datalogger->setPort(portNameInput->currentText());
    datalogger->setBaudrate(baudrateInput->currentText().toInt());
    if( datalogger->testConnection() ) {
        return QDialog::accept();
    }
    showError(NULL, "Error connecting to Datalogger");
}
