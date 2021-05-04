#ifndef SYSTEM_INFO_FORM_H
#define SYSTEM_INFO_FORM_H

#include <QWidget>

namespace Ui {
class System_Info_Form;
}

class System_Info_Form : public QWidget
{
    Q_OBJECT

public:
    explicit System_Info_Form(QWidget *parent = nullptr);
    ~System_Info_Form();

private:
    Ui::System_Info_Form *ui;
};

#endif // SYSTEM_INFO_FORM_H
