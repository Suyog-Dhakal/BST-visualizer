#include "visualtree.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisualTree obj;
    obj.show();

    return a.exec();
}
