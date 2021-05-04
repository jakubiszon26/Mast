#include "system_info_form.h"
#include "ui_system_info_form.h"

System_Info_Form::System_Info_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::System_Info_Form)
{
    ui->setupUi(this);
}

System_Info_Form::~System_Info_Form()
{
    delete ui;
}
