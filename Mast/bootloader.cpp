#include "bootloader.h"
#include "ui_bootloader.h"
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QTextStream>
bootloader::bootloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bootloader)
{
    ui->setupUi(this);
    //search for boot partition
    QFile file("/etc/fstab");
    QString line;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    do{
        line = in.readLine();
        if(line.startsWith("# /boot/efi")){
            QString line_removed_left_side = line.replace("# /boot/efi was on ", "");
            bootPartition = line_removed_left_side.replace(" during installation", "");

        }
    }while (!line.isNull());
}

bootloader::~bootloader()
{
    delete ui;
}

void bootloader::install_refind(){
    QMessageBox whatDoing;
    whatDoing.setText("please make sure you have internet connection");
    whatDoing.exec();
    QProcess p;
    whatDoing.setText("apt update...");
    whatDoing.exec();
    p.execute("apt", {"update", "-y"});
    p.waitForFinished();
    whatDoing.setText("executing \"apt install refind -y\"");
    whatDoing.exec();
    p.execute("apt", {"install", "refind", "-y"});
    p.waitForFinished();
    whatDoing.setText("installing refind");
    whatDoing.exec();
    p.execute("refind-install", {"--yes"});
    p.waitForFinished();
    whatDoing.setText("Done");
    whatDoing.exec();
}

void bootloader::on_install_button_clicked()
{
    QMessageBox warning;
    warning.setIcon(QMessageBox::Warning);
    warning.setText("Installing bootloader is experimental feature. Please report any issues");
    warning.exec();

    if(ui->bootloader_choose->currentText() == "Refind"){
        install_refind();
    }
}

