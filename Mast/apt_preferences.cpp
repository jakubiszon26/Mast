#include "apt_preferences.h"
#include "ui_apt_preferences.h"
#include <QDirIterator>
#include <QListWidgetItem>
#include<QDebug>

Apt_Preferences::Apt_Preferences(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Apt_Preferences)
{
    ui->setupUi(this);
    ui->listWidget->clear();
    //show aditional repos in list
    QDirIterator iterator("/etc/apt/sources.list.d/");
    while(iterator.hasNext()){
    ui->listWidget->addItem(iterator.next());
    }
}

Apt_Preferences::~Apt_Preferences()
{
    delete ui;
}

void Apt_Preferences::on_listWidget_itemClicked(QListWidgetItem *item)
{
    //save selected item text in variable
    selectedFile = item->text();
    QFile file(selectedFile);
    QString line;
    bool isOn = false;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    do{
        line = in.readLine();
        if(line.startsWith("deb")){
             isOn = true;
        }
    }while (!line.isNull());

    file.close();
    if(isOn){
        ui->on_and_off_button->setText("turn off");
    }else{
        ui->on_and_off_button->setText("turn on");
    }
}

void Apt_Preferences::on_on_and_off_button_clicked()
{
  bool isOn = true;
  QString line, repo;
  QFile file(selectedFile);

  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream in(&file);
  do{
      line = in.readLine();
      if(line.startsWith("deb")){
           repo = line;
           qDebug() << "found "+line.toUtf8();
           isOn = true;
      }else if (line.startsWith("#deb") || line.startsWith("# deb")){
         isOn = false;
         repo = line;
         qDebug() << "found" +line.toUtf8();
      }
  }while (!line.isNull());

    file.close();
    file.open(QFile::WriteOnly);
    if (isOn == true){
        QString output = "#" + repo;
        qDebug() << "writing " + output;
        file.write(output.toUtf8());
        ui->on_and_off_button->setText("turn on");
    }else{
        QString output = repo.remove(0, 1);
        qDebug() << "writing " + output;
        file.write(output.toUtf8());
        ui->on_and_off_button->setText("turn off");
    }
    file.close();



}
