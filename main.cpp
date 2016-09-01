#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    if(w.hiddenGUI()) {
        w.setWindowState(Qt::WindowMinimized);
    }
    
    return a.exec();
}
