#include "hostname.h"
#include "ui_hostname.h"
#include <QFile>
#include <QMessageBox>
Hostname::Hostname(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hostname)
{
    ui->setupUi(this);
}

Hostname::~Hostname()
{
    delete ui;
}


void Hostname::on_set_button_clicked()
{
    QString oldHostname;
    QString newHostname = ui->hostname_input->text();
    QString line;
    QFile hostnameFile("/etc/hostname");
    QFile hostsFile("/etc/hosts");
    QFile temporaryFile("/etc/hosts_temp");

    hostnameFile.open(QFile::ReadWrite);
    hostsFile.open(QFile::ReadWrite);
    temporaryFile.open(QFile::ReadWrite | QIODevice::Append);

    oldHostname = hostnameFile.readAll();
    hostnameFile.resize(0);
    hostnameFile.write(newHostname.toUtf8());
    hostnameFile.close();

    qDebug() << "old hostname: " + oldHostname;

    //edit /etc/hosts
    QTextStream orginalFileStream(&hostsFile);
    QTextStream temporaryFileStream(&temporaryFile);
    temporaryFile.resize(0);
    do{
        line = orginalFileStream.readLine();
        if(line.endsWith(oldHostname.replace("\n", ""))){
            temporaryFile.write(line.replace(oldHostname.replace("\n", ""), newHostname).toUtf8() + "\n");
        }else{
            temporaryFile.write(line.toUtf8() + "\n");
        }
    }
    while (!line.isNull());
    hostsFile.remove();
    temporaryFile.rename("/etc/hosts");
    QMessageBox doneMessage;
    doneMessage.setText("you must restart your computer for the changes to take effect");
    doneMessage.show();
}

