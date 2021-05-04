#ifndef MASTWINDOW_H
#define MASTWINDOW_H

#include <QMainWindow>
#include "system_info_form.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MastWindow; }
QT_END_NAMESPACE

class MastWindow : public QMainWindow
{
    Q_OBJECT

public:
    MastWindow(QWidget *parent = nullptr);
    ~MastWindow();

private slots:
    void on_system_info_button_clicked();

private:
    Ui::MastWindow *ui;
    System_Info_Form systemInfoForm;
};
#endif // MASTWINDOW_H
