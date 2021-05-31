#ifndef SECURITY_H
#define SECURITY_H

#include <QWidget>

namespace Ui {
class Security;
}

class Security : public QWidget
{
    Q_OBJECT

public:
    explicit Security(QWidget *parent = nullptr);
    ~Security();
    void apt_policy_get_info();
    void read_xml();

private:
    Ui::Security *ui;
};

#endif // SECURITY_H
