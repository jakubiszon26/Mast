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
    QFile file("/proc/cpuinfo");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }
    QString line;
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
}
