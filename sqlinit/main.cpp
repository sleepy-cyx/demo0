#include "sql.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sql w;
    w.pointInit();
    w.edgeInit();
    w.graphtidy();
    w.show();

    return a.exec();
}
