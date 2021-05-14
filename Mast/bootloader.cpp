#include "bootloader.h"
#include "ui_bootloader.h"
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QTextStream>
bootloader::bootloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bootloader)
{
    ui->setupUi(this);
}

bootloader::~bootloader()
{
    delete ui;
}

void bootloader::install_refind(){
    QMessageBox message;
    message.setText("please make sure you have internet connection");
    message.exec();
    command("apt-add-repository", {"ppa:rodsmith/refind", "-y"}, "finished adding ppa", false);
    command("apt", {"update", "-y"}, "finished apt update", false);
    command("apt", {"install", "refind", "-y"}, "finished installing refind package", false);
    command("refind-install", {"--yes"}, "finished installing refind", true);
}

void bootloader::on_install_button_clicked()
{
    QMessageBox warning;
    warning.setIcon(QMessageBox::Warning);
    warning.setText("Installing bootloader is experimental feature. Please report any issues");
    warning.exec();

    if(ui->bootloader_choose->currentText() == "Refind"){
        install_refind();
    }
}

void bootloader::command(QString command, QStringList args, QString finishMessage, bool isMessageBox){
    QProcess *updateProcess = new QProcess( this );
    updateProcess->setEnvironment( QProcess::systemEnvironment() );
    updateProcess->setProcessChannelMode( QProcess::MergedChannels );
    updateProcess->start(command, args);
    updateProcess->waitForStarted();
    connect( updateProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
    connect( updateProcess, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
    connect(updateProcess, &QProcess::finished, [=](){
        if(isMessageBox){
            QMessageBox message;
            message.setText(finishMessage);
            message.exec();
        }else{
            ui->output_textBrowser->append(finishMessage);
        }
    });
}

void bootloader::ReadOut(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );
    if (p)
        ui->output_textBrowser->append(p->readAllStandardOutput());
}

void bootloader::ReadErr(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );
    if (p)
        ui->output_textBrowser->append(p->readAllStandardError());
}


