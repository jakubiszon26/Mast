#include "apt_preferences.h"
#include "ui_apt_preferences.h"
#include <QDirIterator>
#include <QListWidgetItem>
#include<QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>
#include "bootloader.h"
#include <QTextBrowser>
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
    refresh_repositories_list();
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
    refresh_repositories_list();
}

void Apt_Preferences::refresh_repositories_list(){

    ui->repositories_in_file_list->clear();
    QString line;
    QFile repositoriesFile(selectedFile);
    repositoriesFile.open(QFile::ReadOnly);
    QTextStream repositoriesFileStream(&repositoriesFile);
    do{
        line = repositoriesFileStream.readLine();
        if(line.startsWith("deb") ||
                line.startsWith(" deb") ||
                line.startsWith("#deb")||
                line.startsWith("# deb")||
                line.startsWith("deb-src")||
                line.startsWith("#deb-src")||
                line.startsWith("# deb-src")||
                line.startsWith(" deb-src")
                ){
            ui->repositories_in_file_list->addItem(line);
        }
    }while(!line.isNull());
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
        if(line == "#" + selectedRepo){
            tempFile.write(line.remove(0,1).toUtf8() + "\n");
            ui->on_and_off_button->setText("turn off");
        }else if(line == selectedRepo){
            tempFile.write("#" + line.toUtf8() + "\n");
            ui->on_and_off_button->setText("turn on");
        }
        else{
            tempFile.write(line.toUtf8() + "\n");
        }
    }
    while (!line.isNull());
    orginalFile.remove();
    tempFile.rename(selectedFile);
    tempFile.close();
}

void Apt_Preferences::on_ppa_submit_button_clicked()
{
    QString ppa = ui->insert_ppa->text();
    if(ppa.startsWith("ppa:")){
        QMessageBox warning;
        warning.setText("you should insert this without \"ppa:\"");
        warning.exec();
    }else{
        QMessageBox message;
        QProcess p;
        p.start("add-apt-repository", {"ppa:" + ppa, "-y"});
        p.waitForFinished();
        QString output(p.readAllStandardOutput());
        message.setText(output);
        message.exec();
    }
}


void Apt_Preferences::on_select_deb_button_clicked()
{
    QString debPackage = QFileDialog::getOpenFileName(this,
                                                      tr("Select package"), "/home",
                                                      tr("Deb packages (*.deb)"));
    ui->deb_path_edit->setText(debPackage);
    //info about package
    QProcess p;
    p.start("dpkg-deb", {"-I", debPackage});
    p.waitForFinished();
    QString packageInfo = p.readAllStandardOutput();
    ui->package_info_text->insertPlainText(packageInfo);
}


void Apt_Preferences::on_install_button_clicked()
{
    command("dpkg", {"-i", ui->deb_path_edit->text()}, "finished installing package with", true, ui->output_textBrowser );
}

void Apt_Preferences::command(QString command, QStringList args, QString finishMessage, bool isMessageBox, QTextBrowser *output){
    activeOutput = output;
    QProcess *p = new QProcess( this );
    p->setEnvironment( QProcess::systemEnvironment() );
    p->setProcessChannelMode( QProcess::MergedChannels );
    p->start(command, args);
    p->waitForStarted();
    connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
    connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
    connect(p, &QProcess::finished, [=](int exitCode){
        if(isMessageBox){
            QMessageBox message;
            message.setText(finishMessage + "\nexit code: " + QString::number(exitCode));
            message.exec();
        }else{
            output->append(finishMessage + "exit code: " + QString::number(exitCode));
        }
    });
}

void Apt_Preferences::ReadOut(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );
    if (p)
        activeOutput->append(p->readAllStandardOutput());
}

void Apt_Preferences::ReadErr(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );
    if (p)
        activeOutput->append(p->readAllStandardError());
}

void Apt_Preferences::HandleFinished(){
    QMessageBox message;
    message.setText("Done");
    message.exec();
}

/////////////////////////APT GUI//////////////////////////
void Apt_Preferences::on_update_button_clicked()
{
    command("apt", {"update"}, "finished apt update", false, ui->apt_output);
}

void Apt_Preferences::on_upgrade_button_clicked()
{
    command("apt", {"upgrade"}, "finished apt upgrade", false, ui->apt_output);
}


void Apt_Preferences::on_autoremove_button_clicked()
{
    command("apt", {"autoremove"}, "finished apt autoremove ", false, ui->apt_output);
}


void Apt_Preferences::on_install_missing_button_clicked()
{
    command("apt", {"update", "--fix-missing"}, "update --fix-missing done ", false, ui->apt_output);
    command("apt", {"install", "-f"}, "apt install -f finished work", false, ui->apt_output);
}


void Apt_Preferences::on_full_upgrade_button_clicked()
{
    command("apt", {"full-upgrade"}, "full upgrade finished", false, ui->apt_output);
}


void Apt_Preferences::on_list_installed_button_clicked()
{
    command("apt", {"list", "--installed"}, "list installed packages finished", false, ui->apt_output);
}


void Apt_Preferences::on_install_button_2_clicked()
{
    command("apt", {"install", ui->install_edit->text(), "-y"}, "install finished ", false, ui->apt_output);
}


void Apt_Preferences::on_remove_button_clicked()
{
    command("apt", {"remove", ui->remove_edit->text(), "-y"}, "remove finished ", false, ui->apt_output);
}


void Apt_Preferences::on_search_button_clicked()
{
    command("apt", {"search", ui->search_edit->text()}, "search finished ", false, ui->apt_output);

}

