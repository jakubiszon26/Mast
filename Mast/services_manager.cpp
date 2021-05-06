#include "services_manager.h"
#include "ui_services_manager.h"
#include <QDirIterator>

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
    show_services();
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

