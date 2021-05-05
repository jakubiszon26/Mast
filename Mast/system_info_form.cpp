#include "system_info_form.h"
#include "ui_system_info_form.h"
#include <qfile.h>
#include <qdebug.h>

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
            ui->output_container->insertPlainText("System - " + line.replace("NAME=", "") + "\n");
        }
        else if(line.startsWith("VERSION=")){
            ui->output_container->insertPlainText("System Version - " + line.replace("VERSION=", "") + "\n");
        }
        else if(line.startsWith("ID_LIKE=")){
            ui->output_container->insertPlainText("Based on - " + line.replace("ID_LIKE=", "") + "\n");
        }
        else if(line.startsWith("HOME_URL=")){
            ui->output_container->insertPlainText("Website - " + line.replace("HOME_URL=", "") + "\n");
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
    line = kernelInstream.readLine();
    ui->output_container->insertPlainText("\nKernel info - " + line);

}
