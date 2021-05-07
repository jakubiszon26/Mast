#ifndef SERVICES_MANAGER_H
#define SERVICES_MANAGER_H

#include <QWidget>
#include <QListWidgetItem>

static QString selectedService;
namespace Ui {
class services_manager;
}

class services_manager : public QWidget
{
    Q_OBJECT

public:
    explicit services_manager(QWidget *parent = nullptr);
    ~services_manager();

private slots:
    void on_search_button_clicked();
    void show_services();
    void on_enable_button_clicked();
    void on_servicesList_currentItemChanged(QListWidgetItem *current);

    void on_disable_button_clicked();

    void on_restart_button_clicked();

    void on_start_button_clicked();

    void on_stop_button_clicked();

private:
    Ui::services_manager *ui;
};

#endif // SERVICES_MANAGER_H
