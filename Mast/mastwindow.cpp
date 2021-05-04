#include "mastwindow.h"
#include "ui_mastwindow.h"

MastWindow::MastWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MastWindow)
{
    ui->setupUi(this);
}

MastWindow::~MastWindow()
{
    delete ui;
}

