#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int result = 0;
    do
    {
        MainWindow w;
        w.show();
        result = a.exec();
    } while (result == 200); // if exited by QMessageBox at end of program which means restart

    return result;
}
