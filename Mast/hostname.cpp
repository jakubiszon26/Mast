#include "hostname.h"
#include "ui_hostname.h"

Hostname::Hostname(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hostname)
{
    ui->setupUi(this);
}

Hostname::~Hostname()
{
    delete ui;
}
