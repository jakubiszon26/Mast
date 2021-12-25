#include "mastwindow.h"
#include <unistd.h>
#include <QApplication>
#include <QMessageBox>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MastWindow w;
    w.show();
    return a.exec();
}
