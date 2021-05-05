#include "services_manager.h"
#include "ui_services_manager.h"
#include <QDirIterator>
services_manager::services_manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::services_manager)
{
    ui->setupUi(this);

    ui->servicesList->clear();
    //show aditional repos in list
    QDirIterator iterator("/lib/systemd/system/");
    while(iterator.hasNext()){
    ui->servicesList->addItem(iterator.next());
    }
}

services_manager::~services_manager()
{
    delete ui;
}
