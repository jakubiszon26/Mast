#ifndef APT_PREFERENCES_H
#define APT_PREFERENCES_H

#include <QWidget>

namespace Ui {
class Apt_Preferences;
}

class Apt_Preferences : public QWidget
{
    Q_OBJECT

public:
    explicit Apt_Preferences(QWidget *parent = nullptr);
    ~Apt_Preferences();

private:
    Ui::Apt_Preferences *ui;
};

#endif // APT_PREFERENCES_H
