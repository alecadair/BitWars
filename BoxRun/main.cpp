#include "mainwindow.h"
#include <QApplication>
#include "Box2D/Box2D.h"

int main(int argc, char *argv[])
{

   //b2World* myWorld = new b2World(b2Vec2(0, 9.8));
    b2World* myWorld = new b2World(b2Vec2(0, 9.8));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
