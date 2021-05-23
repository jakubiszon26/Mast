#include "system_info_form.h"
#include "ui_system_info_form.h"
#include <qfile.h>
#include <qdebug.h>

QString systemName, systemVersion, systemBasedOn, systemWebsite, kernelInfo;

System_Info_Form::System_Info_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::System_Info_Form)
{
    ui->setupUi(this);
    display_system_info();
}

System_Info_Form::~System_Info_Form()
{
    delete ui;
}

void System_Info_Form::display_system_info(){
    // Find system info
    QFile file("/etc/os-release");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    QString line;
    QTextStream instream(&file);
    do{
        line = instream.readLine();
        if(line.startsWith("NAME=")){
            systemName = line.replace("NAME=", "");
        }
        else if(line.startsWith("VERSION=")){
            systemVersion = line.replace("VERSION=", "");
        }
        else if(line.startsWith("ID_LIKE=")){
            systemBasedOn = line.replace("ID_LIKE=", "");
        }
        else if(line.startsWith("HOME_URL=")){
           systemWebsite = line.replace("HOME_URL=", "");
        }
    } while (!line.isNull());
    file.close();

    QFile kernelFile("/proc/version");
    QTextStream kernelInstream(&kernelFile);
    if(!kernelFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    kernelInfo = kernelInstream.readLine();

    //append system info into widgets
    ui->system_name->setText(systemName);
    ui->system_version->setText(systemVersion);
    ui->based_on->setText(systemBasedOn);
    ui->system_website->setText(systemWebsite);
    ui->kernel_info->setText(kernelInfo);
}



