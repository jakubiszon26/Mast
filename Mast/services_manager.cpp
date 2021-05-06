#include "services_manager.h"
#include "ui_services_manager.h"
#include <QDirIterator>
services_manager::services_manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::services_manager)
{
    ui->setupUi(this);

    ui->servicesList->clear();
    QDirIterator iterator("/lib/systemd/system/");
    while(iterator.hasNext()){
    ui->servicesList->addItem(iterator.next());
    }
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

