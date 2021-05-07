#include "services_manager.h"
#include "ui_services_manager.h"
#include <QDirIterator>
#include <QListWidgetItem>
#include <QProcess>
#include <QFileDialog>

void show_services();

services_manager::services_manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::services_manager)
{
    ui->setupUi(this);
    show_services();
}

services_manager::~services_manager()
{
    delete ui;
}

void services_manager::on_search_button_clicked()
{
    QString query = ui->search_input->text();
    for(int i=0; i < ui->servicesList->count(); i++)
    {
        QListWidgetItem* item = ui->servicesList->item(i);
        if(!item->text().contains(query)){
            item->setHidden(true);
        }
    }

}

void services_manager::show_services(){
    QDirIterator iterator("/lib/systemd/system/");
    ui->servicesList->clear();
    while(iterator.hasNext()){
        ui->servicesList->addItem(iterator.next());
    }
}


void services_manager::on_enable_button_clicked()
{
    QString serviceName = selectedService.replace("/lib/systemd/system/", "");
    qDebug() << "executing command to enable service: " + serviceName;
    QProcess::execute("systemctl", {"enable", serviceName });
    qDebug() << "done";
}


void services_manager::on_servicesList_currentItemChanged(QListWidgetItem *current)
{
    selectedService = current->text();
}

