#include "headers/glwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);
    qApp->addLibraryPath("plugins/");

    QApplication a(argc, argv);
    GLWidget w;
    w.setWindowTitle("Slot Machine");
    w.setGeometry(100, 100, const_sm::window_width, const_sm::window_height); // Смещение и положение окна
    w.show();
    return a.exec();
}
