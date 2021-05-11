#ifndef HARDWARE_INFO_H
#define HARDWARE_INFO_H

#include <QWidget>
#include <QFile>

namespace Ui {
class Hardware_Info;
}

class Hardware_Info : public QWidget
{
    Q_OBJECT

public:
    explicit Hardware_Info(QWidget *parent = nullptr);
    ~Hardware_Info();
    void display_cpu_info();

private slots:
    void on_show_board_serial_button_clicked();
    QString read_info_from_file(QString filePath);

private:
    Ui::Hardware_Info *ui;
};

#endif // HARDWARE_INFO_H
