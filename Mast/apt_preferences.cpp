#include "apt_preferences.h"
#include "ui_apt_preferences.h"
#include <QDirIterator>

Apt_Preferences::Apt_Preferences(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Apt_Preferences)
{
    ui->setupUi(this);
    ui->listWidget->clear();
    QDirIterator iterator("/etc/apt/sources.list.d/");
    while(iterator.hasNext()){
    ui->listWidget->addItem(iterator.next());
    }
}

Apt_Preferences::~Apt_Preferences()
{
    delete ui;
}
