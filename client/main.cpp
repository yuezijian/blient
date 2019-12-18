#include <QtWidgets>

#include "MainWindow.hpp"


int main( int argc, char* argv[] )
{
    // QApplication 对象创建之前
    //
    // 调用

    QApplication::setOrganizationName( "Luna" );

    // QApplication 对象创建之前
    //
    // 结束

    QApplication application( argc, argv );

    MainWindow window;

    window.showMaximized();

    return QApplication::exec();
}
