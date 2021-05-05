#include "mastwindow.h"
#include <unistd.h>
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MastWindow w;
    w.show();
    return a.exec();
}
