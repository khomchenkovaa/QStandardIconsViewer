#include "standardiconswidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Windows"));

    QApplication a(argc, argv);
    StandardIconsWidget w;
    w.show();

    return a.exec();
}
