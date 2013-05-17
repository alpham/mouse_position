#include "mainwindow.h"
#include <QApplication>


/*
 * START TIME :
 *  Friday, May 17, 2013 08:10 PM
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
//    w.setVisible(false);
    return a.exec();
}

/*
 * RESOURCES :
 *  http://qt-project.org/forums/viewthread/14768
 *
 * END TIME :
 *  Friday, May 17, 2013 08:36 PM
*/
