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
    ui->pc_vendor->setText(read_info_from_file("/sys/devices/virtual/dmi/id/board_vendor"));

    //motherboard version
    ui->motherboard->setText(read_info_from_file("/sys/devices/virtual/dmi/id/board_name"));

    //BIOS version
    ui->bios_version->setText(read_info_from_file("/sys/devices/virtual/dmi/id/bios_version"));

    //board serial
    ui->board_serial->setText(read_info_from_file("/sys/devices/virtual/dmi/id/board_serial"));
}

void Hardware_Info::on_show_board_serial_button_clicked()
{
    if(ui->board_serial->echoMode() == QLineEdit::Password){
        ui->board_serial->setEchoMode(QLineEdit::Normal);
        ui->show_board_serial_button->setText("hide");
    }else{
        ui->board_serial->setEchoMode(QLineEdit::Password);
        ui->show_board_serial_button->setText("show");
    }
}

QString Hardware_Info::read_info_from_file(QString filePath){
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return "error - Make sure Mast is running as root";
    }
    QString info = file.readAll();
    file.close();
    return info;
}
