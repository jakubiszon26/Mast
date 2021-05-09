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
    QMessageBox warning;
    warning.setText("Installing bootloader is experimental feature, please report any issues");
    warning.exec();
    qDebug() << "installing refind";
    QProcess p;
    p.execute("apt", {"install", "refind", "-y"});
    p.waitForFinished();
    p.execute("refind-install", {"--yes"});
    p.waitForFinished();
    qDebug() << "done";
    QMessageBox msg;
    msg.setText("Done");
    msg.exec();
}

void bootloader::on_install_button_clicked()
{
    if(ui->bootloader_choose->currentText() == "Refind"){
        install_refind();
    }
}

