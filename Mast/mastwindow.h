#ifndef MASTWINDOW_H
#define MASTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MastWindow; }
QT_END_NAMESPACE

class MastWindow : public QMainWindow
{
    Q_OBJECT

public:
    MastWindow(QWidget *parent = nullptr);
    ~MastWindow();

private:
    Ui::MastWindow *ui;
};
#endif // MASTWINDOW_H
