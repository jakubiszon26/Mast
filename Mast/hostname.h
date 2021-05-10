#ifndef HOSTNAME_H
#define HOSTNAME_H

#include <QWidget>

namespace Ui {
class Hostname;
}

class Hostname : public QWidget
{
    Q_OBJECT

public:
    explicit Hostname(QWidget *parent = nullptr);
    ~Hostname();

private slots:
    void on_set_button_clicked();

private:
    Ui::Hostname *ui;
};

#endif // HOSTNAME_H
