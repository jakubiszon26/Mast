#include "mastwindow.h"
#include "ui_mastwindow.h"
#include <qpixmap.h>
#include <unistd.h>
#include <QMessageBox>
MastWindow::MastWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MastWindow)
{
    ui->setupUi(this);
    if (getuid()) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Mast must be run as root. Most of things won't work without root privileges");
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }
    QPixmap picture(":/assets/images/mast_img.jpg");
    int width = ui->mast_image->width();
    int height = ui->mast_image->height();
    picture = picture.scaled(width, height);
    ui->mast_image->setPixmap(picture);
}

MastWindow::~MastWindow()
{
    delete ui;
}


void MastWindow::on_system_info_button_clicked()
{
    systemInfoForm.show();

}



void MastWindow::on_apt_settings_button_clicked()
{
    aptPreferences.show();
}

void MastWindow::on_services_manager_button_clicked()
{
    servicesManager.show();
}


void MastWindow::on_hardware_info_button_clicked()
{
    hardwareInfo.show();
}


void MastWindow::on_bootloader_button_clicked()
{
    bootloaderForm.show();
}


void MastWindow::on_hostname_button_clicked()
{
    hostnames.show();
}

