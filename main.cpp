#include "appmain.h"
//#include "appview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppMain appMain;
//    AppView w;
//    w.show();

    return a.exec();
}
