#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "hullwidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    HullWidget w;
    w.setUseSlow(false); // change to true to use slow convex hull
    w.show();

    return a.exec();
}
