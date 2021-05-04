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

    QTextStream instream(&file);
    while(!instream.atEnd()){
        QString line = instream.readLine();
        ui->output_container->insertPlainText(line + "\n");
    }
    file.close();

}
