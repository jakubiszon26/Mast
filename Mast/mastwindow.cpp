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
    //check is Mast executed as privileged user
    if (getuid()) {
        QMessageBox noRootMsgBox;
        noRootMsgBox.critical(0,"Error","Mast must be run as root. Most of things won't work without root privileges");
        noRootMsgBox.setFixedSize(500,200);
        noRootMsgBox.show();
    }

    //warning for alpha version
    QMessageBox alphaWarning;
    alphaWarning.setText("this is alpha version. Please report any issues");
    alphaWarning.exec();   
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

