#include "mastwindow.h"
#include "ui_mastwindow.h"
#include <qpixmap.h>
MastWindow::MastWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MastWindow)
{
    ui->setupUi(this);
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
