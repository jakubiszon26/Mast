#ifndef SERVICES_MANAGER_H
#define SERVICES_MANAGER_H

#include <QWidget>

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

private:
    Ui::services_manager *ui;
};

#endif // SERVICES_MANAGER_H
