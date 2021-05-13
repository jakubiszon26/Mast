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
    //show aditional repos files in list
    QDirIterator repositoriesFilesIterator("/etc/apt/sources.list.d/");
    while(repositoriesFilesIterator.hasNext()){
        ui->listWidget->addItem(repositoriesFilesIterator.next());
    }
}

Apt_Preferences::~Apt_Preferences()
{
    delete ui;
}

void Apt_Preferences::on_listWidget_itemClicked(QListWidgetItem *item)
{
    selectedFile = item->text();
    ui->repositories_in_file_list->clear();
    QString line;
    QFile repositoriesFile(item->text());
    repositoriesFile.open(QFile::ReadOnly);
    QTextStream repositoriesFileStream(&repositoriesFile);
    do{
        line = repositoriesFileStream.readLine();
        if(line.startsWith("deb") || line.startsWith("#deb") || line.startsWith("# deb")){
            ui->repositories_in_file_list->addItem(line);
        }
    }while(!line.isNull());
}

void Apt_Preferences::on_repositories_in_file_list_itemClicked(QListWidgetItem *item)
{
    if(item->text().startsWith("#")){
        ui->on_and_off_button->setText("turn on");
        selectedRepo = item->text().remove(0,1);
    }else{
        ui->on_and_off_button->setText("turn off");
        selectedRepo = item->text();
    }
    qDebug() << "selected repo: " + selectedRepo;
}

void Apt_Preferences::on_on_and_off_button_clicked()
{
    write_to_file();
}

void Apt_Preferences::write_to_file(){

    QFile orginalFile(selectedFile);
    orginalFile.open(QFile::ReadWrite);

    QFile tempFile(selectedFile + "_temp");
    tempFile.open(QFile::ReadWrite | QIODevice::Append);
    tempFile.resize(0);
    QString line;

    QTextStream orginalFileStream(&orginalFile);
    QTextStream temporaryFileStream(&tempFile);
    do{
        line = orginalFileStream.readLine();
        qDebug() << "line: " + line;
        if(line == "#" + selectedRepo){
            tempFile.write(line.remove(0,1).toUtf8() + "\n");
            ui->on_and_off_button->setText("turn off");
            qDebug() << "turn on";
        }else if(line == selectedRepo){
            tempFile.write("#" + line.toUtf8() + "\n");
            ui->on_and_off_button->setText("turn on");
            qDebug() << "turn off";
        }
        else{
            tempFile.write(line.toUtf8() + "\n");
            qDebug() << "zwykła linia";
        }
    }
    while (!line.isNull());
    orginalFile.remove();
    tempFile.rename(selectedFile);
    tempFile.close();
}



