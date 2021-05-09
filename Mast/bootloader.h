#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <QWidget>

static QString bootPartition;
namespace Ui {
class bootloader;
}

class bootloader : public QWidget
{
    Q_OBJECT

public:
    explicit bootloader(QWidget *parent = nullptr);
    ~bootloader();

private slots:
    void on_install_button_clicked();
    void install_refind();

private:
    Ui::bootloader *ui;
};

#endif // BOOTLOADER_H
