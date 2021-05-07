#ifndef MASTWINDOW_H
#define MASTWINDOW_H

#include <QMainWindow>
#include "system_info_form.h"
#include "apt_preferences.h"
#include "services_manager.h"
#include "hardware_info.h"
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

    void on_apt_settings_button_clicked();

    void on_services_manager_button_clicked();

    void on_hardware_info_button_clicked();

private:
    Ui::MastWindow *ui;
    System_Info_Form systemInfoForm;
    Apt_Preferences aptPreferences;
    services_manager servicesManager;
    Hardware_Info hardwareInfo;

};
#endif // MASTWINDOW_H
