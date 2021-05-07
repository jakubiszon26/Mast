#include "hardware_info.h"
#include "ui_hardware_info.h"
#include <QFile>

Hardware_Info::Hardware_Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hardware_Info)
{
    ui->setupUi(this);
    display_cpu_info();
}

Hardware_Info::~Hardware_Info()
{
    delete ui;
}

void Hardware_Info::display_cpu_info(){
    bool model_name;
    bool brand_name;
    QString line;
    //cpu info
    QFile file("/proc/cpuinfo");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    QTextStream instream(&file);
    do{
        line = instream.readLine();
        if(line.startsWith("model name") && model_name == false){
            ui->cpu_model->setText(line.replace("model name", ""));
            model_name = true;
        }else if(line.startsWith("vendor_id") && brand_name == false){
            ui->cpu_brand->setText(line.replace("vendor_id", ""));
            brand_name = true;
        }
    } while (!line.isNull());
    file.close();

    //brand of laptop/pc
    QFile pc_vendor_file("/sys/devices/virtual/dmi/id/board_vendor");
    QTextStream in(&pc_vendor_file);
    if(!pc_vendor_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    line = pc_vendor_file.readLine();
    ui->pc_vendor->setText(line);
    pc_vendor_file.close();

    //motherboard version
    QFile motherboard_name_file("/sys/devices/virtual/dmi/id/board_name");
    QTextStream motherboard_in(&motherboard_name_file);
    if(!motherboard_name_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    line = motherboard_name_file.readAll();
    ui->motherboard->setText(line);
    motherboard_name_file.close();

    //BIOS version
    QFile bios_version_file("/sys/devices/virtual/dmi/id/bios_version");
    QTextStream bios_in(&motherboard_name_file);
    if(!bios_version_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    line = bios_version_file.readAll();
    ui->bios_version->setText(line);
    bios_version_file.close();
}
