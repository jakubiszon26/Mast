#include "security.h"
#include "ui_security.h"
#include <QFile>

Security::Security(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Security)
{
    ui->setupUi(this);
}

Security::~Security()
{
    delete ui;
}

void Security::apt_policy_get_info(){
       QFile aptPolicyFile("/usr/share/polkit-1/actions/nano org.debian.apt.policy");

}

