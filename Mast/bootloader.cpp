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
    QFile fstabFile("/etc/fstab");
    QString line;
    fstabFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fstabFileStream(&fstabFile);
    do{
        line = fstabFileStream.readLine();
        if(line.startsWith("# /boot/efi")){
            /* example:
                # /boot/efi was on /dev/nvme0n1p1 during installation
                UUID=7038-5BN7  /boot/efi       vfat    umask=0077      0       1
             */
            //we need only /dev/nvme0n1p1 (in this example)
            QString lineRemovedLeftSide = line.replace("# /boot/efi was on ", "");
            bootPartition = lineRemovedLeftSide.replace(" during installation", "");
        }
    }while (!line.isNull());

    //show error if partition not found
    if(bootPartition.length() == 0){
        QMessageBox partitionNotFoundError;
        partitionNotFoundError.critical(0,"Error", "Mast couldn't found your boot partition in fstab comment. Have you edited fstab manually?");
        partitionNotFoundError.setFixedSize(500,200);
        partitionNotFoundError.show();
    }
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

